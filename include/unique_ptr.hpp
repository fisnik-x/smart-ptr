/*++
    unique_ptr.hpp
    
    Author: Fisnik
    Copyright (C) Fisnik. All rights reserved.

    Abstract:
    
    
    
    This source code is licensed under the MIT license found in the
    LICENSE file in the root directory of this source tree. 
--*/
#pragma once

#include <cassert>
#include <memory>

template<typename T, typename D = std::default_delete<T>>
class unique_ptr{
public:
	constexpr unique_ptr() noexcept = default;
	explicit unique_ptr(T* data) : m_ptr{data}{}
	explicit unique_ptr(T*, D){}
	unique_ptr(unique_ptr&& other) noexcept 
		: m_ptr{other.m_ptr} {}
	~unique_ptr() {}

	unique_ptr& operator=(const unique_ptr& other){}
	unique_ptr& operator=(unique_ptr&& other) {}

	T* get() const noexcept{}
	D get_deleter const noexcept{}
	T* operator*() const noexcept{}
	T* operator->() const noexcept{}
	explicit operator* bool() const explicit{}
	T* release() noexcept {}
	void reset(T* data) noexcept{}

	template<class T> friend void swap(unique_ptr<T>& lhs, unique_ptr<T>& rhs) noexcept;

private:
	T* m_ptr{nullptr};
	D m_deleter;
};

template<class T> void swap(unique_ptr<T>& lhs, unique_ptr<T> rhs) noexcept {}
