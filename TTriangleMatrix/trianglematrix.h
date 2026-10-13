#pragma once
#include "matrix.h"
#include "mathvector.h"

template<typename vector_type>
class TriangleMatrix : public MathVector<MathVector<vector_type>> {
public:
    TriangleMatrix();
    TriangleMatrix(size_t N);
    TriangleMatrix(const Matrix<vector_type>& other);
    TriangleMatrix(const MathVector<MathVector<vector_type>>& other);
    TriangleMatrix(std::initializer_list<std::initializer_list<vector_type>> list);
    TriangleMatrix(const TriangleMatrix& other);

    inline size_t getN() const noexcept;
    vector_type getDeterminant() const noexcept;

    bool operator==(const TriangleMatrix<vector_type>& other) const noexcept;
    bool operator!=(const TriangleMatrix<vector_type>& other) const noexcept;

    TriangleMatrix<vector_type> operator*(const TriangleMatrix<vector_type>& other) const;
};

template<typename vector_type>
std::ostream& operator<<(std::ostream&, const TriangleMatrix<vector_type>&);

template<typename vector_type>
inline size_t TriangleMatrix<vector_type>::getN() const noexcept {
    return this->MathVector<MathVector<vector_type>>::get_size();
}

//=======–≈¿À»«¿÷»ﬂ=======

template<typename vector_type>
TriangleMatrix<vector_type>::TriangleMatrix() : MathVector<MathVector<vector_type>>() {}

template<typename vector_type>
TriangleMatrix<vector_type>::TriangleMatrix(size_t N) : MathVector<MathVector<vector_type>>() {
    for (size_t i = 1; i <= N; ++i) {
        MathVector<vector_type> row;
        for (size_t j = i; j <= N; ++j) {
            static_cast<Vector<vector_type>&>(row).push_back(vector_type(0));
        }
        row.set_start_index(i);
        this->push_back(row);
    }
}
template<typename vector_type>
TriangleMatrix<vector_type>::TriangleMatrix(const Matrix<vector_type>& other) : MathVector<MathVector<vector_type>>() {
    size_t N = other.getN();
    for (size_t i = 1; i <= N; ++i) {
        MathVector<vector_type> row;
        for (size_t j = i; j <= N; ++j) {
            static_cast<Vector<vector_type>&>(row).push_back(other[i][j]);
        }
        row.set_start_index(i);
        this->push_back(row);
    }
}
template<typename vector_type>
TriangleMatrix<vector_type>::TriangleMatrix(const MathVector<MathVector<vector_type>>& other) : MathVector<MathVector<vector_type>>() {
    size_t N = other.getN();
    for (size_t i = 1; i <= N; ++i) {
        MathVector<vector_type> row;
        for (size_t j = i; j <= N; ++j) {
            static_cast<Vector<vector_type>&>(row).push_back(other[i][j]);
        }
        row.set_start_index(i);
        this->push_back(row);
    }
}
template<typename vector_type>
TriangleMatrix<vector_type>::TriangleMatrix(std::initializer_list<std::initializer_list<vector_type>> list) : MathVector<MathVector<vector_type>>() {
    size_t current_row = 1;
    for (auto& row_list : list) {
        MathVector<vector_type> row;
        size_t current_col = 1;
        for (auto& elem : row_list) {
            if (current_col < current_row) {
                if (elem != vector_type(0)) {
                    throw std::invalid_argument("ERROR: Initial data has non-zero elements below the main diagonal!");
                }
            }
            else {
                static_cast<Vector<vector_type>&>(row).push_back(elem);
            }
            current_col++;
        }
        row.shrink_to_fit();
        row.set_start_index(current_row);
        this->push_back(row);
        current_row++;
    }
}

template<typename vector_type>
TriangleMatrix<vector_type>::TriangleMatrix(const TriangleMatrix<vector_type>& other) : MathVector<MathVector<vector_type>>(other) {}

template<typename vector_type>
vector_type TriangleMatrix<vector_type>::getDeterminant() const noexcept {
    size_t N = getN();
    if (N == 0) {
        return vector_type(0);
    }
    vector_type res = (*this)[1][1];
    for (size_t i = 2; i <= N; ++i) {
        res *= (*this)[i][i];
    }
    return res;
}

template<typename vector_type>
bool TriangleMatrix<vector_type>::operator==(const TriangleMatrix<vector_type>& other) const noexcept {
    if (getN() != other.getN()) {
        return false;
    }
    size_t N = getN();
    for (size_t i = 1; i <= N; ++i) {
        if (this->MathVector<MathVector<vector_type>>::operator[](i) != other.MathVector<MathVector<vector_type>>::operator[](i)) {
            return false;
        }
    }
    return true;
}

template<typename vector_type>
bool TriangleMatrix<vector_type>::operator!=(const TriangleMatrix<vector_type>& other) const noexcept {
    return !((*this) == other);
}
template<typename vector_type>
TriangleMatrix<vector_type> TriangleMatrix<vector_type>::operator*(const TriangleMatrix<vector_type>& other) const {
    size_t N = getN();
    if (N != other.getN()) {
        throw std::logic_error("ERROR: Triangle matrices can't be multiplied! Can multiply only [n*n]*[n*n]!");
    }
    TriangleMatrix<vector_type> res(N);
    for (size_t i = 1; i <= N; ++i) {
        for (size_t j = i; j <= N; ++j) {
            vector_type sum = vector_type(0);
            for (size_t k = i; k <= j; ++k) {
                sum += this->MathVector<MathVector<vector_type>>::operator[](i)[k] *
                    other.MathVector<MathVector<vector_type>>::operator[](k)[j];
            }
            res.MathVector<MathVector<vector_type>>::operator[](i)[j] = sum;
        }
    }
    return res;
}

template<typename vector_type>
std::ostream& operator<<(std::ostream& out, const TriangleMatrix<vector_type>& tm) {
    size_t N = tm.getN();
    for (size_t i = 1; i <= N; ++i) {
        out << "[ ";
        for (size_t j = 1; j <= N; ++j) {
            if (j < i) {
                out << vector_type(0) << " ";
            }
            else {
                out << tm[i][j] << " ";
            }
        }
        out << "]\n";
    }
    return out;
}
