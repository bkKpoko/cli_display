#ifndef _ROT_MAT_H_
#define _ROT_MAT_H_

#include "mat3.h"
#include "quat.h"

enum AXIS { X = 0, Y = 1, Z = 2 };

class rot_mat : public mat3<double> {
public:
  using mat3<double>::mat3;
  rot_mat(const double &a) = delete;
  rot_mat(const double *a) = delete;
  rot_mat(const mat3<double> &rhs) = delete;
  rot_mat(const Nmatrix<double> &rhs) = delete;
  rot_mat(std::initializer_list<std::initializer_list<double>> matrix) = delete;

  rot_mat(const rot_mat &rhs);
  rot_mat(quat q);
  rot_mat(AXIS axis, const double &angle);

  rot_mat &operator=(const rot_mat &rhs);
  mat3 &operator=(const mat3 &rhs) = delete;
  mat3 &operator=(const Nmatrix<double> &rhs) = delete;

  ~rot_mat();
};

#endif // !_ROT_MAT_H_
