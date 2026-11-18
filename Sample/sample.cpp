#include <stdio.h>

#include <iomanip>
#include <iostream>
#include <sstream>

#include "ColVector.h"
#include "Matrix.h"

int main(int argc, char* argv[]) {
  /* Original matrix */
  Matrix<double> mat = {{1.0, -1.0, 3.0}, {5.0, 3.0, -1.0}, {3.0, 5.0, 1.0}};
  Matrix<double> inv = mat.Inverse();     /**< Inverse matrix */
  Matrix<double> trans = mat.Transpose(); /**< Transposed matrix */
  Matrix<double> multi = mat * inv; /**< Matrix multiplied by its inverse */
  ColVector<double> colvec = {2.0, 3.0, 1.0};
  ColVector<double> multi2 = mat * colvec;

  std::stringstream sstr;
  sstr << "mat=" << std::endl << "{" << std::endl;
  for (size_t row = 0; row < mat.RowSize(); row++) {
    sstr << "  {";
    for (size_t col = 0; col < mat.ColSize(); col++) {
      if (0 < col) {
        sstr << ",";
      }
      sstr << std::setfill(' ') << std::setw(8) << std::fixed
           << std::setprecision(4) << mat[row][col];
    }
    sstr << "}" << std::endl;
  }
  sstr << "}" << std::endl << std::endl;

  sstr << "Inverse of mat: inv=" << std::endl << "{" << std::endl;
  for (size_t row = 0; row < inv.RowSize(); row++) {
    sstr << "  {";
    for (size_t col = 0; col < inv.ColSize(); col++) {
      if (0 < col) {
        sstr << ",";
      }
      sstr << std::setfill(' ') << std::setw(8) << std::fixed
           << std::setprecision(4) << inv[row][col];
    }
    sstr << "}" << std::endl;
  }
  sstr << "}" << std::endl << std::endl;

  sstr << "Product of mat and inv: multi =" << std::endl << "{" << std::endl;
  for (size_t row = 0; row < multi.RowSize(); row++) {
    sstr << "  {";
    for (size_t col = 0; col < multi.ColSize(); col++) {
      if (0 < col) {
        sstr << ",";
      }
      sstr << std::setfill(' ') << std::setw(8) << std::fixed
           << std::setprecision(4) << multi[row][col];
    }
    sstr << "}" << std::endl;
  }
  sstr << "}" << std::endl << std::endl;

  sstr << "Transpose of mat: trans=" << std::endl << "{" << std::endl;
  for (size_t row = 0; row < trans.RowSize(); row++) {
    sstr << "  {";
    for (size_t col = 0; col < trans.ColSize(); col++) {
      if (0 < col) {
        sstr << ",";
      }
      sstr << std::setfill(' ') << std::setw(8) << std::fixed
           << std::setprecision(4) << trans[row][col];
    }
    sstr << "}" << std::endl;
  }
  sstr << "}" << std::endl << std::endl;

  sstr << "Column vector: colvec=" << std::endl << "{" << std::endl;
  for (size_t row = 0; row < colvec.RowSize(); row++) {
    sstr << std::setfill(' ') << std::setw(8) << std::fixed
         << std::setprecision(4) << colvec[row];
    if (row + 1 < colvec.RowSize()) {
      sstr << ",";
    }
    sstr << std::endl;
  }
  sstr << "}" << std::endl << std::endl;

  sstr << "Product of mat and colvec: multi2 =" << std::endl
       << "{" << std::endl;
  for (size_t row = 0; row < multi2.RowSize(); row++) {
    sstr << std::setfill(' ') << std::setw(8) << std::fixed
         << std::setprecision(4) << multi2[row];
    if (row + 1 < multi2.RowSize()) {
      sstr << ",";
    }
    sstr << std::endl;
  }
  sstr << "}" << std::endl << std::endl;
  std::cout << sstr.str();
  return 0;
}
