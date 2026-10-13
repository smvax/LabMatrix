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