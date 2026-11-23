#include <gtest/gtest.h>

#include <cmath>
#include <limits>
#include <memory>

#include "ColVector.h"
#include "Matrix.h"
#include "RowVector.h"

TEST(MatrixTest, AddsMatrices) {
  const Matrix<int> lhs = {{1, 2}, {3, 4}};
  const Matrix<int> rhs = {{5, 6}, {7, 8}};
  const Matrix<int> expected = {{6, 8}, {10, 12}};

  EXPECT_TRUE(lhs + rhs == expected);
}

TEST(MatrixTest, MultipliesMatrices) {
  const Matrix<int> lhs = {{1, 2}, {3, 4}};
  const Matrix<int> rhs = {{5, 6}, {7, 8}};
  const Matrix<int> expected = {{19, 22}, {43, 50}};

  EXPECT_TRUE(lhs * rhs == expected);
}

TEST(MatrixTest, TransposesMatrix) {
  const Matrix<int> matrix = {{1, 2, 3}, {4, 5, 6}};
  const Matrix<int> expected = {{1, 4}, {2, 5}, {3, 6}};

  EXPECT_TRUE(matrix.Transpose() == expected);
}

TEST(MatrixTest, CalculatesDeterminant) {
  const Matrix<double> matrix = {{1.0, 2.0}, {3.0, 4.0}};

  EXPECT_DOUBLE_EQ(matrix.Determinant(), -2.0);
}

TEST(MatrixTest, CalculatesSubmatrixAndCofactor) {
  const Matrix<double> matrix = {
      {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
  const Matrix<double> expected = {{1.0, 3.0}, {7.0, 9.0}};
  const Matrix<int> integerMatrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  const Matrix<int> integerSubmatrix = {{1, 3}, {7, 9}};
  const Matrix<double> zeroDeterminant = {{0.0, 1.0}, {0.0, 1.0}};

  EXPECT_TRUE(matrix.SubMatrix(1, 1) == expected);
  EXPECT_TRUE(integerMatrix.SubMatrix(1, 1) == integerSubmatrix);
  EXPECT_DOUBLE_EQ(matrix.Cofactor(0, 0), -3.0);
  EXPECT_DOUBLE_EQ(Matrix<double>{{5.0}}.Determinant(), 5.0);
  EXPECT_DOUBLE_EQ(zeroDeterminant.Determinant(), 0.0);
}

TEST(MatrixTest, ComparesDimensionsAndValues) {
  const Matrix<int> matrix = {{1, 2}, {3, 4}};
  const Matrix<int> differentRowCount = {{1, 2}};
  const Matrix<int> differentDimensions = {{1, 2, 3}, {4, 5, 6}};
  const Matrix<int> differentValues = {{1, 2}, {3, 5}};
  const Matrix<double> doubleMatrix = {{1.0, 2.0}, {3.0, 4.0}};
  const Matrix<double> differentDoubleDimensions = {{1.0, 2.0}};
  const Matrix<double> differentDoubleValues = {{1.0, 2.0}, {3.0, 5.0}};

  EXPECT_FALSE(matrix == differentRowCount);
  EXPECT_FALSE(matrix == differentDimensions);
  EXPECT_FALSE(matrix == differentValues);
  EXPECT_FALSE(doubleMatrix == differentDoubleDimensions);
  EXPECT_FALSE(doubleMatrix == differentDoubleValues);
}

TEST(MatrixTest, SupportsScalarArithmetic) {
  const Matrix<int> matrix = {{2, 4}, {6, 8}};
  const Matrix<int> other = {{1, 2}, {3, 4}};
  const Matrix<int> difference = {{1, 2}, {3, 4}};
  const Matrix<int> scaled = {{4, 8}, {12, 16}};

  EXPECT_TRUE(matrix - other == difference);
  EXPECT_TRUE(matrix * 2 == scaled);
  EXPECT_TRUE(2 * matrix == scaled);
  EXPECT_TRUE(matrix / 2 == other);
}

TEST(MatrixTest, PerformsDoubleMatrixArithmetic) {
  const Matrix<double> lhs = {{2.0, 4.0}, {6.0, 8.0}};
  const Matrix<double> rhs = {{1.0, 2.0}, {3.0, 4.0}};
  const Matrix<double> sum = {{3.0, 6.0}, {9.0, 12.0}};
  const Matrix<double> difference = {{1.0, 2.0}, {3.0, 4.0}};
  const Matrix<double> product = {{14.0, 20.0}, {30.0, 44.0}};
  const Matrix<double> scaled = {{4.0, 8.0}, {12.0, 16.0}};
  const Matrix<double> transposed = {{2.0, 6.0}, {4.0, 8.0}};

  EXPECT_TRUE(lhs + rhs == sum);
  EXPECT_TRUE(lhs - rhs == difference);
  EXPECT_TRUE(lhs * rhs == product);
  EXPECT_TRUE(lhs * 2.0 == scaled);
  EXPECT_TRUE(lhs / 2.0 == rhs);
  EXPECT_TRUE(lhs.Transpose() == transposed);
}

TEST(MatrixTest, InvertsNonsingularMatrix) {
  const Matrix<double> matrix = {{4.0, 7.0}, {2.0, 6.0}};
  const Matrix<double> inverse = matrix.Inverse();

  EXPECT_NEAR(inverse.Cell(0, 0), 0.6, 1e-12);
  EXPECT_NEAR(inverse.Cell(0, 1), -0.7, 1e-12);
  EXPECT_NEAR(inverse.Cell(1, 0), -0.2, 1e-12);
  EXPECT_NEAR(inverse.Cell(1, 1), 0.4, 1e-12);
}

TEST(MatrixTest, InvertsIntegerIdentityMatrix) {
  const Matrix<int> identity = {{1, 0}, {0, 1}};

  EXPECT_TRUE(identity.Inverse() == identity);
}

TEST(MatrixTest, HandlesNonConformableOperations) {
  const Matrix<double> matrix = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
  const Matrix<double> other = {{1.0, 2.0}, {3.0, 4.0}};
  const Matrix<double> product = matrix * other;
  const Matrix<double> inverse = matrix.Inverse();

  EXPECT_TRUE(std::isnan(product.Cell(0, 0)));
  EXPECT_TRUE(std::isnan(product.Cell(1, 1)));
  EXPECT_TRUE(std::isnan(inverse.Cell(0, 0)));
  EXPECT_TRUE(std::isnan(inverse.Cell(1, 2)));
}

TEST(MatrixTest, HandlesSingularAndNanInverses) {
  const Matrix<double> singular = {{1.0, 2.0}, {2.0, 4.0}};
  const Matrix<double> nanMatrix = {{std::numeric_limits<double>::quiet_NaN()}};
  const Matrix<double> singularInverse = singular.Inverse();
  const Matrix<double> nanInverse = nanMatrix.Inverse();

  EXPECT_TRUE(std::isnan(singularInverse.Cell(0, 0)));
  EXPECT_TRUE(std::isnan(nanInverse.Cell(0, 0)));
}

TEST(MatrixTest, SelectsDeterminantsAndPreservesSource) {
  const Matrix<double> one = {{5.0}};
  const Matrix<double> two = {{0.0, 2.0}, {3.0, 4.0}};
  const Matrix<double> three = {
      {1.0, 2.0, 3.0}, {0.0, 4.0, 5.0}, {1.0, 0.0, 6.0}};
  const Matrix<double> four = {{0.0, 1.0, 0.0, 0.0},
                               {2.0, 0.0, 0.0, 0.0},
                               {0.0, 0.0, 3.0, 0.0},
                               {0.0, 0.0, 0.0, 4.0}};
  const Matrix<double> five = {{0.0, 2.0, 1.0, 0.0, 0.0},
                               {3.0, 0.0, 1.0, 0.0, 0.0},
                               {0.0, 0.0, 4.0, 1.0, 0.0},
                               {0.0, 0.0, 0.0, 5.0, 1.0},
                               {0.0, 0.0, 0.0, 0.0, 6.0}};
  const Matrix<double> original = five;
  EXPECT_DOUBLE_EQ(one.Determinant(), 5.0);
  EXPECT_DOUBLE_EQ(two.Determinant(), -6.0);
  EXPECT_DOUBLE_EQ(three.Determinant(), 22.0);
  EXPECT_DOUBLE_EQ(four.Determinant(), -24.0);
  EXPECT_DOUBLE_EQ(five.Determinant(), -720.0);
  EXPECT_DOUBLE_EQ(five.DeterminantGaussian(), five.DeterminantRecursive());
  EXPECT_TRUE(five == original);
  EXPECT_TRUE(std::isnan(Matrix<double>{{1.0, 2.0}}.Determinant()));
  EXPECT_TRUE(std::isnan(Matrix<double>{{1.0, 2.0}}.DeterminantGaussian()));
  EXPECT_DOUBLE_EQ(
      (Matrix<double>{{0.0, 1.0}, {0.0, 2.0}}.DeterminantGaussian()), 0.0);
}

TEST(MatrixTest, SelectsInversesAndPreservesSource) {
  const Matrix<double> one = {{4.0}};
  const Matrix<double> three = {
      {1.0, 2.0, 3.0}, {0.0, 4.0, 5.0}, {1.0, 0.0, 6.0}};
  const Matrix<double> five = {{0.0, 2.0, 1.0, 0.0, 0.0},
                               {3.0, 0.0, 1.0, 0.0, 0.0},
                               {0.0, 0.0, 4.0, 1.0, 0.0},
                               {0.0, 0.0, 0.0, 5.0, 1.0},
                               {0.0, 0.0, 0.0, 0.0, 6.0}};
  const Matrix<double> original = five;
  EXPECT_DOUBLE_EQ(one.Inverse().Cell(0, 0), 0.25);
  EXPECT_NEAR(three.InverseAdjugate().Cell(0, 0), 24.0 / 22.0, 1e-12);
  for (size_t size = 3; size <= 5; size++) {
    Matrix<double> matrix(size, size);
    for (size_t row = 0; row < size; row++) {
      for (size_t col = 0; col < size; col++) {
        matrix.Cell(row, col) = five.Cell(row, col);
      }
    }
    const Matrix<double> inverse = matrix.Inverse();
    const Matrix<double> product = matrix * inverse;
    for (size_t row = 0; row < size; row++) {
      for (size_t col = 0; col < size; col++) {
        EXPECT_NEAR(product.Cell(row, col), row == col ? 1.0 : 0.0, 1e-12);
      }
    }
  }
  EXPECT_TRUE(five == original);
  const Matrix<double> singular(5, 5);
  EXPECT_TRUE(std::isnan(singular.Inverse().Cell(4, 4)));
  EXPECT_TRUE(std::isnan(singular.InverseGaussJordan().Cell(0, 0)));
  const Matrix<double> rectangular = {{1.0, 2.0}};
  EXPECT_TRUE(std::isnan(rectangular.InverseGaussJordan().Cell(0, 1)));
  const Matrix<double> nonfinite = {
      {std::numeric_limits<double>::quiet_NaN(), 1.0}, {1.0, 0.0}};
  EXPECT_TRUE(std::isnan(nonfinite.InverseGaussJordan().Cell(0, 0)));
}

TEST(MatrixTest, CalculatesRankForRectangularAndIntegerMatrices) {
  const Matrix<double> matrix = {{1, 2, 3}, {2, 4, 6}, {1, 1, 1}};
  const Matrix<double> wide = {{0, 1, 2, 3}, {0, 2, 4, 6}};
  const Matrix<double> tall = {{0, 0}, {1, 2}, {2, 4}};
  const Matrix<int> integers = {{3, 1, 2}, {1, 1, 1}, {4, 2, 3}};
  const Matrix<double> original = matrix;
  EXPECT_EQ(matrix.Rank(), 2U);
  EXPECT_EQ(wide.Rank(), 1U);
  EXPECT_EQ(tall.Rank(), 1U);
  EXPECT_EQ(integers.Rank(), 2U);
  EXPECT_EQ(Matrix<double>(3, 2).Rank(), 0U);
  /* Singularity is judged relative to the matrix scale */
  EXPECT_EQ(Matrix<double>{{std::numeric_limits<double>::epsilon() / 2}}.Rank(),
            1U);
  EXPECT_EQ(Matrix<double>({{1, 0}, {0, std::numeric_limits<double>::epsilon() / 2}})
                .Rank(),
            1U);
  const Matrix<double> smallScale = {{1e-6, 0, 0}, {0, 1e-6, 0}, {0, 0, 1e-6}};
  EXPECT_NEAR(smallScale.Inverse().Cell(0, 0), 1e6, 1e-3);
  EXPECT_TRUE(matrix == original);
  EXPECT_THROW(
      (Matrix<double>{{std::numeric_limits<double>::quiet_NaN()}}.Rank()),
      std::domain_error);
}

TEST(MatrixTest, SupportsEmptyAndIntegerElimination) {
  Matrix<double> empty;
  EXPECT_EQ(empty.Rank(), 0U);
  EXPECT_DOUBLE_EQ(empty.Determinant(), 0.0);
  EXPECT_EQ(empty.Inverse().RowSize(), 0U);
  const Matrix<int> matrix = {{2, 1, 0, 0, 0},
                              {3, 2, 0, 0, 0},
                              {0, 0, 1, 0, 0},
                              {0, 0, 0, 1, 0},
                              {0, 0, 0, 0, 1}};
  EXPECT_EQ(matrix.Determinant(), 1);
  EXPECT_EQ(matrix.Inverse().Cell(0, 0), 2);
  EXPECT_EQ(matrix.Inverse().Cell(0, 1), -1);
  EXPECT_THROW(Matrix<int>(5, 5).Inverse(), std::domain_error);
}

TEST(MatrixTest, EliminatesLargerMatricesAndSmallPivots) {
  Matrix<double> matrix(25, 25);
  for (size_t row = 0; row < 25; row++) {
    matrix.Cell(row, row) = 1.0;
    if (row + 1 < 25) {
      matrix.Cell(row, row + 1) = 0.5;
    }
  }
  EXPECT_DOUBLE_EQ(matrix.Determinant(), 1.0);
  EXPECT_EQ(matrix.Rank(), 25U);
  const Matrix<double> product = matrix * matrix.Inverse();
  for (size_t row = 0; row < 25; row++) {
    for (size_t col = 0; col < 25; col++) {
      EXPECT_NEAR(product.Cell(row, col), row == col ? 1.0 : 0.0, 1e-12);
    }
  }
  Matrix<double> tiny(5, 5);
  for (size_t row = 0; row < 5; row++) {
    tiny.Cell(row, row) = 1.0;
  }
  tiny.Cell(0, 0) = std::numeric_limits<double>::epsilon() / 2;
  EXPECT_DOUBLE_EQ(tiny.Determinant(), 0.0);
  EXPECT_EQ(tiny.Rank(), 4U);
  EXPECT_TRUE(std::isnan(tiny.Inverse().Cell(0, 0)));
}

TEST(MatrixTest, HandlesDivisionByZeroWithoutChangingSource) {
  const Matrix<double> matrix = {{2.0, 4.0}};
  const Matrix<double> result = matrix / 0.0;

  EXPECT_TRUE(std::isnan(result.Cell(0, 0)));
  EXPECT_DOUBLE_EQ(matrix.Cell(0, 0), 2.0);
}

TEST(MatrixTest, ConstructsAndAssignsFromArraysAndPointers) {
  const int values[2][2] = {{1, 2}, {3, 4}};
  const int flatValues[4] = {5, 6, 7, 8};
  const int replacement[1][3] = {{9, 10, 11}};
  const int flatReplacement[3] = {12, 13, 14};

  Matrix<int> fromArray(values);
  EXPECT_EQ(fromArray.Cell(1, 1), 4);

  fromArray = replacement;
  EXPECT_EQ(fromArray.RowSize(), 1U);
  EXPECT_EQ(fromArray.ColSize(), 3U);
  EXPECT_EQ(fromArray.Cell(0, 2), 11);

  Matrix<int> fromPointer(flatValues, 2, 2);
  EXPECT_EQ(fromPointer.c_matrix()[3], 8);
  fromPointer = flatReplacement;
  EXPECT_EQ(fromPointer.Cell(0, 2), 14);
}

TEST(MatrixTest, SupportsDoubleArrayAndPointerAssignment) {
  const double values[2][2] = {{1.0, 2.0}, {3.0, 4.0}};
  const double flatValues[4] = {5.0, 6.0, 7.0, 8.0};
  const double replacement[2][1] = {{9.0}, {10.0}};
  const double flatReplacement[2] = {11.0, 12.0};
  const Matrix<double> expected = {{1.0, 2.0}, {3.0, 4.0}};

  Matrix<double> fromArray(values);
  Matrix<double> fromPointer(flatValues, 2, 2);
  Matrix<double> assigned(1, 1);
  assigned = fromArray;

  fromArray = replacement;
  fromPointer = flatReplacement;

  EXPECT_TRUE(assigned == expected);
  EXPECT_EQ(fromArray.ColSize(), 1U);
  EXPECT_DOUBLE_EQ(fromArray.Cell(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(fromPointer.Cell(0, 1), 12.0);
}

TEST(MatrixTest, CopiesMatrixIndependently) {
  Matrix<int> original = {{1, 2}, {3, 4}};
  Matrix<int> copied = original;
  Matrix<int> assigned(1, 1);
  assigned = original;

  copied.Cell(0, 0) = 10;
  assigned.Cell(0, 0) = 20;
  original = original;

  EXPECT_EQ(original.Cell(0, 0), 1);
  EXPECT_EQ(copied.Cell(0, 0), 10);
  EXPECT_EQ(assigned.Cell(0, 0), 20);

  Matrix<double> doubleMatrix = {{1.0, 2.0}};
  doubleMatrix = doubleMatrix;
  EXPECT_DOUBLE_EQ(doubleMatrix.Cell(0, 1), 2.0);
}

TEST(MatrixTest, DestroysRowsAndDerivedMatricesPolymorphically) {
  Matrix<int> matrix = {{1, 2}, {3, 4}};
  auto row = std::make_unique<Matrix<int>::MatrixRow>(&matrix, 1);
  std::unique_ptr<Matrix<double>> derived = std::make_unique<RowVector<double>>(
      std::initializer_list<double>{1.0, 2.0});
  std::unique_ptr<Matrix<double>> column = std::make_unique<ColVector<double>>(
      std::initializer_list<double>{1.0, 2.0});

  EXPECT_EQ((*row)[0], 3);
  EXPECT_EQ(derived->RowSize(), 1U);
  EXPECT_EQ(column->ColSize(), 1U);
}

TEST(RowVectorTest, CalculatesInnerProduct) {
  const RowVector<double> lhs = {1.0, 2.0, 3.0};
  const RowVector<double> rhs = {4.0, 5.0, 6.0};

  EXPECT_DOUBLE_EQ(lhs.InnerProduct(rhs), 32.0);
}

TEST(RowVectorTest, CalculatesLengthAndCrossProducts) {
  const RowVector<double> vector = {3.0, 4.0};
  const RowVector<double> lhs = {1.0, 2.0, 3.0};
  const RowVector<double> rhs = {4.0, 5.0, 6.0};
  const RowVector<double> e1 = {1.0, 0.0, 0.0, 0.0};
  const RowVector<double> e2 = {0.0, 1.0, 0.0, 0.0};
  const RowVector<double> e3 = {0.0, 0.0, 1.0, 0.0};
  const RowVector<double> invalid = {1.0, 2.0};

  EXPECT_DOUBLE_EQ(vector.Length(), 5.0);

  const RowVector<double> cross = lhs.CrossProduct(rhs);
  EXPECT_DOUBLE_EQ(cross[0], -3.0);
  EXPECT_DOUBLE_EQ(cross[1], 6.0);
  EXPECT_DOUBLE_EQ(cross[2], -3.0);

  const RowVector<double> generalized = e1.CrossProduct(e2, e3);
  EXPECT_DOUBLE_EQ(generalized[0], 0.0);
  EXPECT_DOUBLE_EQ(generalized[1], 0.0);
  EXPECT_DOUBLE_EQ(generalized[2], 0.0);
  EXPECT_DOUBLE_EQ(generalized[3], -1.0);

  EXPECT_TRUE(std::isnan(invalid.CrossProduct(invalid)[0]));
  EXPECT_TRUE(std::isnan(vector.InnerProduct(lhs)));
}

TEST(RowVectorTest, ConstructsAndAssignsFromArraysAndMatrices) {
  const double values[] = {1.0, 2.0, 3.0};
  const double replacement[] = {4.0, 5.0, 6.0};
  RowVector<double> fromArray(values);
  RowVector<double> fromPointer(values, 3);
  RowVector<double> fromMatrix(static_cast<const Matrix<double>&>(fromArray));
  RowVector<double> assigned(1);

  fromPointer = replacement;
  assigned = fromArray;

  EXPECT_DOUBLE_EQ(fromArray.c_vector()[2], 3.0);
  EXPECT_DOUBLE_EQ(fromPointer[0], 4.0);
  EXPECT_DOUBLE_EQ(fromMatrix[1], 2.0);
  EXPECT_DOUBLE_EQ(assigned[2], 3.0);
}

TEST(ColVectorTest, CalculatesInnerProduct) {
  const ColVector<double> lhs = {1.0, 2.0, 3.0};
  const ColVector<double> rhs = {4.0, 5.0, 6.0};

  EXPECT_DOUBLE_EQ(lhs.InnerProduct(rhs), 32.0);
}

TEST(ColVectorTest, CalculatesLengthAndCrossProducts) {
  const ColVector<double> vector = {3.0, 4.0};
  const ColVector<double> lhs = {1.0, 2.0, 3.0};
  const ColVector<double> rhs = {4.0, 5.0, 6.0};
  const ColVector<double> e1 = {1.0, 0.0, 0.0, 0.0};
  const ColVector<double> e2 = {0.0, 1.0, 0.0, 0.0};
  const ColVector<double> e3 = {0.0, 0.0, 1.0, 0.0};
  const ColVector<double> invalid = {1.0, 2.0};

  EXPECT_DOUBLE_EQ(vector.Length(), 5.0);

  const ColVector<double> cross = lhs.CrossProduct(rhs);
  EXPECT_DOUBLE_EQ(cross[0], -3.0);
  EXPECT_DOUBLE_EQ(cross[1], 6.0);
  EXPECT_DOUBLE_EQ(cross[2], -3.0);

  const ColVector<double> generalized = e1.CrossProduct(e2, e3);
  EXPECT_DOUBLE_EQ(generalized[0], 0.0);
  EXPECT_DOUBLE_EQ(generalized[1], 0.0);
  EXPECT_DOUBLE_EQ(generalized[2], 0.0);
  EXPECT_DOUBLE_EQ(generalized[3], -1.0);

  EXPECT_TRUE(std::isnan(invalid.CrossProduct(invalid)[0]));
  EXPECT_TRUE(std::isnan(vector.InnerProduct(lhs)));
}

TEST(ColVectorTest, ConstructsAndAssignsFromArraysAndMatrices) {
  const double values[] = {1.0, 2.0, 3.0};
  const double replacement[] = {4.0, 5.0, 6.0};
  ColVector<double> fromArray(values);
  ColVector<double> fromPointer(values, 3);
  ColVector<double> fromMatrix(static_cast<const Matrix<double>&>(fromArray));
  ColVector<double> assigned(1);

  fromPointer = replacement;
  assigned = fromArray;

  EXPECT_DOUBLE_EQ(fromArray.c_vector()[2], 3.0);
  EXPECT_DOUBLE_EQ(fromPointer[0], 4.0);
  EXPECT_DOUBLE_EQ(fromMatrix[1], 2.0);
  EXPECT_DOUBLE_EQ(assigned[2], 3.0);
}
