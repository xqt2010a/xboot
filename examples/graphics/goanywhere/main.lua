local Dobject = require "graphic.dobject"
local Pattern = require "graphic.pattern"
local M_PI = math.pi

local sw, sh = stage:getSize()

stage:addChild(DisplayShape.new(sw, sh)
		:setSource(Pattern.image(assets:loadImage("bg.png")):setExtend(Pattern.EXTEND_REPEAT))
		:paint())

local snowman = assets:loadDisplay("snowman.png"):setAnchor(0.5, 0.5):setPosition(sw / 2, sh / 2)
local w, h = snowman:getSize();

stage:addTimer(Timer.new(1, 0, function(t)
	local s = math.random() * 1.0 + 0.5
	snowman:animate({x = math.random(w / 2, sw - w / 2), y = math.random(h / 2, sh - h / 2), scalex = s, scaley = s}, 1, "outCirc")
end))

stage:addChild(snowman)
stage:showfps(true)
