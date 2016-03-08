//
//  fla_TextureCache.h
//  FlashCocos2d-xTest
//
//  Created by HJC on 15/6/16.
//
//

#ifndef __FLA_TEXTURECACHE_H__
#define __FLA_TEXTURECACHE_H__

#include <boost/intrusive/list.hpp>
#include <boost/noncopyable.hpp>
#include <boost/container/flat_map.hpp>
#include "cocos2d_bridge.h"
#include "core/base/fla_Ref.h"
#include "../base/fla_RefDict.h"
#include "fla_TextureFrame.h"

namespace fla
{
    class TextureCache : boost::noncopyable
    {
    public:
        TextureCache();
        ~TextureCache();
        
        uint64_t addTexture2d(const std::string& key, cocos2d_bridge::Texture2D* texture2d);
        cocos2d_bridge::Texture2D* getTexture2d(const std::string& key);
        cocos2d_bridge::Texture2D* getTexture2d(uint64_t Id);
        
        void setSpriteFrame(TextureFrame* frame, const std::string& key);
        TextureFrame* getSpriteFrame(const std::string& key);
        
        void clear();
        
    private:
        typedef boost::intrusive::link_mode<boost::intrusive::auto_unlink> AutoLinkMode;
        typedef boost::intrusive::list_base_hook<AutoLinkMode> ListBaseHook;
        typedef boost::intrusive::constant_time_size<false> TimeSizeFalse;
        
        struct TextureCacheItem : public ListBaseHook
        {
            TextureCacheItem()
            {
                texture = nullptr;
                Id = 0;
                textureBytes = 0;
            }
            
            ~TextureCacheItem()
            {
                if (texture)
                {
                    texture->release();
                }
            }
            
            void setTexture2d(cocos2d_bridge::Texture2D* texture2d_)
            {
                clover::intrusive_ptr_safe_assign(texture, texture2d_);
            }
            
            cocos2d_bridge::Texture2D* texture;
            uint64_t Id;
            std::string key;
            size_t textureBytes;
        };
        
        struct ItemDisposer
        {
            void operator()(TextureCacheItem* item)
            {
                delete item;
            }
        };
        
        typedef boost::intrusive::list<TextureCacheItem, TimeSizeFalse> TextureList;
        
        TextureList _textureList;
        RefDict<TextureFrame> _frames;
        
        boost::container::flat_map<std::string, TextureCacheItem*> _keyMap;
        boost::container::flat_map<uint64_t, TextureCacheItem*> _IdMap;
        uint64_t _nextId;
        size_t _totalTextureBytes;
        size_t _maxTextureBytes;
    };
}

#endif
