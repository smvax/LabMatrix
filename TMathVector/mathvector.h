#pragma once
#include "memdata.h"
#include "vector.h"

template<typename vector_type>
class MathVector : public Vector<vector_type> {
	//size_t start_index; //<--- поле излишне, так как shrink_to_fit() сбрасывает _front
public:
	MathVector();
	MathVector(const vector_type* data, size_t size);
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
	double operator*(const MathVector&) const;

	inline const vector_type operator[](size_t i) const noexcept;
	inline vector_type& operator[](size_t i) noexcept;
	MathVector& operator*=(double) noexcept;
	MathVector operator*(double) const noexcept;
	MathVector& operator/=(double);
	MathVector operator/(double) const;
};

template<typename vector_type>
inline size_t MathVector<vector_type>::get_size() const noexcept {
	return this->Vector<vector_type>::get_size();
}

template<typename vector_type>
const vector_type MathVector<vector_type>::operator[](size_t i) const noexcept;
template<typename vector_type>
vector_type& MathVector<vector_type>::operator[](size_t i) noexcept;

//============–≈јЋ»«ј÷»я=============
template<typename vector_type>
MathVector<vector_type>::MathVector() : Vector<vector_type>() {
	this->shrink_to_fit();
}
template<typename vector_type>
MathVector<vector_type>::MathVector(const vector_type* data, size_t size) : Vector<vector_type>(data, size) {
	this->shrink_to_fit();
}
template<typename vector_type>
MathVector<typename vector_type>::MathVector(std::initializer_list<vector_type> list) : Vector<vector_type>(list) {
	this->shrink_to_fit();
}
template<typename vector_type>
MathVector<vector_type>::MathVector(const MathVector& other) : Vector<vector_type>(other) {
	this->shrink_to_fit();
}
template<typename vector_type>
MathVector<vector_type>::MathVector(const Vector<vector_type>& other) : Vector<vector_type>(other) {
	this->shrink_to_fit();
}

template<typename vector_type>
MathVector<vector_type>& MathVector<vector_type>::operator=(const MathVector<vector_type>& other) {
	if (this != &other) {
		this->Vector<vector_type>::operator=(other);
	}
	return (*this);
}
template<typename vector_type>
MathVector<vector_type>& MathVector<vector_type>::operator+=(const MathVector<vector_type>& other) {
	if (this->get_size() != other.get_size()) {
		throw std::logic_error("ERROR: Two MathVectors being added have unequal sizes!");
	}
	size_t size = this->get_size();
	for (size_t i = 1; i <= size; ++i) {
		(*this)[i] += other[i];
	}
	return (*this);
}
template<typename vector_type>
MathVector<vector_type>& MathVector<vector_type>::operator-=(const MathVector<vector_type>& other) {
	if (this->get_size() != other.get_size()) {
		throw std::logic_error("ERROR: Two MathVectors being substracted have unequal sizes!");
	}
	size_t size = this->get_size();
	for (size_t i = 1; i <= size; ++i) {
		(*this)[i] -= other[i];
	}
	return (*this);
}
template<typename vector_type>
MathVector<vector_type> MathVector<vector_type>::operator+(const MathVector<vector_type>& other) const {
	MathVector<vector_type> mv_summ(*this);
	mv_summ += other; //<--- operator+=
	return (mv_summ);
}
template<typename vector_type>
MathVector<vector_type> MathVector<vector_type>::operator-(const MathVector<vector_type>& other) const {
	MathVector<vector_type> mv_diff(*this);
	mv_diff -= other; //<--- operator-=
	return (mv_diff);
}
template<typename vector_type>
bool MathVector<vector_type>::operator==(const MathVector<vector_type>& other) const noexcept {
	if (this != &other) {
		size_t size = this->get_size();
		if (size != other.get_size()) {
			return false;
		}
		for (size_t i = 1; i <= size; ++i) {
			if ((*this)[i] != other[i]) {
				return false;
			}
		}
	}
	return true;
}
template<typename vector_type>
bool MathVector<vector_type>::operator!=(const MathVector<vector_type>& other) const noexcept {
	return !((*this) == other); //<--- operator==
}
template<typename vector_type>
double MathVector<vector_type>::operator*(const MathVector& other) const {
	if ((*this).get_size() != other.get_size()) {
		throw std::logic_error("ERROR: MathVectors have different dimensions!");
	}
	double res = 0;
	size_t size = this->get_size();
	for (int i = 1; i <= size; ++i) {
		res += (*this)[i] * other[i];
	}
	return res;
}
template<typename vector_type>
MathVector<vector_type>& MathVector<vector_type>::operator*=(double scalar) noexcept {
	size_t size = this->get_size();
	for (size_t i = 1; i <= size; ++i) {
		(*this)[i] *= scalar;
	}
	return *this;
}
template<typename vector_type>
MathVector<vector_type> MathVector<vector_type>::operator*(double scalar) const noexcept {
	MathVector<vector_type> mv_res(*this);
	mv_res *= scalar; //<--- operator*=
	return mv_res;
}
template<typename vector_type>
MathVector<vector_type>& MathVector<vector_type>::operator/=(double scalar) {
	if (scalar == 0) {
		throw std::logic_error("ERROR: Division by zero!");
	}
	size_t size = this->get_size();
	for (size_t i = 1; i <= size; ++i) {
		(*this)[i] /= scalar;
	}
	return *this;
}
template<typename vector_type>
MathVector<vector_type> MathVector<vector_type>::operator/(double scalar) const {
	MathVector<vector_type> mv_res(*this);
	mv_res /= scalar; //<--- operator/=
	return mv_res;
}

template<typename vector_type>
std::ostream& operator<<(std::ostream& out, const MathVector<vector_type>& mv) {
	Vector<vector_type> obj(mv);
	out << obj;
	return out;
}
template<typename vector_type>
std::istream& operator>>(std::istream& in, MathVector<vector_type>& mv) {
	Vector<vector_type> obj;
	in >> obj;
	mv = MathVector<vector_type>(obj);
	return in;
}

template<typename vector_type>
const vector_type MathVector<vector_type>::operator[](size_t i) const noexcept {
	return this->Vector<vector_type>::operator[](i - 1);
}
template<typename vector_type>
vector_type& MathVector<vector_type>::operator[](size_t i) noexcept {
	return this->Vector<vector_type>::operator[](i - 1);
}

//// инстанцирование шаблона (генераци€ объектного файла под определенный тд):
//template class MathVector<double>;
////template class Vector<MathVector<double>>;
//template std::ostream& operator<<(std::ostream& out, const MathVector<double>& mv);
//template std::istream& operator>>(std::istream& in, MathVector<double>& mv);
////template std::ostream& operator<<(std::ostream& out, const MathVector<MathVector<double>>& mv);
////template std::istream& operator>>(std::istream& in, MathVector<MathVector<double>>& mv);