#pragma once
#include "mathvector.h"

template<typename vector_type>
class Matrix : public MathVector<MathVector<vector_type>> {
public:
	inline size_t getN() const noexcept;
	inline size_t getM() const noexcept;
	Matrix();
	Matrix(size_t, size_t);
	Matrix(std::initializer_list<std::initializer_list<vector_type>>);
	Matrix(const Matrix&);
	Matrix(const MathVector<MathVector<vector_type>>&);
	Matrix<vector_type> operator* (const Matrix<vector_type>&) const;
	Matrix<vector_type> Transposition() const noexcept;

	bool operator==(const Matrix<vector_type>& other) const noexcept;
	bool operator!=(const Matrix<vector_type>& other) const noexcept;
};


template<typename vector_type>
inline size_t Matrix<vector_type>::getN() const noexcept {
	return (*this).MathVector<MathVector<vector_type>>::get_size();
}
template<typename vector_type>
inline size_t Matrix<vector_type>::getM() const noexcept {
	if (getN() == 0) {
		return 0;
	}
	return (*this)[0].MathVector<vector_type>::get_size();
}

template<typename vector_type>
std::ostream& operator<< (std::ostream& out, Matrix<vector_type>& matrix) {
	for (size_t i = 0;i < matrix.getN();++i) {
		out << matrix[i];
	}
	return out;
}

template<typename vector_type>
Matrix<vector_type>::Matrix() :MathVector<MathVector<vector_type>>() {}

template<typename vector_type>
Matrix<vector_type>::Matrix(size_t N, size_t M) : MathVector<MathVector<vector_type>>(N) {
	for (size_t i = 0;i < N;++i) {
		(*this)[i] = MathVector<vector_type>(M);
	}
}

template<typename vector_type>
Matrix<vector_type>::Matrix(std::initializer_list<std::initializer_list<vector_type>> list) :MathVector<MathVector<vector_type>>(list.size()) {
	size_t i = 0;
	for (auto row : list) {
		(*this)[i] = MathVector<vector_type>(row);
		++i;
	}
}

template<typename vector_type>
Matrix<vector_type>::Matrix(const Matrix& other) :MathVector<MathVector<vector_type>>(other) {}

template<typename vector_type>
Matrix<vector_type>::Matrix(const MathVector<MathVector<vector_type>>& other) : MathVector<MathVector<vector_type>>(other) {}

template<typename vector_type>
Matrix<vector_type> Matrix<vector_type>::Transposition()const noexcept {
	size_t this_N = (*this).getN();
	size_t this_M = (*this).getM();
	Matrix<vector_type> res(this_M, this_N);
	for (size_t i = 0;i < this_M;++i) {
		for (size_t j = 0;j < this_N;++j) {
			res[i][j] = (*this)[j][i];
		}
	}
	return res;
}

template<typename vector_type>
Matrix<vector_type> Matrix<vector_type>::operator*(const Matrix<vector_type>& other)const {
	size_t this_N = (*this).getN();
	size_t this_M = (*this).getM();
	if (this_M != other.getN()) { throw std::logic_error("No way dimension"); }
	Matrix<vector_type> otherT = other.Transposition();
	size_t otherM = other.getM();
	Matrix<vector_type> res((*this).getN(), otherM);
	for (size_t i = 0;i < this_N;++i) {
		for (size_t j = 0;j < otherM;++j) {
			res[i][j] = (*this)[i] * otherT[j];
		}
	}
	return res;
}

template<typename vector_type>
bool Matrix<vector_type>::operator==(const Matrix<vector_type>& other)const noexcept {
	if ((*this).getM() != other.getM() || (*this).getN() != other.getN()) { return false; }
	for (size_t i = 0;i < other.getN();++i) {
		if ((*this)[i] != other[i]) { return false; }
	}
	return true;
}

template<typename vector_type>
bool Matrix<vector_type>::operator!=(const Matrix<vector_type>& other)const noexcept {
	return !((*this) == other);
}
