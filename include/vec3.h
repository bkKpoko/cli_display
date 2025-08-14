#ifndef _VEC3_H_
#define _VEC3_H_

#include "lin_alg.h"
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

  void set(const int i, const T &a);
  void print(const int prec = 2) const;

  const T &x() const;
  const T &y() const;
  const T &z() const;

  ~vec3();
};

template <class T> vec3<T>::vec3() : data(3, 0) {}

template <class T> vec3<T>::vec3(const T &a) : data(3, a) {}

template <class T> vec3<T>::vec3(const T *a) : data(3, a) {}

template <class T> vec3<T>::vec3(const vec3 &rhs) : data(rhs.data) {}

template <class T> vec3<T>::vec3(const Nvector<T> &rhs) {
  if (rhs.size() != 3)
    throw std::runtime_error("incorrect data size for vec3\n");
  data = rhs;
}

template <class T> vec3<T>::vec3(const std::initializer_list<T> list) {
  if (list.size() != 3)
    throw std::runtime_error("incorrect data size for vec3\n");
  data = Nvector<T>(list);
}

template <class T> vec3<T> &vec3<T>::operator=(const Nvector<T> &rhs) {
  return vec3(rhs);
}

template <class T> vec3<T> &vec3<T>::operator=(const vec3 &rhs) {
  return vec3(rhs);
}

template <class T> T &vec3<T>::operator[](const int i) { return data[i]; }

template <class T> const T &vec3<T>::operator[](const int i) const {
  return data[i];
}

template <class T> void vec3<T>::set(const int i, const T &a) { data[i] = a; }

template <class T> void vec3<T>::print(const int prec) const {
  data.print(prec);
}

template <class T> const T &vec3<T>::x() const { return data[0]; }

template <class T> const T &vec3<T>::y() const { return data[1]; }

template <class T> const T &vec3<T>::z() const { return data[2]; }

template <class T> vec3<T>::~vec3() {}

#endif // !_VEC3_H_
