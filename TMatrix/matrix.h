#pragma once
#include "mathvector.h"

template<typename vector_type>
class Matrix : public MathVector<MathVector<vector_type>> {
public:
	Matrix();
	Matrix(size_t, size_t);
	Matrix(std::initializer_list<std::initializer_list<vector_type>>);
	Matrix(const Matrix&);
	Matrix(const MathVector<MathVector<vector_type>>&);

	inline size_t getN() const noexcept;
	inline size_t getM() const noexcept;
	Matrix<vector_type> Transposition() const noexcept;

	Matrix<vector_type> operator*(const Matrix<vector_type>&) const;
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
std::ostream& operator<< (std::ostream&, Matrix<vector_type>&);

//=========РЕАЛИЗАЦИЯ==========

template<typename vector_type>
Matrix<vector_type>::Matrix() : MathVector<MathVector<vector_type>>() {}
template<typename vector_type>
Matrix<vector_type>::Matrix(size_t N, size_t M) : MathVector<MathVector<vector_type>>() {
	for (size_t i = 1; i <= N; ++i) {
		MathVector<vector_type> row;
		for (size_t j = 1; j <= M; ++j) {
			static_cast<Vector<vector_type>&>(row).push_back(vector_type(0));
		}
		this->push_back(row);
	}
}
template<typename vector_type>
Matrix<vector_type>::Matrix(std::initializer_list<std::initializer_list<vector_type>> list) : MathVector<MathVector<vector_type>>() {
	for (std::initializer_list<vector_type> row : list) {
		this->push_back(MathVector<vector_type>(row));
	}
}
template<typename vector_type>
Matrix<vector_type>::Matrix(const Matrix& other) :MathVector<MathVector<vector_type>>(other) {}
template<typename vector_type>
Matrix<vector_type>::Matrix(const MathVector<MathVector<vector_type>>& other) : MathVector<MathVector<vector_type>>(other) {}

template<typename vector_type>
Matrix<vector_type> Matrix<vector_type>::Transposition() const noexcept {
	size_t this_N = (*this).getN();
	size_t this_M = (*this).getM();
	Matrix<vector_type> res;
	for (size_t i = 1; i <= this_M; ++i) {
		MathVector<vector_type> row;
		for (size_t j = 1; j <= this_N; ++j) {
			// напрямую элемент из родительского Vector, иначе компилятор говнится ^^
			static_cast<Vector<vector_type>&>(row).push_back((*this)[j][i]);
		}
		res.push_back(row);
	}
	return res;
}

template<typename vector_type>
Matrix<vector_type> Matrix<vector_type>::operator*(const Matrix<vector_type>& other)const {
	size_t this_N = (*this).getN();
	size_t this_M = (*this).getM();
	if (this_M != other.getN()) {
		throw std::logic_error("ERROR: Matrices can't be multiplied! Can multiply only [m*n]*[n*p]");
	}
	Matrix<vector_type> otherT = other.Transposition();
	size_t other_M = other.getM();
	Matrix<vector_type> res;
	for (size_t i = 1; i <= this_N; ++i) {
		MathVector<vector_type> row;
		for (size_t j = 1; j <= other_M; ++j) {
			double val = (*this)[i] * otherT[j];
			static_cast<Vector<vector_type>&>(row).push_back(val);
		}
		res.push_back(row);
	}
	return res;
}
template<typename vector_type>
bool Matrix<vector_type>::operator==(const Matrix<vector_type>& other) const noexcept {
	if (this != &other) {
		if ((*this).getM() != other.getM() || (*this).getN() != other.getN()) {
			return false;
		}
		size_t other_N = other.getN();
		for (size_t i = 1; i <= other_N; ++i) {
			if ((*this)[i] != other[i]) {
				return false;
			}
		}
	}
	return true;
}
template<typename vector_type>
bool Matrix<vector_type>::operator!=(const Matrix<vector_type>& other) const noexcept {
	return !((*this) == other);
}

template<typename vector_type>
std::ostream& operator<< (std::ostream& out, Matrix<vector_type>& matrix) {
	size_t N = matrix.getN();
	for (size_t i = 1; i <= N; ++i) {
		out << matrix[i] << "\n";
	}
	return out;
}
////инстанцирование шаблона (генерация объектного файла под определенный тд):
//template class Matrix<double>;
//template std::ostream& operator<<(std::ostream&, Matrix<double>&);
