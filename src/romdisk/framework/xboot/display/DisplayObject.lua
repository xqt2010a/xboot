---
-- The 'DisplayObject' class is the base class for all objects that can
-- be placed on the screen.
--
-- @module DisplayObject
local M = Class(EventDispatcher)

---
-- Creates a new display object.
--
-- @function [parent=#DisplayObject] new
-- @param content (userdata) The content of the display object.
-- @param width (number) The width of the display object in pixels.
-- @param height (number) The height of the display object in pixels.
-- @return #DisplayObject
function M:init(content, width, height)
	self.super:init()
	self.object = Dobject.new(content)
	self.object:setSize(width or 0, height or 0)
end

---
-- Adds a display object as a child to this display object. The child
-- is added as a last child of this 'DisplayObject' instance.
--
-- Display object can have only one parent. Therefore if you add a child
-- object that already has a different display object as a parent, the
-- display object is removed from the child list of the other display
-- object and then added to this display object.
--
-- @function [parent=#DisplayObject] addChild
-- @param self
-- @param child (DisplayObject) The child display object to add.
-- @return A value of 'true' or 'false'.
function M:addChild(child)
	return self.object:addChild(child)
end

---
-- Removes the specified child 'DisplayObject' instance from the child list
-- of this 'DisplayObject' instance.
--
-- @function [parent=#DisplayObject] removeChild
-- @param self
-- @param child (DisplayObject) The child display object to remove.
-- @return A value of 'true' or 'false'.
function M:removeChild(child)
	return self.object:removeChild(child)
end

---
-- If the display object has a parent, removes the display object from the
-- child list of its parent display object.
--
-- @function [parent=#DisplayObject] removeSelf
-- @param self
-- @return A value of 'true' or 'false'.
function M:removeSelf()
	return self.object:removeSelf()
end

---
-- Moves the display object to the visual front of its parent.
--
-- @function [parent=#DisplayObject] toFront
-- @param self
-- @return A value of 'true' or 'false'.
function M:toFront()
	return self.object:toFront()
end

---
-- Moves the display object to the visual back of its parent.
--
-- @function [parent=#DisplayObject] toBack
-- @param self
-- @return A value of 'true' or 'false'.
function M:toBack()
	return self.object:toBack()
end

---
-- Sets the width and height of the display object in pixels. (Inner, No transform matrix)
--
-- @function [parent=#DisplayObject] setSize
-- @param self
-- @param width (number) The width of the display object.
-- @param height (number) The height of the display object.
function M:setSize(width, height)
	self.object:setSize(width, height)
	return self
end

---
-- Returns the width and height of the display object in pixels. (Inner, No transform matrix)
--
-- @function [parent=#DisplayObject] getSize
-- @param self
-- @return The width and height of the display object.
function M:getSize()
	return self.object:getSize()
end

---
-- Sets the x coordinates of the display object.
--
-- @function [parent=#DisplayObject] setX
-- @param self
-- @param x (number) The new x coordinate of the display object.
function M:setX(x)
	self.object:setX(x)
	return self
end

---
-- Returns the x coordinate of the display object.
--
-- @function [parent=#DisplayObject] getX
-- @param self
-- @return The x coordinate of the display object.
function M:getX()
	return self.object:getX()
end

---
-- Sets the y coordinates of the display object.
--
-- @function [parent=#DisplayObject] setY
-- @param self
-- @param y (number) The new y coordinate of the display object.
function M:setY(y)
	self.object:setY(y)
	return self
end

---
-- Returns the y coordinate of the display object.
--
-- @function [parent=#DisplayObject] getY
-- @param self
-- @return The y coordinate of the display object.
function M:getY()
	return self.object:getY()
end

---
-- Sets the x and y coordinates of the display object.
--
-- @function [parent=#DisplayObject] setPosition
-- @param self
-- @param x (number) The new x coordinate of the display object.
-- @param y (number) The new y coordinate of the display object.
function M:setPosition(x, y)
	self.object:setPosition(x, y)
	return self
end

---
-- Returns the x and y coordinates of the display object.
--
-- @function [parent=#DisplayObject] getPosition
-- @param self
-- @return The x and y coordinates of the display object.
function M:getPosition()
	return self.object:getPosition()
end

---
-- Sets the rotation of the display object in degrees.
--
-- @function [parent=#DisplayObject] setRotation
-- @param self
-- @param rotation (number) rotation of the display object
function M:setRotation(rotation)
	self.object:setRotation(rotation)
	return self
end

---
-- Returns the rotation of the display object in degrees.
--
-- @function [parent=#DisplayObject] getRotation
-- @param self
-- @return Rotation of the display object.
function M:getRotation()
	return self.object:getRotation()
end

---
-- Sets the horizontal scale of the display object.
--
-- @function [parent=#DisplayObject] setScaleX
-- @param self
-- @param x (number) horizontal scale of the display object
function M:setScaleX(x)
	self.object:setScaleX(x)
	return self
end

---
-- Returns the horizontal scale of the display object.
--
-- @function [parent=#DisplayObject] getScaleX
-- @param self
-- @return The horizontal scale (percentage) of the display object.
function M:getScaleX()
	return self.object:getScaleX()
end

---
-- Sets the vertical scale of the display object.
--
-- @function [parent=#DisplayObject] setScaleY
-- @param self
-- @param y (number) vertical scale of the display object
function M:setScaleY(y)
	self.object:setScaleY(y)
	return self
end

---
-- Returns the vertical scale of the display object.
--
-- @function [parent=#DisplayObject] getScaleY
-- @param self
-- @return The vertical scale of the display object.
function M:getScaleY()
	return self.object:getScaleY()
end

---
-- Sets the horizontal and vertical scales of the display object.
--
-- @function [parent=#DisplayObject] setScale
-- @param self
-- @param x (number) horizontal scale (percentage) of the display object
-- @param y (number) vertical scale (percentage) of the display object
function M:setScale(x, y)
	self.object:setScale(x, y or x)
	return self
end

---
-- Returns the horizontal and vertical scales of the display object.
--
-- @function [parent=#DisplayObject] getScale
-- @param self
-- @return The horizontal and vertical scales of the display object
function M:getScale()
	return self.object:getScale()
end

---
-- Sets the anchor point of the display object in percentage.
--
-- @function [parent=#DisplayObject] setAnchor
-- @param self
-- @param x (number) The horizontal percentage of anchor point.
-- @param y (number) The vertical percentage of anchor point.
function M:setAnchor(x, y)
	self.object:setAnchor(x, y or x)
	return self
end

---
-- Returns the anchor point of the display object in percentage.
--
-- @function [parent=#DisplayObject] getAnchor
-- @param self
-- @return The anchor point of the display object in percentage.
function M:getAnchor()
	return self.object:getAnchor()
end

---
-- Sets the alpha transparency of this display object. 0 means fully transparent and 1 means fully opaque.
--
-- @function [parent=#DisplayObject] setAlpha
-- @param self
-- @param alpha (number) The new alpha transparency of the display object
function M:setAlpha(alpha)
	self.object:setAlpha(alpha)
	return self
end

---
-- Returns the alpha transparency of this display object.
--
-- @function [parent=#DisplayObject] getAlpha
-- @param self
-- @return The alpha of the display object
function M:getAlpha()
	return self.object:getAlpha()
end

---
-- Sets the alignment of this display object.
--
-- @function [parent=#DisplayObject] setAlignment
-- @param self
-- @param align the alignment of display object
function M:setAlignment(align)
	self.object:setAlignment(align)
	return self
end

---
-- Returns the alignment of this display object.
--
-- @function [parent=#DisplayObject] getAlignment
-- @param self
-- @return the alignment of display object
function M:getAlignment()
	return self.object:getAlignment()
end

---
-- Sets whether or not the display object is visible. Display objects that are not visible are also taken
-- into consideration while calculating bounds.
--
-- @function [parent=#DisplayObject] setVisible
-- @param self
-- @param visible (bool) whether or not the display object is visible
function M:setVisible(visible)
	self.object:setVisible(visible)
	return self
end

---
-- Returns whether or not the display object is visible.
--
-- @function [parent=#DisplayObject] getVisible
-- @param self
-- @return A value of 'true' if display object is visible; 'false' otherwise.
function M:getVisible()
	return self.object:getVisible()
end

---
-- Sets whether or not the display object is touchable.
--
-- @function [parent=#DisplayObject] setTouchable
-- @param self
-- @param touchable (bool) whether or not the display object is touchable
function M:setTouchable(touchable)
	self.object:setTouchable(touchable)
	return self
end

---
-- Returns whether or not the display object is touchable.
--
-- @function [parent=#DisplayObject] getTouchable
-- @param self
-- @return A value of 'true' if display object is touchable; 'false' otherwise.
function M:getTouchable()
	return self.object:getTouchable()
end

---
-- Converts the x,y coordinates from the global to the display object's (local) coordinates.
--
-- @function [parent=#DisplayObject] globalToLocal
-- @param self
-- @param x (number) x coordinate of the global coordinate.
-- @param y (number) y coordinate of the global coordinate.
-- @return x coordinate relative to the display object.
-- @return y coordinate relative to the display object.
function M:globalToLocal(x, y)
	return self.object:globalToLocal(x, y)
end

---
-- Converts the x,y coordinates from the display object's (local) coordinates to the global coordinates.
--
-- @function [parent=#DisplayObject] localToGlobal
-- @param self
-- @param x (number) x coordinate of the local coordinate.
-- @param y (number) y coordinate of the local coordinate.
-- @return x coordinate relative to the display area.
-- @return y coordinate relative to the display area.
function M:localToGlobal(x, y)
	return self.object:localToGlobal(x, y)
end

---
-- Checks whether the given coordinates (in global coordinate system) is in bounds of the display object.
--
-- @function [parent=#DisplayObject] hitTestPoint
-- @param self
-- @param x (number)
-- @param y (number)
-- @param target (DisplayObject) The display object that defines the other coordinate system to transform
-- @return 'true' if the given global coordinates are in bounds of the display object, 'false' otherwise.
function M:hitTestPoint(x, y)
	return self.object:hitTestPoint(x, y)
end

---
-- Returns a area (as x, y, w and h) that encloses the display object as
-- it appears in another display object’s coordinate system.
--
-- @function [parent=#DisplayObject] getBounds
-- @param self
-- @return area has 4 values as x, y, w and h of bounds
function M:getBounds()
	return self.object:bounds()
end

return M
