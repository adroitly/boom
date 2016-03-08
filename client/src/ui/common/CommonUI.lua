local M = {}

function M:errorAlertView(code)
    if code == 0 then
        return false
    end
    local ErrorConfig = require("config.ErrorConfig")
    local errorStr = ErrorConfig[code]
    if not errorStr then
        errorStr = string.format("错误码：%d", code)
    end
    AlertView.new(errorStr)
    return true
end

function M:lightTips(text)
	require("ui.common.LightTips"):lightTips(text)
end

function M:lightTipsFormat(...)
    local text = string.format(...)
    self:lightTips(text)
end

function M:showLoadingLayer(isShow)
    if isShow then
        require("ui.common.LoadingLayer"):show()
    else
        require("ui.common.LoadingLayer"):hide()
    end
end

function M:createTextButton(parent, text, normalImageFile, highlightImageFile)
    local button = ButtonText.new(normalImageFile, highlightImageFile)
    parent:addChild(button)
    button:setLabel(text, 30)
    return button
end

function M:createTextSprite(parent, spriteName,text, size)
    return require("ui.common.TextSprite"):createTextSprite(parent, spriteName, text, size)
end

function M:createLabel(text, fontSize)
    local fontSize = fontSize or 40
    local label = cc.Label:create()
    label:setSystemFontSize(fontSize)
    label:setSystemFontName("STHeitiSC-Medium")
    label:setHorizontalAlignment(Enum.TextHAlignment.Center)
    label:setString(text)
    label:enableOutline(cc.c4b(0, 0, 0, 255), 3)
    label:setTextColor(cc.c4b(255, 255, 255, 255))
    return label
end

function M:createSpriteFrameFullName(fullName, key)
    assert(fullName and key)
    cc.SpriteFrameCache:getInstance():addSpriteFrames(fullName)
    local frame = cc.SpriteFrameCache:getInstance():getSpriteFrame(key)
    if nil==frame then
        local text = string.format("找不到资源图片%s，key=%s", fullName, key)
        print("错误提示：", text)
        self:lightTips(text)
    end
    return frame
end

function M:createSpriteFrameTinyName(fileName, key)
    assert(fileName)
    local fullName = string.format("ui/%s/%s.plist", fileName, fileName)
    return self:createSpriteFrameFullName(fullName, key)
end

function M:createSpriteWithFrame(fileName, key)
    local frame = self:createSpriteFrameTinyName(fileName, key)
    if nil == frame then
        return nil
    else
        return cc.Sprite:createWithSpriteFrameName(key)
    end
end

function M:alertRechargeLayer()
    local showText = __Localized("元宝不足,是否充值")
    local alertView = AlertView.new(showText,__Localized("取 消"), __Localized("充 值"))
    alertView.onClicked = function(index)
        if 1 == index then
            local layer = require("ui.recharge.layer-manager.RechargeLayer").new()
            local scene = cc.Director:getInstance():getRunningScene()
            scene:addChild(layer)
        end
    end
end

return M