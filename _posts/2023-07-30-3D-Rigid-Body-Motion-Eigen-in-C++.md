---
layout: post
category: blog
title: 3D Rigid Body Motion by using Eigen in C++
snippet: Learn the rigid body geometry in 3D and Eigen library in matrix and geometry module.
tags: [C++, robotics, math]
katex: True
---

**Main Goal:**

- Learn the rigid body geometry in 3D: rotational matrix, transformation matrix, quaternion and Euler angle.
- Learn *Eigen* library matrix and geometry module

## I.  3D RIGID BODY MOTION
In the context of matrices, 3D rigid body motion refers to representing the movement of a solid object in three-dimensional space using transformation matrices. A rigid body motion is a transformation that preserves the shape and size of the object. It involves both translation and rotation. In this representation, a 3D rigid body motion can be described by a 4x4 transformation matrix. The upper-left 3x3 submatrix represents the rotation of the object, while the rightmost column represents the translation. By multiplying this transformation matrix with the coordinates of points or vectors in the object's local coordinate system, the new coordinates in the global coordinate system can be obtained.
### 1.1 Properties of Matrix

- Definition of **Trace**: 
If A a square matrix, we can obtain $$A^T$$ by interchanging the entries that are symmetriically positions about the main diagonal. Example

$$A= \begin{vmatrix}
-1 && 2 && 4\\
3 && 7 && 0 \\
5 && 8 && -6
\end{vmatrix}\space 
, 
A^T = \begin{vmatrix}
-1 && 3 && 5\\
2 && 7 && 8 \\
4 && 0 && -6
\end{vmatrix}
$$

 trace of A is: 
 $$tr(A) = tr(A^T)= -1 +7+(-6)=0$$
 
- Inner and Outer Product: If $$u$$ and $$v$$ are column vectors with the same size, then $$u^Tv$$ is the inner product of $$u$$ and $$v$$; if $$u$$ and $$v$$ are column vectors of **any size**, the $$uv^T$$ is the outer product of $$u$$ and $$v$$.

__Example inner product:__

$$u = \begin{vmatrix}
-1\\
3  \\
\end{vmatrix}
, v = \begin{vmatrix}
2\\
5  \\
\end{vmatrix}
, u^Tv =\begin{vmatrix}
-1 &&3\\
\end{vmatrix}
\begin{vmatrix}
2\\
5  \\
\end{vmatrix}
= -1.2 + 3.5 =13$$

__Example outer product__

$$uv^T =\begin{vmatrix}
-1 \\ 3\\
\end{vmatrix}
\begin{vmatrix}
2 && 5  \\
\end{vmatrix}=
\begin{vmatrix}
-1.2 && -1.5 \\
3.2 && 3.5
\end{vmatrix}=
\begin{vmatrix}
-2 && -5 \\
 6 && 15
\end{vmatrix}.$$

- Cross product: In mathematics, the cross product or vector product (occasionally directed area product, to emphasize its geometric significance) is a binary operation on two vectors in a three-dimensional oriented Euclidean vector space , and is denoted by the symbol × . Given two linearly independent vectors a and b, the cross product, a × b (read "a cross b"), is a vector that is perpendicular to both a and b, and thus normal to the plane containing them. (wiki). Where $$[a]_{\times}$$ is skew-symmetric matrix 

$$a \times b = [a]_{\times} b =
\begin{vmatrix}
0  && -a_3 && a_2 \\
a_3 && 0 && -a_1 \\
-a_2 && a_1 && 0
\end{vmatrix}\begin{vmatrix}
b_1 \\ b_2 \\ b_3
\end{vmatrix}$$

### 1.2 Points, vectors, and coordinate systems.
The most fundamental elements in space are points and vectors. Points have no length or volume, and connecting two points creates a vector, which can be thought of as an arrow pointing from one point to another. It's important to note that a vector should not be confused with its coordinates, as a vector is one thing in space, such as "a," and does not need to be associated with several real numbers. We can naturally talk about the plus or minus operation of two vectors without relating to any real numbers. Only when we specify a coordinate system in this 3D space can we talk about the vector's coordinates in this system, finding several real numbers corresponding to this vector.



--- 

### 1.3 Rotation Vectors and Euler Angles

Homogeneous coordinates are a 4D vector with $$R$$ as a rotation matrix, and $$t$$ as translation.

$$\begin{vmatrix}
R && t  \\
0^T && 1
\end{vmatrix}$$

This set of transform matrices is also known as the special Euclidean group:

$$SE(3) = \bigg\{ T = \begin{vmatrix}
R && t  \\
0^T && 1
\end{vmatrix}\in R^{4\times4} | R \in SO(3),  t \in R^3 \bigg\} $$


**Rodrigues' rotation** formula: In the theory of three-dimensional rotation, Rodrigues' rotation formula, named after Olinde Rodrigues, is an efficient algorithm for rotating a vector in space, given an axis and angle of rotation. By extension, this can be used to transform all three basis vectors to compute a rotation matrix in SO(3), the group of all rotation matrices, from an axis–angle representation. (Wiki)

Consider a rotation represented by $$R$$. If described by a rotation vector, assuming that the rotation axis is a unit-length vector $$n$$ and the angle is $$\theta$$, then the vector
$$\theta n$$ can also describe this rotation.

$$R = cos\theta I + (1-cos\theta)nn^T + sin\theta [n]_\times$$ 

Where $$[n]_\times$$ is vector to skew-symmetric conversion, $$I$$ is the identiy matrix

- Euler Angles and Quaternions

---
## II. What is Eigen 3?
Eigen3 is a C++ template library for linear algebra, providing functionality for matrices, vectors, numerical solvers, and related algorithms. It offers a simple and intuitive interface for performing basic matrix and vector operations. Eigen3 utilizes expression templates, a technique that optimizes the evaluation of mathematical expressions
### 2.1 Install Eigen3

To install Eigen3 on Ubuntu, you can follow these general steps:

1. **Open a terminal**: Open a terminal on your Ubuntu system.
2. **Update the package list**: Run the command `sudo apt update` to update the package list.
3. **Install Eigen3**: Run the command `sudo apt install libeigen3-dev` to install the Eigen3 library.
4. **Verify installation**: To verify that Eigen3 has been installed correctly, you can run a simple C++ program that includes the Eigen3 header file and performs a
basic linear algebra operation.



### 2.2 Eigen summarized ([more detail](http://eigen.tuxfamily.org/dox/group__TutorialGeometry.html) )
- Rotation matrix (3x3): `Eigen::Matrix3d`
- Rotation vector (3x1): `Eigen::AngleAxisd`
- Euler angle (3x1): `Eigen::Vector3d`
- Quaternion (4x1): `Eigen::Quaterniond`
- Euclidean transformation matrix (4x4): `Eigen::Isometry3d`
- Affine transform (4x4): `Eigen::Affine3d`
- Perspective transformation(4x4): `Eigen::Projective3d`

Practice: Use Eigen, Install Eigen
```
sudo apt−get install libeigen3−dev
sudo locate eigen3
```
Basic working with matrix and matrix operation by run an example `eigenMatrix.cpp`

### III. Practice with Eigen
This tutorial shows how to build a simple C++ project with Eigen.
We start with the ```eigenMatrix.cpp``` and ```useGeometry.cpp```

```
├── helloworld
│   ├── build
│   │   ├── **/*.so --> library files
|   |   ├── **/*.a --> executable files
│   ├── CMakeList.txt
│   ├── eigenMatrix.cpp
│   ├── useGeometry.cpp
│   ├── coordinateTransform.cpp
```

* Add to the ```CMakeLists.txt```

CMakeLists.txt
{:.filename}
```
# Add CMake Version
cmake_minimum_required(VERSION 2.8)
# Name of project 
project(helloEigen)
# Add header file
include_directories("/usr/include/eigen3")

# Add executable
add_executable(eigenMatrix eigenMatrix.cpp)
add_executable(useGeometry useGeometry.cpp)
add_executable(coordinateTransform coordinateTransform.cpp)

```

* Example code using Eigen to perform some basic matrix operation

eigenMatrix.cpp
{:.filename}
```
# include <iostream>
using namespace std;

#include <ctime>

//Eigen core
#include <Eigen/Core>
//Algebraic operations of dense matrices (inverse, eigenvalues, etc)
#include <Eigen/Dense>
using namespace Eigen;

#define MATRIX_SIZE 50

// Program demonstrates the use of the basic Eigen type
int main(int argc , char **argv){
    // All vector and matrices in Eigen are Eigen::Matrix, 
    // Its first 3 parameters are: data type, row, collum. 
    // Example Declare a 2*3 float matrix
    Matrix<float, 2, 3> matrix_23;
    // 3D vector the same with matrix 3x1
    Vector3d v_3d;
    // This is the same
    Matrix<float , 3, 1> vd_3d;

    // Define 3x3 zeros matrix
    Matrix3d matrix_33 = Matrix3d::Zero();
    
    // If you are not sure about the size of the matrix, 
    // you can use the dynamic size
    Matrix<double, Dynamic, Dynamic> matrix_dynamic;
    //Simpler way
    MatrixXd matrix_x;

    //---------Operation of the Matrix -----------
    //Input data
    matrix_23 << 1, 2, 3, 4, 5, 6;
    //Output
    cout << "matrix 2x3 from 1 to 6: \n" << matrix_23 << endl;
    // Use () to access elements in the matrix
    cout << "print matrix 2x3: " << endl;
    for(int i=0; i <2; i++){
        for(int j=0; j<3; j++)
        cout << matrix_23(i,j) << "\t";
        cout << endl;
    }
    
    // Multiply a matrix with a vector (actually still matrices and matrices)
    v_3d << 3, 2, 1;
    vd_3d << 4, 5, 6;
    // In Eigen you can't mix two diffirent types of matrices, like this
    // wrong Matrix<double, 2, 1> result_wrong_type = matrix_23 * v_3d;
    // it should be explicitly converted
    Matrix<double, 2, 1> result = matrix_23.cast<double>() *v_3d;
    cout << "Multiply matrix [1, 2, 3; 4, 5, 6]*[3, 2, 1]=" << result.transpose() << endl;
    // define the float size of the matrix 2x1
    Matrix<float, 2, 1> result2 = matrix_23*vd_3d;
    cout << "Multiply matrix [1, 2, 3; 4, 5, 6]*[4, 5, 6]=" << result2.transpose() << endl;

    //--- Matrix operation
    matrix_33 << 1, 2, 3, 4, 5, 6, 7, 8, 9; //random number of matrix
    cout << "random matrix: \n" << matrix_33 << endl;
    cout << "transpose: \n" << matrix_33.transpose() << endl;
    cout << "sum: " << matrix_33.sum() << endl;
    cout << "trace: " << matrix_33.trace() << endl;
    cout << "times 10: \n" << 10 * matrix_33 << endl;
    cout << "inverse: \n" << matrix_33.inverse() << endl;
    cout << "det: " << matrix_33.determinant() << endl;
    
    // Eigen Values
    // Real sysmetric matrix can guarantee successful diagonalization 
    SelfAdjointEigenSolver<Matrix3d> eigen_solver(matrix_33.transpose()*matrix_33);
    cout << "Eigen values = \n" << eigen_solver.eigenvalues() << endl;
    cout << "Eigen vectors = \n" << eigen_solver.eigenvectors() << endl;
    // the Matrix 3x3:A, Eigen vectors: X, and Eigen value E  equation:
    // A*X = E*X
    
    // Solving the equations
    // The basic equation A*x = B with matrix_NN *x = v_Nd
    Matrix<double, MATRIX_SIZE, MATRIX_SIZE> matrix_NN = 
                        MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);
    matrix_NN = matrix_NN*matrix_NN.transpose(); // Guarantee semi-positive definite
    Matrix<double, MATRIX_SIZE, 1> v_Nd = MatrixXd::Random(MATRIX_SIZE, 1);

    // Start timming
    clock_t time_stt = clock();
    // Method 1:  Direct inversion  
    Matrix<double, MATRIX_SIZE, 1> x = matrix_NN.inverse()*v_Nd;
    cout << "time of normal inverse is "  << 1000 * (clock() - time_stt) / (double)CLOCKS_PER_SEC << "ms" << endl;
    cout << "x = " << x.transpose() << endl;

    // Method 2: QR decomposition 
    time_stt = clock();
    x = matrix_NN.colPivHouseholderQr().solve(v_Nd);
    cout << "time of QR decomposition is "  << 1000 * (clock() - time_stt) / (double)CLOCKS_PER_SEC << "ms" << endl;
    cout << "x = " << x.transpose() << endl;
    
    // Method 3: Cholesky Decomposition
    time_stt = clock();
    x = matrix_NN.ldlt().solve(v_Nd);
    cout << "time of Cholesky Decomposition is "  << 1000 * (clock() - time_stt) / (double)CLOCKS_PER_SEC << "ms" << endl;
    cout << "x = " << x.transpose() << endl;

    return 0; 
    }
```

Result
{:.filename}
```
matrix 2x3 from 1 to 6: 
1 2 3
4 5 6
print matrix 2x3: 
1	2	3	
4	5	6	
Multiply matrix [1, 2, 3; 4, 5, 6]*[3, 2, 1]=10 28
Multiply matrix [1, 2, 3; 4, 5, 6]*[4, 5, 6]=32 77
random matrix: 
1 2 3
4 5 6
7 8 9
transpose: 
1 4 7
2 5 8
3 6 9
sum: 45
trace: 15
times 10: 
10 20 30
40 50 60
70 80 90
inverse: 
-inf  inf -inf
 inf -inf  inf
-inf  inf -inf
det: 0
Eigen values = 
9.30184e-16
    1.14141
    283.859
Eigen vectors = 
 -0.408248  -0.776691   0.479671
  0.816497 -0.0756865   0.572368
 -0.408248   0.625318   0.665064
time of normal inverse is 7.959ms
x =   2.91155   10.6997   3.43027   -2.6258  -1.14637   1.55867   1.03946   3.68188  -13.0695   1.87163   2.80044   9.72767   9.88619  -6.15914   2.10578  0.450982  -3.58146  -3.01118   8.34067   10.5629 -0.681178   4.72464  -6.14278 -0.191873   3.41807  -3.36318   2.64461  -8.38439  0.620947  -5.11558  -7.43408  -2.18593  -3.23169  0.194099  -2.69517    7.2354  -4.10885  -3.74595  -4.52556  -11.9484   8.27016   7.33514  0.384987   3.41304    -1.809   9.19733 -0.121441  -8.20668   1.72084     4.577
time of QR decomposition is 5.544ms
x =   2.91155   10.6997   3.43027   -2.6258  -1.14637   1.55867   1.03946   3.68188  -13.0695   1.87163   2.80044   9.72767   9.88619  -6.15914   2.10578  0.450982  -3.58146  -3.01118   8.34067   10.5629 -0.681178   4.72464  -6.14278 -0.191873   3.41807  -3.36318   2.64461  -8.38439  0.620947  -5.11558  -7.43408  -2.18593  -3.23169  0.194099  -2.69517    7.2354  -4.10885  -3.74595  -4.52556  -11.9484   8.27016   7.33514  0.384987   3.41304    -1.809   9.19733 -0.121441  -8.20668   1.72084     4.577
time of Cholesky Decomposition is 1.671ms
x =   2.91155   10.6997   3.43027   -2.6258  -1.14637   1.55867   1.03946   3.68188  -13.0695   1.87163   2.80044   9.72767   9.88619  -6.15914   2.10578  0.450982  -3.58146  -3.01118   8.34067   10.5629 -0.681178   4.72464  -6.14278 -0.191873   3.41807  -3.36318   2.64461  -8.38439  0.620947  -5.11558  -7.43408  -2.18593  -3.23169  0.194099  -2.69517    7.2354  -4.10885  -3.74595  -4.52556  -11.9484   8.27016   7.33514  0.384987   3.41304    -1.809   9.19733 -0.121441  -8.20668   1.72084     4.577
```


* Config ```c_pp_propertive``` in VSCode
```
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "${workspaceFolder}/**",
                "/usr/include/eigen3"
            ],
            "defines": [],
            "compilerPath": "/usr/bin/clang",
            "cStandard": "c17",
            "cppStandard": "c++14",
            "intelliSenseMode": "linux-clang-x64"
        }
    ],
    "version": 4
}
```
**To run the code**
```
mkdir build && cd build
cmake ..
make
sudo ldconfig
```
