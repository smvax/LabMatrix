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
    return this->MathVector<MathVector<vector_type>>::get_size();
}

template<typename vector_type>
inline size_t Matrix<vector_type>::getM() const noexcept {
    if (getN() == 0) {
        return 0;
    }
    return this->Vector<MathVector<vector_type>>::operator[](0).get_size();
}

template<typename vector_type>
std::ostream& operator<< (std::ostream&, const Matrix<vector_type>&);

//========= –≈јЋ»«ј÷»я ==========

template<typename vector_type>
Matrix<vector_type>::Matrix() : MathVector<MathVector<vector_type>>() {}
template<typename vector_type>
Matrix<vector_type>::Matrix(size_t N, size_t M) : MathVector<MathVector<vector_type>>() {
    for (size_t i = 1; i <= N; ++i) {
        MathVector<vector_type> row; // сам инициализируетс€ старт индексом 1
        for (size_t j = 1; j <= M; ++j) {
            static_cast<Vector<vector_type>&>(row).push_back(vector_type(0));
        }
        this->push_back(row);
    }
}
template<typename vector_type>
Matrix<vector_type>::Matrix(std::initializer_list<std::initializer_list<vector_type>> list) : MathVector<MathVector<vector_type>>() {
    for (std::initializer_list<vector_type> row_list : list) {
        MathVector<vector_type> row(row_list); // сам инициализируетс€ старт индексом 1
        this->push_back(row);
    }
}
template<typename vector_type>
Matrix<vector_type>::Matrix(const Matrix& other) : MathVector<MathVector<vector_type>>() {
    size_t other_N = other.getN();
    for (size_t i = 1; i <= other_N; ++i) {
        MathVector<vector_type> row = other.MathVector<MathVector<vector_type>>::operator[](i);
        row.set_start_index(1);
        this->push_back(row);
    }
}
template<typename vector_type>
Matrix<vector_type>::Matrix(const MathVector<MathVector<vector_type>>& other) : MathVector<MathVector<vector_type>>() {
    size_t other_N = other.get_size();
    for (size_t i = 1; i <= other_N; ++i) {
        MathVector<vector_type> row = other.MathVector<MathVector<vector_type>>::operator[](i);
        row.set_start_index(1); // принудительно выставл€ем 1 (дл€ обычной матрицы)
        this->push_back(row);
    }
}

template<typename vector_type>
Matrix<vector_type> Matrix<vector_type>::Transposition() const noexcept {
    size_t this_N = (*this).getN();
    size_t this_M = (*this).getM();
    Matrix<vector_type> res;
    for (size_t i = 1; i <= this_M; ++i) {
        MathVector<vector_type> row; // сам инициализируетс€ старт индексом 1
        for (size_t j = 1; j <= this_N; ++j) {
            static_cast<Vector<vector_type>&>(row).push_back(this->MathVector<MathVector<vector_type>>::operator[](j)[i]);
        }
        res.push_back(row);
    }
    return res;
}

template<typename vector_type>
Matrix<vector_type> Matrix<vector_type>::operator*(const Matrix<vector_type>& other) const {
    size_t this_N = (*this).getN();
    size_t this_M = (*this).getM();
    if (this_M != other.getN()) {
        throw std::logic_error("ERROR: Matrices can't be multiplied! Can multiply only [m*n]*[n*p]");
    }
    Matrix<vector_type> otherT = other.Transposition();
    size_t other_M = other.getM();
    Matrix<vector_type> res;
    for (size_t i = 1; i <= this_N; ++i) {
        MathVector<vector_type> row; // сам инициализируетс€ старт индексом 1
        for (size_t j = 1; j <= other_M; ++j) {
            double val = this->MathVector<MathVector<vector_type>>::operator[](i) *
                otherT.MathVector<MathVector<vector_type>>::operator[](j);
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
            if (this->MathVector<MathVector<vector_type>>::operator[](i) != other.MathVector<MathVector<vector_type>>::operator[](i)) {
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
inline std::ostream& operator<< (std::ostream& out, const Matrix<vector_type>& matrix) {
    size_t N = matrix.getN();
    for (size_t i = 1; i <= N; ++i) {
        out << matrix.MathVector<MathVector<vector_type>>::operator[](i) << "\n";
    }
    return out;
}