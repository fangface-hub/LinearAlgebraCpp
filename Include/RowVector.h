#ifndef __ROW_VECTOR_H__
#define __ROW_VECTOR_H__
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <vector>

#include "Matrix.h"

/**
 * @brief Row vector
 */
template <class T>
class RowVector : public Matrix<T> {
 public:
  /**
   * @brief Constructor
   * @param [in] a_vector Pointer to the row vector
   * @param [in] a_colSize Number of columns
   */
  RowVector(const T* a_vector, const size_t& a_colSize);

  /**
   * @brief Constructor
   * @param [in] a_colSize Number of columns
   */
  RowVector(const size_t& a_colSize);

  /**
   * @brief Constructor
   * @param [in] a_vector Array reference
   */
  template <size_t COL>
  RowVector(const T (&a_vector)[COL]);

  /**
   * @brief Constructor
   * @param [in] a_vector Vector initializer list
   */
  RowVector(std::initializer_list<T> a_vector);

  /**
   * @brief Copy constructor
   * @param [in] src Source
   */
  RowVector(const RowVector<T>& src);

  /**
   * @brief Copy constructor
   * @param [in] src Source
   */
  RowVector(const Matrix<T>& src);

  /**
   * @brief Convert to a C-style vector
   * @return Pointer to the first array element
   */
  T* c_vector(void) const;

  /**
   * @brief Destructor
   */
  ~RowVector() override;

  /**
   * @brief Dot product
   * @param [in] src Other row vector
   * @return Dot product
   */
  T InnerProduct(const RowVector<T>& src) const;

  /**
   * @brief Cross product
   * @param [in] head First row vector operand
   * @param [in] tail Remaining row vector operands
   * @return Cross product
   */
  template <typename... Args>
  RowVector<T> CrossProduct(const RowVector<T>& head, Args... tail) const;

  /**
   * @brief Cross product
   * @param [in] src Other row vector
   * @return Cross product
   */
  RowVector<T> CrossProduct(const RowVector<T>& head) const;

  /**
   * @brief Length
   * @return Length
   */
  T Length(void) const;

  /**
   * @brief Subscript operator
   * @param [in] col Column
   * @return Column
   */
  T& operator[](const size_t& col) const;

  /**
   * @brief Assignment operator
   * @param [in] src Source
   * @return Assignment result
   */
  template <size_t COL>
  RowVector<T>& operator=(const T (&src)[COL]);

  /**
   * @brief Assignment operator
   * @param [in] src Source
   * @return Assignment result
   */
  RowVector<T>& operator=(const Matrix<T>& src);

  /**
   * @brief Assignment operator
   * @param [in] src Source
   * @return Assignment result
   */
  RowVector<T>& operator=(const RowVector<T>& src);

  /**
   * @brief Build a matrix
   * @param [in/out] mat Matrix
   * @param [in] row Row index
   * @param [in] head First row vector
   * @param [in] tail Variadic pack of row vectors
   */
  template <typename... Args>
  void CreateMatrix(Matrix<T>& mat, const size_t& row, const RowVector<T>& head,
                    Args... tail) const;

  /**
   * @brief Build a matrix
   * @param [in/out] mat Matrix
   * @param [in] row Row index
   * @param [in] head First row vector
   * @return Resulting matrix
   */
  void CreateMatrix(Matrix<T>& mat, const size_t& row,
                    const RowVector<T>& head) const;
};

/**
 * @brief Constructor
 * @param [in] a_vector Pointer to the column vector
 * @param [in] a_colSize Number of columns
 */
template <class T>
RowVector<T>::RowVector(const T* a_vector, const size_t& a_colSize)
    : Matrix<T>(a_vector, 1, a_colSize) {}

/**
 * @brief Constructor
 * @param [in] a_colSize Number of columns
 */
template <class T>
RowVector<T>::RowVector(const size_t& a_colSize) : Matrix<T>(1, a_colSize) {}

/**
 * @brief Constructor
 * @param [in] a_vector Array reference
 */
template <class T>
template <size_t COL>
RowVector<T>::RowVector(const T (&a_vector)[COL]) : Matrix<T>::Matrix(1, COL) {
  for (size_t col = 0; col < COL; col++) {
    this->Cell(0, col) = a_vector[col];
  }
}

/**
 * @brief Constructor
 * @param [in] a_vector Vector initializer list
 */
template <class T>
RowVector<T>::RowVector(std::initializer_list<T> a_vector)
    : Matrix<T>::Matrix(1, a_vector.size()) {
  size_t col = 0;
  typename std::initializer_list<T>::iterator vecItr;

  for (vecItr = a_vector.begin(); vecItr != a_vector.end(); vecItr++) {
    this->Cell(0, col) = *vecItr;
    col++;
  }
}

/**
 * @brief Copy constructor
 * @param [in] src Source
 */
template <class T>
RowVector<T>::RowVector(const RowVector<T>& src) : Matrix<T>(src) {}

/**
 * @brief Copy constructor
 * @param [in] src Source
 */
template <class T>
RowVector<T>::RowVector(const Matrix<T>& src) : Matrix<T>(src) {}

/**
 * @brief Convert to a C-style vector
 * @return Pointer to the first array element
 */
template <class T>
T* RowVector<T>::c_vector(void) const {
  return Matrix<T>::c_matrix();
}

/**
 * @brief Destructor
 */
template <class T>
RowVector<T>::~RowVector() {}

/**
 * @brief Dot product
 * @param [in] src Other column vector
 * @return Dot product
 */
template <class T>
T RowVector<T>::InnerProduct(const RowVector<T>& src) const {
  T ret = static_cast<T>(0);
  if (this->ColSize() == src.ColSize()) {
    for (size_t col = 0; col < this->ColSize(); col++) {
      ret += this->Cell(0, col) * src[col];
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
RowVector<T> RowVector<T>::CrossProduct(const RowVector<T>& head,
                                        Args... tail) const {
  RowVector<T> ret(this->ColSize());
  Matrix<T> mat(this->ColSize(), this->ColSize());
  for (size_t col = 0; col < this->ColSize(); col++) {
    mat[0][col] = static_cast<T>(1);
  }
  this->CreateMatrix(mat, static_cast<size_t>(1), *this, head, tail...);
  for (size_t col = 0; col < mat.ColSize(); col++) {
    ret[col] =
        static_cast<T>(pow(-1.0, col)) * mat.SubMatrix(0, col).Determinant();
  }
  return ret;
}

/**
 * @brief Cross product
 * @param [in] src Other column vector
 * @return Cross product
 */
template <class T>
RowVector<T> RowVector<T>::CrossProduct(const RowVector<T>& head) const {
  RowVector<T> ret(this->ColSize());
  if (ret.ColSize() == 3) {
    Matrix<T> mat(3, 3);
    for (size_t col = 0; col < this->ColSize(); col++) {
      mat[1][col] = this->Cell(0, col);
      mat[2][col] = head[col];
    }
    for (size_t col = 0; col < mat.ColSize(); col++) {
      ret[col] =
          static_cast<T>(pow(-1.0, col)) * mat.SubMatrix(0, col).Determinant();
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
T RowVector<T>::Length(void) const {
  T ret = static_cast<T>(0);
  for (size_t col = 0; col < this->ColSize(); col++) {
    ret += this->Cell(0, col) * this->Cell(0, col);
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
T& RowVector<T>::operator[](const size_t& col) const {
  return this->Cell(0, col);
}

/**
 * @brief Assignment operator
 * @param [in] src Source
 * @return Assignment result
 */
template <class T>
template <size_t COL>
RowVector<T>& RowVector<T>::operator=(const T (&src)[COL]) {
  T matrix[1][COL] = {
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
RowVector<T>& RowVector<T>::operator=(const Matrix<T>& src) {
  dynamic_cast<Matrix<T>*>(this)->operator=(src);
  return *this;
}

/**
 * @brief Assignment operator
 * @param [in] src Source
 * @return Assignment result
 */
template <class T>
RowVector<T>& RowVector<T>::operator=(const RowVector<T>& src) {
  dynamic_cast<Matrix<T>*>(this)->operator=(src);
  return *this;
}

/**
 * @brief Build a matrix
 * @param [in/out] mat Matrix
 * @param [in] row Row index
 * @param [in] head First column vector
 * @param [in] tail Variadic pack of column vectors
 * @return Resulting matrix
 */
template <class T>
template <typename... Args>
void RowVector<T>::CreateMatrix(Matrix<T>& mat, const size_t& row,
                                const RowVector<T>& head, Args... tail) const {
  for (size_t col = 0; col < mat.ColSize(); col++) {
    mat[row][col] = head[col];
  }
  this->CreateMatrix(mat, row + 1, tail...);
  return;
}

/**
 * @brief Build a matrix
 * @param [in/out] mat Matrix
 * @param [in] row Row index
 * @param [in] head First column vector
 * @return Resulting matrix
 */
template <class T>
void RowVector<T>::CreateMatrix(Matrix<T>& mat, const size_t& row,
                                const RowVector<T>& head) const {
  for (size_t col = 0; col < mat.ColSize(); col++) {
    mat[row][col] = head[col];
  }
  return;
}
#endif
