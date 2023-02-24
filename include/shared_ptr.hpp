/*++

shared_ptr.hpp

@author:
	Fisnik

Copyright (c) Fisnik. All rights reserved.
--*/
#pragma once
#include <algorithm>
#include <iterator>
#include <compare>
#include <cassert>
#include <memory>

#include "control_block.hpp"

template<typename T>
class shared_ptr {
public:
    constexpr shared_ptr() : shared_ptr(nullptr) {}
    explicit shared_ptr(T* other) : m_ptr{other}, m_ctrlBlock{new Control_Block}{}
    constexpr shared_ptr(const std::nullptr_t) noexcept : m_ptr{nullptr}, m_ctrlBlock{nullptr}{}

    shared_ptr(shared_ptr&& other) noexcept
        : m_ptr{ other.m_ptr }, m_ctrlBlock{ other.m_ctrlBlock }
    {}

    explicit shared_ptr(weak_ptr<T>& other) 
        : m_ptr{ other.m_ptr }, m_ctrlBlock{ other.m_ctrlBlock } 
    {}

    ~shared_ptr() {}

    shared_ptr& operator=(const shared_ptr& other) noexcept {}
    shared_ptr& operator=(shared_ptr&& other) noexcept {}
    shared_ptr& operator=(std::nullptr_t)

    T* get() const noexcept {}
    T* operator*() const noexcept {}
    T* operator->() const noexcept {}
    explicit operator bool() const noexcept {}

    int use_count() const noexcept {}
    void reset() noexcept {}

    template<class T> friend void swap(shared_ptr<T>& lhs, shared_ptr<T>& rhs) noexcept;

    friend auto operator<=>(const shared_ptr& lhs, const shared_ptr& rhs) = default;
    friend auto operator==(const shared_ptr& lhs, const shared_ptr& rhs) {}

private:
    T* m_ptr;
    Control_Block* m_ctrlBlock;

    void add_reference(){}
    void remove_reference(){}
};

template<class T> void swap(shared_ptr<T>& lhs, shared_ptr<T> rhs) noexcept {}

template<class T, class ...Args>
shared_ptr<T> make_shared(Args && ...args){}