//
//  UmengConfig.h
//  big-devil
//
//  Created by ming on 15/5/18.
//
//

#ifndef __BOOM__UmengConfig__
#define __BOOM__UmengConfig__

#include <string>
#include "json/document.h"

class UmengConfig
{
public:
    UmengConfig();
    std::string getChannelID();
    
private:
    void readConfig();
    
    std::string     _channelID;
    rapidjson::Document _docRootjson;
};

#endif /* defined(__BOOM__UmengConfig__) */
