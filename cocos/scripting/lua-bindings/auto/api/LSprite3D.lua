
--------------------------------
-- @module LSprite3D
-- @extend Node,BlendProtocol
-- @parent_module cc

--------------------------------
-- @overload self, cc.Texture2D         
-- @overload self, string         
-- @function [parent=#LSprite3D] setTexture
-- @param self
-- @param #string texFile
-- @return LSprite3D#LSprite3D self (return value: cc.LSprite3D)

--------------------------------
-- 
-- @function [parent=#LSprite3D] initWithFile 
-- @param self
-- @param #string path
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#LSprite3D] setBlendFunc 
-- @param self
-- @param #cc.BlendFunc blendFunc
-- @return LSprite3D#LSprite3D self (return value: cc.LSprite3D)
        
--------------------------------
-- 
-- @function [parent=#LSprite3D] onDraw 
-- @param self
-- @param #mat4_table transform
-- @param #unsigned int flags
-- @return LSprite3D#LSprite3D self (return value: cc.LSprite3D)
        
--------------------------------
-- 
-- @function [parent=#LSprite3D] getBlendFunc 
-- @param self
-- @return BlendFunc#BlendFunc ret (return value: cc.BlendFunc)
        
--------------------------------
-- @overload self, string         
-- @overload self         
-- @overload self, string, string         
-- @function [parent=#LSprite3D] create
-- @param self
-- @param #string modelPath
-- @param #string texturePath
-- @return LSprite3D#LSprite3D ret (return value: cc.LSprite3D)

--------------------------------
-- draw
-- @function [parent=#LSprite3D] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table transform
-- @param #unsigned int flags
-- @return LSprite3D#LSprite3D self (return value: cc.LSprite3D)
        
--------------------------------
-- 
-- @function [parent=#LSprite3D] visit 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table parentTransform
-- @param #unsigned int parentFlags
-- @return LSprite3D#LSprite3D self (return value: cc.LSprite3D)
        
--------------------------------
-- 
-- @function [parent=#LSprite3D] runAction 
-- @param self
-- @param #cc.Action action
-- @return Action#Action ret (return value: cc.Action)
        
--------------------------------
-- 
-- @function [parent=#LSprite3D] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#LSprite3D] setGLProgram 
-- @param self
-- @param #cc.GLProgram glprogram
-- @return LSprite3D#LSprite3D self (return value: cc.LSprite3D)
        
--------------------------------
-- 
-- @function [parent=#LSprite3D] getBoundingBox 
-- @param self
-- @return rect_table#rect_table ret (return value: rect_table)
        
--------------------------------
-- 
-- @function [parent=#LSprite3D] LSprite3D 
-- @param self
-- @return LSprite3D#LSprite3D self (return value: cc.LSprite3D)
        
return nil
