#pragma once

#include "memdata.h"
#include "vector.h"

template<typename vector_type>
class MathVector : public Vector<vector_type> {
	//size_t start_index; //<--- поле излишне, так как shrink_to_fit() сбрасывает _front
public:
	MathVector(const vector_type* data = nullptr, size_t size = 0);
	MathVector(std::initializer_list<vector_type>);
	MathVector(const MathVector&);
	MathVector(const Vector<vector_type>&);
	~MathVector() = default;
	
	inline size_t get_size() const noexcept;

	MathVector& operator=(const MathVector&);
	MathVector& operator+=(const MathVector&);
	MathVector& operator-=(const MathVector&);
	MathVector operator+(const MathVector&) const;
	MathVector operator-(const MathVector&) const;
	bool operator==(const MathVector&) const noexcept;
	bool operator!=(const MathVector&) const noexcept;

	inline const vector_type operator[](size_t i) const noexcept;
	inline vector_type& operator[](size_t i) noexcept;
	MathVector& operator*=(double) noexcept;
	MathVector operator*(double) const noexcept;
	MathVector& operator/=(double);
	MathVector operator/(double) const;

	template<typename vector_type>
	friend std::ostream& operator<< (std::ostream&, const MathVector<vector_type>&);
	template<typename vector_type>
	friend std::istream& operator>> (std::istream&, MathVector<vector_type>&);
};