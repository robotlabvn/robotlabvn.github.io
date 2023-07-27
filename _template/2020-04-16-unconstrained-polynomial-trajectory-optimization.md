---
layout: post
category: blog
title: Derivation of Unconstrained Polynomial Trajectory Optimization
snippet: How to compute the spline trajectory representation given higher order derivative constraints.
tags: [robotics, math]
katex: True
---

This paper derives the equations mentioned in C. Richter's 2016 [IJRR
paper](https://dspace.mit.edu/bitstream/handle/1721.1/106840/Roy_Polynomial%20trajectory.pdf?sequence=1&isAllowed=y) [1]. The IJRR paper is very brief in derivations, however the conference paper [2] (published in ICRA
2013) covers more detail. This writeup works out all of the equations in [2].

- TOC
{:toc .toc}

------------------------------------------------------------------------

# Polynomial Preliminaries

## Polynomial representation

A polynomial with degree $$N$$ is represented by:

$$\begin{aligned}
  p(t) & = a_0 + a_1 t + a_2 t^2 + \dots + a_Nt^N \\
  & = \sum_{n=0} ^{N} a_n t^n\end{aligned}$$

## Derivatives of a polynomial

  $$\tag{1} $$

Taking time derivatives of the polynomial:

$$
\begin{aligned}
  p(t)        &= a_0 +& a_1& t +& a_2& t^2 &+ a_3& t^3      &+ a_4& t^4       &+ a_5 & t^5         &+ a_6 & t^6         &+ a_7  &t^7          &+ a_8& t^8         &+ a_9  &t^9     +...\\
  \dot p(t)   &=      & a_1&  +& 2 a_2& t &+ 3 a_3& t^2     &+ 4 a_4& t^3     &+ 5 a_5 & t^4       &+ 6 a_6 & t^5       &+ 7a_7 &t^6          &+ 8a_8&t^7         &+ 9a_9 &t^8     +... \\
  \ddot p(t)  &=      &    &   & 2a_2&    &+ 2{\cdot}3 a_3& t    &+ 3{\cdot}4 a_4& t^2  &+ 4{\cdot}5 a_5 & t^3    &+ 5{\cdot}6 a_6 & t^4    &+ 6{\cdot}7 a_7 &t^5      &+ 7{\cdot}8 a_8&t^6     &+ 8{\cdot}9 a_9 &t^7 +... \\
   p^{(3)}(t) &=      &    &   &     &    & 1{\cdot}2{\cdot}3 a_3&     &+ 2{\cdot}3{\cdot}4 a_4& t &+ 3{\cdot}4{\cdot}5 a_5 & t^2 &+ 4{\cdot}5{\cdot}6 a_6 & t^3 &+ 5{\cdot}6{\cdot}7 a_7 & t^4  &+ 6{\cdot}7{\cdot}8 a_8& t^5 &+ 7{\cdot}8{\cdot}9 a_9 & t^6 +...\\
   p^{(4)}(t) &=      &    &   &     &    &            &     &+ 1{\cdot}2{\cdot}3{\cdot}4 a_4& &+ 2{\cdot}3{\cdot}4{\cdot}5 a_5 & t &+ 3{\cdot}4{\cdot}5{\cdot}6 a_6 & t^2 &+ 4{\cdot}5{\cdot}6{\cdot}7 a_7 & t^3  &+ 5{\cdot}6{\cdot}7{\cdot}8 a_8& t^4 &+ 6{\cdot}7{\cdot}8{\cdot}9 a_9 & t^5 +...\end{aligned}$$



From this, we can conclude that, in coefficient-wise form, the $$k$$-th
derivative of each term $$a_nt^n$$ is:

$$\begin{aligned}
  \frac{\partial^k}{\partial t^k}(a_nt^n) &=
  \begin{cases}
    n(n{-}1)(n{-}2)\cdots(n{-}k{-}1) \; a_nt^{n-k}  & \text{for } n \geq k\\
    0 & \text{otherwise }
  \end{cases}\\
  &= \prod_{i =0}^{k-1} (n{-}i)\;  a_nt^{n-k} \qquad  \text{for } n \geq k\end{aligned}$$

Therefore the $$k$$-th derivative of $$p(t)$$ is:

$$\begin{aligned}
  p^{(k)}(t) &= \frac{\partial^k}{\partial t^k} \left(\sum_{n=0} ^{N} a_n t^n\right)\\
  &=  \sum_{n=0} ^{N} \frac{\partial^k}{\partial t^k} \left(a_n t^n\right)\\
  &=  \sum_{n = k} ^{N}  \left(\prod_{i =0}^{k-1} (n{-}i) \right)\;  a_nt^{n-k} \end{aligned} \tag{2}$$

## Square of a polynomial

Suppose that we have a 2nd order polynomial
$$p(t) = a_0 + a_1t + a_2 t^2$$, the square of the polynomial is given by:

$$\begin{aligned}
  p(t)^2 &= (a_0 + a_1t + a_2 t^2)(a_0 + a_1t + a_2 t^2)\\
  &= (a_0^2 + a_0 a_1 t + a_0 a_2 t^2 ) + (a_1 a_0 t + a_1^2 t^2 + a_1a_2 t^3) + (a_0 a_2 t^2 + a_1 a_2 t^3 + a_2^2 t^4)\\
  &= (a_0^2) + (a_0a_1 + a_1a_0) t + (a_0 a_2 + a_1^2 + a_0 a_2) t^2  + (a_1 a_2 + a_1 a_2) t^3 + (a_2^2) t^4\end{aligned}$$

We notice that there is a general pattern: The $$N$$th coefficient of the
squared polynomial of degree $$N$$ is given by:

$$\tag{3} (a^2)_n = \sum_{j = 0}^{N} a_j a_{n-j} $$

Therefore the squared polynomial of degree $$N$$ is given by:

$$\tag{4} p(t)^2 = \sum_{n=0} ^{2N} {(a^2)}_n t^n$$

For the second order polynomial, this is like such:

$$\begin{aligned}
  p(t)^2
  &= \underbrace{(a_0^2)}_{(a^2)_0} + \underbrace{(a_0a_1 + a_1a_0)}_{(a^2)_1} t + \underbrace{(a_0 a_2 + a_1^2 + a_0 a_2)}_{(a^2)_2} t^2  + \underbrace{(a_1 a_2 + a_1 a_2)}_{(a^2)_3} t^3 + \underbrace{(a_2^2)}_{(a^2)_4} t^4\end{aligned}$$
$$\begin{aligned}
  &(a^2)_0 =\sum_{j = 0}^{N=2} a_j a_{0-j} & &(a^2)_1 = \sum_{j = 0}^{N=2} a_j a_{1-j} &&(a^2)_2 = \sum_{j = 0}^{N=2} a_j a_{2-j} && (a^2)_3 = \sum_{j = 0}^{N=2} a_j a_{3-j} && (a^2)_4 = \sum_{j = 0}^{N=2} a_j a_{4-j}\\
  & = a_0 a_{0-0} + \cancel{a_1a_{0-1}} + \cancel{a_2a_{0-2}} && = a_0 a_{1} + a_1a_{1-1} + \cancel{a_2a_{1-2}} && = a_0 a_{2} + a_1a_{1} + a_2a_{0} &&= \cancel{a_0 a_{3}} + a_1a_{2} + a_2a_{1} &&  = \cancel{a_0 a_{4}} + \cancel{a_1a_{3} }+ a_2a_{2}\\
  & = a_0^2 && = a_0 a_{1} + a_1a_{0} &&   = a_0 a_{2} + a_1^2 + a_2a_{0} && = a_1a_{2} + a_2a_{1} && = a_2^2\end{aligned}$$

----------------
# QP form cost function for minimizing derivatives

The cost function for optimization of a polynomial is:

$$\tag{5} \begin{aligned}
  J &= \int_0^T w_0p(t)^2 + w_1 \dot p(t)^2 + w_2 \ddot p(t)^2 + \dots + w_Np^{(N)}(t)^2 \; dt\\
  &= \int_0^T \sum_{n=0}^N w_np^{(n)}(t)^2 \; dt \end{aligned}$$

This can be written in matrix form as:
$$J = \mathbf{a}^TQ \mathbf{a}$$

where $$\mathbf{a}= [a_0, a_1, ..., a_N]$$ and

$$Q = \sum_{k = 0}^N w_k Q_k$$

is the Hessian. we will now derive $$Q$$.

## Square of the $$k$$-th derivative of an $$N$$-th order polynomial

In order to compute $$J$$, we first compute $$p^{(k)}(t)^2$$, which is the square of the $$k$$th derivative for an arbitrary $$N$$-th order polynomial.

From Equation 4, we know that the square of a polynomial is given by:

$$p(t)^2 = \sum_{n=0} ^{2N} {(a^2)}_n t^n$$

Therefore for the $$k$$th derivative for this polynomial, we want:

$$\tag{6} p^{(k)}(t)^2 = \sum_{n=0} ^{2N} {(\alpha^2)}_n t^{(n-2k)} $$

where $${(\alpha^2)}_n$$ is the $$N$$th coefficient of the square of the polynomial derivative. Following Eq. 3:

$$\begin{aligned}
  {(\alpha^2)}_n = \sum_{j = 0}^{N} \alpha_j \alpha_{n-j}\end{aligned}$$


where $$\alpha_n$$ is the $$N$$th coefficient of the derivative of a
polynomial.
From Equation 2, we know that the derivative of a polynomial is given by:

$$p^{(k)}(t)
  =  \sum_{n=k} ^{N}  \left(\prod_{i =0}^{k-1} (n{-}i) \right)\;  a_nt^{n-k}$$

therefore, the $$N$$th coefficient of the derivative is:

$$\begin{aligned}
  \alpha_n = \left(\prod_{i =0}^{k-1} (n{-}i) \right) a_n\end{aligned}$$


the $$N$$th coefficient of the squared derivative is:

$$\tag{7} \begin{aligned}
  {(\alpha^2)}_n &= \sum_{j = 0}^{N} \alpha_j \alpha_{n-j}\\
  &= \sum_{j = 0}^{N} \left(\prod_{i=0}^{k-1} (j-i) \right) a_j \left(\prod_{i =0}^{k-1} (n{-}j{-}i) \right)  a_{n-j}\\
&= \sum_{j = 0}^{N} \left(\prod_{i=0}^{k-1} (j{-}i)(n{-}j{-}i) \right) a_j a_{n-j}\end{aligned}$$


Plugging Eq. 7 back into Eq. 6:

$$ p^{(k)}(t)^2 = \sum_{n=0} ^{2N} \left(\sum_{j = 0}^{N} \left(\prod_{i=0}^{k-1} (j{-}i)(n{-}j{-}i) \right) a_j a_{n-j}\right) t^{(n-2k)}$$

----------------

## Cost function

The component of the cost function of the $$k$$-th derivative is:

$$\begin{aligned}
  J_k &= \int_0^T p^{(k)}(t)^2 \; dt\\
  &= \int_0^T p^{(k)}(t)^2 \; dt\\
  &= \int_0^T \underbrace{\sum_{n=0} ^{2N} \sum_{j = 0}^{N} \left(\prod_{i=0}^{k-1} (j{-}i)(n{-}j{-}i) \right) a_j a_{n-j}}_{\text{not a function of } t} t^{(n-2k)} \; dt\\
  &= \sum_{n=0} ^{2N} \left(\sum_{j = 0}^{N} \prod_{i=0}^{k-1} (j{-}i)(n{-}j{-}i) \right) a_j a_{n-j} \int_0^T t^{(n-2k)} \; dt\\
  &= \sum_{n=0} ^{2N} \left(\sum_{j = 0}^{N} \prod_{i=0}^{k-1} (j{-}i)(n{-}j{-}i) \right) a_j a_{n-j}\frac{T^{n{-}2k{+}1}}{n{-}2k{+}1}\end{aligned}$$

## Jacobian and Hessian

The first derivative of the cost component of the $$k$$-th derivative with
respect to a coefficient $$a_h$$ is given by:

$$\begin{aligned}
  \frac{\partial J_k}{\partial a_h}
  &= \sum_{n=0} ^{2N} \sum_{j = 0}^{N} \left(\prod_{i=0}^{k-1} (j{-}i)(n{-}j{-}i) \right) \Biggl(\underbrace{\frac{\partial a_j}{\partial a_h}}_{ \mathclap{= 1 \text{ when } j = h}}a_{n-j} +  a_{j}\underbrace{\frac{\partial a_{n-j}}{\partial a_h}}_{ \mathclap{= 1 \text{ when } n-j = h}}\Biggr) \frac{T^{n{-}2k{+}1}}{n{-}2k{+}1}\\
  &= \sum_{n=0} ^{2N} \left(\prod_{i=0}^{k-1} (h{-}i)(n{-}h{-}i) \right) \biggl(1 \cdot\underbrace{a_{n-h}}_{  \mathllap{\text{ when } }j = h} +  \underbrace{a_{n-h}}_{ \text{ when }\mathrlap{j = n-h}}\cdot 1\biggr) \frac{T^{n{-}2k{+}1}}{n{-}2k{+}1}\\
  &= \sum_{n=0} ^{2N} \left(\prod_{i=0}^{k-1} (h{-}i)(n{-}h{-}i) \right) \biggl(2 a_{n-h}\biggr) \frac{T^{n{-}2k{+}1}}{n{-}2k{+}1}\\
  &= 2\sum_{n=0} ^{2N} \left(\prod_{i=0}^{k-1} (h{-}i)(n{-}h{-}i) \right) \biggl( a_{n-h}\biggr) \frac{T^{n{-}2k{+}1}}{n{-}2k{+}1}\end{aligned}$$

The second derivative of the cost component of the $$k$$-th derivative
with respect to a coefficient $$a_h$$ is given by:

$$\begin{aligned}
  \frac{\partial^2 J_k}{\partial a_l \partial a_h}
  &= 2\sum_{n=0} ^{2N} \left(\prod_{i=0}^{k-1} (h{-}i)(n{-}h{-}i) \right) \biggl( \underbrace{\frac{\partial a_{n-h}}{\partial a_l}}_{\mathclap{=1 \text{ when } l = n-h}}\biggr) \frac{T^{n{-}2k{+}1}}{n{-}2k{+}1}\\
  &= 2\sum_{n=0} ^{2N} \left(\prod_{i=0}^{k-1} (h{-}i)(n{-}h{-}i) \right) \biggl(1\biggr) \frac{T^{n{-}2k{+}1}}{n{-}2k{+}1} \qquad \text{ when } l = n-h,\;  0 \text{ otherwise}\\
  &\text{therefore, when }n=l+h\\
  &= 2 \left(\prod_{i=0}^{k-1} (h{-}i)(l{-}i) \right) \frac{T^{l{+}h{-}2k{+}1}}{l{+}h{-}2k{+}1}\end{aligned}$$

Therefore,

$$\begin{aligned}
  Q^{hl}_k =
  \begin{cases}
    2 \left(\prod_{i=0}^{k-1} (h{-}i)(l{-}i) \right) \frac{T^{l{+}h{-}2k{+}1}}{l{+}h{-}2k{+}1} & \text{if } h, l \geq k\\
    0 & \text{otherwise}
  \end{cases}\end{aligned}$$

and the complete Hessian is given by:

$$Q = \sum_{k=0}^{k=N} w_k Q_k$$

----------------

# Constraint formulation

We will derive the end point constraints for a single polynomial in matrix form. Going back to the derivatives in Eq. 1 and evaluating them at $$t=0$$:

$$\begin{aligned}
  p(t)        &= a_0 \\
  \dot p(t)   &= a_1 \\
  \ddot p(t)  &= 2a_2\\
   p^{(3)}(t) &= 1{\cdot}2{\cdot}3 a_3 \\
   p^{(4)}(t) &= 1{\cdot}2{\cdot}3{\cdot}4 a_4\end{aligned}$$

coefficient-wise, this would be:

$$\begin{aligned}
  p^{(k)}(0) = \prod_{n = 0}^{k-1} (k - n) a_k\end{aligned}$$

And similarly, for $$t = T$$, the coefficient-wise representation would be given by directly substituting $$t = T$$ in Eq. 2:

$$\begin{aligned}
  p^{(k)}(T) = \sum_{n = k} ^{N}  \left(\prod_{i =0}^{k-1} (n{-}i) \right)\;  a_nT^{n-k}\end{aligned}$$

Suppose that we have constraints at the initial point $$p(0) = d_{0,0}$$,
$$\dot p(0) = d_{0,1}$$, $$\ddot p(0) = d_{0,2}$$, ...etc, and endpoint
$$p(T) = d_{T,0}$$, $$\dot p(T) = d_{T,1}$$, $$\ddot p(T) = d_{T,2}$$... We
would like to formulate these constraints as a function of the
polynomial coefficients $$\mathbf{a}= [a_i]$$. This is to say, we would
like to form a linear function:

$$\begin{aligned}
   A \mathbf{a}= d\\
   \begin{bmatrix} 1 & 0 & 0 & 0 & 0 & 0 & \dots & 0 & 0 \\
                  0 & 1 & 0 & 0 & 0 & 0 & \dots & 0 & 0 \\
                  0 & 0 & 2 & 0 & 0 & 0 & \dots & 0 & 0 \\
                  0 & 0 & 0 & 6 & 0 & 0 & \dots & 0 & 0 \\
                  0 & 0 & 0 & 0 &  24 & 0 & \dots & 0 & 0 \\
                  0 & 0 & 0 & 0 &  0 & 120 & \dots & 0 & 0 \\
                  \vdots & & & & &  \vdots & \vdots \\
                  1 & T & T^2 & T^3 & T^4 & T^5 &\dots & T^{N-1} & T^N \\
                  0 & 1 & 2T & 3T^2 & 4T^3 & 5T^4 & \dots & (N-1)T^{N-2} & NT^{N-1}\\
                  0 & 0 & 2 & 2{\cdot}3T & 3{\cdot}4T^2 & 4{\cdot}5T^3 & \dots& (N-2)(N-1)T^{N-3} & (N-1)NT^{N-2}\\
                  \vdots & & & & & & & \vdots& \vdots \\
  \end{bmatrix}
  \begin{bmatrix} a_0\\ a_1\\ a_2\\ \vdots \\ a_N \end{bmatrix} =
    \begin{bmatrix}  d_{0,0} \\  d_{0,1} \\  d_{0,2} \\ \vdots  \\  d_{T,0} \\  d_{T,1} \\  d_{T,2} \\ \vdots \end{bmatrix}\\
     \begin{bmatrix} A_0 \\ A_T
      \end{bmatrix}  \mathbf{a}=
        \begin{bmatrix} d_0 \\ d_T \end{bmatrix}\end{aligned}$$

Where the coefficient wise matrices for the are given as follows:

$$\begin{aligned}
& \text{Initial conditions:} && \text{Final conditions:} \\
  A_{0, nk} &= \begin{cases}
  \prod_{i=0}^{k-1} (n-i) &\text{if } n=k\\
  0 & \text{otherwise}
\end{cases}
& A_{T, nk} &= \begin{cases}
\left(\prod_{i=0}^{k-1} (n-i)\right)T^{n-k} &\text{if } n \geq k\\
0 &\text{ otherwise }
\end{cases}\\
d_{0, k} &= P^{(k)}(0) & d_{T, k} &= P^{(k)}(T)\end{aligned}$$

For $$n = 0, ..., N$$. Here $$N$$ refer to the column, and $$k$$ refer to the
order of the derivative, thus the row. Therefore:

-   $$A$$ is a $$N \times N$$ square matrix
-   $$A_0$$ and $$A_T$$ are both of dimension $$N \times N/2$$.
-   $$\mathbf{a}$$ is an $$N \times 1$$ vector
-   $$D$$ is an $$N \times 1$$ vector

For an $$N$$-th order polynomial (with $$N+1$$ coefficients), we can at most
take $$N$$ derivatives.

----------------

# QP for a single polynomial

The quadratic program is:

$$\begin{aligned}
  \min_{\mathbf{a}} \quad  &\mathbf{a}^\top Q \mathbf{a}\\
  \ \mathrm{s.t.}\ \quad & A\mathbf{a}- d = 0\end{aligned}$$

# Unconstrained QP for a spline

The original cost function for a single polynomial:

$$J = \mathbf{a}^\top Q \mathbf{a}$$

Solve $$\mathbf{a}$$ as a function of the constraints:

$$\begin{aligned}
  A\mathbf{a}- d &= 0\\
  \mathbf{a}&= A^{-1}d\end{aligned}$$

substitute back into the cost function:

$$\begin{aligned}
  J &= \left(A^{-1}d\right)^\top Q \left(A^{-1}d\right)\\
  &= \left(d^\top A^{-\top}\right) Q \left(A^{-1}d\right)\\
  &= d^\top A^{-\top}Q A^{-1}d\end{aligned}$$

Now, we consider the joint optimization of a multi-segment polynomial
trajectory. For a multi-segment polynomial (spline), we assume the
following:

- A set of position waypoints are given, which will act as segments of the spline.
- Endpoint constraints on the higher order derivatives are given for the spline.
- Continuity of higher order derivatives is maintained for the spline; that means, the higher order derivatives are constrained between segments of polynomials.

For each segment of the spline, we have:

$$\begin{aligned}
  J_i &= d_i^\top A_i^{-\top}Q_{J_i} A_i^{-1}d_i\\
  &= \begin{bmatrix} d_{i, 0} \\ d_{i, T} \end{bmatrix}^\top
     \begin{bmatrix}A_{i, 0} \\ A_{i, T} \end{bmatrix}^{-\top}Q_{J_i}
    \begin{bmatrix}A_{i, 0} \\ A_{i, T} \end{bmatrix}^{-1}
      \begin{bmatrix} d_{i, 0} \\ d_{i, T} \end{bmatrix}\end{aligned}$$


The derivatives are set up as follows: in $$d_{i, t}$$, $$i$$ represents the
segment and $$T$$ represents the upper half block of the derivative
constraints on the initial point, and $$T$$ represents the lower block of
the derivative constraints on the final point.

In order to satisfy the assumptions, for an $$M$$-segment spline with
duration $$T$$, the initial and final derivatives are constrained to the
given values, and the intermediate derivatives are continuous:

$$\begin{aligned}
  d_{0, 0} &= \begin{bmatrix} P(0) \\ \dot P(0) \\ \vdots \end{bmatrix}\\
  d_{M-1, T_{M-1}} &= \begin{bmatrix} P(T) \\ \dot P(T) \\ \vdots \end{bmatrix}\\
  d_{i-1, T_{i-1}} &= d_{i, 0}\end{aligned}$$

Therefore assembling a joint optimization problem looks like this:

$$\begin{aligned}
    \mathbf{J}&= \mathbf{D}^\top\mathbf{A}^{-\top}\mathbf{Q}\mathbf{A}^{-1}\mathbf{D}\\
    &=
    \begingroup
    \begin{bmatrix} d_{0, 0} \\ d_{0, T} \\ d_{1, 0} \\ d_{1, T} \\ \vdots \\ d_{M-1, 0} \\ d_{M-1, T} \end{bmatrix}^\top
       \begin{bmatrix}\begin{bmatrix} A_{0, 0} \\ A_{0, T} \end{bmatrix} ^{-\top}& 0 & 0 & \dots \\
         0 & \begin{bmatrix} A_{1, 0} \\ A_{1, T} \end{bmatrix} ^{-\top}& 0 &\dots \\
         \vdots &   & \ddots  &\vdots \\
         0 & 0 & 0  & \begin{bmatrix} A_{M-1, 0} \\ A_{M-1, T} \end{bmatrix} ^{-\top}\\
       \end{bmatrix}
    \endgroup
    \begingroup
     \begin{bmatrix} Q_{J_0} & 0 & 0  & \dots \\
       0 & Q_{J_1} & 0  & \dots \\
       \vdots &  & \ddots  &\vdots \\
      0 & 0 & 0 &Q_{J_{M-1}}\\
     \end{bmatrix}
     \endgroup
     \begingroup
     \begin{bmatrix}\begin{bmatrix} A_{0, 0} \\ A_{0, T} \end{bmatrix} ^{-1}& 0 & 0  & \dots \\
       0 & \begin{bmatrix} A_{1, 0} \\ A_{1, T} \end{bmatrix} ^{-1}& 0  &\dots \\
       \vdots &    & \ddots  &\vdots \\
       0 & 0 & 0 & \begin{bmatrix} A_{M-1, 0} \\ A_{M-1, T} \end{bmatrix} ^{-1}\\
     \end{bmatrix}
     \endgroup
    \begin{bmatrix} d_{0, 0} \\ d_{0, T} \\ d_{1, 0} \\ d_{1, T} \\ \vdots \\ d_{M-1, 0} \\ d_{M-1, T} \end{bmatrix}\end{aligned}$$

$$\begin{aligned}
    \mathbf{J}&=
    \begingroup
    \begin{bmatrix} d_{0, 0} \\ d_{0, T} \\ d_{1, 0} \\ d_{1, T} \\ \vdots \\ d_{M-1, 0} \\ d_{M-1, T} \end{bmatrix}^\top
       \begin{bmatrix}\begin{bmatrix} A_{0, 0} \\ A_{0, T} \end{bmatrix}   & 0 & 0 & \dots \\
         0 & \begin{bmatrix} A_{1, 0} \\ A_{1, T} \end{bmatrix}   & 0 &\dots \\
         \vdots &   & \ddots  &\vdots \\
         0 & 0 & 0  & \begin{bmatrix} A_{M-1, 0} \\ A_{M-1, T} \end{bmatrix}   \\
       \end{bmatrix}^{-\top}
    \endgroup
    \begingroup
     \begin{bmatrix} Q_{J_0} & 0 & 0  & \dots \\
       0 & Q_{J_1} & 0  & \dots \\
       \vdots &  & \ddots  &\vdots \\
      0 & 0 & 0 &Q_{J_{M-1}}\\
     \end{bmatrix}
     \endgroup
     \begingroup
     \begin{bmatrix}\begin{bmatrix} A_{0, 0} \\ A_{0, T} \end{bmatrix}  & 0 & 0  & \dots \\
       0 & \begin{bmatrix} A_{1, 0} \\ A_{1, T} \end{bmatrix}  & 0  &\dots \\
       \vdots &    & \ddots  &\vdots \\
       0 & 0 & 0 & \begin{bmatrix} A_{M-1, 0} \\ A_{M-1, T} \end{bmatrix}   \\
     \end{bmatrix}^{-1}
     \endgroup
    \begin{bmatrix} d_{0, 0} \\ d_{0, T} \\ d_{1, 0} \\ d_{1, T} \\ \vdots \\ d_{M-1, 0} \\ d_{M-1, T} \end{bmatrix}\end{aligned}$$

Given that the endpoint constraints are fixed, then the new optimization
variable are the free derivatives. We can rewrite the ordered derivative
vector $$\mathbf{D}$$ into a new derivative vector $$D$$, which separates
out the fixed derivatives ($$D_F$$) and the free derivatives ($$D_P$$):

$$D = \begin{bmatrix} D_F \\ D_P \end{bmatrix}$$

Let's rewrite this
equation in terms of $$D$$, keeping in mind that $$D_P$$ is the new
optimization variable. Then, we can use a mapping matrix ($$\mathbf{M}$$)
to map the new derivative vector $$D$$ to the ordered derivative vector
$$\mathbf{D}$$.

$$\begin{aligned}
  \mathbf{J}&= \mathbf{D}^\top\mathbf{A}^{-\top}\mathbf{Q}\mathbf{A}^{-1}\mathbf{D}\\
  \mathbf{J}&= D ^\top\mathbf{M}\mathbf{A}^{-\top}\mathbf{Q}\mathbf{A}^{-1}\mathbf{M}^\top D\end{aligned}$$

Recall that the new derivative vector $$D$$ will serve two purposes:

-   Separate the fixed and free derivatives into $$D_F$$ and $$D_P$$
-   Satisfy $$d_{i-1, T_{i-1}} = d_{i, 0}$$ by remapping redundant
    elements in $$\mathbf{D}$$ with
    $$d_{i-1, T_{i-1}} = d_{i, 0} = d_{i-1, i}$$.

Thus

$$\begin{aligned}
    \mathbf{J}&=
    \begingroup
    \overbrace{\begin{bmatrix} d_{0, 0} \\ d_{0, T} \\ d_{1, 0} \\ d_{1, T} \\ \vdots \\ d_{M-1, 0} \\ d_{M-1, T} \end{bmatrix}^\top}^{\mathbf{D}^\top}
       \begin{bmatrix}\begin{bmatrix} A_{0, 0} \\ A_{0, T} \end{bmatrix}   & 0 & 0 & \dots \\
         0 & \begin{bmatrix} A_{1, 0} \\ A_{1, T} \end{bmatrix}   & 0 &\dots \\
         \vdots &   & \ddots  &\vdots \\
         0 & 0 & 0  & \begin{bmatrix} A_{M-1, 0} \\ A_{M-1, T} \end{bmatrix}   \\
       \end{bmatrix}^{-\top}
    \endgroup
    \begingroup
     \begin{bmatrix} Q_{J_0} & 0 & 0  & \dots \\
       0 & Q_{J_1} & 0  & \dots \\
       \vdots &  & \ddots  &\vdots \\
      0 & 0 & 0 &Q_{J_{M-1}}\\
     \end{bmatrix} \cdots
     \endgroup\\
     &=
     \underbrace{\begin{bmatrix} d_{0, 0} \\ d_{M-1, T} \\\hline d_{0, 1} \\ d_{1, 2} \\ \vdots \\ d_{M-2, M-1} \\  \end{bmatrix}^\top}_{D^\top}
       \begingroup
       \underbrace{\begin{bmatrix}
         1 & 0 & 0 & 0 & 0 &\dots  & 0 & 0 & 0\\
         0 & 0 & 0 & 0 & 0 &\dots  & 0 & 0 & 1 \\
         0 & 1 & 1 & 0 & 0 & \dots & 0 & 0 & 0 \\
         0 & 0 & 0 & 1 & 1 & \dots & 0 & 0 & 0 \\
          & & & &  & \ddots &  &  &  \\
         0 & 0 & 0 & 0 & 0 & \dots & 1 & 1 & 0\\
       \end{bmatrix}}_{\mathbf{M}}
     \endgroup
         \begingroup
        \begin{bmatrix}\begin{bmatrix} A_{0, 0} \\ A_{0, T} \end{bmatrix}   & 0 & 0 & \dots \\
          0 & \begin{bmatrix} A_{1, 0} \\ A_{1, T} \end{bmatrix}   & 0 &\dots \\
          \vdots &   & \ddots  &\vdots \\
          0 & 0 & 0  & \begin{bmatrix} A_{M-1, 0} \\ A_{M-1, T} \end{bmatrix}   \\
        \end{bmatrix}^{-\top}
     \endgroup
     \begingroup
      \begin{bmatrix} Q_{J_0} & 0 & 0  & \dots \\
        0 & Q_{J_1} & 0  & \dots \\
        \vdots &  & \ddots  &\vdots \\
       0 & 0 & 0 & Q_{J_{M-1}}\\
      \end{bmatrix} \cdots
      \endgroup\\
      & => (M{+}1 \times 1)^\top(M{+}1 \times 2M) (2M \times 2M) ...\end{aligned}$$

The new cost matrix is given by:
$$\begin{aligned}
  R &=  \mathbf{M}\mathbf{A}^{-\top}\mathbf{Q}\mathbf{A}^{-1}\mathbf{M}^\top\end{aligned}$$

$$\begin{aligned}
  \mathbf{J}&= \mathbf{D}^\top\mathbf{A}^{-\top}\mathbf{Q}\mathbf{A}^{-1}\mathbf{D}\\
  &=  \begin{bmatrix} D_F \\ D_P \end{bmatrix}^\top
      \begin{bmatrix} R_{FF} & R_{FP} \\ R_{PF} & R_{PP} \end{bmatrix}
        \begin{bmatrix} D_F \\ D_P \end{bmatrix}\\
  &= D_F^\top R_{FF} D_F + D_F^\top R_{FP} D_P + D_P^\top R_{PF} D_F + D_P^\top R_{PP} D_P\end{aligned}$$

If we optimize for $$D_P$$ directly, then the closed form solution is given
by:

$$ D_P^* = -R_{PP}^{-1}R_{FP}^\top D_F$$

----------------
# References

1. C. Richter, A. Bry, and N. Roy, “[Polynomial trajectory planning for aggressive quadrotor flight in dense indoor environments](https://dspace.mit.edu/bitstream/handle/1721.1/106840/Roy_Polynomial%20trajectory.pdf?sequence=1&isAllowed=y),” in Robotics Research. Springer, 2016, pp. 649–666.

2. R. Charles, A. Bry, and N. Roy, “Polynomial trajectory planning for quadrotor flight,” in Proceedings of the IEEE International Conference on Robotics and Automation, ICRA, 2013. _Note: At the time of writing, I can't seem to find an online PDF version of this paper._
