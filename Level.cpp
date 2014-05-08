#include <algorithm>
#include <Eigen\Core>
#include <iostream>

#include "Model.h"
#include "Level.h"
#include "Geometry.h"
#include "Wall.h"
#include "BoundingSphere.h"

#include "kdtree\kdtree-0.5.6\kdtree.h"

Level::Level() {
	imovable_models = new Models();
	movable_models = new Models();
	geometries = new Geometries();
	bombs = new Bombs();
	missiles = new Missiles();
	walls = new Walls();
	ship = NULL;

	imovable_tree = kd_create(3);
	movable_tree = kd_create(3);

	create_tree();
}

Level::~Level() {
	clean_all_models();
	clean_geometries(geometries);
	clean(bombs);
	clean(missiles);
	clean(walls);

	kd_free(imovable_tree);
	kd_free(movable_tree);
}

void Level::create_tree() {
	for(int i = 0; i < imovable_models->size(); i++) {
		Model* model = imovable_models->at(i);
		model->add_model(imovable_tree);
	}
}

void Level::clean_all_models() {
	clean_models(imovable_models);
	clean_models(movable_models);
}

void Level::clean_geometries(Geometries* geometries) {
	for(int i = 0; i < geometries->size(); i++) 
		delete geometries->at(i);
	geometries->clear();
	delete geometries;
}

void Level::clean_models(Models* models) {
	for(int i = 0; i < models->size(); i++)
		delete models->at(i);
	models->clear();
	delete models;
}

void Level::clean(Bombs* bombs) {
	for(int i = 0; i < bombs->size(); i++)
		delete bombs->at(i);
	bombs->clear();
	delete bombs;
}

void Level::clean(Missiles* missiles) {
	for(int i = 0; i < missiles->size(); i++)
		delete missiles->at(i);
	missiles->clear();
	delete missiles;
}

void Level::clean(Walls* walls) {
	for(int i = 0; i < walls->size(); i++)
		delete walls->at(i);
	walls->clear();
	delete walls;
}

Level::Models* Level::get_imovable_models() {
	return imovable_models;
}

Level::Models* Level::get_movable_models() {
	return movable_models;
}

Level::Geometries* Level::get_geometries() {
	return geometries;
}

Level::Walls* Level::get_walls() {
	return walls;
}

void Level::check_movable_models() {
	MovableModel* movable_model;
	Model* model;
	BoundingSphere* bounding_sphere;
	BoundingShape* bounding_shape;
	struct kdres* results;
	Eigen::Vector3f position;

	for(size_t t = 0; t < movable_models->size(); t++) {
		movable_model = (MovableModel*) movable_models->at(t);
		position = movable_model->get_position();

		//imovable objects
		results = kd_nearest_range3f(movable_tree, position.x(), position.y(), position.z(), 
			movable_model->get_bounding_shape()->get_radius()+100);
		if(kd_res_size(results) > 0) {
			while(!kd_res_end(results)) {
				bounding_shape = (BoundingShape* ) kd_res_item(results, 0);
				if(bounding_shape->intersect((BoundingSphere* )movable_model->get_bounding_shape())) {
					model = bounding_shape->get_model();
					std::cout << " check imovable collision" << std::endl;
					if(!movable_model->is_dead() && !model->is_dead()) {
						if(!movable_model->is_asteroid) {
							model->hit_model(movable_model);
							movable_model->hit_model(model);
						}
					}
				}
				kd_res_next(results);
			}
		}
		
		//movable objects
		results = kd_nearest_range3f(movable_tree, position.x(), position.y(), position.z(),
			movable_model->get_radius());
		while(!kd_res_end(results)) {
			bounding_sphere = (BoundingSphere* ) kd_res_item(results, 0);
			if(movable_model->get_bounding_shape()->intersect(bounding_sphere)) {
				model = bounding_sphere->get_model();
				std::cout << " check movable collision" << std::endl;
				if(movable_model != model && !model->dead && !movable_model->dead) {
					model->hit_model(movable_model);
					movable_model->hit_model(model);
				}
			}
			kd_res_next(results);
		}
		kd_res_free(results);
	}
}

void Level::check_ship_collision() {
	Model* model;
    BoundingSphere* bs;
	Eigen::Vector3f position = ship->get_position();
	struct kdres* results = kd_nearest_range3f(movable_tree, position.x(),
		position.y(), position.z(), ship->get_radius() + 10);

    if(kd_res_size(results) > 0) {
        while(!kd_res_end(results)) {
            bs = (BoundingSphere* ) kd_res_item(results, 0);
            // check intersection
			if (ship->get_bounding_shape()->intersect(bs)) {
				model = bs->get_model();
				std::cout << "ship collision" << std::endl;
				if(!model->is_dead()) {
					model->hit_model(ship);
					ship->hit_model(model);
                }
            }
            kd_res_next(results);
        }
    }
    
	results = kd_nearest_range3f(movable_tree, position.x(), 
		position.y(), position.z(), ship->get_radius() + 10);
    if(kd_res_size(results) > 0) {
        while(!kd_res_end(results)) {
            bs = (BoundingSphere*) kd_res_item(results, 0);
            //Checks intersection
			if(ship->get_bounding_shape()->intersect(bs)){
				model = bs->get_model();
				if(!model->is_dead()) {
					model->hit_model(ship);
					ship->hit_model(model);
                }
            }
            kd_res_next(results);
        }
    }
    kd_res_free(results);
}
	
void Level::check_wall_collision() {
	MovableModel* movable_model;
	Wall* wall;

	for(size_t i = 0; i < walls->size(); i++) {
		wall = walls->at(i);
		for(size_t j = 0; j < movable_models->size(); j++) {
			movable_model = (MovableModel* ) movable_models->at(j);
			if(wall->collide(movable_model->get_position(), ship->get_position())) {
				std::cout << " wall ship collision" << std::endl;
				movable_model->destroy_model();
			}
		}
	}
}

void Level::add_ship(Ship* other) {
	ship = other;
}

void Level::draw() {
	draw_movable_models();
	draw_imovable_models();
}

void Level::draw_movable_models() {
	for(int i = 0; i < movable_models->size(); i++)
		movable_models->at(i)->draw();
}

void Level::draw_imovable_models() {
	for(int i = 0; i < imovable_models->size(); i++)
		imovable_models->at(i)->draw();
}

void Level::update() {
	update_movable_models();
	
	check_movable_models();
	check_ship_collision();
	check_wall_collision();
}

void Level::update_movable_models() {
	MovableModel* movable_model;
	for(int i = 0; i < movable_models->size(); i++) {
		movable_model = (MovableModel*) movable_models->at(i);
		movable_model->update();
	}
	update_movable_tree();
}

void Level::update_movable_tree() {
	kd_free(movable_tree);
	movable_tree = kd_create(3);
	for(int j = 0; j < movable_models->size(); j++) {
		Model* model = movable_models->at(j);
		model->add_model(movable_tree);
	}
}