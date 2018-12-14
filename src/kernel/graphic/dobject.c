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

bool_t dobject_init(struct dobject_t * o, enum dobject_type_t type, dobject_draw_t draw, enum draw_type_t dtype, void * priv)
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
	o->alignment = XALIGN_NONE;
	o->visible = 1;
	o->touchable = 1;
	o->mflag = 0;
	matrix_init_identity(&o->local_matrix);
	matrix_init_identity(&o->global_matrix);

	o->draw = draw;
	o->dtype = dtype;
	o->priv = priv;

	return TRUE;
}

bool_t dobject_add(struct dobject_t * parent, struct dobject_t * o)
{
	if(!parent || !o)
		return FALSE;

	if(parent->type != DOBJECT_TYPE_CONTAINER)
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
