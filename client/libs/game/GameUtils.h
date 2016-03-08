//
//  GameUtils.h
//  WeAreHeros
//
//  Created by HJC on 14/12/29.
//
//

#ifndef __GAMEUTILS_H__
#define __GAMEUTILS_H__

#include <string>

namespace GameUtils
{
    void removeAllUnusedResources();
    void setPackagePath(const std::string& path);
    std::string getPackagePath();
    
    std::string getResourcePath();
    
    void removeDirContent(const std::string& path);
    
    void saveDecryptString(const std::string& content, const std::string& filePath);
    std::string readDecryptFile(const std::string& filePath);
    
    void callLuaFunction(const std::string& funName);
    void callLuaFunction(const std::string& funName, const char* value);
}

#endif

