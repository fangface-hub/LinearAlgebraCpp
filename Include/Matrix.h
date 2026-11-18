#ifndef __MATRIX_H__
#define __MATRIX_H__
#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <limits>
#include <memory>
#include <new>

/**
 * @brief Matrix
 */
template <class T>
class Matrix {
 public:
  /**
   * @brief Row
   */
  class MatrixRow {
   public:
    /**
     * @brief Constructor
     * @param [in] a_matrix Pointer to the matrix
     * @param [in] a_row Row
     */
    MatrixRow(const Matrix<T>* a_matrix, const size_t& a_row);

    /**
     * @brief Destructor
     */
    virtual ~MatrixRow();

    /**
     * @brief Subscript operator
     * @param [in] col Column
     * @return Reference to the specified column
     */
    T& operator[](const size_t& col) const;

    /**
     * @brief Assignment operator
     * @param [in] src
     * @return Assignment result
     */
    MatrixRow& operator=(const MatrixRow& src);

   private:
    const Matrix<T>* m_matrix; /**< Pointer to the matrix */
    size_t m_row;              /**< Row */

    /**
     * @brief Constructor
     * @remarks Do not use
     */
    MatrixRow();
  };

  /**
   * @brief Constructor
   * @param [in] a_matrix Pointer to the matrix
   * @param [in] a_rowSize Number of rows
   * @param [in] a_colSize Number of columns
   */
  Matrix(const T* a_matrix, const size_t& a_rowSize, const size_t& a_colSize);

  /**
   * @brief Constructor
   * @param [in] a_rowSize Number of rows
   * @param [in] a_colSize Number of columns
   */
  Matrix(const size_t& a_rowSize, const size_t& a_colSize);

  /**
   * @brief Constructor
   * @param [in] a_matrix Matrix reference
   */
  template <size_t ROW, size_t COL>
  Matrix(const T (&a_matrix)[ROW][COL]);

  /**
   * @brief Constructor
   * @param [in] a_matrix Matrix initializer list
   */
  Matrix(std::initializer_list<std::initializer_list<T> > a_matrix);

  /**
   * @brief Copy constructor
   * @param [in] src Source
   */
  Matrix(const Matrix<T>& src);

  /**
   * @brief Convert to a C-style array
   * @return Pointer to the first array element
   */
  T* c_matrix(void) const;

  /**
   * @brief Destructor
   */
  virtual ~Matrix();

  /**
   * @brief Get a reference to a cell
   * @param [in] row Row
   * @param [in] col Column
   * @return Reference to the cell
   */
  T& Cell(const size_t& row, const size_t& col) const;

  /**
   * @brief Get row
   * @param [in] row Row
   * @return Row
   */
  MatrixRow Row(const size_t& row) const;

  /**
   * @brief Number of rows
   */
  size_t RowSize(void) const;

  /**
   * @brief Number of columns
   */
  size_t ColSize(void) const;

  /**
   * @brief Submatrix calculation
   * @param [in] delRow Row to remove
   * @param [in] delCol Column to remove
   * @return Matrix with the specified row and column removed
   */
  Matrix<T> SubMatrix(const size_t& delRow, const size_t& delCol) const;

  /**
   * @brief Determinant calculation
   * @param [in] squareMatrix Square matrix
   * @return Determinant
   */
  T Determinant(void) const;

  /**
   * @brief Cofactor calculation
   * @param [in] squareMatrix Square matrix
   * @param [in] row Row
   * @param [in] col Column
   * @return Cofactor
   */
  T Cofactor(const size_t& row, const size_t& col) const;

  /**
   * @brief Inverse matrix calculation
   * @return Inverse matrix
   */
  Matrix<T> Inverse(void) const;

  /**
   * @brief Transposed matrix
   * @return Transposed matrix
   */
  Matrix<T> Transpose(void) const;

  /**
   * @brief Subscript operator
   * @param [in] row Row
   * @return Row
   */
  MatrixRow operator[](const size_t& row) const;

  /**
   * @brief Assignment operator
   * @param [in] src Source
   * @return Assignment result
   */
  Matrix<T>& operator=(const Matrix<T>& src);

  /**
   * @brief Assignment operator
   * @param [in] src Source
   * @return Assignment result
   */
  Matrix<T>& operator=(const T* src);

  /**
   * @brief Assignment operator
   * @param [in] src Source
   * @return Assignment result
   */
  template <size_t ROW, size_t COL>
  Matrix<T>& operator=(const T (&src)[ROW][COL]);

  /**
   * @brief Addition operator
   * @param [in] src Source
   * @return Addition result
   */
  Matrix<T> operator+(const Matrix<T>& src) const;

  /**
   * @brief Subtraction operator
   * @param [in] src Source
   * @return Subtraction result
   */
  Matrix<T> operator-(const Matrix<T>& src) const;

  /**
   * @brief Multiplication operator
   * @param [in] src Source
   * @return Multiplication result
   */
  Matrix<T> operator*(const Matrix<T>& src) const;

  /**
   * @brief Multiplication operator
   * @param [in] src Source
   * @return Multiplication result
   */
  Matrix<T> operator*(const T& src) const;

  /**
   * @brief Division operator
   * @param [in] src Source
   * @return Division result
   */
  Matrix<T> operator/(const T& src) const;

 protected:
  std::unique_ptr<T[]> m_matrix; /**< Pointer to the first matrix element */
  size_t m_rowSize;              /**< Number of rows */
  size_t m_colSize;              /**< Number of columns */

  /**
   * @brief Constructor
   * @remarks Do not use
   */
  Matrix();

  /**
   * @brief Initialize object
   */
  void Init(void);

  /**
   * @brief Fill with a value
   * @param [in] val Value
   */
  void Fill(const T& val);

  /**
   * @brief Create object
   * @param [in] a_rowSize Number of rows
   * @param [in] a_colSize Number of columns
   * @return Status
   * @retval true:success,false:failure
   */
  bool Create(const size_t& a_rowSize, const size_t& a_colSize);

  /**
   * @brief Destroy object
   */
  void Destroy(void);
};

template <class T>
Matrix<T> operator*(const T src1, const Matrix<T>& src2) {
  Matrix<T> ret = src2 * src1;
  return ret;
}

/**
 * @brief Equality operator
 * @param [in] src Source
 * @return Comparison result
 * @retval true:equal,false:not equal
 */
template <class T>
bool operator==(const Matrix<T>& src1, const Matrix<T>& src2) {
  bool ret = true;
  if ((src1.RowSize() != src2.RowSize()) ||
      (src1.ColSize() != src2.ColSize())) {
    ret = false;
    return ret;
  }

  for (size_t row = 0; row < src1.RowSize() && ret == true; row++) {
    for (size_t col = 0; col < src1.ColSize() && ret == true; col++) {
      T val = src1[row][col] - src2[row][col];
      if (std::numeric_limits<T>::epsilon() < std::abs(val)) {
        ret = false;
      }
    }
  }
  return ret;
}

/***** Implementation *****/

/**
 * @brief Constructor
 * @param [in] a_matrix Pointer to the matrix
 * @param [in] a_row Row
 */
template <class T>
Matrix<T>::MatrixRow::MatrixRow(const Matrix<T>* a_matrix,
                                const size_t& a_row) {
  m_matrix = a_matrix;
  m_row = a_row;
}

/**
 * @brief Destructor
 */
template <class T>
Matrix<T>::MatrixRow::~MatrixRow() {
  m_matrix = nullptr;
  m_row = 0;
}

/**
 * @brief Subscript operator
 * @param [in] col Column
 * @return Reference to the specified column
 */
template <class T>
T& Matrix<T>::MatrixRow::operator[](const size_t& col) const {
  return m_matrix->Cell(m_row, col);
}

/**
 * @brief Assignment operator
 * @param [in] src
 * @return Assignment result
 */
template <class T>
typename Matrix<T>::MatrixRow& Matrix<T>::MatrixRow::operator=(
    const MatrixRow& src) {
  m_matrix = src.m_matrix;
  m_row = src.m_row;
  return *this;
}

/**
 * @brief Constructor
 * @remarks Do not use
 */
template <class T>
Matrix<T>::MatrixRow::MatrixRow() {
  m_matrix = nullptr;
  m_row = 0;
}

/**
 * @brief Constructor
 * @remarks Do not use
 */
template <class T>
Matrix<T>::Matrix() {
  Init();
}

/**
 * @brief Constructor
 * @param [in] a_matrix Pointer to the matrix
 * @param [in] a_rowSize Number of rows
 * @param [in] a_colSize Number of columns
 */
template <class T>
Matrix<T>::Matrix(const T* a_matrix, const size_t& a_rowSize,
                  const size_t& a_colSize) {
  Init();
  if (Create(a_rowSize, a_colSize) == true) {
    std::copy_n(a_matrix, a_rowSize * a_colSize, m_matrix.get());
  }
}

/**
 * @brief Constructor
 * @param [in] a_rowSize Number of rows
 * @param [in] a_colSize Number of columns
 */
template <class T>
Matrix<T>::Matrix(const size_t& a_rowSize, const size_t& a_colSize) {
  Init();
  if (Create(a_rowSize, a_colSize) == true) {
    Fill(static_cast<T>(0));
  }
}

/**
 * @brief Constructor
 * @param [in] a_matrix Matrix reference
 */
template <class T>
template <size_t ROW, size_t COL>
Matrix<T>::Matrix(const T (&a_matrix)[ROW][COL]) {
  Init();
  if (Create(ROW, COL) == true) {
    for (size_t row = 0; row < ROW; row++) {
      std::copy_n(a_matrix[row], COL, m_matrix.get() + row * COL);
    }
  }
}

/**
 * @brief Constructor
 * @param [in] a_matrix Matrix initializer list
 */
template <class T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T> > a_matrix) {
  size_t rowSize = a_matrix.size();
  size_t colSize = a_matrix.begin()->size();
  Init();
  if (Create(rowSize, colSize) == true) {
    size_t row = 0;
    typename std::initializer_list<std::initializer_list<T> >::iterator rowItr;
    for (rowItr = a_matrix.begin(); rowItr != a_matrix.end(); rowItr++) {
      size_t col = 0;
      typename std::initializer_list<T>::iterator colItr;
      for (colItr = rowItr->begin(); colItr != rowItr->end(); colItr++) {
        Cell(row, col) = *colItr;
        col++;
      }
      row++;
    }
  }
}

/**
 * @brief Copy constructor
 * @param [in] src Source
 */
template <class T>
Matrix<T>::Matrix(const Matrix<T>& src) {
  Init();
  if (Create(src.m_rowSize, src.m_colSize) == true) {
    std::copy_n(src.m_matrix.get(), src.m_rowSize * src.m_colSize,
                m_matrix.get());
  }
}

/**
 * @brief Convert to a C-style array
 * @return Pointer to the first array element
 */
template <class T>
T* Matrix<T>::c_matrix(void) const {
  return m_matrix.get();
}

/**
 * @brief Destructor
 */
template <class T>
Matrix<T>::~Matrix() {
  Destroy();
}

/**
 * @brief Submatrix calculation
 * @param [in] delRow Row to remove
 * @param [in] delCol Column to remove
 * @return Submatrix
 */
template <class T>
Matrix<T> Matrix<T>::SubMatrix(const size_t& delRow,
                               const size_t& delCol) const {
  Matrix<T> ret(m_rowSize - 1, m_colSize - 1);
  size_t dstRow = 0;
  for (size_t srcRow = 0; srcRow < m_rowSize; srcRow++) {
    if (srcRow == delRow) {
      continue;
    }
    size_t dstCol = 0;
    for (size_t srcCol = 0; srcCol < m_colSize; srcCol++) {
      if (srcCol == delCol) {
        continue;
      }
      ret.Cell(dstRow, dstCol) = Cell(srcRow, srcCol);
      dstCol++;
    }
    dstRow++;
  }
  return ret;
}

/**
 * @brief Determinant calculation
 * @param [in] squareMatrix Square matrix
 * @return Determinant
 */
template <class T>
T Matrix<T>::Determinant(void) const {
  /* Single-element case */
  if (m_rowSize == 1 && m_colSize == 1) {
    return Cell(0, 0);
  }
  T ret = static_cast<T>(0);
  /* Expand along row 0 using cofactors */
  for (size_t col = 0; col < m_colSize; col++) {
    /* Skip zero-valued elements */
    if (std::abs(Cell(0, col)) < std::numeric_limits<T>::epsilon()) {
      continue;
    }
    ret += Cell(0, col) * Cofactor(0, col);
  }
  return ret;
}

/**
 * @brief Cofactor
 * @param [in] squareMatrix Square matrix
 * @param [in] row Row
 * @param [in] col Column
 * @return Cofactor
 */
template <class T>
T Matrix<T>::Cofactor(const size_t& row, const size_t& col) const {
  T ret = static_cast<T>(0); /* Return value */
  Matrix<T> subMatrix = SubMatrix(row, col);
  ret = static_cast<T>(pow(-1.0, row + col)) * subMatrix.Determinant();
  return ret;
}

/**
 * @brief Inverse matrix calculation
 * @return Inverse matrix
 */
template <class T>
Matrix<T> Matrix<T>::Inverse(void) const {
  Matrix<T> ret(m_rowSize, m_colSize); /* Return value */
  /* Not a square matrix */
  if (m_rowSize != m_colSize) {
    ret.Fill(NAN);
    return ret;
  }
  T det = Determinant(); /* Determinant */
  /* If the determinant cannot be computed or is approximately zero */
  if (std::isnan(det) || std::abs(det) < std::numeric_limits<T>::epsilon()) {
    ret.Fill(NAN);
    return ret;
  }
  /* Repeat once for each row */
  for (size_t row = 0; row < m_rowSize; row++) {
    /* Repeat once for each column */
    for (size_t col = 0; col < m_colSize; col++) {
      /* Transposed cofactor divided by the determinant */
      ret.Cell(row, col) = Cofactor(col, row) / det;
    }
  }
  return ret;
}

/**
 * @brief Transposed matrix
 * @return Transposed matrix
 */
template <class T>
Matrix<T> Matrix<T>::Transpose(void) const {
  Matrix<T> ret(m_colSize, m_rowSize); /* Return value */
  for (size_t row = 0; row < m_rowSize; row++) {
    for (size_t col = 0; col < m_colSize; col++) {
      ret.Cell(col, row) = Cell(row, col);
    }
  }
  return ret;
}

/**
 * @brief Assignment operator
 * @param [in] src Source matrix
 * @return Assignment result
 */
template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& src) {
  if (this == &src) {
    return *this;
  }

  if (Create(src.m_rowSize, src.m_colSize) == true) {
    std::copy_n(src.m_matrix.get(), src.m_rowSize * src.m_colSize,
                m_matrix.get());
  }
  return *this;
}

/**
 * @brief Assignment operator
 * @param [in] src Source
 * @return Assignment result
 */
template <class T>
Matrix<T>& Matrix<T>::operator=(const T* src) {
  if (m_matrix != nullptr) {
    std::copy_n(src, m_rowSize * m_colSize, m_matrix.get());
  }
  return *this;
}

/**
 * @brief Assignment operator
 * @param [in] src Source
 * @return Assignment result
 */
template <class T>
template <size_t ROW, size_t COL>
Matrix<T>& Matrix<T>::operator=(const T (&src)[ROW][COL]) {
  if (m_matrix == nullptr || m_rowSize != ROW || m_colSize != COL) {
    if (Create(ROW, COL) == false) {
      return *this;
    }
  }

  for (size_t row = 0; row < ROW; row++) {
    std::copy_n(src[row], COL, m_matrix.get() + row * COL);
  }
  return *this;
}

/**
 * @brief Subscript operator
 * @param [in] row Row
 * @return Row
 */
template <class T>
typename Matrix<T>::MatrixRow Matrix<T>::operator[](const size_t& row) const {
  return Row(row);
}

/**
 * @brief Addition operator
 * @param [in] src Source matrix
 * @return Addition result
 */
template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& src) const {
  Matrix<T> ret(*this); /* Return value */
  for (size_t row = 0; row < ret.m_rowSize; row++) {
    for (size_t col = 0; col < ret.m_colSize; col++) {
      ret.Cell(row, col) += src.Cell(row, col);
    }
  }
  return ret;
}

/**
 * @brief Subtraction operator
 * @param [in] src Source matrix
 * @return Subtraction result
 */
template <class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& src) const {
  Matrix<T> ret(*this); /* Return value */
  for (size_t row = 0; row < ret.m_rowSize; row++) {
    for (size_t col = 0; col < ret.m_colSize; col++) {
      ret.Cell(row, col) -= src.Cell(row, col);
    }
  }
  return ret;
}

/**
 * @brief Multiplication operator
 * @param [in] src Source matrix
 * @return Multiplication result
 */
template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& src) const {
  Matrix<T> ret(m_rowSize, src.m_colSize); /* Return value */
  if (m_colSize != src.m_rowSize) {
    ret.Fill(NAN);
    return ret;
  }

  for (size_t row = 0; row < ret.m_rowSize; row++) {
    for (size_t col = 0; col < src.m_colSize; col++) {
      for (size_t rowcol = 0; rowcol < m_colSize; rowcol++) {
        ret.Cell(row, col) += Cell(row, rowcol) * src.Cell(rowcol, col);
      }
    }
  }
  return ret;
}

/**
 * @brief Multiplication operator
 * @param [in] src Source scalar
 * @return Multiplication result
 */
template <class T>
Matrix<T> Matrix<T>::operator*(const T& src) const {
  Matrix<T> ret(*this); /* Return value */
  for (size_t row = 0; row < ret.m_rowSize; row++) {
    for (size_t col = 0; col < ret.m_colSize; col++) {
      ret.Cell(row, col) *= src;
    }
  }
  return ret;
}

/**
 * @brief Division operator
 * @param [in] src Source scalar
 * @return Division result
 */
template <class T>
Matrix<T> Matrix<T>::operator/(const T& src) const {
  Matrix<T> ret(*this); /* Return value */
  if (std::abs(src) < std::numeric_limits<T>::epsilon()) {
    ret.Fill(NAN);
    return ret;
  }

  for (size_t row = 0; row < ret.m_rowSize; row++) {
    for (size_t col = 0; col < ret.m_colSize; col++) {
      ret.Cell(row, col) /= src;
    }
  }
  return ret;
}

/**
 * @brief Get a reference to a cell
 * @param [in] row Row
 * @param [in] col Column
 * @return Reference to the cell
 */
template <class T>
T& Matrix<T>::Cell(const size_t& row, const size_t& col) const {
  T& ret = m_matrix[row * m_colSize + col];
  return ret;
}

/**
 * @brief Get row
 * @param [in] row Row
 * @return Row
 */
template <class T>
typename Matrix<T>::MatrixRow Matrix<T>::Row(const size_t& row) const {
  MatrixRow ret(this, row);
  return ret;
}

/**
 * @brief Number of rows
 */
template <class T>
size_t Matrix<T>::RowSize(void) const {
  return m_rowSize;
}

/**
 * @brief Number of columns
 */
template <class T>
size_t Matrix<T>::ColSize(void) const {
  return m_colSize;
}

/**
 * @brief Initialize object
 */
template <class T>
void Matrix<T>::Init(void) {
  m_matrix.reset();
  m_rowSize = 0;
  m_colSize = 0;
}

/**
 * @brief Fill with a value
 * @param [in] val Value
 */
template <class T>
void Matrix<T>::Fill(const T& val) {
  for (size_t row = 0; row < m_rowSize; row++) {
    for (size_t col = 0; col < m_colSize; col++) {
      Cell(row, col) = val;
    }
  }
}

/**
 * @brief Create object
 * @param [in] a_rowSize Number of rows
 * @param [in] a_colSize Number of columns
 * @return Status
 * @retval true:success,false:failure
 */
template <class T>
bool Matrix<T>::Create(const size_t& a_rowSize, const size_t& a_colSize) {
  bool ret = true;
  Destroy();
  m_rowSize = a_rowSize;
  m_colSize = a_colSize;
  m_matrix.reset(new (std::nothrow) T[m_rowSize * m_colSize]);
  if (m_matrix == nullptr) {
    ret = false;
  }
  return ret;
}

/**
 * @brief Destroy object
 */
template <class T>
void Matrix<T>::Destroy(void) {
  Init();
}

#endif
