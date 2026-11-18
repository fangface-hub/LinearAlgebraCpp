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
- Determinant calculation
- Cofactor calculation
- Matrix inversion
- Equality comparison

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

### Simplicity

The implementation prioritizes readability over sophistication. Algorithms are intentionally written in a straightforward manner so that users can easily understand how they work.

### Portability

The library depends only on the C++ standard library and can be integrated into a wide range of environments.

### Educational Value

The source code is intended to be readable enough to serve as a learning resource for matrix algebra, determinants, cofactors, and inverse matrix calculations.

### Easy Integration

Being a header-only library, integration requires nothing more than copying a few header files into an existing project.

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
