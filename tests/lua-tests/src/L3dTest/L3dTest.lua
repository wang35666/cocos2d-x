local L3dTestScene = class("L3dTestScene", function ()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    return layer
end)


function L3dTestScene:ctor()
    -- body
    local function onNodeEvent(event)
        if "enter" == event then
            self:onEnter()
        elseif "exit" == event then
            self:onExit()
        end
    end
     self:registerScriptHandler(onNodeEvent)
end

function L3dTestScene:onEnter()
    self:init()
end

function L3dTestScene:onExit()

end

function L3dTestScene:init()
    Helper.titleLabel:setString(self:title())
    Helper.subtitleLabel:setString(self:subtitle())

    self._3dNinja = cc.LSprite3D:create("C:/program1/LightWorld/media/ninja.b3d")
    self._3dNinja:setTexture("C:/program1/LightWorld/media/nskinbl.jpg")

    self:addChild(self._3dNinja)
end

function L3dTestScene:title()
    return "3d test "
end

function L3dTestScene:subtitle()
    return "3d test "
end

function L3dTestMain()
    local scene = cc.Scene:create()

    Helper.createFunctionTable =
    {
        L3dTestScene.create,
    }

    scene:addChild(L3dTestScene.create())
    local menu = CreateBackMenuItem()
    menu:setCameraMask(s_CM[GAME_LAYER.LAYER_UI])
    scene:addChild(menu)

    return scene
end
