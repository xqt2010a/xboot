/*
 * kernel/graphic/dobject.c
 *
 * Copyright(c) 2007-2018 Jianjun Jiang <8192542@qq.com>
 * Official site: http://xboot.org
 * Mobile phone: +86-18665388956
 * QQ: 8192542
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <xboot.h>
#include <graphic/dobject.h>

bool_t dobject_init(struct dobject_t * o, enum dobject_type_t type, dobject_draw_t draw, void * priv)
{
	if(!o)
		return FALSE;

	o->type = type;
	o->parent = o;
	init_list_head(&o->entry);
	init_list_head(&o->children);

	o->width = 0;
	o->height = 0;
	o->x = 0;
	o->y = 0;
	o->rotation = 0;
	o->scalex = 1;
	o->scaley = 1;
	o->anchorx = 0;
	o->anchory = 0;
	o->alpha = 1;
	o->alignment = ALIGN_NONE;
	o->visible = 1;
	o->touchable = 1;
	o->mflag = 0;
	matrix_init_identity(&o->local_matrix);
	matrix_init_identity(&o->global_matrix);

	o->draw = draw;
	o->priv = priv;

	return TRUE;
}

bool_t dobject_add(struct dobject_t * parent, struct dobject_t * o)
{
	if(!parent || !o || (parent == o))
		return FALSE;

	if(parent->type != DOBJECT_TYPE_CONTAINER)
		return FALSE;

	if(o->parent == parent)
		return FALSE;

	o->parent = parent;
	list_add_tail(&o->entry, &parent->children);
	return TRUE;
}

bool_t dobject_remove(struct dobject_t * parent, struct dobject_t * o)
{
	struct dobject_t * pos, * n;

	if(!parent || !o)
		return FALSE;

	if(parent->type != DOBJECT_TYPE_CONTAINER)
		return FALSE;

	list_for_each_entry_safe(pos, n, &(parent->children), entry)
	{
		if(pos == o)
		{
			pos->parent = pos;
			list_del(&(pos->entry));
			return TRUE;
		}
	}
	return FALSE;
}

bool_t dobject_remove_self(struct dobject_t * o)
{
	struct dobject_t * parent;
	struct dobject_t * pos, * n;

	if(!o)
		return FALSE;

	if(o->type == DOBJECT_TYPE_CONTAINER)
	{
		list_for_each_entry_safe(pos, n, &(o->children), entry)
		{
			dobject_remove_self(pos);
		}
	}

	parent = o->parent;
	if(parent && (parent != o))
	{
		return dobject_remove(parent, o);
	}
	return TRUE;
}

bool_t dobject_to_front(struct dobject_t * o)
{
	return TRUE;
}

bool_t dobject_to_back(struct dobject_t * o)
{
	return TRUE;
}

struct matrix_t * dobject_local_matrix(struct dobject_t * o)
{
	struct matrix_t * m = &o->local_matrix;
	if(o->mflag & MFLAG_LOCAL_MATRIX)
	{
		matrix_init_identity(m);
		if(o->mflag & MFLAG_TRANSLATE)
			matrix_translate(m, o->x, o->y);
		if(o->mflag & MFLAG_ROTATE)
			matrix_rotate(m, o->rotation);
		if(o->mflag & MFLAG_ANCHOR)
			matrix_translate(m, -o->anchorx * o->width * o->scalex, -o->anchory * o->height * o->scaley);
		if(o->mflag & MFLAG_SCALE)
			matrix_scale(m, o->scalex, o->scaley);
		o->mflag &= ~(MFLAG_LOCAL_MATRIX);
	}
	return m;
}

struct matrix_t * dobject_global_matrix(struct dobject_t * o)
{
	struct dobject_t * t = o;
	struct matrix_t m;

	matrix_init_identity(&m);
	while((o->parent != o))
	{
		matrix_multiply(&m, &m, dobject_local_matrix(o));
		o = o->parent;
	}
	memcpy(&t->global_matrix, &m, sizeof(struct matrix_t));
	return &t->global_matrix;
}

void dobject_bounds(struct dobject_t * o, double * x1, double * y1, double * x2, double * y2)
{
	struct matrix_t * m = dobject_global_matrix(o);
	*x1 = 0;
	*y1 = 0;
	*x2 = o->width;
	*y2 = o->height;
	matrix_transform_bounds(m, x1, y1, x2, y2);
}

void dobject_global_to_local(struct dobject_t * o, double * x, double * y)
{
	struct matrix_t m;

	memcpy(&m, dobject_global_matrix(o), sizeof(struct matrix_t));
	matrix_invert(&m);
	matrix_transform_point(&m, x, y);
}

void dobject_local_to_global(struct dobject_t * o, double * x, double * y)
{
	struct matrix_t * m = dobject_global_matrix(o);
	matrix_transform_point(m, x, y);
}

int dobject_hit_test_point(struct dobject_t * o, double x, double y)
{
	if(!o->visible || !o->touchable)
		return 0;
	dobject_global_to_local(o, &x, &y);
	return ((x >= 0) && (y >= 0) && (x <= o->width) && (y <= o->height)) ? 1 : 0;
}
