local M = {}
local m_listeners = {}
setmetatable(m_listeners, {__mode="kv"})

M.EventName = 
{
	onListenSoldierDataUpdate    = "onListenSoldierDataUpdate",

	onListenMailPersonalChanged  = "onListenMailPersonalChanged",
	onListenMailSystemChanged    = "onListenMailSystemChanged",
	onListenMailGameChanged      = "onListenMailGameChanged",

	onListenGuildMemberOperate   = "onListenGuildMemberOperate",

	onListenBackpackDataChange   = "onListenBackpackDataChange",
	onListenHeroDataChange       = "onListenHeroDataChange",
	onListenTeamDataChange       = "onListenTeamDataChange",

	onListenOpenAlertCoordinate  = "onListenOpenAlertCoordinate",
	onListenCollectDataChanged	 = "onListenCollectDataChanged",
	onViewCenterToPositionChanged= "onViewCenterToPositionChanged",

	onProduceBuildingInfoGet	 = "onProduceBuildingInfoGet",
	onProduceSoldierReceived	 = "onProduceSoldierReceived",
	onProduceResourceReceived	 = "onProduceResourceReceived",

	onListenUserInfoDataChange 	 = "onListenUserInfoDataChange",
	onListenCountryWarInfoShow   = "onListenCountryWarInfoShow",
	onListenCountryWarOpened     = "onListenCountryWarOpened",
	-- BridgeSDK began 
	onListenSDKDidInitSuccess    = "onListenSDKDidInitSuccess",
	onListenSDKDidInitFailed     = "onListenSDKDidInitFaild",
	onListenSDKDidLoginSuccess   = "onListenSDKDidLoginSuccess",
	onListenSDKDidLoginFailed    = "onListenSDKDidLoginFailed",
	onListenSDKDidLogoutSuccess	 = "onListenSDKDidLogoutSuccess",
	onListenSDKDidLogoutFailed 	 = "onListenSDKDidLogoutFailed",
	onListenSDKDidPaySuccess     = "onListenSDKDidPaySuccess",
	onListenSDKDidPayFailed	     = "onListenSDKDidPayFailed",
	onListenSDKDidPayCancel	     = "onListenSDKDidPayCancel",
	-- BridgeSDK end
}

function M:postEvent(name, ...)
	for _, lister in pairs(m_listeners) do
		if lister[name] then
			lister[name](lister, ...)
		end
	end
end

function M:addListener(listener)
	if not Table:has_value(m_listeners, listener) then 
		table.insert(m_listeners, listener)
	end
end

function M:removeListener(listener)
	for k, v in pairs(m_listeners) do 
        if v == listener then 
            m_listeners[k] = nil 
            break
        end
    end
end

return M 

