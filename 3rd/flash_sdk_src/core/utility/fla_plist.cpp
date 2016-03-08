//=============================================================================
//  clover
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#include "fla_plist.h"
#include <sstream>

namespace clover
{
    namespace plist
    {
        static void writeValue(std::stringstream& strstream, const Value& value, int level);
        static void writeLevel(std::stringstream& strstream, int level);
        static void writeLine(std::stringstream& strstream, const char* str, int level);

        std::string valueToPlistString(const Value& value)
        {
            std::stringstream strstream;
            strstream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
            strstream << "<!DOCTYPE plist PUBLIC \"-//Apple Computer//DTD "
                         "PLIST 1.0//EN\" "
                         "\"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">" << std::endl;
            strstream << "<plist version=\"1.0\">" << std::endl;

            writeValue(strstream, value, 0);

            strstream << "</plist>" << std::endl;
            return strstream.str();
        }

        static void writeBoolean(std::stringstream& strstream, bool value, int level)
        {
            if (value)
            {
                writeLine(strstream, "<true/>", level);
            }
            else
            {
                writeLine(strstream, "<false/>", level);
            }
        }

        static void writeString(std::stringstream& strstream, const std::string& value, int level)
        {
            writeLevel(strstream, level);
            strstream << "<string>";
            strstream << value;
            strstream << "</string>" << std::endl;
        }

        static void writeInteger(std::stringstream& strstream, int value, int level)
        {
            writeLevel(strstream, level);
            strstream << "<integer>";
            strstream << value;
            strstream << "</integer>" << std::endl;
        }

        static void writeDict(std::stringstream& strstream, const Value::Dict& dict, int level)
        {
            if (dict.size() == 0)
            {
                writeLine(strstream, "<dict/>", level);
            }
            else
            {
                writeLine(strstream, "<dict>", level);
                for (auto& item : dict)
                {
                    writeLevel(strstream, level + 1);
                    strstream << "<key>" << item.first << "</key>" << std::endl;
                    writeValue(strstream, item.second, level + 1);
                }
                writeLine(strstream, "</dict>", level);
            }
        }

        static void writeArray(std::stringstream& strstream, const Value::Array& array, int level)
        {
            if (array.size() == 0)
            {
                writeLine(strstream, "<array/>", level);
            }
            else
            {
                writeLine(strstream, "<array>", level);
                for (auto& item : array)
                {
                    writeValue(strstream, item, level + 1);
                }
                writeLine(strstream, "</array>", level);
            }
        }

        static void writeValue(std::stringstream& strstream, const Value& value, int level)
        {
            switch (value.type())
            {
                case ValueType::Boolean:
                    writeBoolean(strstream, value.boolean(), level);
                    break;

                case ValueType::Dict:
                    writeDict(strstream, value.dict(), level);
                    break;

                case ValueType::String:
                    writeString(strstream, value.string(), level);
                    break;

                case ValueType::Integer:
                    writeInteger(strstream, value.integer(), level);
                    break;

                case ValueType::Array:
                    writeArray(strstream, value.array(), level);
                    break;

                default:
                    break;
            }
        }

        static void writeLevel(std::stringstream& strstream, int level)
        {
            if (level != 0)
            {
                const char* space = "    ";
                for (int i = 0; i < level; i++)
                {
                    strstream << space;
                }
            }
        }

        static void writeLine(std::stringstream& strstream, const char* str, int level)
        {
            writeLevel(strstream, level);
            strstream << str << std::endl;
        }
    }
}
