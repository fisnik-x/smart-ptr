/*++

unique_ptr.hpp

@author:
	Fisnik

Copyright (c) Fisnik. All rights reserved.
--*/
#pragma once

#include <cassert>
#include <algorithm>

template<typename T>
class unique_ptr{
public:
	constexpr unique_ptr() noexcept = default;
	explicit unique_ptr(T* data) : m_ptr{data}{}
	unique_ptr(unique_ptr&& other) noexcept 
		: m_ptr{other.m_ptr} {}
	~unique_ptr() {}

	unique_ptr& operator=(const unique_ptr& other){}
	unique_ptr& operator=(unique_ptr&& other) {}

	T* get() const noexcept{}
	T* operator*() const noexcept{}
	T* operator->() const noexcept{}
	explicit operator* bool() const explicit{}
	T* release() noexcept {}
	void reset(T* data) noexcept{}

	template<class T> friend void swap(unique_ptr<T>& lhs, unique_ptr<T>& rhs) noexcept;

private:
	T* m_ptr{nullptr};
};

template<class T> void swap(unique_ptr<T>& lhs, unique_ptr<T> rhs) noexcept {}