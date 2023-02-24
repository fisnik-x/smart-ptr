/*++
    weak_ptr.hpp
    
    Author: Fisnik
    Copyright (C) Fisnik. All rights reserved.

    Abstract:
    
    

    This source code is licensed under the MIT license found in the
    LICENSE file in the root directory of this source tree. 
--*/
#pragma once

#include "control_block.hpp"
#include "shared_ptr.hpp"

template<typename T>
class weak_ptr{
public:
    constexpr weak_ptr() noexcept : m_ptr{}, m_ctrlBlock{} {}
    weak_ptr(T* other) : m_ptr{other}, m_ctrlBlock{new Control_Block} { increment_weakptr(); }
    weak_ptr(const shared_ptr<T>& other) noexcept 
        : m_ptr{other.m_ptr}, m_ctrlBlock{other.m_ctrlBlock} 
    {}
    ~weak_ptr() {}

    void reset() noexcept {}
    bool expired() noexcept {}
    auto lock() {}

    WeakPtr& operator=(const weak_ptr& other) 
    weak_ptr& operator=(const shared_ptr<T>& other){}
    
    template<class T> friend void swap(weak_ptr<T>& lhs, weak_ptr<T>& rhs) noexcept;

private:
    T* m_ptr{nullptr};
    Control_Block* m_ctrlBlock{nullptr};
    
    void increment_weakptr(){}
    void decrement_weakptr(){}
};

template<class T>
inline void swap(weak_ptr<T>& lhs, weak_ptr<T>& rhs) noexcept{}