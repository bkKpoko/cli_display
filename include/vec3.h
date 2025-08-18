#ifndef _VEC3_H_
#define _VEC3_H_

#include "lin_alg.h"
#include "mat3.h"
#include <cassert>
#include <stdexcept>

template <class T> class vec3 {
private:
  Nvector<T> data;

public:
  typedef T value_type;

  vec3();
  vec3(const T &a);
  vec3(const T *a);
  vec3(const Nvector<T> &rhs);
  vec3(const vec3 &rhs);
  vec3(const std::initializer_list<T> list);

  vec3 &operator=(const Nvector<T> &rhs);
  vec3 &operator=(const vec3 &rhs);

  inline T &operator[](const int i);
  inline const T &operator[](const int i) const;

  vec3 operator+(const T &a) const;
  vec3 operator-(const T &a) const;
  vec3 operator*(const T &a) const;
  vec3 operator/(const T &a) const;

  vec3 &operator+=(const T &a);
  vec3 &operator-=(const T &a);
  vec3 &operator*=(const T &a);
  vec3 &operator/=(const T &a);

  vec3 operator+(const vec3<T> &a) const;
  vec3 operator-(const vec3<T> &a) const;
  vec3 operator*(const vec3<T> &a) const;
  vec3 operator*(const mat3<T> &a) const;

  vec3 &operator+=(const vec3<T> &a);
  vec3 &operator-=(const vec3<T> &a);
  vec3 &operator*=(const vec3<T> &a);
  vec3 &operator*=(const mat3<T> &a);

  void set(const int i, const T &a);
  void print(const int prec = 2) const;

  T &x();
  T &y();
  T &z();

  const T &x() const;
  const T &y() const;
  const T &z() const;

  ~vec3();
};

template <class T> vec3<T>::vec3() : data(3, (T)0) {}

template <class T> vec3<T>::vec3(const T &a) : data(3, a) {}

template <class T> vec3<T>::vec3(const T *a) : data(3, a) {}

template <class T> vec3<T>::vec3(const vec3 &rhs) : data(rhs.data) {}

template <class T> vec3<T>::vec3(const Nvector<T> &rhs) {
  assert(rhs.size() == 3);
  data = rhs;
}

template <class T> vec3<T>::vec3(const std::initializer_list<T> list) {
  assert(list.size() == 3);
  data = Nvector<T>(list);
}

template <class T> vec3<T> &vec3<T>::operator=(const Nvector<T> &rhs) {
  assert(rhs.size() == 3);
  this->data = rhs;
  return *this;
}

template <class T> vec3<T> &vec3<T>::operator=(const vec3 &rhs) {
  if (this != &rhs)
    this->data = rhs.data;
  return *this;
}

template <class T> T &vec3<T>::operator[](const int i) { return data[i]; }

template <class T> const T &vec3<T>::operator[](const int i) const {
  return data[i];
}

template <class T> vec3<T> vec3<T>::operator+(const T &a) const {
  vec3<T> tmp = *this;
  for (size_t i = 0; i < 3; i++) {
    tmp[i] += a;
  }
  return tmp;
}

template <class T> vec3<T> vec3<T>::operator-(const T &a) const {
  vec3<T> tmp = *this;
  for (size_t i = 0; i < 3; i++) {
    tmp[i] -= a;
  }
  return tmp;
}

template <class T> vec3<T> vec3<T>::operator*(const T &a) const {
  vec3<T> tmp = *this;
  for (size_t i = 0; i < 3; i++) {
    tmp[i] *= a;
  }
  return tmp;
}

template <class T> vec3<T> vec3<T>::operator/(const T &a) const {
  vec3<T> tmp = *this;
  for (size_t i = 0; i < 3; i++) {
    tmp[i] /= a;
  }
  return tmp;
}

template <class T> vec3<T> &vec3<T>::operator+=(const T &a) {
  *this = *this + a;
  return *this;
}

template <class T> vec3<T> &vec3<T>::operator-=(const T &a) {
  *this = *this - a;
  return *this;
}

template <class T> vec3<T> &vec3<T>::operator*=(const T &a) {
  *this = *this * a;
  return *this;
}

template <class T> vec3<T> &vec3<T>::operator/=(const T &a) {
  *this = *this / a;
  return *this;
}

template <class T> vec3<T> vec3<T>::operator+(const vec3<T> &a) const {
  vec3<T> tmp = *this;
  for (size_t i = 0; i < 3; i++) {
    tmp[i] += a[i];
  }
  return tmp;
}

template <class T> vec3<T> vec3<T>::operator-(const vec3<T> &a) const {
  vec3<T> tmp = *this;
  for (size_t i = 0; i < 3; i++) {
    tmp[i] -= a[i];
  }
  return tmp;
}

template <class T> vec3<T> vec3<T>::operator*(const vec3<T> &a) const {
  vec3<T> tmp = *this;
  for (size_t i = 0; i < 3; i++) {
    tmp[i] *= a[i];
  }
  return tmp;
}

template <class T> vec3<T> vec3<T>::operator*(const mat3<T> &a) const {
  T x = this->x();
  T y = this->y();
  T z = this->z();

  vec3<T> res = {a[0][0] * x + a[1][0] * y + a[2][0] * z,
                 a[0][1] * x + a[1][1] * y + a[2][1] * z,
                 a[0][2] * x + a[1][2] * y + a[2][2] * z};

  return res;
}

template <class T> vec3<T> &vec3<T>::operator+=(const vec3<T> &a) {
  *this = *this + a;
  return *this;
}

template <class T> vec3<T> &vec3<T>::operator-=(const vec3<T> &a) {
  *this = *this - a;
  return *this;
}

template <class T> vec3<T> &vec3<T>::operator*=(const vec3<T> &a) {
  *this = *this * a;
  return *this;
}

template <class T> vec3<T> &vec3<T>::operator*=(const mat3<T> &a) {
  *this = *this * a;
  return *this;
}

template <class T> void vec3<T>::set(const int i, const T &a) { data[i] = a; }

template <class T> void vec3<T>::print(const int prec) const {
  data.print(prec);
}

template <class T> T &vec3<T>::x() { return data[0]; }

template <class T> T &vec3<T>::y() { return data[1]; }

template <class T> T &vec3<T>::z() { return data[2]; }

template <class T> const T &vec3<T>::x() const { return data[0]; }

template <class T> const T &vec3<T>::y() const { return data[1]; }

template <class T> const T &vec3<T>::z() const { return data[2]; }

template <class T> vec3<T>::~vec3() {}

#endif // !_VEC3_H_
