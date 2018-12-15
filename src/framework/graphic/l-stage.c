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

#if 0
static int l_stage_new(lua_State * L)
{
	struct stage_t * s = (struct stage_t *)(luahelper_task(L)->__stage);
	lua_pushlightuserdata(L, s);
	luaL_setmetatable(L, MT_STAGE);
	return 1;
}

static const luaL_Reg l_stage[] = {
	{"new",	l_stage_new},
	{NULL,	NULL}
};

static int m_add_child(lua_State * L)
{
	struct stage_t * s = luaL_checkudata(L, 1, MT_STAGE);
	struct dobject_t * o = luaL_checkudata(L, 2, MT_DOBJECT);
	lua_pushboolean(L, dobject_add(&s->o, o));
	return 1;
}

static int m_remove_child(lua_State * L)
{
	struct stage_t * s = luaL_checkudata(L, 1, MT_STAGE);
	struct dobject_t * o = luaL_checkudata(L, 2, MT_DOBJECT);
	lua_pushboolean(L, dobject_remove(&s->o, o));
	return 1;
}

static int m_set_size(lua_State * L)
{
	struct stage_t * s = luaL_checkudata(L, 1, MT_STAGE);
	double w = luaL_checknumber(L, 2);
	double h = luaL_checknumber(L, 3);
	dobject_set_size(&s->o, w, h);
	return 0;
}

static int m_get_size(lua_State * L)
{
	struct stage_t * s = luaL_checkudata(L, 1, MT_STAGE);
	lua_pushnumber(L, s->o.width);
	lua_pushnumber(L, s->o.height);
	return 2;
}

static int m_set_x(lua_State * L)
{
	struct stage_t * s = luaL_checkudata(L, 1, MT_STAGE);
	double x = luaL_checknumber(L, 2);
	dobject_set_x(&s->o, x);
	return 0;
}

static int m_get_x(lua_State * L)
{
	struct stage_t * s = luaL_checkudata(L, 1, MT_STAGE);
	lua_pushnumber(L, s->o.x);
	return 1;
}

static int m_set_y(lua_State * L)
{
	struct stage_t * s = luaL_checkudata(L, 1, MT_STAGE);
	double y = luaL_checknumber(L, 2);
	dobject_set_y(&s->o, y);
	return 0;
}

static int m_get_y(lua_State * L)
{
	struct stage_t * s = luaL_checkudata(L, 1, MT_STAGE);
	lua_pushnumber(L, s->o.y);
	return 1;
}

static int m_set_position(lua_State * L)
{
	struct stage_t * s = luaL_checkudata(L, 1, MT_STAGE);
	double x = luaL_checknumber(L, 2);
	double y = luaL_checknumber(L, 3);
	dobject_set_position(&s->o, x, y);
	return 0;
}

static int m_get_position(lua_State * L)
{
	struct stage_t * s = luaL_checkudata(L, 1, MT_STAGE);
	lua_pushnumber(L, s->o.x);
	lua_pushnumber(L, s->o.y);
	return 2;
}

static int m_set_rotation(lua_State * L)
{
	struct stage_t * s = luaL_checkudata(L, 1, MT_STAGE);
	double r = luaL_checknumber(L, 2);
	dobject_set_rotation(&s->o, r);
	return 0;
}

static int m_get_rotation(lua_State * L)
{
	struct stage_t * s = luaL_checkudata(L, 1, MT_STAGE);
	lua_pushnumber(L, s->o.rotation / (M_PI / 180.0));
	return 1;
}

static int m_set_scale_x(lua_State * L)
{
	struct stage_t * s = luaL_checkudata(L, 1, MT_STAGE);
	double x = luaL_checknumber(L, 2);
	dobject_set_scale_x(&s->o, x);
	return 0;
}

static int m_get_scale_x(lua_State * L)
{
	struct stage_t * s = luaL_checkudata(L, 1, MT_STAGE);
	lua_pushnumber(L, s->o.scalex);
	return 1;
}

static int m_set_scale_y(lua_State * L)
{
	struct stage_t * s = luaL_checkudata(L, 1, MT_STAGE);
	double y = luaL_checknumber(L, 2);
	dobject_set_scale_y(&s->o, y);
	return 0;
}

static int m_get_scale_y(lua_State * L)
{
	struct stage_t * s = luaL_checkudata(L, 1, MT_STAGE);
	lua_pushnumber(L, s->o.scaley);
	return 1;
}

static int m_set_scale(lua_State * L)
{
	struct stage_t * s = luaL_checkudata(L, 1, MT_STAGE);
	double x = luaL_checknumber(L, 2);
	double y = luaL_checknumber(L, 3);
	dobject_set_scale(&s->o, x, y);
	return 0;
}

static int m_get_scale(lua_State * L)
{
	struct stage_t * s = luaL_checkudata(L, 1, MT_STAGE);
	lua_pushnumber(L, s->o.scalex);
	lua_pushnumber(L, s->o.scaley);
	return 2;
}

static int m_set_archor(lua_State * L)
{
	struct stage_t * s = luaL_checkudata(L, 1, MT_STAGE);
	double x = luaL_checknumber(L, 2);
	double y = luaL_checknumber(L, 3);
	dobject_set_archor(&s->o, x, y);
	return 0;
}

static int m_get_archor(lua_State * L)
{
	struct stage_t * s = luaL_checkudata(L, 1, MT_STAGE);
	lua_pushnumber(L, s->o.anchorx);
	lua_pushnumber(L, s->o.anchory);
	return 2;
}

static int m_set_alpha(lua_State * L)
{
	struct stage_t * s = luaL_checkudata(L, 1, MT_STAGE);
	double alpha = luaL_checknumber(L, 2);
	dobject_set_alpha(&s->o, alpha);
	return 0;
}

static int m_get_alpha(lua_State * L)
{
	struct stage_t * s = luaL_checkudata(L, 1, MT_STAGE);
	lua_pushnumber(L, s->o.alpha);
	return 1;
}

static int m_set_alignment(lua_State * L)
{
	struct stage_t * s = luaL_checkudata(L, 1, MT_STAGE);
	dobject_set_alignment(&s->o, (enum alignment_t)luaL_checkinteger(L, 2));
	return 0;
}

static int m_get_alignment(lua_State * L)
{
	struct stage_t * s = luaL_checkudata(L, 1, MT_STAGE);
	lua_pushinteger(L, s->o.alignment);
	return 1;
}

static int m_set_visible(lua_State * L)
{
	struct stage_t * s = luaL_checkudata(L, 1, MT_STAGE);
	dobject_set_visible(&s->o, lua_toboolean(L, 2) ? 1 : 0);
	return 0;
}

static int m_get_visible(lua_State * L)
{
	struct stage_t * s = luaL_checkudata(L, 1, MT_STAGE);
	lua_pushboolean(L, s->o.visible);
	return 1;
}

static int m_set_touchable(lua_State * L)
{
	struct stage_t * s = luaL_checkudata(L, 1, MT_STAGE);
	dobject_set_touchable(&s->o, lua_toboolean(L, 2) ? 1 : 0);
	return 0;
}

static int m_get_touchable(lua_State * L)
{
	struct stage_t * s = luaL_checkudata(L, 1, MT_STAGE);
	lua_pushboolean(L, s->o.touchable);
	return 1;
}

static int m_global_to_local(lua_State * L)
{
	struct stage_t * s = luaL_checkudata(L, 1, MT_STAGE);
	double x = luaL_checknumber(L, 2);
	double y = luaL_checknumber(L, 3);
	dobject_global_to_local(&s->o, &x, &y);
	lua_pushnumber(L, x);
	lua_pushnumber(L, y);
	return 2;
}

static int m_local_to_global(lua_State * L)
{
	struct stage_t * s = luaL_checkudata(L, 1, MT_STAGE);
	double x = luaL_checknumber(L, 2);
	double y = luaL_checknumber(L, 3);
	dobject_local_to_global(&s->o, &x, &y);
	lua_pushnumber(L, x);
	lua_pushnumber(L, y);
	return 2;
}

static int m_hit_test_point(lua_State * L)
{
	struct stage_t * s = luaL_checkudata(L, 1, MT_STAGE);
	double x = luaL_checknumber(L, 2);
	double y = luaL_checknumber(L, 3);
	lua_pushboolean(L, dobject_hit_test_point(&s->o, x, y) ? 1 : 0);
	return 1;
}

static int m_bounds(lua_State * L)
{
	struct stage_t * s = luaL_checkudata(L, 1, MT_STAGE);
	double x1, y1, x2, y2;
	dobject_bounds(&s->o,  &x1, &y1, &x2, &y2);
	lua_pushnumber(L, x1);
	lua_pushnumber(L, y1);
	lua_pushnumber(L, x2 - x1);
	lua_pushnumber(L, y2 - y1);
	return 4;
}

static int m_layout(lua_State * L)
{
	return 0;
}

static const luaL_Reg m_stage[] = {
	{"addChild",				m_add_child},
	{"removeChild",				m_remove_child},
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

int luaopen_stage(lua_State * L)
{
	luaL_newlib(L, l_stage);
	luahelper_create_metatable(L, MT_STAGE, m_stage);
	return 1;
}

#endif
