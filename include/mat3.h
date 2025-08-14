#ifndef _MAT3_H_
#define _MAT3_H_

#include "lin_alg.h"

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
  void print(const int prec = 2);

  ~mat3();
};

template <class T> mat3<T>::mat3() : data(3, 3, 0) {}

template <class T> mat3<T>::mat3(const T &a) : data(3, 3, a) {}

template <class T> mat3<T>::mat3(const T *a) : data(3, 3, a) {}

template <class T> mat3<T>::mat3(const mat3 &rhs) : data(rhs.data) {}

template <class T> mat3<T>::mat3(const Nmatrix<T> &rhs) {
  if (rhs.ncols() != 3 || rhs.nrows() != 3)
    throw std::runtime_error("incorrect data size for matrix\n");
  data = rhs;
}

template <class T>
mat3<T>::mat3(std::initializer_list<std::initializer_list<T>> matrix) {
  if (matrix.size() != 3)
    throw std::runtime_error("incorrect data size for matrix\n");
  for (auto line : matrix)
    if (line.size() != 3)
      throw std::runtime_error("incorrect data size for matrix\n");
  data = Nmatrix<T>(matrix);
}

template <class T> mat3<T> &mat3<T>::operator=(const mat3 &rhs) {
  return mat3(rhs);
}

template <class T> mat3<T> &mat3<T>::operator=(const Nmatrix<T> &rhs) {
  return mat3(rhs);
}

template <class T> T *mat3<T>::operator[](const int i) { return data[i]; }

template <class T> const T *mat3<T>::operator[](const int i) const {
  return data[i];
}

template <class T> void mat3<T>::set(int n, int m, const T &a) {
  data[n][m] = a;
}

template <class T> void mat3<T>::print(const int prec) { data.print(prec); }

template <class T> mat3<T>::~mat3() {}

#endif // !_MAT3_H_
