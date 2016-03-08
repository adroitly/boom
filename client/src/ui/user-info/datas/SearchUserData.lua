local M = class("ui.user-info.datas.SearchUserData")

function M:ctor(playerBaseInfo)
	assert(playerBaseInfo and playerBaseInfo.player_id and playerBaseInfo.nickname and 
		playerBaseInfo.level and playerBaseInfo.icon)
	Table:copy(self, playerBaseInfo)
	Print:Table(playerBaseInfo, "playerBaseInfo")
end

function M:getSearchUserDataList(msgTable)
	local playerBaseInfos = msgTable.player_infos
	local dataList = {}
	for _,playerBaseInfo in pairs(playerBaseInfos) do
		table.insert(dataList, M.new(playerBaseInfo))
	end
	return dataList
end

function M:updateLevel(level)
	self.level = level
end

function M:getId()
	return self.player_id
end
function M:getName()
	return self.nickname
end
function M:getGuildName()
	return self.guild_name
end
function M:getLevel()
	return self.level
end

function M:getIcon()
	return self.icon
end


return M