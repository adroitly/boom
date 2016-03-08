//
//  UmengConfig.cpp
//  big-devil
//
//  Created by ming on 15/5/18.
//
//

#include "UmengConfig.h"
#include "cocos2d.h"
#include <string>

#define CONFIG_FILE "umeng.json"

UmengConfig::UmengConfig()
{
    readConfig();
}

std::string UmengConfig::getChannelID()
{
    return _channelID.empty() ? "mowang" : _channelID;
}

void UmengConfig::readConfig()
{
    // read config file
    std::string fullPathFile = cocos2d::FileUtils::getInstance()->fullPathForFilename(CONFIG_FILE);
    std::string fileContent = cocos2d::FileUtils::getInstance()->getStringFromFile(fullPathFile);

    if (fileContent.empty())
    {
        return;
    }

    if (_docRootjson.Parse<0>(fileContent.c_str()).HasParseError())
    {
        cocos2d::log("read json file %s failed because of %s", fullPathFile.c_str(), _docRootjson.GetParseError());
        return;
    }

    if (_docRootjson.HasMember("channel_ID") && _docRootjson["channel_ID"].IsString())
    {
        _channelID = _docRootjson["channel_ID"].GetString();
    }
}