//=============================================================================
//  clover
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#ifndef __CLOVER_OBJCOUNTER__
#define __CLOVER_OBJCOUNTER__

#include <type_traits>
#include <stdio.h>
#include <typeinfo>

namespace clover
{
    /*
     用于计算对象的数目, 使用例子为
     class Test : public Counter<Test>
     {
     public:
        static void print(int count)
        {
            printf("Test obj: %d", count");
        }
     };

     或者
     class TestPrinter
     {
     public:
        static void print(int count)
        {
            printf("Test obj: %d", count");
        }
     };

     class Test : public Counter<Test, TestPrinter>
     {
     };

     可实现一个打印函数，作为第二个参数传进去。默认为不打印
     */

    template <typename T, typename PrinterT = T>
    class Counter
    {
    public:
        Counter();
        Counter(const Counter&);
        ~Counter();

        static int getCount()
        {
            return s_count;
        }

    private:
        static int s_count;
    };

    template <typename T>
    class PrintCounter : public Counter<T, PrintCounter<T>>
    {
    public:
        static void print(int count)
        {
            printf("[%s]: %d\n", typeid(T).name(), count);
        }
    };

    ////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        // 用于判断类型是否有 static void print(int count)函数
        template <typename T>
        struct TypeHasPrint
        {
            typedef char yes;
            typedef void* no;

            template <typename U, U>
            struct sign_check;

            template <typename U>
            static yes check(sign_check<void(int), &U::print>*);

            template <typename>
            static no check(...);

            enum
            {
                value = sizeof(check<T>(0)) == sizeof(yes)
            };
        };

        // 类型有print函数就调用
        template <typename PrinterT>
        inline typename std::enable_if<TypeHasPrint<PrinterT>::value>::type doPrint(int count)
        {
            PrinterT::print(count);
        }

        // 没有，不调用
        template <typename PrinterT>
        inline typename std::enable_if<!TypeHasPrint<PrinterT>::value>::type doPrint(int)
        {
        }
    }

    // 统计对象的个数
    template <typename T, typename PrinterT>
    inline Counter<T, PrinterT>::Counter()
    {
        s_count++;
        detail::doPrint<PrinterT>(s_count);
    }

    template <typename T, typename PrinterT>
    inline Counter<T, PrinterT>::Counter(const Counter&)
    {
        s_count++;
        detail::doPrint<PrinterT>(s_count);
    }

    template <typename T, typename PrinterT>
    inline Counter<T, PrinterT>::~Counter()
    {
        s_count--;
        detail::doPrint<PrinterT>(s_count);
    }

    template <typename T, typename PrinterT>
    int Counter<T, PrinterT>::s_count = 0;
}

#endif
