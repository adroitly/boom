local M = {}

local kIsMusicClose                 = "kIsSoundClose"
local kIsEffectClose                = "kIsEffectClose"

local m_lastMusicPath               = nil
local m_isEffectCloseCache          = nil 
local m_isBgMusicCloseCache         = nil 

-- 控制播放
function M:isMusicClose()
    return m_isBgMusicCloseCache
end

function M:isEffectClose()
    return m_isEffectCloseCache
end

function M:setEffectClose(isClose)
    if m_isEffectCloseCache == isClose then 
        return
    end

    m_isEffectCloseCache = isClose
    local userDefault = cc.UserDefault:getInstance()
    userDefault:setBoolForKey(kIsEffectClose, isClose)
    userDefault:flush()

    if isClose then 
        self:stopAllEffects()
    end
end

function M:setMusicClose(isClose)
    if m_isBgMusicCloseCache == isClose then 
        return
    end

    m_isBgMusicCloseCache = isClose
    local userDefault = cc.UserDefault:getInstance()
    userDefault:setBoolForKey(kIsMusicClose, isClose)
    userDefault:flush()

    if isClose then 
        self:stopMusic()
    end

    if not isClose and m_lastMusicPath then 
        self:playMusic(m_lastMusicPath, true) 
    end
end

-- 背景音乐
function M:preloadMusic(filePath)
    assert(filePath)
    if cc.FileUtils:getInstance():isFileExist(filePath) then
        cc.SimpleAudioEngine:getInstance():preloadMusic(filePath)
    end
end

function M:playMusic(filePath, isLoop)
    assert(filePath and "boolean"==type(isLoop))
    if m_isBgMusicCloseCache then 
        return 
    end

    if cc.FileUtils:getInstance():isFileExist(filePath) then
        m_lastMusicPath = filePath
        cc.SimpleAudioEngine:getInstance():playMusic(filePath, isLoop)
    end
end

function M:stopMusic(isReleaseData)
    cc.SimpleAudioEngine:getInstance():stopMusic(isReleaseData)
end

function M:pauseMusic()
    cc.SimpleAudioEngine:getInstance():pauseMusic() 
end

function M:resumeMusic()
    cc.SimpleAudioEngine:getInstance():resumeMusic()  
end

function M:setMusicVolume(volume)
    assert(volume)
    cc.SimpleAudioEngine:getInstance():setMusicVolume(volume) 
end

-- 音效
function M:playEffect(filePath)
    assert(filePath)
    if self:isEffectClose() then 
        return 
    end

    -- 当声音为空时候，不能直接调用playEffect，playEffect的内部实现使用了
    -- AudioFileOpenURL函数，这个函数似乎有个bug
    -- 当声音路径不存在的时候，打开的文件描述符不会关闭，引起文件描述符泄露
    -- 每个程序的文件描述符，个数会有一个上限值。当超过这个上限值的时候，就算文件存在，也打不开。
    -- 使得png图片就算存在，也不能生成纹理。
    if cc.FileUtils:getInstance():isFileExist(filePath) then
        cc.SimpleAudioEngine:getInstance():playEffect(filePath)
    end
end

function M:setEffectsVolume(volume)
    assert(volume)
    cc.SimpleAudioEngine:getInstance():setEffectsVolume(volume) 
end

function M:stopAllEffects()
    cc.SimpleAudioEngine:getInstance():stopAllEffects() 
end

function M:pauseAllEffects()
    cc.SimpleAudioEngine:getInstance():pauseAllEffects()  
end

function M:resumeAllEffects()
    cc.SimpleAudioEngine:getInstance():resumeAllEffects()  
end

function M:__preloadSetting()
    m_isBgMusicCloseCache = cc.UserDefault:getInstance():getBoolForKey(kIsMusicClose, false)
    m_isEffectCloseCache = cc.UserDefault:getInstance():getBoolForKey(kIsEffectClose, false)
end

M:__preloadSetting()

return M


