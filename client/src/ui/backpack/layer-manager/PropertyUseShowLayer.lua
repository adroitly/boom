local M = class("ui.backpack.layer-manager.PropertyUseShowLayer", function()
    return cc.LayerColor:create(cc.c4b(0, 0, 0, 120))
end)

function M:ctor()
    self:_initData()
    self:_createBackground()
    self:_createView()
    Event:registerNodeEvent(self)
end

function M:onEnterTransitionFinish()
    Touch:registerTouchOneByOne(self, true)
    Touch:addKeyboardTouch(self)
    -- 测试
    -- self:removeFromParent()
end

function M:onExit()
    Touch:removeKeyboardTouch(self)
end

function M:onKeyReleased(keyCode, event)
    if keyCode == cc.KeyCode.KEY_BACK then
        self:removeFromParent()
    end
end

function M:onTouchBegan(touch, event)
    self._isTouchInside = Touch:isTouchHitted(self._gridView, touch)
    return true
end

function M:onTouchEnded(touch, event)
    if true == self._isTouchInside then
        return
    end
    if false == Touch:isTouchHitted(self._gridView, touch) then
        self:removeFromParent()
    end
end

function M:onGridViewCellCount(gridView)
    return table.getn(self._backpackIdList)
end

function M:onGridViewLineHeight(gridView)
    return 150
end

function M:onGridViewCellAtIndex(gridView, idx)
    local cell = gridView:dequeueCell()
    if nil == cell then
        cell = require("ui.backpack.layer-manager.PropertyUseShowCell").new()
    end
    cell:reloadData(self._backpackIdList[idx + 1])
    return cell
end

function M:_initData()
    self._backpackIdList = {}
    for _,backpackId in pairs(Enum.MainPageBackpackType) do
        table.insert(self._backpackIdList, backpackId)
    end
end

function M:_createView()
    local viewSize = cc.size(Screen.width * 0.75, 100)
    self._gridView = GridView.new(viewSize, self, 1)
    self._gridView:setScrollType(GridView.ScrollType.Horizontal)
    self:addChild(self._gridView)
    self._gridView:setPosition(cc.p(Screen.width * 0.15, Screen.height * 0.25))
end

function M:_createBackground()
    local background = cc.Sprite:create("ui/backpack/timeliness-item-bg.png")
    self:addChild(background)
    background:setAnchorPoint(cc.p(0.5, 0))
    background:setPosition(cc.p(Screen.width * 0.52, Screen.height * 0.23))
end

return M
     