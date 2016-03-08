
local M = class("ui.team.MainLayer",function ()
	return cc.Layer:create()
end)


function M:ctor()
    self:_createEditTeamLayer()
end

function M:_createEditTeamLayer()
    local layer = require("ui.team.layer-manager.EditTeamLayer").new()
    self:addChild(layer)
end
return M