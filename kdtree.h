/*
This file is part of ``kdtree'', a library for working with kd-trees.
Copyright (C) 2007-2011 John Tsiombikas <nuclear@member.fsf.org>

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
3. The name of the author may not be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#ifndef _KDTREE_H_
#define _KDTREE_H_

struct kdtree;
struct kdres;

// create a kd-tree for "k"-dimensional data 
struct kdtree *kd_create(int k);

// free the struct kdtree
void kd_free(struct kdtree *tree);

// remove all the elements from the tree
void kd_clear(struct kdtree *tree);

/* Find the nearest node from a given point.
 * This function returns a pointer to a result set with at most one element.
 */
struct kdres *kd_nearest(struct kdtree *tree, const double *pos);
struct kdres *kd_nearest3f(struct kdtree *tree, float x, float y, float z);

/* Find any nearest nodes from a given point within a range.
 *
 * This function returns a pointer to a result set, which can be manipulated
 * by the kd_res_* functions.
 * The returned pointer can be null as an indication of an error. Otherwise
 * a valid result set is always returned which may contain 0 or more elements.
 * The result set must be deallocated with kd_res_free after use.
 */
struct kdres *kd_nearest_range(struct kdtree *kd, const double *pos, double range);
struct kdres *kd_nearest_range3f(struct kdtree *tree, float x, float y, float z, float range);

int kd_insert(struct kdtree *tree, const double *pos, void *data);
int kd_insert3f(struct kdtree *tree, float x, float y, float z,
	void *data);

static void hyperrect_free(struct kdhyperrect *rect);

/* returns the size of the result set (in elements) */
int kd_res_size(struct kdres *set);

void kd_res_free(struct kdres *set);

void kd_res_rewind(struct kdres *set);

int kd_res_end(struct kdres *rset);

int kd_res_next(struct kdres *rset);

/* returns the data pointer (can be null) of the current result set item
 * and optionally sets its position to the pointers(s) if not null.
 */
void *kd_res_item(struct kdres *rset, double *pos);
void *kd_res_item3f(struct kdres *rset, float *x, float *y, float *z);

/* equivalent to kd_res_item(set, 0) */
void *kd_res_item_data(struct kdres *set);

#endif
// _KDTREE_H_
