local BackpackConfigRead= require("ui.backpack.data-manager.BackpackConfigRead")
local HeroConfigRead = require("ui.team.data-manager.HeroConfigRead")
local M = class("ui.market.datas.MarketData")
local function _assertMsgTable(msgTable)
	assert(msgTable and msgTable.id and msgTable.price and msgTable.resource_id and msgTable.number and 
		msgTable.item_id and msgTable.level and msgTable.player_id and msgTable.nickname and msgTable.time)
end

function M:newMarketDataByHeroData(heroData)
	local marketData = M.new()
	local data = self:_getDataByHeroData(heroData)
	if data then
		Table:copy(marketData, data)
		return marketData
	else
		return nil
	end
end

function M:newMarketDataByBackpackData(backpackData)
	local marketData = M.new()
	local data = self:_getDataByBackpackData(backpackData)
	if data then
		Table:copy(marketData, data)
		return marketData
	else
		return nil
	end
end

function M:newMarketDataByServer(msgTable)
	local marketData = M.new()
	_assertMsgTable(msgTable)
	Table:copy(marketData, msgTable)
	return marketData
end

function M:getPrice()
	return self.price
end

-- 资源类型ID，
function M:getResourceId()
	return self.resource_id
end

function M:getNumber()
	return self.number
end
-- 资源ID
function M:getItemId()
	return self.item_id
end

function M:getLevel()
	return self.level
end

function M:getPlayerId()
	return self.player_id
end

function M:getNickName()
	return self.nickname
end

-- 页数ID
function M:getId()
	return self.id
end

function M:getTime()
	return self.time
end

function M:updateNumber(number)
	self.number = number
end

function M:updatePrice(price)
	self.price = price
end

function M:updateTime(time)
	self.time = time
end


function M:_getDataByBackpackData(backpackData)
	local itemId = backpackData:getItemType()
	local itemType = BackpackConfigRead:getItemType(itemId)
	local count = backpackData:getItemNumber()
	if count > 0 and 2 ~=  itemType then
		if true == BackpackConfigRead:isBind(itemId) then
			return nil
		end
		return {
					resource_id = Enum.ResourceTypeId.Item,
					item_id     = itemId,
					number      = backpackData:getItemNumber(),
					price       = BackpackConfigRead:getPrice(backpackData:getItemType()),
					id          = itemId
				}
	else 
		return nil
	end
end

function M:_getDataByHeroData(heroData)
	local heroType = heroData:getHeroType()
	if true == HeroConfigRead:isBind(heroType) or true == heroData:isLock() then
		return nil
	end
	return {
				resource_id = Enum.ResourceTypeId.Hero,
				item_id     = heroData:getHeroType(),
				number      = 1,
				price       = HeroConfigRead:getPrice(heroType),
				level       = heroData:getHeroLevel(),
				id          = heroData:getHeroId()
			}
end

return M