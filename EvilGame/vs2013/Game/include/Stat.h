
#pragma once

#include "UtH\UtHEngine.hpp"
#include "Util.h"

template<typename T>
class Stat
{
	static_assert(std::is_arithmetic<T>::value, "error: type must be arithmetic");

	T m_min, m_max, m_value;
public:
	Stat() = delete;
	Stat(const T& min, const T& max);
	Stat(const T& min, const T& max, const T& value);
	Stat(const Stat<T>&) = default;
	Stat(Stat<T>&& other);

	const T& getMin() const;
	const T& getMax() const;
	const T& getValue() const;

	void setMin(const T& min);
	void setMax(const T& max);
	void setValue(const T& value);
	void setValuePercent(float percent);

	bool isMin() const;
	bool isMax() const;

	bool operator< (const T& value) const;
	bool operator> (const T& value) const;
	bool operator<=(const T& value) const;
	bool operator>=(const T& value) const;
	bool operator==(const T& value) const;
	bool operator!=(const T& value) const;

	bool operator< (const Stat<T>& other) const;
	bool operator> (const Stat<T>& other) const;
	bool operator<=(const Stat<T>& other) const;
	bool operator>=(const Stat<T>& other) const;
	bool operator==(const Stat<T>& other) const;
	bool operator!=(const Stat<T>& other) const;

	Stat<T>& operator=(const T& value);
	Stat<T>& operator=(T&& value);
	Stat<T>& operator=(const Stat<T>& other);
	Stat<T>& operator=(Stat<T>&& other);

	Stat<T> operator-() const;

	Stat<T> operator-(const T& value) const;
	Stat<T> operator+(const T& value) const;
	Stat<T>& operator+=(const T& value);
	Stat<T>& operator-=(const T& value);

	Stat<T> operator-(const Stat<T>& other) const;
	Stat<T> operator+(const Stat<T>& other) const;
	Stat<T>& operator+=(const Stat<T>& other);
	Stat<T>& operator-=(const Stat<T>& other);
};

template<typename T>
Stat<T>::Stat(const T& min, const T& max)
	:
	m_min(min),
	m_max(util::Math::clamp(max, min, max)),
	m_value(min)
{
}

template<typename T>
Stat<T>::Stat(const T& min, const T& max, const T& value)
	:
	m_min(min),
	m_max(util::Math::clamp(max, min, max)),
	m_value(util::Math::clamp(value, min, max))
{
}

template<typename T>
Stat<T>::Stat(Stat<T>&& other)
	:
	m_min(std::move(other.m_min)),
	m_max(std::move(other.m_max)),
	m_value(std::move(other.m_value))
{
}


template<typename T>
const T& Stat<T>::getMin() const
{
	return m_min;
}

template<typename T>
const T& Stat<T>::getMax() const
{
	return m_max;
}

template<typename T>
const T& Stat<T>::getValue() const
{
	return m_value;
}


template<typename T>
void Stat<T>::setMin(const T& min)
{
	if (m_max < min) m_max = min;
	if (m_value < min) m_value = min;
	m_min = min;
}

template<typename T>
void Stat<T>::setMax(const T& max)
{
	if (m_min > max) m_min = max;
	if (m_value > max) m_value = max;
	m_max = max;
}

template<typename T>
void Stat<T>::setValue(const T& value)
{
	m_value = util::Math::clamp(value, m_min, m_max);
}

template<typename T>
void Stat<T>::setValuePercent(float percent)
{
	m_value = util::Math::lerp(m_min, m_max, util::Math::clamp(percent));
}

template<typename T>
bool Stat<T>::isMin() const
{
	return m_value == m_min;
}

template<typename T>
bool Stat<T>::isMax() const
{
	return m_value == m_max;
}


template<typename T>
bool Stat<T>::operator< (const T& value) const
{
	return m_value < value;
}

template<typename T>
bool Stat<T>::operator> (const T& value) const
{
	return m_value > value;
}

template<typename T>
bool Stat<T>::operator<=(const T& value) const
{
	return m_value <= value;
}

template<typename T>
bool Stat<T>::operator>=(const T& value) const
{
	return m_value >= value;
}

template<typename T>
bool Stat<T>::operator==(const T& value) const
{
	return m_value == value;
}

template<typename T>
bool Stat<T>::operator!=(const T& value) const
{
	return m_value != value;
}


template<typename T>
bool Stat<T>::operator< (const Stat<T>& other) const
{
	return m_value < other.m_value;
}

template<typename T>
bool Stat<T>::operator> (const Stat<T>& other) const
{
	return m_value > other.m_value;
}

template<typename T>
bool Stat<T>::operator<=(const Stat<T>& other) const
{
	return m_value <= other.m_value;
}

template<typename T>
bool Stat<T>::operator>=(const Stat<T>& other) const
{
	return m_value >= other.m_value;
}

template<typename T>
bool Stat<T>::operator==(const Stat<T>& other) const
{
	return m_value == other.m_value;
}

template<typename T>
bool Stat<T>::operator!=(const Stat<T>& other) const
{
	return m_value != other.m_value;
}


template<typename T>
Stat<T>& Stat<T>::operator=(const T& value)
{
	m_value = value;
	return *this;
}

template<typename T>
Stat<T>& Stat<T>::operator=(T&& value)
{
	m_value = std::move(value);
	return *this;
}

template<typename T>
Stat<T>& Stat<T>::operator=(const Stat<T>& other)
{
	m_min = other.m_min;
	m_max = other.m_max;
	m_value = other.m_value;
	return *this;
}

template<typename T>
Stat<T>& Stat<T>::operator=(Stat<T>&& other)
{
	m_min = std::move(other.m_min);
	m_max = std::move(other.m_max);
	m_value = std::move(other.m_value);
	return *this;
}


template<typename T>
Stat<T> Stat<T>::operator-() const
{
	return Stat<T>(m_min, m_max, -m_value);
}

template<typename T>
Stat<T> Stat<T>::operator-(const T& value) const
{
	return Stat<T>(m_min, m_max, m_value - value);
}

template<typename T>
Stat<T> Stat<T>::operator+(const T& value) const
{
	return Stat<T>(m_min, m_max, m_value + value);
}

template<typename T>
Stat<T>& Stat<T>::operator-=(const T& value)
{
	setValue(m_value - value);
	return *this;
}

template<typename T>
Stat<T>& Stat<T>::operator+=(const T& value)
{
	setValue(m_value + value);
	return *this;
}


template<typename T>
Stat<T> Stat<T>::operator-(const Stat<T>& other) const
{
	return Stat<T>(m_min, m_max, m_value - other.m_value);
}

template<typename T>
Stat<T> Stat<T>::operator+(const Stat<T>& other) const
{
	return Stat<T>(m_min, m_max, m_value + other.m_value);
}

template<typename T>
Stat<T>& Stat<T>::operator-=(const Stat<T>& other)
{
	setValue(m_value - other.m_value);
	return *this;
}

template<typename T>
Stat<T>& Stat<T>::operator+=(const Stat<T>& other)
{
	setValue(m_value + other.m_value);
	return *this;
}
