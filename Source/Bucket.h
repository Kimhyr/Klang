#pragma once

#include <string_view>
#include <stdexcept>

#include "Types.h"

namespace Klang {

template<typename Water_T, natptr CAPACITY_T>
class Bucket {
public:
	typedef std::basic_string_view<Water_T> ViewType;

public:
	Bucket() noexcept
		: _end(this->_water) {}
	Bucket(Bucket&&) = delete;
	Bucket(const Bucket& other) noexcept
		: _end(this->begin() + other.end()) {
		copy(other.begin(), other.end(), this->_water);
	}

	Bucket& operator=(Bucket&&) = delete;
	Bucket& operator=(const Bucket& other) noexcept {
		this->_weight = other.weight();
		copy(other.begin(), other.end(), this->_water);
		return *this;
	}

	~Bucket() = default;

public:
	constexpr const Water_T* water() const noexcept { return this->_water; }
	constexpr natptr capacity() const noexcept { return CAPACITY_T; }

	constexpr const Water_T* begin() const noexcept { return this->water(); }
	constexpr const Water_T* end() const noexcept { return this->_end; }
	
	constexpr natptr weight() const noexcept { return this->end() - this->begin(); }
	constexpr bool is_empty() const noexcept { return this->begin() == this->end(); }
	constexpr bool is_full() const noexcept { return this->weight() >= this->capacity(); }

	constexpr Water_T& operator[](intptr index) noexcept { return this->_water[index]; }
	constexpr Water_T& at(natptr index) {
		if (index >= this->weight())
			throw std::out_of_range(__FUNCTION__);
		return this->water()[index];
	}

	constexpr const Water_T& operator[](intptr index) const noexcept { return this->_water[index]; }
	constexpr const Water_T& at(natptr index) const { 
		if (index >= this->weight())
			throw std::out_of_range("");
		return this->water()[index];
	}

public:
	inline bool operator==(const Bucket& other) const noexcept { return equal(this->begin(), this->end(), other.begin()); }

	void put(Water_T&& bit) {
		if (this->is_full())
			throw std::out_of_range(__FUNCTION__);
		*this->_end = bit;
		++this->_end;
	}

	void put(const Water_T& bit) {
		if (this->is_full())
			throw std::out_of_range(__FUNCTION__);
		*this->_end = bit;
		++this->_end;
	}
	
	void pop(natptr count = 1) noexcept {
		if (this->is_empty())
			return;
		do {
			--this->_end;
			this->_end->~Water_T();
		} while (--count && !this->is_empty());
	}

	Water_T* flush() {
		auto water = new Water_T[this->weight()];
		std::copy(this->begin(), this->end(), water);
		return water;
	}

private:
	Water_T _water[CAPACITY_T];
	Water_T* _end;
};

}
