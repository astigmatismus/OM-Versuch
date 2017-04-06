// Copyright Kevlin Henney, 2000, 2001, 2002. All rights reserved.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef MANY_H
#define MANY_H

#include <algorithm>
#include <typeinfo>
#include <iostream>

//namespace milan
//{

class MAny
{
public:
    // structors
    MAny() : content(0) {}
    template<typename ValueType> MAny(const ValueType& value) : content(new holder<ValueType>(value)) {}
    MAny(const MAny& other) : content(other.content ? other.content->clone() : 0) {}
    ~MAny()
    {
        if(content != 0)
        {
            delete content;
            content = 0;
        }
    }

    // modifiers
    MAny& swap(MAny& rhs) {std::swap(content, rhs.content); return *this;}
    template<typename ValueType> MAny& operator=(const ValueType& rhs) {MAny(rhs).swap(*this); return *this;}
    MAny& operator=(const MAny& rhs) {MAny(rhs).swap(*this); return *this; }

    // queries
    bool empty() const {return !content;}
    const std::type_info& type() const {return content ? content->type() : typeid(void);}

    class placeholder
    {
    public: 
        // structors
        virtual ~placeholder() {}

        // queries
        virtual const std::type_info & type() const = 0;
        virtual placeholder* clone() const = 0;
    };

    template<typename ValueType>
    class holder : public placeholder
    {
    public:
        // structors
        holder(const ValueType & value) : held(value) {}
        virtual ~holder() {}

        // queries
        virtual const std::type_info & type() const {return typeid(ValueType);}
        virtual placeholder* clone() const {return new holder(held); }

        // representation
        ValueType held;
    };
public:
    placeholder* content;
}; // class MAny

template<typename ValueType>
const ValueType* anyCast(const MAny* operand)
{
    return &static_cast<MAny::holder<ValueType> *>(operand->content)->held;
}

template<typename ValueType>
ValueType* anyCast(MAny* operand)
{
    return const_cast<ValueType*>(
            &static_cast<MAny::holder<ValueType>*>(operand->content)->held
            );
}

//} // namespace milan

#endif
