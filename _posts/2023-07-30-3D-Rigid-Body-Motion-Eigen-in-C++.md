
# 3D Rigid Body Motion by using Eigen in C++
**Main Goal:**

- Learn the rigid body geometry in 3D: rotational matrix, transformation matrix, quaternion and Euler angle.
- Learn *Eigen* library matrix and geometry module

**To run the code**
```
mkdir build && cd build
cmake ..
make
sudo ldconfig
```

## 2.1 Rotation Matrix
### 2.2.1 Points, vectors, and coordinate systems.
- Definition of **Trace**: 
If A a square matrix, we can obtain $A^T$ by interchanging the entries that are symmetriically positions about the main diagonal. Example

$$A= \begin{bmatrix}
-1 && 2 && 4\\
3 && 7 && 0 \\
5 && 8 && -6
\end{bmatrix} \space 
A^T = \begin{bmatrix}
-1 && 3 && 5\\
2 && 7 && 8 \\
4 && 0 && -6
\end{bmatrix}$$

 trace of A is: 
 $tr(A) = tr(A^T)= -1 +7+(-6)=0$
 
- Inner and Outer Product: If $u$ and $v$ are column vectors with the same size, then $u^Tv$ is the inner product of $u$ and $v$; if $u$ and $v$ are column vectors of **any size**, the $uv^T$ is the outer product of $u$ and $v$.

Example inner product

$$u = \begin{bmatrix}
-1\\
3  \\
\end{bmatrix}  
, v = \begin{bmatrix}
2\\
5  \\
\end{bmatrix} 
, u^Tv =\begin{bmatrix}
-1 &&3\\
\end{bmatrix} 
\begin{bmatrix}
2\\
5  \\
\end{bmatrix} 
= -1.2 + 3.5 =13$$

Example outer product

$$uv^T =\begin{bmatrix}
-1 \\ 3\\
\end{bmatrix}
\begin{bmatrix}
2 && 5  \\
\end{bmatrix} =
\begin{bmatrix}
-1.2 && -1.5 \\
3.2 && 3.5
\end{bmatrix} =
\begin{bmatrix}
-2 && -5 \\
 6 && 15
\end{bmatrix} .$$

- Cross product: In mathematics, the cross product or vector product (occasionally directed area product, to emphasize its geometric significance) is a binary operation on two vectors in a three-dimensional oriented Euclidean vector space , and is denoted by the symbol × . Given two linearly independent vectors a and b, the cross product, a × b (read "a cross b"), is a vector that is perpendicular to both a and b, and thus normal to the plane containing them. (wiki). Where $[a]_{\times}$ is skew-symmetric matrix 

$$a \times b = [a]_{\times} b =
\begin{bmatrix}
0  && -a_3 && a_2 \\
a_3 && 0 && -a_1 \\
-a_2 && a_1 && 0
\end{bmatrix} \begin{bmatrix}
b_1 \\ b_2 \\ b_3
\end{bmatrix}$$


Homogeneous coordinates are a 4D vector with $R$ as a rotation matrix, and $t$ as translation.

$$\begin{bmatrix}
R && t  \\
0^T && 1
\end{bmatrix}$$

This set of transform matrices is also known as the special Euclidean group:

$$SE(3) = \{ T = \begin{bmatrix}
R && t  \\
0^T && 1
\end{bmatrix} \in R^{4\times4} | R \in SO(3),  t \in R^3\}$$

Practice: Use Eigen, Install Eigen
```
sudo apt−get install libeigen3−dev
sudo locate eigen3
```
Basic working with matrix and matrix operation by run an example `eigenMatrix.cpp`

### 2.1.2 Rotation Vectors and Euler Angles
- Rotation vectors

**Rodrigues' rotation** formula: In the theory of three-dimensional rotation, Rodrigues' rotation formula, named after Olinde Rodrigues, is an efficient algorithm for rotating a vector in space, given an axis and angle of rotation. By extension, this can be used to transform all three basis vectors to compute a rotation matrix in SO(3), the group of all rotation matrices, from an axis–angle representation. (Wiki)

Consider a rotation represented by $R$. If described by a rotation vector, assuming that the rotation axis is a unit-length vector $n$ and the angle is $\theta$, then the vector
$\theta n$ can also describe this rotation.

$$R = cos\theta I + (1-cos\theta)nn^T + sin\theta [n]_\times$$ 

Where $[n]_\times$ is vector to skew-symmetric conversion, $I$ is the identiy matrix

- Euler Angles and Quaternions
## Eigen summarized ([more infor](http://eigen.tuxfamily.org/dox/group__TutorialGeometry.html) )
- Rotation matrix (3x3): `Eigen::Matrix3d`
- Rotation vector (3x1): `Eigen::AngleAxisd`
- Euler angle (3x1): `Eigen::Vector3d`
- Quaternion (4x1): `Eigen::Quaterniond`
- Euclidean transformation matrix (4x4): `Eigen::Isometry3d`
- Affine transform (4x4): `Eigen::Affine3d`
- Perspective transformation(4x4): `Eigen::Projective3d`

## 2.2 Visualization Demo
### 2.2.1 Ploting the Trajectory
 The trajectory file called "trajectory.txt" has each line format:  $time, t_x, t_y, t_z, q_x, q_y, q_z, q_w$  with $t$ is translatition, $q$ is quaternion.

### Install Pangolin
* use pangolin: slambook/3rdpart/Pangolin or download it from github: https://github.com/stevenlovegrove/Pangolin

* install dependency for pangolin (mainly the OpenGL): 
```sudo apt-get install libglew-dev```

* compile and install pangolin

```
cd [path-to-pangolin]
mkdir build
cd build
cmake ..
make 
sudo make install 
```

* Add to the ```CMakeLists.txt```

CMakeLists.txt
{:.filename}
```
....
find_package(Pangolin REQUIRED)
include_directories(${Pangolin_INCLUDE_DIRS})
target_link_libraries(plotTrajectory ${Pangolin_LIBRARIES})
....
```

* Config c_pp_propertive in VSCode
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