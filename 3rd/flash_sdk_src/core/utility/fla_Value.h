//=============================================================================
//  clover
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#ifndef __CLOVER_VALUE_H__
#define __CLOVER_VALUE_H__

#include <string>
#include <map>
#include <vector>
#include <assert.h>
#include <memory>
#include <boost/variant.hpp>

namespace clover
{
    struct EmptyType
    {
    };
    
    enum class ValueType
    {
        Error = 0,  // 错误
        Boolean,    // 布尔值
        Real,       // 数字
        Integer,    // 整数
        String,     // 字符串
        Array,      // 数组
        Dict,       // 字典
    };

    class Value
    {
    public:
        typedef std::map<std::string, Value> Dict;
        typedef std::vector<Value> Array;

        static Value makeDict()
        {
            return Value(std::make_shared<Dict>());
        }

        static Value makeArray()
        {
            return Value(std::make_shared<Array>());
        }

        Value() : _obj(clover::EmptyType())
        {
        }

        explicit Value(const std::string& str) : _obj(str)
        {
        }

        explicit Value(double real) : _obj(real)
        {
        }

        explicit Value(bool value) : _obj(value)
        {
        }

        explicit Value(int value) : _obj(value)
        {
        }

        // 判断
        bool isString() const
        {
            return type() == ValueType::String;
        }

        bool isArray() const
        {
            return type() == ValueType::Array;
        }

        bool isDict() const
        {
            return type() == ValueType::Dict;
        }

        bool isReal() const
        {
            return type() == ValueType::Real;
        }

        bool isError() const
        {
            return type() == ValueType::Error;
        }

        bool isBoolean() const
        {
            return type() == ValueType::Boolean;
        }

        bool isInteger() const
        {
            return type() == ValueType::Integer;
        }

        ValueType type() const
        {
            return static_cast<ValueType>(_obj.which());
        }

        // 字典
        const Dict& dict() const
        {
            return const_cast<Value*>(this)->dict();
        }

        Dict& dict()
        {
            assert(isDict());
            return *boost::get<std::shared_ptr<Dict>>(_obj);
        }

        // 数组
        const Array& array() const
        {
            return const_cast<Value*>(this)->array();
        }

        Array& array()
        {
            assert(isArray());
            return *boost::get<std::shared_ptr<Array>>(_obj);
        }

        // 数字
        const double& real() const
        {
            assert(isReal());
            return boost::get<double>(_obj);
        }

        const std::string& string() const
        {
            assert(isString());
            return boost::get<std::string>(_obj);
        }

        bool boolean() const
        {
            assert(isBoolean());
            return boost::get<bool>(_obj);
        }

        int integer() const
        {
            assert(isInteger());
            return boost::get<int>(_obj);
        }

    private:
        template <typename T>
        Value(const std::shared_ptr<T>& rhs)
            : _obj(rhs)
        {
        }

    private:
        boost::variant<clover::EmptyType, bool, double, int, std::string, std::shared_ptr<Array>, std::shared_ptr<Dict>>
            _obj;
    };
}

#endif
