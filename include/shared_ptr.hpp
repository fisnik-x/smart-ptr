// Copyright (C) Fisnik. All rights reserved.
#pragma once
#include <compare>
#include <memory>

#include "assert.h"
#include "weak_ptr.hpp"
#include "control_block.hpp"

template<typename T>
class shared_ptr {
public:
    constexpr shared_ptr() : shared_ptr(nullptr) {}
    
    explicit shared_ptr(T* other) : m_ptr{other}, m_ctrlBlock{new Control_Block}
    {
        increment_reference();
    }

    constexpr shared_ptr(const std::nullptr_t) noexcept 
        : m_ptr{nullptr}, m_ctrlBlock{nullptr}
    {
        increment_reference();
    }

    shared_ptr(shared_ptr&& other) noexcept
        : m_ptr{ std::exchange(other.m_ptr, nullptr) }, 
          m_ctrlBlock{ std::exchange(other.m_ctrlBlock, nullptr) }
    {}

    explicit shared_ptr(weak_ptr<T>& other) 
        : m_ptr{ other.m_ptr }, m_ctrlBlock{ other.m_ctrlBlock } 
    {
        assert_enforce<std::bad_weak_ptr>(other.expired(), "The weak_ptr has expired.");
        ++m_ctrlBlock->m_refCount;
    }

    ~shared_ptr() { decrement_reference(); }

    shared_ptr& operator=(const shared_ptr& other) noexcept 
    {
        if(this == &other)
            return *this;
        
        decrement_reference();
        m_ptr = other.m_ptr;
        m_ctrlBlock = other.m_ctrlBlock;
        increment_reference();
        return *this;
    }
    
    shared_ptr& operator=(shared_ptr&& other) noexcept 
    {
        if(this == &other)
            return *this;
        
        decrement_reference();
        m_ctrlBlock = std::exchange(other.m_ctrlBlock, nullptr);
        m_ptr = std::exchange(other.m_ptr, nullptr);

        return *this;
    }

    shared_ptr& operator=(std::nullptr_t)
    {
        if(m_ctrlBlock == nullptr)
            return *this;
        
        decrement_reference();
        return *this;
    }

    T* get() const noexcept { return m_ptr; }
    T* operator*() const noexcept { return *m_ptr; }
    T* operator->() const noexcept { return m_ptr; }
    explicit operator bool() const noexcept { return m_ptr != nullptr && m_ctrlBlock != nullptr; }

    int use_count() const noexcept { return (m_ctrlBlock) ? m_ctrlBlock->m_refCount : 0; }
    void reset() noexcept { decrement_reference(); }

    template<class T> friend void swap(shared_ptr<T>& lhs, shared_ptr<T>& rhs) noexcept;

    friend auto operator<=>(const shared_ptr& lhs, const shared_ptr& rhs) = default;
    friend auto operator==(const shared_ptr& lhs, const shared_ptr& rhs) 
    {
        if(lhs.get() != rhs.get())
            return false;
        
        return (lhs.get() <=> rhs.get()) == 0;
    }

private:
    T* m_ptr;
    Control_Block* m_ctrlBlock;

    void increment_reference()
    {
        ++m_ctrlBlock->m_refCount;
    }

    void decrement_reference()
    {
        if(m_ptr) {
            if(--m_ctrlBlock->m_refCount == 0){
                delete m_ptr;
                if(m_ctrlBlock->m_weakCount == 0){
                    delete m_ctrlBlock;
                }
            }

            m_ptr = nullptr;
            m_ctrlBlock = nullptr;
        }
    }
};

template<class T> void swap(shared_ptr<T>& lhs, shared_ptr<T> rhs) noexcept 
{
    T temp(std::move(lhs));
    lhs = std::move(rhs);
    rhs = std::move(temp);
}

template<class T, class ...Args>
shared_ptr<T> make_shared(Args && ...args)
{
    return shared_ptr<T>(new T(std::forward<Args>(args)...));
}