local M = class("share.encrypt") 

function M:ctor()
	self.fix = os.time()
	self.random = math.random(10000)
end

function M:encode(data)
	return game.bxor((game.bxor(data, self.fix) - self.random), self.fix)
end

function M:decode(data)
	return game.bxor((game.bxor(data, self.fix) + self.random), self.fix)
end

function M:initPassword(oldPassword) 
	if oldPassword ~= nil then 
	 	self.fix = oldPassword.fix 
		self.random = oldPassword.random 
		return nil  
	end 

	return {
		fix = self.fix, 
		random = self.random 
	}
end

return M 