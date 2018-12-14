/*
 * framework/graphic/l-dobject.c
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

#include <cairo.h>
#include <cairoint.h>
#include <graphic/stage.h>
#include <graphic/dobject.h>
#include <framework/graphic/l-graphic.h>

static void dobject_texture_draw(struct dobject_t * o, struct stage_t * s)
{
	struct ltexture_t * tex = o->priv;
	cairo_t * cr = s->cr;
	cairo_save(cr);
	cairo_set_matrix(cr, (cairo_matrix_t *)dobject_global_matrix(o));
	cairo_set_source_surface(cr, tex->surface, 0, 0);
	cairo_pattern_set_filter(cairo_get_source(cr), CAIRO_FILTER_FAST);
	cairo_paint_with_alpha(cr, o->alpha);
	cairo_restore(cr);
}

static int l_dobject_new(lua_State * L)
{
	struct dobject_t * o = lua_newuserdata(L, sizeof(struct dobject_t));
	if(luaL_testudata(L, 1, MT_TEXTURE))
		dobject_init(o, DOBJECT_TYPE_NODE, dobject_texture_draw, lua_touserdata(L, 1));
	else
		dobject_init(o, DOBJECT_TYPE_CONTAINER, NULL, NULL);
	luaL_setmetatable(L, MT_DOBJECT);
	return 1;
}

static const luaL_Reg l_dobject[] = {
	{"new",	l_dobject_new},
	{NULL,	NULL}
};

static int m_add_child(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	struct dobject_t * c = luaL_checkudata(L, 2, MT_DOBJECT);
	lua_pushboolean(L, dobject_add(o, c));
	return 1;
}

static int m_remove_child(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	struct dobject_t * c = luaL_checkudata(L, 2, MT_DOBJECT);
	lua_pushboolean(L, dobject_remove(o, c));
	return 1;
}

static int m_remove_self(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	lua_pushboolean(L, dobject_remove_self(o));
	return 1;
}

static int m_to_front(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	lua_pushboolean(L, dobject_to_front(o));
	return 1;
}

static int m_to_back(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	lua_pushboolean(L, dobject_to_back(o));
	return 1;
}

static int m_set_size(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	double w = luaL_checknumber(L, 2);
	double h = luaL_checknumber(L, 3);
	dobject_set_size(o, w, h);
	return 0;
}

static int m_get_size(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	lua_pushnumber(L, o->width);
	lua_pushnumber(L, o->height);
	return 2;
}

static int m_set_x(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	double x = luaL_checknumber(L, 2);
	dobject_set_x(o, x);
	return 0;
}

static int m_get_x(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	lua_pushnumber(L, o->x);
	return 1;
}

static int m_set_y(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	double y = luaL_checknumber(L, 2);
	dobject_set_y(o, y);
	return 0;
}

static int m_get_y(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	lua_pushnumber(L, o->y);
	return 1;
}

static int m_set_position(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	double x = luaL_checknumber(L, 2);
	double y = luaL_checknumber(L, 3);
	dobject_set_position(o, x, y);
	return 0;
}

static int m_get_position(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	lua_pushnumber(L, o->x);
	lua_pushnumber(L, o->y);
	return 2;
}

static int m_set_rotation(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	double r = luaL_checknumber(L, 2);
	dobject_set_rotation(o, r);
	return 0;
}

static int m_get_rotation(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	lua_pushnumber(L, o->rotation / (M_PI / 180.0));
	return 1;
}

static int m_set_scale_x(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	double x = luaL_checknumber(L, 2);
	dobject_set_scale_x(o, x);
	return 0;
}

static int m_get_scale_x(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	lua_pushnumber(L, o->scalex);
	return 1;
}

static int m_set_scale_y(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	double y = luaL_checknumber(L, 2);
	dobject_set_scale_y(o, y);
	return 0;
}

static int m_get_scale_y(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	lua_pushnumber(L, o->scaley);
	return 1;
}

static int m_set_scale(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	double x = luaL_checknumber(L, 2);
	double y = luaL_checknumber(L, 3);
	dobject_set_scale(o, x, y);
	return 0;
}

static int m_get_scale(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	lua_pushnumber(L, o->scalex);
	lua_pushnumber(L, o->scaley);
	return 2;
}

static int m_set_archor(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	double x = luaL_checknumber(L, 2);
	double y = luaL_checknumber(L, 3);
	dobject_set_archor(o, x, y);
	return 0;
}

static int m_get_archor(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	lua_pushnumber(L, o->anchorx);
	lua_pushnumber(L, o->anchory);
	return 2;
}

static int m_set_alpha(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	double alpha = luaL_checknumber(L, 2);
	dobject_set_alpha(o, alpha);
	return 0;
}

static int m_get_alpha(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	lua_pushnumber(L, o->alpha);
	return 1;
}

static int m_set_alignment(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	dobject_set_alignment(o, (enum alignment_t)luaL_checkinteger(L, 2));
	return 0;
}

static int m_get_alignment(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	lua_pushinteger(L, o->alignment);
	return 1;
}

static int m_set_visible(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	dobject_set_visible(o, lua_toboolean(L, 2) ? 1 : 0);
	return 0;
}

static int m_get_visible(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	lua_pushboolean(L, o->visible);
	return 1;
}

static int m_set_touchable(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	dobject_set_touchable(o, lua_toboolean(L, 2) ? 1 : 0);
	return 0;
}

static int m_get_touchable(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	lua_pushboolean(L, o->touchable);
	return 1;
}

static int m_global_to_local(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	double x = luaL_checknumber(L, 2);
	double y = luaL_checknumber(L, 3);
	dobject_global_to_local(o, &x, &y);
	lua_pushnumber(L, x);
	lua_pushnumber(L, y);
	return 2;
}

static int m_local_to_global(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	double x = luaL_checknumber(L, 2);
	double y = luaL_checknumber(L, 3);
	dobject_local_to_global(o, &x, &y);
	lua_pushnumber(L, x);
	lua_pushnumber(L, y);
	return 2;
}

static int m_hit_test_point(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	double x = luaL_checknumber(L, 2);
	double y = luaL_checknumber(L, 3);
	lua_pushboolean(L, dobject_hit_test_point(o, x, y) ? 1 : 0);
	return 1;
}

static int m_bounds(lua_State * L)
{
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	double x1, y1, x2, y2;
	dobject_bounds(o,  &x1, &y1, &x2, &y2);
	lua_pushnumber(L, x1);
	lua_pushnumber(L, y1);
	lua_pushnumber(L, x2 - x1);
	lua_pushnumber(L, y2 - y1);
	return 4;
}

static int m_layout(lua_State * L)
{
#if 0
	struct dobject_t * o = luaL_checkudata(L, 1, MT_DOBJECT);
	struct dobject_t * child = luaL_checkudata(L, 2, MT_DOBJECT);
	double rx1 = luaL_optnumber(L, 3, 0);
	double ry1 = luaL_optnumber(L, 4, 0);
	double rx2 = luaL_optnumber(L, 5, object->width);
	double ry2 = luaL_optnumber(L, 6, object->height);

	if(child->alignment <= ALIGN_NONE)
	{
	}
	else if((child->alignment <= ALIGN_CENTER))
	{
		double ox1 = rx1;
		double oy1 = ry1;
		double ox2 = rx2;
		double oy2 = ry2;
		double cx1 = 0;
		double cy1 = 0;
		double cx2 = child->width;
		double cy2 = child->height;
		_cairo_matrix_transform_bounding_box(__get_obj_matrix(child), &cx1, &cy1, &cx2, &cy2, NULL);

		switch(child->alignment)
		{
		case ALIGN_LEFT:
			__object_translate(child, ox1 - cx1, 0);
			rx1 += cx2 - cx1;
			break;
		case ALIGN_TOP:
			__object_translate(child, 0, oy1 - cy1);
			ry1 += cy2 - cy1;
			break;
		case ALIGN_RIGHT:
			__object_translate(child, ox2 - cx2, 0);
			rx2 -= cx2 - cx1;
			break;
		case ALIGN_BOTTOM:
			__object_translate(child, 0, oy2 - cy2);
			ry2 -= cy2 - cy1;
			break;
		case ALIGN_LEFT_TOP:
			__object_translate(child, ox1 - cx1, oy1 - cy1);
			rx1 += cx2 - cx1;
			ry1 += cy2 - cy1;
			break;
		case ALIGN_RIGHT_TOP:
			__object_translate(child, ox2 - cx2, oy1 - cy1);
			rx2 -= cx2 - cx1;
			ry1 += cy2 - cy1;
			break;
		case ALIGN_LEFT_BOTTOM:
			__object_translate(child, ox1 - cx1, oy2 - cy2);
			rx1 += cx2 - cx1;
			ry2 -= cy2 - cy1;
			break;
		case ALIGN_RIGHT_BOTTOM:
			__object_translate(child, ox2 - cx2, oy2 - cy2);
			rx2 -= cx2 - cx1;
			ry2 -= cy2 - cy1;
			break;
		case ALIGN_LEFT_CENTER:
			__object_translate(child, ox1 - cx1, oy1 - cy1 + ((oy2 - oy1) - (cy2 - cy1)) / 2);
			rx1 += cx2 - cx1;
			break;
		case ALIGN_TOP_CENTER:
			__object_translate(child, ox1 - cx1 + ((ox2 - ox1) - (cx2 - cx1)) / 2, oy1 - cy1);
			ry1 += cy2 - cy1;
			break;
		case ALIGN_RIGHT_CENTER:
			__object_translate(child, ox2 - cx2, oy1 - cy1 + ((oy2 - oy1) - (cy2 - cy1)) / 2);
			rx2 -= cx2 - cx1;
			break;
		case ALIGN_BOTTOM_CENTER:
			__object_translate(child, ox1 - cx1 + ((ox2 - ox1) - (cx2 - cx1)) / 2, oy2 - cy2);
			ry2 -= cy2 - cy1;
			break;
		case ALIGN_HORIZONTAL_CENTER:
			__object_translate(child, ox1 - cx1 + ((ox2 - ox1) - (cx2 - cx1)) / 2, 0);
			break;
		case ALIGN_VERTICAL_CENTER:
			__object_translate(child, 0, oy1 - cy1 + ((oy2 - oy1) - (cy2 - cy1)) / 2);
			break;
		case ALIGN_CENTER:
			__object_translate(child, ox1 - cx1 + ((ox2 - ox1) - (cx2 - cx1)) / 2, oy1 - cy1 + ((oy2 - oy1) - (cy2 - cy1)) / 2);
			break;
		default:
			break;
		}
	}
	else if((child->alignment <= ALIGN_CENTER_FILL))
	{
		double w;
		double h;

		switch(child->alignment)
		{
		case ALIGN_LEFT_FILL:
			w = child->width * child->scalex;
			h = ry2 - ry1;
			__object_translate_fill(child, rx1, ry1, w, h);
			rx1 += w;
			break;
		case ALIGN_TOP_FILL:
			w = rx2 - rx1;
			h = child->height * child->scaley;
			__object_translate_fill(child, rx1, ry1, w, h);
			ry1 += h;
			break;
		case ALIGN_RIGHT_FILL:
			w = child->width * child->scalex;
			h = ry2 - ry1;
			__object_translate_fill(child, rx2 - w, ry1, w, h);
			rx2 -= w;
			break;
		case ALIGN_BOTTOM_FILL:
			w = rx2 - rx1;
			h = child->height * child->scaley;
			__object_translate_fill(child, rx1, ry2 - h, w, h);
			ry2 -= h;
			break;
		case ALIGN_HORIZONTAL_FILL:
			w = rx2 - rx1;
			h = child->height * child->scaley;
			__object_translate_fill(child, rx1, child->y, w, h);
			break;
		case ALIGN_VERTICAL_FILL:
			w = child->width * child->scalex;
			h = ry2 - ry1;
			__object_translate_fill(child, child->x, ry1, w, h);
			break;
		case ALIGN_CENTER_FILL:
			w = rx2 - rx1;
			h = ry2 - ry1;
			__object_translate_fill(child, rx1, ry1, w, h);
			rx1 += w;
			ry1 += h;
			break;
		default:
			break;
		}
	}

	lua_pushnumber(L, rx1);
	lua_pushnumber(L, ry1);
	lua_pushnumber(L, rx2);
	lua_pushnumber(L, ry2);
#endif
	return 4;
}

static const luaL_Reg m_dobject[] = {
	{"addChild",				m_add_child},
	{"removeChild",				m_remove_child},
	{"removeSelf",				m_remove_self},
	{"toFront",					m_to_front},
	{"toBack",					m_to_back},
	{"setSize",					m_set_size},
	{"getSize",					m_get_size},
	{"setX",					m_set_x},
	{"getX",					m_get_x},
	{"setY",					m_set_y},
	{"getY",					m_get_y},
	{"setPosition",				m_set_position},
	{"getPosition",				m_get_position},
	{"setRotation",				m_set_rotation},
	{"getRotation",				m_get_rotation},
	{"setScaleX",				m_set_scale_x},
	{"getScaleX",				m_get_scale_x},
	{"setScaleY",				m_set_scale_y},
	{"getScaleY",				m_get_scale_y},
	{"setScale",				m_set_scale},
	{"getScale",				m_get_scale},
	{"setAnchor",				m_set_archor},
	{"getAnchor",				m_get_archor},
	{"setAlpha",				m_set_alpha},
	{"getAlpha",				m_get_alpha},
	{"setAlignment",			m_set_alignment},
	{"getAlignment",			m_get_alignment},
	{"setVisible",				m_set_visible},
	{"getVisible",				m_get_visible},
	{"setTouchable",			m_set_touchable},
	{"getTouchable",			m_get_touchable},
	{"globalToLocal",			m_global_to_local},
	{"localToGlobal",			m_local_to_global},
	{"hitTestPoint",			m_hit_test_point},
	{"bounds",					m_bounds},
	{"layout",					m_layout},
	{NULL,						NULL}
};

int luaopen_dobject(lua_State * L)
{
	luaL_newlib(L, l_dobject);
	/* enum alignment_t */
	luahelper_set_intfield(L, "ALIGN_NONE", 				ALIGN_NONE);
	luahelper_set_intfield(L, "ALIGN_LEFT", 				ALIGN_LEFT);
	luahelper_set_intfield(L, "ALIGN_TOP", 					ALIGN_TOP);
	luahelper_set_intfield(L, "ALIGN_RIGHT", 				ALIGN_RIGHT);
	luahelper_set_intfield(L, "ALIGN_BOTTOM", 				ALIGN_BOTTOM);
	luahelper_set_intfield(L, "ALIGN_LEFT_TOP", 			ALIGN_LEFT_TOP);
	luahelper_set_intfield(L, "ALIGN_RIGHT_TOP", 			ALIGN_RIGHT_TOP);
	luahelper_set_intfield(L, "ALIGN_LEFT_BOTTOM", 			ALIGN_LEFT_BOTTOM);
	luahelper_set_intfield(L, "ALIGN_RIGHT_BOTTOM", 		ALIGN_RIGHT_BOTTOM);
	luahelper_set_intfield(L, "ALIGN_LEFT_CENTER", 			ALIGN_LEFT_CENTER);
	luahelper_set_intfield(L, "ALIGN_TOP_CENTER", 			ALIGN_TOP_CENTER);
	luahelper_set_intfield(L, "ALIGN_RIGHT_CENTER", 		ALIGN_RIGHT_CENTER);
	luahelper_set_intfield(L, "ALIGN_BOTTOM_CENTER",		ALIGN_BOTTOM_CENTER);
	luahelper_set_intfield(L, "ALIGN_HORIZONTAL_CENTER",	ALIGN_HORIZONTAL_CENTER);
	luahelper_set_intfield(L, "ALIGN_VERTICAL_CENTER", 		ALIGN_VERTICAL_CENTER);
	luahelper_set_intfield(L, "ALIGN_CENTER", 				ALIGN_CENTER);
	luahelper_set_intfield(L, "ALIGN_LEFT_FILL", 			ALIGN_LEFT_FILL);
	luahelper_set_intfield(L, "ALIGN_TOP_FILL", 			ALIGN_TOP_FILL);
	luahelper_set_intfield(L, "ALIGN_RIGHT_FILL", 			ALIGN_RIGHT_FILL);
	luahelper_set_intfield(L, "ALIGN_BOTTOM_FILL", 			ALIGN_BOTTOM_FILL);
	luahelper_set_intfield(L, "ALIGN_HORIZONTAL_FILL", 		ALIGN_HORIZONTAL_FILL);
	luahelper_set_intfield(L, "ALIGN_VERTICAL_FILL", 		ALIGN_VERTICAL_FILL);
	luahelper_set_intfield(L, "ALIGN_CENTER_FILL", 			ALIGN_CENTER_FILL);
	luahelper_create_metatable(L, MT_DOBJECT, m_dobject);
	return 1;
}
