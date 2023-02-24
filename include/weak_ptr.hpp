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
    template<typename X> friend class shared_ptr;
public:
    constexpr weak_ptr() noexcept : m_ptr{}, m_ctrlBlock{} {}
    weak_ptr(T* other) : m_ptr{other}, m_ctrlBlock{new Control_Block} { increment_weakptr(); }
    
    weak_ptr(const shared_ptr<T>& other) noexcept 
        : m_ptr{other.m_ptr}, m_ctrlBlock{other.m_ctrlBlock} 
    {
        increment_weakptr();
    }
    
    ~weak_ptr() { decrement_weakptr(); }

    void reset() noexcept { decrement_weakptr(); }
    
    bool expired() noexcept 
    {
        if(m_ctrlBlock == nullptr)
            return true;
        
        if(m_ctrlBlock->m_refCount == 0)
            --m_ctrlBlock->m_weakCount;
        
        if(m_ctrlBlock->m_refCount + m_ctrlBlock->m_weakCount == 0){
            delete m_ctrlBlock;
            m_ptr = nullptr;
            m_ctrlBlock = nullptr;
        }

        return !m_ctrlBlock || m_ctrlBlock->m_weakCount == 0;
    }

    auto lock() 
    {
        return expired() ? shared_ptr<T>() : shared_ptr<T>(*this);
    }

    WeakPtr& operator=(const weak_ptr& other) 
    {
        if(this != &other){
            decrement_weakptr();
            m_ptr = other.m_ptr;
            m_ctrlBlock = other.m_ctrlBlock;
            increment_weakptr();
        }

        return *this;
    }

    weak_ptr& operator=(const shared_ptr<T>& other)
    {
        m_ptr = other.m_ptr;
        m_ctrlBlock = other.m_ctrlBlock;

        if(m_ptr != nullptr && m_ctrlBlock != nullptr)
            ++m_ctrlBlock->m_weakCount;

        return *this;
    }
    
    template<class T> friend void swap(weak_ptr<T>& lhs, weak_ptr<T>& rhs) noexcept;

private:
    T* m_ptr{nullptr};
    Control_Block* m_ctrlBlock{nullptr};
    
    void increment_weakptr(){ ++m_ctrlBlock->m_weakCount; }
    void decrement_weakptr()
    {
        if(m_ctrlBlock && m_ptr){
            if(--m_ctrlBlock->m_weakCount == 0 && m_ctrlBlock->m_refCount == 0){
                delete m_ctrlBlock;
            }
            m_ctrlBlock = nullptr;
            m_ptr = nullptr;
        }
    }
};

template<class T>
inline void swap(weak_ptr<T>& lhs, weak_ptr<T>& rhs) noexcept
{
    T temp(std::move(lhs));
    lhs = std::move(rhs);
    rhs = std::move(temp);
}