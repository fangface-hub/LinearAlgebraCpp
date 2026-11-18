#ifndef __COL_VECTOR_H__
#define __COL_VECTOR_H__
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <vector>

#include "Matrix.h"

/**
 * @brief Column vector
 */
template <class T>
class ColVector : public Matrix<T> {
 public:
  /**
   * @brief Constructor
   * @param [in] a_vector Pointer to the column vector
   * @param [in] a_rowSize Number of rows
   */
  ColVector(const T* a_vector, const size_t& a_rowSize);

  /**
   * @brief Constructor
   * @param [in] a_rowSize Number of rows
   */
  ColVector(const size_t& a_rowSize);

  /**
   * @brief Constructor
   * @param [in] a_vector Array reference
   */
  template <size_t ROW>
  ColVector(const T (&a_vector)[ROW]);

  /**
   * @brief Constructor
   * @param [in] a_vector Vector initializer list
   */
  ColVector(std::initializer_list<T> a_vector);

  /**
   * @brief Copy constructor
   * @param [in] src Source
   */
  ColVector(const ColVector<T>& src);

  /**
   * @brief Copy constructor
   * @param [in] src Source
   */
  ColVector(const Matrix<T>& src);

  /**
   * @brief Convert to a C-style vector
   * @return Pointer to the first array element
   */
  T* c_vector() const;

  /**
   * @brief Destructor
   */
  ~ColVector() override;

  /**
   * @brief Dot product
   * @param [in] src Other column vector
   * @return Dot product
   */
  T InnerProduct(const ColVector<T>& src) const;

  /**
   * @brief Cross product
   * @param [in] head First column vector operand
   * @param [in] tail Remaining column vector operands
   * @return Cross product
   */
  template <typename... Args>
  ColVector<T> CrossProduct(const ColVector<T>& head, Args... tail) const;

  /**
   * @brief Cross product
   * @param [in] src Other column vector
   * @return Cross product
   */
  ColVector<T> CrossProduct(const ColVector<T>& head) const;

  /**
   * @brief Length
   * @return Length
   */
  T Length() const;

  /**
   * @brief Subscript operator
   * @param [in] row Row
   * @return Row
   */
  T& operator[](const size_t& row) const;

  /**
   * @brief Assignment operator
   * @param [in] src Source
   * @return Assignment result
   */
  template <size_t ROW>
  ColVector<T>& operator=(const T (&src)[ROW]);

  /**
   * @brief Assignment operator
   * @param [in] src Source
   * @return Assignment result
   */
  ColVector<T>& operator=(const Matrix<T>& src);

  /**
   * @brief Assignment operator
   * @param [in] src Source
   * @return Assignment result
   */
  ColVector<T>& operator=(const ColVector<T>& src);

  /**
   * @brief Build a matrix
   * @param [in/out] mat Matrix
   * @param [in] col Column index
   * @param [in] head First column vector
   * @param [in] tail Variadic pack of column vectors
   */
  template <typename... Args>
  void CreateMatrix(Matrix<T>& mat, const size_t& col, const ColVector<T>& head,
                    Args... tail) const;

  /**
   * @brief Build a matrix
   * @param [in/out] mat Matrix
   * @param [in] col Column index
   * @param [in] head First column vector
   * @return Resulting matrix
   */
  void CreateMatrix(Matrix<T>& mat, const size_t& col,
                    const ColVector<T>& head) const;
};

/**
 * @brief Constructor
 * @param [in] a_vector Pointer to the column vector
 * @param [in] a_rowSize Number of rows
 */
template <class T>
ColVector<T>::ColVector(const T* a_vector, const size_t& a_rowSize)
    : Matrix<T>(a_vector, a_rowSize, 1) {}

/**
 * @brief Constructor
 * @param [in] a_rowSize Number of rows
 */
template <class T>
ColVector<T>::ColVector(const size_t& a_rowSize) : Matrix<T>(a_rowSize, 1) {}

/**
 * @brief Constructor
 * @param [in] a_vector Array reference
 */
template <class T>
template <size_t ROW>
ColVector<T>::ColVector(const T (&a_vector)[ROW]) : Matrix<T>::Matrix(ROW, 1) {
  for (size_t row = 0; row < ROW; row++) {
    this->Cell(row, 0) = a_vector[row];
  }
}

/**
 * @brief Constructor
 * @param [in] a_vector Vector initializer list
 */
template <class T>
ColVector<T>::ColVector(std::initializer_list<T> a_vector)
    : Matrix<T>::Matrix(a_vector.size(), 1) {
  size_t row = 0;
  typename std::initializer_list<T>::iterator vecItr;

  for (vecItr = a_vector.begin(); vecItr != a_vector.end(); vecItr++) {
    this->Cell(row, 0) = *vecItr;
    row++;
  }
}

/**
 * @brief Copy constructor
 * @param [in] src Source
 */
template <class T>
ColVector<T>::ColVector(const ColVector<T>& src) : Matrix<T>(src) {}

/**
 * @brief Copy constructor
 * @param [in] src Source
 */
template <class T>
ColVector<T>::ColVector(const Matrix<T>& src) : Matrix<T>(src) {}

/**
 * @brief Convert to a C-style vector
 * @return Pointer to the first array element
 */
template <class T>
T* ColVector<T>::c_vector() const {
  return this->c_matrix();
}

/**
 * @brief Destructor
 */
template <class T>
ColVector<T>::~ColVector() {}

/**
 * @brief Dot product
 * @param [in] src Other column vector
 * @return Dot product
 */
template <class T>
T ColVector<T>::InnerProduct(const ColVector<T>& src) const {
  T ret = static_cast<T>(0);
  if (this->RowSize() == src.RowSize()) {
    for (size_t row = 0; row < this->RowSize(); row++) {
      ret += this->Cell(row, 0) * src[row];
    }
  } else {
    ret = NAN;
  }
  return ret;
}

/**
 * @brief Cross product
 * @param [in] head First column vector operand
 * @param [in] tail Remaining column vector operands
 * @return Cross product
 */
template <class T>
template <typename... Args>
ColVector<T> ColVector<T>::CrossProduct(const ColVector<T>& head,
                                        Args... tail) const {
  ColVector<T> ret(this->RowSize());
  Matrix<T> mat(this->RowSize(), this->RowSize());
  for (size_t row = 0; row < this->RowSize(); row++) {
    mat[row][0] = static_cast<T>(1);
  }
  this->CreateMatrix(mat, static_cast<size_t>(1), *this, head, tail...);
  for (size_t row = 0; row < mat.RowSize(); row++) {
    ret[row] =
        static_cast<T>(pow(-1.0, row)) * mat.SubMatrix(row, 0).Determinant();
  }
  return ret;
}

/**
 * @brief Cross product
 * @param [in] src Other column vector
 * @return Cross product
 */
template <class T>
ColVector<T> ColVector<T>::CrossProduct(const ColVector<T>& head) const {
  ColVector<T> ret(this->RowSize());
  if (ret.RowSize() == 3) {
    Matrix<T> mat(3, 3);
    for (size_t row = 0; row < this->RowSize(); row++) {
      mat[row][1] = this->Cell(row, 0);
      mat[row][2] = head[row];
    }
    for (size_t row = 0; row < mat.RowSize(); row++) {
      ret[row] =
          static_cast<T>(pow(-1.0, row)) * mat.SubMatrix(row, 0).Determinant();
    }
  } else {
    ret.Fill(NAN);
  }
  return ret;
}

/**
 * @brief Length
 * @return Length
 */
template <class T>
T ColVector<T>::Length(void) const {
  T ret = static_cast<T>(0);
  for (size_t row = 0; row < this->RowSize(); row++) {
    ret += this->Cell(row, 0) * this->Cell(row, 0);
  }
  ret = std::sqrt(ret);
  return ret;
}

/**
 * @brief Subscript operator
 * @param [in] row Row
 * @return Row
 */
template <class T>
T& ColVector<T>::operator[](const size_t& row) const {
  return this->Cell(row, 0);
}

/**
 * @brief Assignment operator
 * @param [in] src Source
 * @return Assignment result
 */
template <class T>
template <size_t ROW>
ColVector<T>& ColVector<T>::operator=(const T (&src)[ROW]) {
  T matrix[ROW][1] = {
      0,
  };
  /* Copy into a matrix */
  memcpy(&matrix[0][0], &src[0], sizeof(src));

  dynamic_cast<Matrix<T>*>(this)->operator=(matrix);

  return *this;
}

/**
 * @brief Assignment operator
 * @param [in] src Source
 * @return Assignment result
 */
template <class T>
ColVector<T>& ColVector<T>::operator=(const Matrix<T>& src) {
  dynamic_cast<Matrix<T>*>(this)->operator=(src);
  return *this;
}

/**
 * @brief Assignment operator
 * @param [in] src Source
 * @return Assignment result
 */
template <class T>
ColVector<T>& ColVector<T>::operator=(const ColVector<T>& src) {
  dynamic_cast<Matrix<T>*>(this)->operator=(src);
  return *this;
}

/**
 * @brief Build a matrix
 * @param [in/out] mat Matrix
 * @param [in] col Column index
 * @param [in] head First column vector
 * @param [in] tail Variadic pack of column vectors
 * @return Resulting matrix
 */
template <class T>
template <typename... Args>
void ColVector<T>::CreateMatrix(Matrix<T>& mat, const size_t& col,
                                const ColVector<T>& head, Args... tail) const {
  for (size_t row = 0; row < mat.RowSize(); row++) {
    mat[row][col] = head[row];
  }
  this->CreateMatrix(mat, col + 1, tail...);
  return;
}

/**
 * @brief Build a matrix
 * @param [in/out] mat Matrix
 * @param [in] col Column index
 * @param [in] head First column vector
 * @return Resulting matrix
 */
template <class T>
void ColVector<T>::CreateMatrix(Matrix<T>& mat, const size_t& col,
                                const ColVector<T>& head) const {
  for (size_t row = 0; row < mat.RowSize(); row++) {
    mat[row][col] = head[row];
  }
  return;
}
#endif
