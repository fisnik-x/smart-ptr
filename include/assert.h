// Copyright (C) Fisnik. All rights reserved.
#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#ifndef ASSERT_H
#define ASSERT_H

#include <stddef.h>
#include <stdexcept>
#include <cassert>
#include <limits>
#include <utility>
#include <iterator>
#include <initializer_list>

template <typename E>
void throw_exception(E&& e)
{
    throw static_cast<E&&>(e);
}

template <typename E, typename... Args>
void throw_exception_(Args&&... args){
    throw_exception(E(static_cast<Args&&>(args)...));
}

template <typename E, typename... Args>
inline static void assert_enforce(bool condition, Args&&... args)
{
    if(!condition){
        throw_exception(E(static_cast<Args&&>(args)...));       
    }
}

#endif // ASSERT_H
