//=============================================================================
//  clover
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#include "./fla_Json.h"
#include <sstream>
#include <cctype>

namespace clover
{
    namespace json
    {
        static std::string valueToStringNoStyle(const Value& value)
        {
            std::stringstream stream;
            switch (value.type())
            {
                case ValueType::Real:
                    stream << value.real();
                    break;

                case ValueType::String:
                    stream << "\"" << value.string() << "\"";
                    break;

                case ValueType::Array:
                {
                    stream << "[";
                    size_t i = 0;
                    for (auto& val : value.array())
                    {
                        stream << valueToStringNoStyle(val);
                        if (++i != value.array().size())
                        {
                            stream << ",";
                        }
                    }
                    stream << "]";
                }
                break;

                case ValueType::Dict:
                {
                    stream << "{";
                    size_t i = 0;
                    for (auto& iter : value.dict())
                    {
                        stream << "\"" << iter.first << "\":";
                        stream << valueToStringNoStyle(iter.second);
                        if (++i != value.dict().size())
                        {
                            stream << ",";
                        }
                    }
                    stream << "}";
                }
                break;

                default:
                    break;
            }
            return stream.str();
        }

        std::string valueToString(const Value& value)
        {
            return valueToStringNoStyle(value);
        }

        Value stringToValue(const std::string& str)
        {
            return stringToValue(&str[0], str.size());
        }

        ////////////////////////////////////////////////////////////////////////
        class JsonStream
        {
        public:
            JsonStream(const char* str, size_t len) : _cur(str), _end(str + len)
            {
            }

            int get()
            {
                if (_cur >= _end)
                    return EOF;
                return *_cur++;
            }

            void unget()
            {
                _cur--;
            }

            int peek()
            {
                if (_cur >= _end)
                    return EOF;
                return *_cur;
            }

            int skipSpaces()
            {
                int c = get();
                while (c != EOF && ::isspace(c))
                {
                    c = get();
                }
                unget();
                return c;
            }

        private:
            const char* _cur;
            const char* _end;
        };

        static inline bool is_number(int c)
        {
            return isdigit(c) || c == '-' || c == '.' || c == '+';
        }

        static Value getValue(JsonStream& stream);
        static std::string getString(JsonStream& stream)
        {
            std::string str;
            int c = stream.get();
            while (c != '\"' && c != EOF)
            {
                str.push_back(c);
                c = stream.get();
            }
            return str;
        }

        static Value getNum(JsonStream& stream)
        {
            std::string str;
            int c = stream.get();
            while (is_number(c) || c == 'e' || c == 'E')
            {
                str.push_back(c);
                c = stream.get();
            }
            stream.unget();
            return Value(atof(str.c_str()));
        }

        static Value getArray(JsonStream& stream)
        {
            Value array = json::Value::makeArray();
            int c = stream.skipSpaces();
            while (c != ']' && c != EOF)
            {
                Value val = getValue(stream);
                if (val.isError())
                {
                    return val;
                }
                c = stream.skipSpaces();
                if (c != ',' && c != ']')
                {
                    return Value();
                }

                if (c == ',')
                {
                    stream.get();
                    c = stream.skipSpaces();
                }
                array.array().push_back(val);
            }
            if (c == ']')
            {
                stream.get();
            }
            return array;
        }

        static Value getDict(JsonStream& stream)
        {
            Value dict = Value::makeDict();
            int c = stream.skipSpaces();
            std::string key;

            while (c != '}' && c != EOF)
            {
                if (c != '\"')
                {
                    return Value();
                }

                stream.get();
                key = getString(stream);

                c = stream.skipSpaces();
                if (c != ':')
                {
                    return Value();
                }
                stream.get();

                Value value = getValue(stream);
                if (value.isError())
                {
                    return Value();
                }
                c = stream.skipSpaces();
                if (c != ',' && c != '}')
                {
                    return Value();
                }

                if (c == ',')
                {
                    stream.get();
                    c = stream.skipSpaces();
                }

                dict.dict()[key] = value;
            }

            if (c == '}')
            {
                stream.get();
            }

            return dict;
        }

        static Value getValue(JsonStream& stream)
        {
            int c = stream.skipSpaces();
            if (c == EOF)
            {
                return Value();
            }
            else if (c == '[')  // 数组
            {
                stream.get();
                return getArray(stream);
            }
            else if (c == '{')  // 字典
            {
                stream.get();
                return getDict(stream);
            }
            else if (is_number(c))  // 数字
            {
                return getNum(stream);
            }
            else if (c == '\"')  // 字符串
            {
                stream.get();
                auto str = getString(stream);
                return Value(str);
            }
            return Value();
        }

        Value stringToValue(const char* str, size_t len)
        {
            JsonStream stream(str, len);
            return getValue(stream);
        }
    }
}
