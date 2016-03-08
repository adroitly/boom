//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_DEFINEFONT__
#define __FLA_DEFINEFONT__


#include "fla_Definition.h"
#include "Shape/fla_Shape.h"
#include <string>
#include <map>


namespace fla
{
    typedef enum
    {
        LanguageCode_Latin              = 1,
        LanguageCode_Japanese           = 2,
        LanguageCode_Korean             = 3,
        LanguageCode_SimplifiedChinese  = 4,
        LanguageCode_TraditionalChinese = 5,
    } LanguageCode;
    
    
    class KerningRecord
    {
    public:
        KerningRecord() : code1(0), code2(0), adjustment(0) {}
        uint16_t    code1;
        uint16_t    code2;
        float       adjustment;
    };
    
    
    
    class FontItem
    {
    public:
        FontItem()
        {
            code = 0;
            advance = 0;
        }
        uint16_t    code;
        Shape       glyph;
        
        // 字体有hasLayout才应该保存
        Rect        bounds;
        float       advance;
    };
    
    
    class DefinitionFont : public DefinitionHelper<DefinitionFont>
    {
    public:
        float       ascent;
        float       descent;
        float       leading;
        uint8_t     fontFlags;
        uint8_t     languageCode;
        

        const FontItem* findItem(uint16_t code) const;
        FontItem* findItem(uint16_t code);
        
        void      addItem(const FontItem& item);
        
        const std::map<uint16_t, FontItem>&  items() const
        {
            return _items;
        }
        
        const FontItem* defaultItem() const         {   return findItem(_defaultCode);  }
        
        virtual Rect getBounds() const override;
        
        uint16_t defaultCode() const                {   return _defaultCode;            }
        void     setDefaultCode(uint16_t code)      {   _defaultCode = code;            }
        

        bool hasLayout() const      {   return ((fontFlags & 0x80) != 0);  }
        bool shiftJIS() const       {   return ((fontFlags & 0x40) != 0);  }
        bool smallText() const      {   return ((fontFlags & 0x20) != 0);  }
        bool ansi() const           {   return ((fontFlags & 0x10) != 0);  }
        bool wideOffsets() const    {   return ((fontFlags & 0x08) != 0);  }
        bool wideCodes() const      {   return ((fontFlags & 0x04) != 0);  }
        bool italic() const         {   return ((fontFlags & 0x02) != 0);  }
        bool bold() const           {   return ((fontFlags & 0x01) != 0);  }
        
        const std::vector<KerningRecord>& kerningTables() const     {   return _kerningTables;  }
        void addKerningRecord(const KerningRecord& record)
        {
            _kerningTables.push_back(record);
        }
        
        virtual void onFinishParse() override   {}
        
    private:
        friend class DefinitionHelper<DefinitionFont>;
        DefinitionFont()
        {
            _defaultCode = 0;
        }
        
    private:
        uint16_t                        _defaultCode;
        std::map<uint16_t, FontItem>    _items;
        std::vector<KerningRecord>      _kerningTables;
    };
}

#endif
