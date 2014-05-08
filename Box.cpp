#include "Box.h"
#include <glut.h>
#include <gl\GL.h>

Box::Box() : Geometry("Box") {
	uln = Eigen::Vector3f(-1.f, 1.f, -1.f);
	lln = Eigen::Vector3f(-1.f, -1.f, -1.f);
	lrn = Eigen::Vector3f(1.f, -1.f, -1.f);
	urn = Eigen::Vector3f(1.f, 1.f, -1.f);

	ulf = Eigen::Vector3f(-1.f, 1.f, 1.f);
	llf = Eigen::Vector3f(-1.f, -1.f, 1.f);	
	lrf = Eigen::Vector3f(1.f, -1.f, 1.f);
	urf = Eigen::Vector3f(1.f, 1.f, 1.f);

	this->update();
}

void Box::draw() {
	glBegin(GL_POLYGON);
    glVertex3f(urn[0], urn[1], urn[2]);
    glVertex3f(uln[0], uln[1], uln[2]);
    glVertex3f(lln[0], lln[1], lln[2]);
    glVertex3f(lrn[0], lrn[1], lrn[2]);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex3f(uln[0], uln[1], uln[2]);
    glVertex3f(urn[0], urn[1], urn[2]);
    glVertex3f(urf[0], urf[1], urf[2]);
    glVertex3f(ulf[0], ulf[1], ulf[2]);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex3f(urn[0], urn[1], urn[2]);
    glVertex3f(lrn[0], lrn[1], lrn[2]);
    glVertex3f(lrf[0], lrf[1], lrf[2]);
    glVertex3f(urf[0], urf[1], urf[2]);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex3f(lln[0], lln[1], lln[2]);
    glVertex3f(uln[0], uln[1], uln[2]);
    glVertex3f(ulf[0], ulf[1], ulf[2]);
    glVertex3f(llf[0], llf[1], llf[2]);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex3f(lrn[0], lrn[1], lrn[2]);
    glVertex3f(lln[0], lln[1], lln[2]);
    glVertex3f(llf[0], llf[1], llf[2]);
    glVertex3f(lrf[0], lrf[1], lrf[2]);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex3f(ulf[0], ulf[1], ulf[2]);
    glVertex3f(urf[0], urf[1], urf[2]);
    glVertex3f(lrf[0], lrf[1], lrf[2]);
    glVertex3f(llf[0], llf[1], llf[2]);
    glEnd();
}

void Box::update() {
	set_radius(1.7f);
	set_bmin(lln);
	set_bmax(urf);
	set_center(Eigen::Vector3f(0.f, 0.f, 0.f));
}