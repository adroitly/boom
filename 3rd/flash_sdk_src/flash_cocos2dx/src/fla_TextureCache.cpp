//
//  fla_TextureCache.cpp
//  FlashCocos2d-xTest
//
//  Created by HJC on 15/6/16.
//
//

#include "fla_TextureCache.h"

namespace fla
{
    TextureCache::TextureCache()
    {
        _nextId = 0;
        _totalTextureBytes = 0;
        _maxTextureBytes = 256 * 1024 * 1204;  // 256 M
    }

    TextureCache::~TextureCache()
    {
        clear();
    }

    void TextureCache::clear()
    {
        _textureList.clear_and_dispose(ItemDisposer());
        _frames.clear();
        _IdMap.clear();
        _keyMap.clear();
        _totalTextureBytes = 0;
    }

    uint64_t TextureCache::addTexture2d(const std::string& key, cocos2d_bridge::Texture2D* texture2d)
    {
        auto iter = _keyMap.find(key);
        if (iter != _keyMap.end())
        {
            return iter->second->Id;
        }

        _nextId++;

        auto item = new TextureCacheItem();
        item->setTexture2d(texture2d);
        item->key = key;
        item->Id = _nextId;

        auto size = texture2d->getContentSizeInPixels();

#if COCOS2D_VERSION >= 0x00030000
        auto bitsPerPixelForFormat = texture2d->getBitsPerPixelForFormat();
#else
        auto bitsPerPixelForFormat = texture2d->bitsPerPixelForFormat();
#endif

        item->textureBytes = (size.width * size.height * bitsPerPixelForFormat) / 8;

        _textureList.push_front(*item);
        _keyMap[item->key] = item;
        _IdMap[item->Id] = item;

        _totalTextureBytes += item->textureBytes;

        return item->Id;
    }

    cocos2d_bridge::Texture2D* TextureCache::getTexture2d(const std::string& key)
    {
        auto iter = _keyMap.find(key);
        if (iter != _keyMap.end())
        {
            return iter->second->texture;
        }
        return nullptr;
    }

    cocos2d_bridge::Texture2D* TextureCache::getTexture2d(uint64_t Id)
    {
        auto iter = _IdMap.find(Id);
        if (iter != _IdMap.end())
        {
            return iter->second->texture;
        }
        return nullptr;
    }

    void TextureCache::setSpriteFrame(TextureFrame* textureFrame, const std::string& key)
    {
        assert(textureFrame->getTexture() == nullptr);
        _frames.set(textureFrame, key);
    }

    TextureFrame* TextureCache::getSpriteFrame(const std::string& key)
    {
        auto frame = _frames.get(key);
        if (!frame)
        {
            return frame;
        }

        if (frame->getTexture())
        {
            return frame;
        }

        auto texture = getTexture2d(frame->getTextureId());
        if (texture)
        {
            frame->setTexture(texture);
            return frame;
        }
        return nullptr;
    }
}
