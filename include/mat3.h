#ifndef _MAT3_H_
#define _MAT3_H_

// #define DEBUG 1

#include "lin_alg.h"
#include <cassert>
#include <cstdio>

template <class T> class mat3 {
private:
  Nmatrix<T> data;

public:
  typedef T value_type;

  mat3();
  mat3(const T &a);
  mat3(const T *a);
  mat3(const mat3 &rhs);
  mat3(const Nmatrix<T> &rhs);
  mat3(std::initializer_list<std::initializer_list<T>> matrix);

  mat3 &operator=(const mat3 &rhs);
  mat3 &operator=(const Nmatrix<T> &rhs);

  inline T *operator[](const int i);
  inline const T *operator[](const int i) const;

  void set(int n, int m, const T &a);
  void set_diag(const T &a);
  void set_eye();

  void Inv();

  mat3 operator+(const T &a) const;
  mat3 operator-(const T &a) const;
  mat3 operator*(const T &a) const;
  mat3 operator/(const T &a) const;

  mat3 &operator+=(const T &a);
  mat3 &operator-=(const T &a);
  mat3 &operator*=(const T &a);
  mat3 &operator/=(const T &a);

  mat3 operator+(const mat3 &a) const;
  mat3 operator-(const mat3 &a) const;
  mat3 operator*(const mat3 &a) const;
  mat3 operator/(const mat3 &a) const;

  mat3 &operator+=(const mat3 &a);
  mat3 &operator-=(const mat3 &a);
  mat3 &operator*=(const mat3 &a);
  mat3 &operator/=(const mat3 &a);

  void print(const int prec = 2);

  ~mat3();
};

template <class T> mat3<T>::mat3() : data(3, 3, 0.0) {
  set_eye();
#ifdef DEBUG
  puts(__PRETTY_FUNCTION__);
  data.print();
#endif // DEBUG
}

template <class T> mat3<T>::mat3(const T &a) : data(3, 3, a) {
#ifdef DEBUG
  puts(__PRETTY_FUNCTION__);
  data.print();
#endif // DEBUG
}

template <class T> mat3<T>::mat3(const T *a) : data(3, 3, a) {
#ifdef DEBUG
  puts(__PRETTY_FUNCTION__);
  data.print();
#endif // DEBUG
}

template <class T> mat3<T>::mat3(const mat3 &rhs) {
#ifdef DEBUG
  puts(__PRETTY_FUNCTION__);
  rhs.data.print();
#endif // DEBUG
  data = rhs.data;
}

template <class T> mat3<T>::mat3(const Nmatrix<T> &rhs) {
#ifdef DEBUG
  puts(__PRETTY_FUNCTION__);
  rhs.print();
#endif // DEBUG
  assert(rhs.ncols() == 3 && rhs.nrows() == 3);
  data = rhs;
}

template <class T>
mat3<T>::mat3(std::initializer_list<std::initializer_list<T>> matrix) {
#ifdef DEBUG
  puts(__PRETTY_FUNCTION__);
#endif // DEBUG
  assert(matrix.size() == 3);
  for (auto line : matrix)
    assert(line.size() == 3);
  data = matrix;
#ifdef DEBUG
  data.print();
#endif // DEBUG
}

template <class T> mat3<T> &mat3<T>::operator=(const mat3 &rhs) {
#ifdef DEBUG
  puts(__PRETTY_FUNCTION__);
  rhs.data.print();
#endif // DEBUG

  if (this != &rhs)
    this->data = rhs.data;
  return *this;
}

template <class T> mat3<T> &mat3<T>::operator=(const Nmatrix<T> &rhs) {
#ifdef DEBUG
  puts(__PRETTY_FUNCTION__);
  rhs.print();
#endif // DEBUG
  assert(rhs.ncols() == 3 && rhs.nrows() == 3);
  this->data = rhs;
  return *this;
}

template <class T> T *mat3<T>::operator[](const int i) { return data[i]; }

template <class T> const T *mat3<T>::operator[](const int i) const {
  return data[i];
}

template <class T> void mat3<T>::set(int n, int m, const T &a) {
  data[n][m] = a;
}

template <class T> void mat3<T>::set_diag(const T &a) {
  for (size_t i = 0; i < 3; i++) {
    data[i][i] = a;
  }
}

template <class T> void mat3<T>::set_eye() {
  for (size_t i = 0; i < 3; i++) {
    data[i][i] = 1.0;
  }
}

template <class T> void mat3<T>::Inv() {
  // Вычисляем определитель
  double det = this->operator[](0)[0] *
                   (this->operator[](1)[1] * this->operator[](2)[2] -
                    this->operator[](2)[1] * this->operator[](1)[1][2]) -
               this->operator[](0)[1] *
                   (this->operator[](1)[0] * this->operator[](2)[2] -
                    this->operator[](1)[2] * this->operator[](2)[0]) +
               this->operator[](0)[2] *
                   (this->operator[](1)[0] * this->operator[](2)[1] -
                    this->operator[](1)[1] * this->operator[](2)[0]);

  if (std::abs(det) < 1e-6) {
    throw std::runtime_error("Singular matrix");
  }

  double invDet = 1.0 / det;

  mat3<T> result;
  // Вычисляем алгебраические дополнения (союзная матрица)
  result[0][0] = (this->operator[](1)[1] * this->operator[](2)[2] -
                  this->operator[](2)[1] * this->operator[](1)[2]) *
                 invDet;
  result[0][1] = (this->operator[](0)[2] * this->operator[](2)[1] -
                  this->operator[](0)[1] * this->operator[](2)[2]) *
                 invDet;
  result[0][2] = (this->operator[](0)[1] * this->operator[](1)[2] -
                  this->operator[](0)[2] * this->operator[](1)[1]) *
                 invDet;

  result[1][0] = (this->operator[](1)[2] * this->operator[](2)[0] -
                  this->operator[](1)[0] * this->operator[](2)[2]) *
                 invDet;
  result[1][1] = (this->operator[](0)[0] * this->operator[](2)[2] -
                  this->operator[](0)[2] * this->operator[](2)[0]) *
                 invDet;
  result[1][2] = (this->operator[](1)[0] * this->operator[](0)[2] -
                  this->operator[](0)[0] * this->operator[](1)[2]) *
                 invDet;

  result[2][0] = (this->operator[](1)[0] * this->operator[](2)[1] -
                  this->operator[](2)[0] * this->operator[](1)[1]) *
                 invDet;
  result[2][1] = (this->operator[](2)[0] * this->operator[](0)[1] -
                  this->operator[](0)[0] * this->operator[](2)[1]) *
                 invDet;
  result[2][2] = (this->operator[](0)[0] * this->operator[](1)[1] -
                  this->operator[](1)[0] * this->operator[](0)[1]) *
                 invDet;

  *this = result;
}

template <class T> mat3<T> mat3<T>::operator+(const T &a) const {
  mat3<T> tmp = *this;
  for (size_t i = 0; i < 3; i++)
    for (size_t j = 0; j < 3; j++)
      tmp.data[i][j] += a;
  return tmp;
}

template <class T> mat3<T> mat3<T>::operator-(const T &a) const {
  mat3<T> tmp = *this;
  for (size_t i = 0; i < 3; i++)
    for (size_t j = 0; j < 3; j++)
      tmp.data[i][j] -= a;
  return tmp;
}

template <class T> mat3<T> mat3<T>::operator*(const T &a) const {
  mat3<T> tmp = *this;
  for (size_t i = 0; i < 3; i++)
    for (size_t j = 0; j < 3; j++)
      tmp.data[i][j] *= a;
  return tmp;
}

template <class T> mat3<T> mat3<T>::operator/(const T &a) const {
  mat3<T> tmp = *this;
  for (size_t i = 0; i < 3; i++)
    for (size_t j = 0; j < 3; j++)
      tmp.data[i][j] /= a;
  return tmp;
}

template <class T> mat3<T> &mat3<T>::operator+=(const T &a) {
  *this = *this + a;
  return *this;
}

template <class T> mat3<T> &mat3<T>::operator-=(const T &a) {
  *this = *this - a;
  return *this;
}

template <class T> mat3<T> &mat3<T>::operator*=(const T &a) {
  *this = *this * a;
  return *this;
}

template <class T> mat3<T> &mat3<T>::operator/=(const T &a) {
  *this = *this / a;
  return *this;
}

template <class T> mat3<T> mat3<T>::operator+(const mat3<T> &a) const {
  mat3<T> tmp = *this;
  for (size_t i = 0; i < 3; i++) {
    for (size_t j = 0; j < 3; j++) {
      tmp.data[i][j] += a[i][j];
    }
  }
  return tmp;
}

template <class T> mat3<T> mat3<T>::operator-(const mat3<T> &a) const {
  mat3<T> tmp = *this;
  for (size_t i = 0; i < 3; i++) {
    for (size_t j = 0; j < 3; j++) {
      tmp.data[i][j] -= a[i][j];
    }
  }
  return tmp;
}

template <class T> mat3<T> mat3<T>::operator*(const mat3<T> &a) const {
  mat3<T> r;
  r[0][0] = this->operator[](0)[0] * a[0][0] +
            this->operator[](0)[1] * a[1][0] + this->operator[](0)[2] * a[2][0];
  r[0][1] = this->operator[](0)[0] * a[0][1] +
            this->operator[](0)[1] * a[1][1] + this->operator[](0)[2] * a[2][1];
  r[0][2] = this->operator[](0)[0] * a[0][2] +
            this->operator[](0)[1] * a[1][2] + this->operator[](0)[2] * a[2][2];

  r[1][0] = this->operator[](1)[0] * a[0][0] +
            this->operator[](1)[1] * a[1][0] + this->operator[](1)[2] * a[2][0];
  r[1][1] = this->operator[](1)[0] * a[0][1] +
            this->operator[](1)[1] * a[1][1] + this->operator[](1)[2] * a[2][1];
  r[1][2] = this->operator[](1)[0] * a[0][2] +
            this->operator[](1)[1] * a[1][2] + this->operator[](1)[2] * a[2][2];

  r[2][0] = this->operator[](2)[0] * a[0][0] +
            this->operator[](2)[1] * a[1][0] + this->operator[](2)[2] * a[2][0];
  r[2][1] = this->operator[](2)[0] * a[0][1] +
            this->operator[](2)[1] * a[1][1] + this->operator[](2)[2] * a[2][1];
  r[2][2] = this->operator[](2)[0] * a[0][2] +
            this->operator[](2)[1] * a[1][2] + this->operator[](2)[2] * a[2][2];

  return r;
}

template <class T> mat3<T> mat3<T>::operator/(const mat3<T> &a) const {
  mat3<T> tmp = *this;
  tmp *= a.Inv();
  return tmp;
}

template <class T> mat3<T> &mat3<T>::operator+=(const mat3<T> &a) {
  *this = *this + a;
  return *this;
}

template <class T> mat3<T> &mat3<T>::operator-=(const mat3<T> &a) {
  *this = *this - a;
  return *this;
}

template <class T> mat3<T> &mat3<T>::operator*=(const mat3<T> &a) {
  *this = *this * a;
  return *this;
}

template <class T> mat3<T> &mat3<T>::operator/=(const mat3<T> &a) {
  *this = *this / a;
  return *this;
}

template <class T> void mat3<T>::print(const int prec) { data.print(prec); }

template <class T> mat3<T>::~mat3() {}

#endif // !_MAT3_H_
