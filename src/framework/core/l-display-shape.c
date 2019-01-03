/*
 * framework/core/l-display-shape.c
 *
 * Copyright(c) 2007-2019 Jianjun Jiang <8192542@qq.com>
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

#include <framework/core/l-display-shape.h>

static const char display_shape_lua[] = X(
local Shape = require "graphic.shape"

local M = Class(DisplayObject)

function M:init(width, height)
	self.shape = Shape.new(width, height)
	self.super:init(width, height, self.shape)
end

function M:save()
	self.shape:save()
	return self
end

function M:restore()
	self.shape:restore()
	return self
end

function M:pushGroup()
	self.shape:pushGroup()
	return self
end

function M:popGroup()
	self.shape:popGroup()
	return self
end

function M:popGroupToSource()
	self.shape:popGroupToSource()
	return self
end

function M:newPath()
	self.shape:newPath()
	return self
end

function M:newSubPath()
	self.shape:newSubPath()
	return self
end

function M:closePath()
	self.shape:closePath()
	return self
end

function M:setOperator(op)
	self.shape:setOperator(op)
	return self
end

function M:setSource(pattern)
	self.shape:setSource(pattern)
	return self
end

function M:setSourceColor(r, g, b, a)
	self.shape:setSourceColor(r, g, b, a)
	return self
end

function M:setTolerance(tolerance)
	self.shape:setTolerance(tolerance)
	return self
end

function M:setMiterLimit(limit)
	self.shape:setMiterLimit(limit)
	return self
end

function M:setAntialias(antialias)
	self.shape:setAntialias(antialias)
	return self
end

function M:setFillRule(rule)
	self.shape:setFillRule(rule)
	return self
end

function M:setLineWidth(width)
	self.shape:setLineWidth(width)
	return self
end

function M:setLineCap(cap)
	self.shape:setLineCap(cap)
	return self
end

function M:setLineJoin(join)
	self.shape:setLineJoin(join)
	return self
end

function M:setDash(dashes, offset)
	self.shape:setDash(dashes, offset)
	return self
end

function M:moveTo(x, y)
	self.shape:moveTo(x, y)
	return self
end

function M:relMoveTo(dx, dy)
	self.shape:relMoveTo(dx, dy)
	return self
end

function M:lineTo(x, y)
	self.shape:lineTo(x, y)
	return self
end

function M:relLineTo(dx, dy)
	self.shape:relLineTo(dx, dy)
	return self
end

function M:curveTo(x1, y1, x2, y2, x3, y3)
	self.shape:curveTo(x1, y1, x2, y2, x3, y3)
	return self
end

function M:relCurveTo(dx1, dy1, dx2, dy2, dx3, dy3)
	self.shape:relCurveTo(dx1, dy1, dx2, dy2, dx3, dy3)
	return self
end

function M:rectangle(x, y, width, height)
	self.shape:rectangle(x, y, width, height)
	return self
end

function M:arc(xc, yc, radius, angle1, angle2)
	self.shape:arc(xc, yc, radius, angle1, angle2)
	return self
end

function M:arcNegative(xc, yc, radius, angle1, angle2)
	self.shape:arcNegative(xc, yc, radius, angle1, angle2)
	return self
end

function M:stroke()
	self.shape:stroke()
	return self
end

function M:strokePreserve()
	self.shape:strokePreserve()
	return self
end

function M:fill()
	self.shape:fill()
	return self
end

function M:fillPreserve()
	self.shape:fillPreserve()
	return self
end

function M:clip()
	self.shape:clip()
	return self
end

function M:clipPreserve()
	self.shape:clipPreserve()
	return self
end

function M:paint(alpha)
	self.shape:paint(alpha)
	return self
end

return M
);

int luaopen_display_shape(lua_State * L)
{
	if(luaL_loadbuffer(L, display_shape_lua, sizeof(display_shape_lua) - 1, "DisplayShape.lua") == LUA_OK)
		lua_call(L, 0, 1);
	return 1;
}
