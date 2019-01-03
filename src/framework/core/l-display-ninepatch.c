/*
 * framework/core/l-display-ninepatch.c
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

#include <framework/core/l-display-ninepatch.h>

static const char display_ninepatch_lua[] = X(
local Ninepatch = require "graphic.ninepatch"

local M = Class(DisplayObject)

function M:init(ninepatch)
	if ninepatch then
		local w, h = ninepatch:getSize()
		self.ninepatch = ninepatch
		self.super:init(w, h, ninepatch)
	else
		self.super:init()
	end
end

function M:setSize(width, height)
	self.super:setSize(width, height)
	if self.ninepatch then
		self.ninepatch:setSize(width, height)
	end
	return self
end

return M
);

int luaopen_display_ninepatch(lua_State * L)
{
	if(luaL_loadbuffer(L, display_ninepatch_lua, sizeof(display_ninepatch_lua) - 1, "DisplayNinepatch.lua") == LUA_OK)
		lua_call(L, 0, 1);
	return 1;
}
