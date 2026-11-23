# LinearAlgebraCpp

A lightweight header-only C++ template library for linear algebra.

LinearAlgebraCpp aims to provide a simple and readable implementation of linear algebra algorithms. The library is intended for education, embedded development, testing, and small-to-medium scale applications where code readability and ease of integration are more important than highly optimized numerical performance.

## Features

### Matrix

- Dynamic matrix size
- Matrix addition
- Matrix subtraction
- Matrix multiplication
- Scalar multiplication
- Scalar division
- Matrix transpose
- Cofactor calculation
- Equality comparison

### Advanced Operations

- Determinant calculation
- Matrix inversion
- Rank calculation
- Automatic algorithm selection
- Gaussian-elimination-based determinant
- Gauss-Jordan-based inverse matrix
- Recursive cofactor expansion implementation
- Adjugate inverse implementation

### Vectors

#### RowVector

- Dot product (InnerProduct)
- Cross product (CrossProduct)
- Vector length calculation
- Matrix generation from vectors

#### ColVector

- Dot product (InnerProduct)
- Cross product (CrossProduct)
- Vector length calculation
- Matrix generation from vectors

### General

- Header-only library
- Template-based implementation
- No external dependencies
- C++11 compatible
- Easy integration into existing projects

---

## Requirements

- C++11 or later

---

## Installation

Simply copy the header files into your project.

```text
Matrix.h
RowVector.h
ColVector.h
```

No external libraries are required.

```cpp
#include "Matrix.h"
#include "RowVector.h"
#include "ColVector.h"
```

### Linux Packages

The GitHub Releases page provides architecture-independent Debian and RPM
packages. For example:

```bash
sudo dpkg -i linearalgebracpp-dev_1.2.3_all.deb
# Or, on Rocky Linux / RHEL:
sudo rpm -i linearalgebracpp-devel-1.2.3-1.noarch.rpm
```

The headers are installed directly in `/usr/local/include`, so the includes
above continue to work. This is a header-only library: there is no compiled
library to install in `/usr/local/lib`.

### Building Packages

Install `make`, `tar`, `gzip`, and the appropriate packaging tools:

- Ubuntu: `dpkg-deb` (from `dpkg`) for deb, `rpm` for rpmbuild.
- Rocky Linux / RHEL: `rpm-build` for rpm; `dpkg` from EPEL for deb.

Then run:

```bash
make deb              # dist/linearalgebracpp-dev_VERSION_all.deb
make rpm              # dist/linearalgebracpp-devel-VERSION-1.noarch.rpm
make release-package  # build both
make package-test     # test package contents and version selection
```

The package version is read from the `VERSION` file at the repository root
(`X.Y.Z`, currently `1.0.0`). To override it for a development build, set
`PACKAGE_VERSION` to an `X.Y.Z` version:

```bash
PACKAGE_VERSION=1.2.3 make release-package
```

`PACKAGE_VERSION` takes precedence over `VERSION`.

### Publishing a Release

Update the `VERSION` file (`X.Y.Z`, no `v` prefix) and merge it, then run
**Release packages** from GitHub Actions on the desired branch. The workflow
reads `VERSION`, builds both packages with that version, and creates the
`vX.Y.Z` release with GitHub-generated release notes and both packages
attached. The workflow requires permission to create tags and releases. An
existing tag for the same version is rejected; bump `VERSION` before retrying.

---

## Quick Start

### Matrix Example

```cpp
#include "Matrix.h"

int main()
{
    Matrix<double> a{
        {1.0, 2.0},
        {3.0, 4.0}
    };

    Matrix<double> b{
        {5.0, 6.0},
        {7.0, 8.0}
    };

    Matrix<double> c = a * b;

    return 0;
}
```

### Row Vector Example

```cpp
#include "RowVector.h"

int main()
{
    RowVector<double> v1{1.0, 2.0, 3.0};
    RowVector<double> v2{4.0, 5.0, 6.0};

    double dot = v1.InnerProduct(v2);

    RowVector<double> cross = v1.CrossProduct(v2);

    return 0;
}
```

### Column Vector Example

```cpp
#include "ColVector.h"

int main()
{
    ColVector<double> v1{1.0, 2.0, 3.0};
    ColVector<double> v2{4.0, 5.0, 6.0};

    double dot = v1.InnerProduct(v2);

    ColVector<double> cross = v1.CrossProduct(v2);

    return 0;
}
```

---

## Matrix Operations

### Addition

```cpp
Matrix<double> c = a + b;
```

### Subtraction

```cpp
Matrix<double> c = a - b;
```

### Multiplication

```cpp
Matrix<double> c = a * b;
```

### Scalar Multiplication

```cpp
Matrix<double> c = a * 2.0;
```

### Scalar Division

```cpp
Matrix<double> c = a / 2.0;
```

### Transpose

```cpp
Matrix<double> t = a.Transpose();
```

### Determinant

```cpp
double det = a.Determinant();
```

### Inverse Matrix

```cpp
Matrix<double> inv = a.Inverse();
```

The educational `DeterminantRecursive()` and `InverseAdjugate()` methods and
the elimination-based `DeterminantGaussian()` and `InverseGaussJordan()`
methods can also be called directly.
`DeterminantRecursive()` expects a square matrix. `InverseAdjugate()` retains
the original 1×1 cofactor behavior (a zero result); use `Inverse()` or
`InverseGaussJordan()` for a 1×1 inverse.

### Rank Calculation

```cpp
Matrix<double> mat{
    {1, 2, 3},
    {2, 4, 6},
    {1, 1, 1}
};

size_t rank = mat.Rank();
```

Result:

```text
2
```

Elimination uses partial pivoting and an absolute zero threshold of
`std::numeric_limits<T>::epsilon()` for floating-point matrices. Rank throws
`std::domain_error` for non-finite elements. Non-square determinants and
non-invertible matrices return NaN for floating-point element types. Integer
types cannot represent NaN or fractional inverse elements; invalid operations
that require NaN throw `std::domain_error` for these types. Use floating-point
types for inversion and numerical calculations. Integer elimination uses
long-double arithmetic and a scale-dependent rounding tolerance, so it is not
an exact integer algorithm.

---

## Matrix Construction

### C-style Array

```cpp
double data[2][3] =
{
    {1, 2, 3},
    {4, 5, 6}
};

Matrix<double> mat(data);
```

### Initializer List

```cpp
Matrix<double> mat{
    {1, 2, 3},
    {4, 5, 6}
};
```

---

## Vector Construction

### Row Vector

```cpp
RowVector<double> vec{1.0, 2.0, 3.0};
```

### Column Vector

```cpp
ColVector<double> vec{1.0, 2.0, 3.0};
```

---

## Design Philosophy

LinearAlgebraCpp is designed with the following principles:

LinearAlgebraCpp uses multiple algorithms internally and automatically selects
the most appropriate implementation according to matrix size.

Small matrices use direct formulas or recursive methods for clarity. Larger
matrices automatically switch to Gaussian elimination and Gauss-Jordan methods
for significantly improved performance.

### Simplicity

The implementation prioritizes readability over sophistication. Algorithms are intentionally written in a straightforward manner so that users can easily understand how they work.

### Portability

The library depends only on the C++ standard library and can be integrated into a wide range of environments.

### Educational Value

The source code is intended to be readable enough to serve as a learning resource for matrix algebra, determinants, cofactors, and inverse matrix calculations.

### Easy Integration

Being a header-only library, integration requires nothing more than copying a few header files into an existing project.

---

## Performance

Determinant calculation automatically selects an algorithm according to matrix size.

| Size | Algorithm |
|--------|--------|
| 1×1 | Direct |
| 2×2 | Closed-form Formula |
| 3×3 | Sarrus Formula |
| 4×4 | Recursive Cofactor Expansion |
| 5×5+ | Gaussian Elimination |

Inverse matrix calculation also selects an implementation automatically.

| Size | Algorithm |
|--------|--------|
| 1×1 | Direct |
| 2×2 | Direct Formula |
| 3×3 | Adjugate Matrix |
| 4×4 | Adjugate Matrix |
| 5×5+ | Gauss-Jordan Elimination |

This hybrid approach combines readability for small matrices with practical performance for larger matrices.

---

## Intended Use Cases

- Education and learning
- Unit testing
- Embedded systems
- Engineering calculations
- Scientific prototypes
- Small-to-medium scale applications
- Algorithm verification

---

## Non-Goals

LinearAlgebraCpp is not intended to compete with highly optimized numerical libraries such as:

- Eigen
- Armadillo
- Blaze

If your application requires SIMD optimization, BLAS integration, GPU acceleration, or very large-scale numerical computation, a specialized numerical library may be a better choice.

---

## Example: Matrix Inversion

```cpp
Matrix<double> a{
    {4, 7},
    {2, 6}
};

Matrix<double> inv = a.Inverse();
```

Result:

```text
 0.6  -0.7
-0.2   0.4
```

---

## Directory Structure

```text
LinearAlgebraCpp/
├── Matrix.h
├── RowVector.h
├── ColVector.h
├── LICENSE
└── README.md
```

---

## License

MIT License

See the LICENSE file for details.
