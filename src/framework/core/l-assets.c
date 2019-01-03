/*
 * framework/core/l-assets.c
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

#include <framework/core/l-assets.h>

static const char assets_lua[] = X(
local Image = require "graphic.image"
local Ninepatch = require "graphic.ninepatch"
local Font = require "graphic.font"
local DisplayImage = DisplayImage
local DisplayNinepatch = DisplayNinepatch

local M = Class()

function M:init()
	self.images = {}
	self.ninepatches = {}
	self.themes = {}
	self.fonts = {}
end

function M:loadImage(filename)
	if not filename then
		return nil
	end

	if not self.images[filename] then
		self.images[filename] = Image.new(filename)
	end

	return self.images[filename]
end

function M:loadNinepatch(filename)
	if not filename then
		return nil
	end

	if not self.ninepatches[filename] then
		self.ninepatches[filename] = Ninepatch.new(filename)
	end

	return self.ninepatches[filename]
end

function M:loadDisplay(image)
	if type(image) == "string" then
		if string.lower(string.sub(image, -6)) == ".9.png" then
			return DisplayNinepatch.new(self:loadNinepatch(image))
		elseif string.lower(string.sub(image, -4)) == ".png" then
			return DisplayImage.new(self:loadImage(image))
		end
	else
		return image
	end
end

function M:loadTheme(name)
	local name = name or "default"

	if not self.themes[name] then
		self.themes[name] = require("assets.themes." .. name)
	end

	return self.themes[name]
end

function M:loadFont(family)
	if not family then
		return nil
	end

	if not self.fonts[family] then
		self.fonts[family] = Font.new(family)
	end

	return self.fonts[family]
end

return M
);

int luaopen_assets(lua_State * L)
{
	if(luaL_loadbuffer(L, assets_lua, sizeof(assets_lua) - 1, "Assets.lua") == LUA_OK)
		lua_call(L, 0, 1);
	return 1;
}
