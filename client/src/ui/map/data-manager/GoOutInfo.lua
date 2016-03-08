local M = {}

function M:newDefalutInfo(twoDCoor)
	return self:newGoOutInfo(Enum.GoOutOperation.Move, twoDCoor)
end

function M:newGoOutInfo(enumGoOutOperation, twoDCoor)
	assert(twoDCoor.i and twoDCoor.j)
	return {
		enumGoOutOperation = enumGoOutOperation, 
		twoDCoor = twoDCoor,
	}
end

function M:getOperation(goOutInfo)
	return goOutInfo.enumGoOutOperation
end

function M:getTwoDCoor(goOutInfo)
	return goOutInfo.twoDCoor
end

function M:externValue(goOutInfo, toPlayerId, toArmyId)
	goOutInfo.toPlayerId = toPlayerId
	goOutInfo.toArmyId = toArmyId
end

function M:getToPlayerId(goOutInfo)
	return goOutInfo.toPlayerId
end

function M:getToArmyId(goOutInfo)
	return goOutInfo.toArmyId
end

return M