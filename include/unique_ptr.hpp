// Copyright (C) Fisnik. All rights reserved.
#pragma once

#include <cassert>
#include <memory>

template<typename T, typename D = std::default_delete<T>>
class unique_ptr{
public:
	constexpr unique_ptr() noexcept = default;
	constexpr unique_ptr(std::nullptr_t) noexcept {}
	explicit unique_ptr(T* data) : m_ptr{data}{}
	explicit unique_ptr(T*, D){}
	
	constexpr unique_ptr(unique_ptr&& other) noexcept 
		: m_ptr{other.m_ptr} {}

	template<class U, class E>
	constexpr unique_ptr(unique_ptr<U, E>&& other) noexcept {}

	constexpr ~unique_ptr() {}

	unique_ptr& operator=(const unique_ptr& other){}
	unique_ptr& operator=(unique_ptr&& other) noexcept {}
	unique_ptr& operator=(std::nullptr_t) noexcept {}

	T* operator*() const noexcept{}
	T* operator->() const noexcept{}
	explicit operator* bool() const explicit{}
	T* release() noexcept {}
	void reset(T* data) noexcept{}

	template<class T> friend void swap(unique_ptr<T>& lhs, unique_ptr<T>& rhs) noexcept;

	T* get() const noexcept{}
	D& get_deleter() noexcept{}
	const D& get_deleter() const noexcept{}
	explicit operator bool() const noexcept {}

private:
	T* m_ptr{nullptr};
	D m_deleter;
};

template<class T> void swap(unique_ptr<T>& lhs, unique_ptr<T> rhs) noexcept {}
