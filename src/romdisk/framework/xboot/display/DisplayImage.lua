---
-- The 'DisplayImage' class is used to display texture related objects that can
-- be placed on the screen.
--
-- @module DisplayImage
local M = Class(DisplayObject)

---
-- Creates a new object of display image.
--
-- @function [parent=#DisplayImage] new
-- @param texture (Texture) The texture object
-- @return #DisplayImage
function M:init(texture)
	self.super:init(texture)
	self:setTexture(texture)
end

---
-- Attach texture to display image.
--
-- @function [parent=#DisplayImage] setTexture
-- @param self
-- @param texture (Texture) The texture object
function M:setTexture(texture)
	if texture then
		local w, h = texture:size()
		self.texture = texture
		self:setSize(w, h)
	end
	return self
end

---
-- Get texture of display image.
--
-- @function [parent=#DisplayImage] getTexture
-- @param self
-- @return The texture object of display image.
function M:getTexture()
	return self.texture
end

return M
