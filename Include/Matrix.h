#ifndef __MATRIX_H__
#define __MATRIX_H__
#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <limits>
#include <memory>
#include <new>
#include <stdexcept>

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
   * @brief Construct an empty matrix
   */
  Matrix();

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
   * @brief Calculate the determinant using an algorithm selected by size
   * @return Determinant, or NaN for a non-square matrix
   * @throw std::domain_error if NaN is needed but T cannot represent it
   */
  T Determinant(void) const;

  /**
   * @brief Calculate the determinant by recursive cofactor expansion
   * @return Determinant
   * @pre The matrix is square
   */
  T DeterminantRecursive(void) const;

  /**
   * @brief Calculate the determinant by Gaussian elimination
   * @return Determinant, or NaN for a non-square matrix
   * @throw std::domain_error if NaN is needed but T cannot represent it
   */
  T DeterminantGaussian(void) const;

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
   * @return Inverse matrix, or a NaN matrix if inversion is impossible
   * @throw std::domain_error if NaN is needed but T cannot represent it
   */
  Matrix<T> Inverse(void) const;

  /**
   * @brief Calculate the inverse using the adjugate matrix
   * @return Inverse matrix, or a NaN matrix if inversion is impossible
   * @remarks Retains the original 1x1 cofactor behavior; use Inverse for 1x1.
   * @throw std::domain_error if NaN is needed but T cannot represent it
   */
  Matrix<T> InverseAdjugate(void) const;

  /**
   * @brief Calculate the inverse using Gauss-Jordan elimination
   * @return Inverse matrix, or a NaN matrix if inversion is impossible
   * @throw std::domain_error if NaN is needed but T cannot represent it
   */
  Matrix<T> InverseGaussJordan(void) const;

  /**
   * @brief Calculate the rank using Gaussian elimination
   * @return Number of pivots in row-echelon form
   * @throw std::domain_error if a matrix element is not finite
   */
  size_t Rank(void) const;

  /**
   * @brief Check whether the matrix is square
   * @return True if the numbers of rows and columns are equal
   */
  bool IsSquare(void) const;

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

 private:
  /**
   * @brief Reduce a working matrix using partial pivoting
   * @param [in,out] matrix Working matrix, optionally augmented
   * @param [in] columns Number of coefficient columns
   * @param [in] reduced Whether to reduce above pivots as well
   * @param [out] pivotProduct Product of pivots, including swap signs
   * @return Number of pivots
   */
  static size_t Eliminate(Matrix<long double>& matrix, size_t columns,
                          bool reduced, long double& pivotProduct);

  /**
   * @brief Return NaN, or report an error when the element type has no NaN
   * @return NaN
   * @throw std::domain_error if the element type cannot represent NaN
   */
  static T InvalidValue(void);
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
 * @brief Construct an empty matrix
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
 * @brief Calculate the determinant using an algorithm selected by size
 */
template <class T>
T Matrix<T>::Determinant(void) const {
  if (!IsSquare()) {
    return InvalidValue();
  }
  if (m_rowSize == 0) {
    return static_cast<T>(0);
  }
  if (m_rowSize == 1) {
    return Cell(0, 0);
  }
  if (m_rowSize == 2) {
    return Cell(0, 0) * Cell(1, 1) - Cell(0, 1) * Cell(1, 0);
  }
  if (m_rowSize == 3) {
    return Cell(0, 0) * Cell(1, 1) * Cell(2, 2) +
           Cell(0, 1) * Cell(1, 2) * Cell(2, 0) +
           Cell(0, 2) * Cell(1, 0) * Cell(2, 1) -
           Cell(0, 2) * Cell(1, 1) * Cell(2, 0) -
           Cell(0, 1) * Cell(1, 0) * Cell(2, 2) -
           Cell(0, 0) * Cell(1, 2) * Cell(2, 1);
  }
  if (m_rowSize == 4) {
    return DeterminantRecursive();
  }
  return DeterminantGaussian();
}

/**
 * @brief Calculate the determinant by recursive cofactor expansion
 */
template <class T>
T Matrix<T>::DeterminantRecursive(void) const {
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
    Matrix<T> subMatrix = SubMatrix(0, col);
    T sign = col % 2 == 0 ? static_cast<T>(1) : static_cast<T>(-1);
    ret += Cell(0, col) * sign * subMatrix.DeterminantRecursive();
  }
  return ret;
}

/**
 * @brief Calculate the determinant by Gaussian elimination
 */
template <class T>
T Matrix<T>::DeterminantGaussian(void) const {
  if (!IsSquare()) {
    return InvalidValue();
  }
  if (m_rowSize == 0) {
    return static_cast<T>(0);
  }
  Matrix<long double> work(m_rowSize, m_colSize);
  for (size_t row = 0; row < m_rowSize; row++) {
    for (size_t col = 0; col < m_colSize; col++) {
      work.Cell(row, col) = static_cast<long double>(Cell(row, col));
      if (!std::isfinite(work.Cell(row, col))) {
        return InvalidValue();
      }
    }
  }
  long double product = 1;
  if (Eliminate(work, m_colSize, false, product) != m_rowSize) {
    return static_cast<T>(0);
  }
  if (std::numeric_limits<T>::is_integer) {
    product = std::round(product);
  }
  return static_cast<T>(product);
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
  if (!IsSquare() || m_rowSize == 0 || m_rowSize == 3 || m_rowSize == 4) {
    return InverseAdjugate();
  }
  if (m_rowSize >= 5) {
    return InverseGaussJordan();
  }
  Matrix<T> ret(m_rowSize, m_colSize);
  T det = Determinant();
  if (std::isnan(det) || det == static_cast<T>(0) ||
      std::abs(det) < std::numeric_limits<T>::epsilon()) {
    ret.Fill(InvalidValue());
    return ret;
  }
  if (m_rowSize == 1) {
    ret.Cell(0, 0) = static_cast<T>(1) / det;
  } else {
    ret.Cell(0, 0) = Cell(1, 1) / det;
    ret.Cell(0, 1) = -Cell(0, 1) / det;
    ret.Cell(1, 0) = -Cell(1, 0) / det;
    ret.Cell(1, 1) = Cell(0, 0) / det;
  }
  return ret;
}

/**
 * @brief Calculate the inverse using the adjugate matrix
 */
template <class T>
Matrix<T> Matrix<T>::InverseAdjugate(void) const {
  Matrix<T> ret(m_rowSize, m_colSize); /* Return value */
  /* Not a square matrix */
  if (m_rowSize != m_colSize) {
    ret.Fill(InvalidValue());
    return ret;
  }
  T det = Determinant(); /* Determinant */
  /* If the determinant cannot be computed or is approximately zero */
  if (std::isnan(det) || det == static_cast<T>(0) ||
      std::abs(det) < std::numeric_limits<T>::epsilon()) {
    ret.Fill(InvalidValue());
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
 * @brief Calculate the inverse using Gauss-Jordan elimination
 */
template <class T>
Matrix<T> Matrix<T>::InverseGaussJordan(void) const {
  Matrix<T> ret(m_rowSize, m_colSize);
  if (!IsSquare()) {
    ret.Fill(InvalidValue());
    return ret;
  }
  Matrix<long double> work(m_rowSize, 2 * m_colSize);
  for (size_t row = 0; row < m_rowSize; row++) {
    for (size_t col = 0; col < m_colSize; col++) {
      work.Cell(row, col) = static_cast<long double>(Cell(row, col));
      if (!std::isfinite(work.Cell(row, col))) {
        ret.Fill(InvalidValue());
        return ret;
      }
    }
    work.Cell(row, m_colSize + row) = 1;
  }
  long double product = 1;
  if (Eliminate(work, m_colSize, true, product) != m_rowSize) {
    ret.Fill(InvalidValue());
    return ret;
  }
  for (size_t row = 0; row < m_rowSize; row++) {
    for (size_t col = 0; col < m_colSize; col++) {
      long double value = work.Cell(row, m_colSize + col);
      if (std::numeric_limits<T>::is_integer) {
        long double rounded = std::round(value);
        long double tolerance = std::numeric_limits<long double>::epsilon() *
                                std::max(1.0L, std::abs(value)) * m_rowSize;
        if (std::abs(value - rounded) <= tolerance) {
          value = rounded;
        }
      }
      ret.Cell(row, col) = static_cast<T>(value);
    }
  }
  return ret;
}

/**
 * @brief Calculate the rank using Gaussian elimination
 */
template <class T>
size_t Matrix<T>::Rank(void) const {
  Matrix<long double> work(m_rowSize, m_colSize);
  for (size_t row = 0; row < m_rowSize; row++) {
    for (size_t col = 0; col < m_colSize; col++) {
      work.Cell(row, col) = static_cast<long double>(Cell(row, col));
      if (!std::isfinite(work.Cell(row, col))) {
        throw std::domain_error(
            "Cannot calculate the rank of a non-finite matrix");
      }
    }
  }
  long double product = 1;
  return Eliminate(work, m_colSize, false, product);
}

/**
 * @brief Check whether the matrix is square
 */
template <class T>
bool Matrix<T>::IsSquare(void) const {
  return m_rowSize == m_colSize;
}

/**
 * @brief Return NaN, or report an error when the element type has no NaN
 */
template <class T>
T Matrix<T>::InvalidValue(void) {
  if (!std::numeric_limits<T>::has_quiet_NaN) {
    throw std::domain_error("Matrix element type cannot represent NaN");
  }
  return std::numeric_limits<T>::quiet_NaN();
}

/**
 * @brief Reduce a working matrix using partial pivoting
 */
template <class T>
size_t Matrix<T>::Eliminate(Matrix<long double>& matrix, size_t columns,
                            bool reduced, long double& pivotProduct) {
  size_t pivotRow = 0;
  pivotProduct = 1;
  long double tolerance =
      static_cast<long double>(std::numeric_limits<T>::epsilon());
  if (std::numeric_limits<T>::is_integer) {
    long double scale = 0;
    for (size_t row = 0; row < matrix.RowSize(); row++) {
      for (size_t col = 0; col < columns; col++) {
        scale = std::max(scale, std::abs(matrix.Cell(row, col)));
      }
    }
    tolerance = std::numeric_limits<long double>::epsilon() * scale *
                std::max(matrix.RowSize(), columns);
  }
  for (size_t col = 0; col < columns && pivotRow < matrix.RowSize(); col++) {
    size_t bestRow = pivotRow;
    for (size_t row = pivotRow + 1; row < matrix.RowSize(); row++) {
      if (std::abs(matrix.Cell(row, col)) >
          std::abs(matrix.Cell(bestRow, col))) {
        bestRow = row;
      }
    }
    long double pivot = matrix.Cell(bestRow, col);
    if (pivot == 0 || std::abs(pivot) < tolerance) {
      continue;
    }
    if (bestRow != pivotRow) {
      for (size_t index = 0; index < matrix.ColSize(); index++) {
        std::swap(matrix.Cell(bestRow, index), matrix.Cell(pivotRow, index));
      }
      pivotProduct = -pivotProduct;
    }
    pivotProduct *= pivot;
    if (reduced) {
      for (size_t index = col; index < matrix.ColSize(); index++) {
        matrix.Cell(pivotRow, index) /= pivot;
      }
    }
    for (size_t row = reduced ? 0 : pivotRow + 1; row < matrix.RowSize();
         row++) {
      if (row == pivotRow) {
        continue;
      }
      long double factor = matrix.Cell(row, col);
      if (!reduced) {
        factor /= pivot;
      }
      matrix.Cell(row, col) = 0;
      for (size_t index = col + 1; index < matrix.ColSize(); index++) {
        matrix.Cell(row, index) -= factor * matrix.Cell(pivotRow, index);
      }
    }
    pivotRow++;
  }
  return pivotRow;
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
