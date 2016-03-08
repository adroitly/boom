 
local M = {}

--[[
    * 描述：平台指的是发行商+平台的统称
      发行商比如：腾讯、网易、云顶、九越等，
      平台一般有3个：AppStore、Android、越狱
      举例：比如腾讯AppStore、腾讯Android、网易AppStore、网易Android、网易越狱等
    * 参数：平台 = { 平台id、平台热更新资源路径名 }
    * 警告：以下的参数配置必须与C++接口配置一致，并且与服务器确认
--]]
local m_platfromConfig = 
{
    PatgameOutnet  = { 1, "outnet" }, 
    PatgameInnet   = { 3, "innet"  },

    -- 待删除
    intranet        = { 3, "innet" },
}

--[[
    * 描述：渠道指的是App上架的渠道商，比如小米、PP、360、应用宝、苹果等，渠道只配置一次即可
           (有些渠道既是发行商又是渠道商，别搞蒙了)
    * 参数：
    * 警告：以下的参数配置必须与C++接口配置一致，并且与服务器确认
--]]
local m_channelConfig = 
{
    outnet      = 1, 
    innet       = 63,

    -- 待删除
    test        = 63,
}
    
--[[
    * 描述：获取平台名称，如JiuYueAndroid、JiuYueYueyu、JiuYueAppStore
--]]
local function _getPlatformName()
    local channelName = c_BridgeSDK:getChannelName()
    local parseTable = String:split(channelName, ":")
    assert(parseTable[1])
    return parseTable[1]
end

--[[
    * 描述：获取平台Id
    * 说明：未防止直接使用id容易写错，所以C++接口返回的是字符串形式，如JiuYueAndroid:Xiaomi(平台:渠道)，由Lua转换为平台Id
--]]
function M:getPlatformId()
    local channelName = c_BridgeSDK:getChannelName()
    local parseTable = String:split(channelName, ":")
    local platformKey = parseTable[1]
    local platformId = m_platfromConfig[platformKey][1]
    assert(platformId, string.format("未配置平台索引值(key=%s)", platformKey))
    return platformId
end

--[[
    * 描述：获取渠道Id
    * 说明：未防止直接使用id容易写错，所以C++接口返回的是字符串形式，如JiuYueAndroid:Xiaomi(平台:渠道)，由Lua转换为平台Id
--]]
function M:getChannelId()
    local channelName = c_BridgeSDK:getChannelName()
    local parseTable = String:split(channelName, ":")
    local channelKey = parseTable[2]
    local channelId = m_channelConfig[channelKey]
    assert(channelId, string.format("未配置渠道索引值(key=%s)", channelKey))
    return channelId
end

--[[
    * 描述：下载热更新资源目录名称(可选的值参考package目录下的文件夹)，内网(innet)、外网(outnet)
--]]
function M:getDowloadResourceDir()
    local platformKey = _getPlatformName()
    local dirName = m_platfromConfig[platformKey][2]
    assert(dirName, string.format("严重警告：未配置的热更新下载路径%s", platformKey))
    return dirName
end

return M

