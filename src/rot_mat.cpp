#include "rot_mat.h"
#include "lin_alg.h"
#include "mat3.h"
#include <cmath>

rot_mat::rot_mat(const rot_mat &rhs) : mat3<double>(rhs) {}

rot_mat::rot_mat(AXIS axis, const double &angle) {
  set_eye();
  switch (axis) {
  case X:
    set(1, 1, cos(angle));
    set(1, 2, -sin(angle));
    set(2, 1, sin(angle));
    set(2, 2, cos(angle));
    break;
  case Y:
    set(0, 0, cos(angle));
    set(0, 2, sin(angle));
    set(2, 0, -sin(angle));
    set(2, 2, cos(angle));
    break;
  case Z:
    set(0, 0, cos(angle));
    set(0, 1, -sin(angle));
    set(1, 0, sin(angle));
    set(1, 1, cos(angle));
    break;
  }
}

rot_mat &rot_mat::operator=(const rot_mat &rhs) {
  if (this != &rhs)
    for (size_t i = 0; i < 3; i++)
      for (size_t j = 0; j < 3; j++)
        *this[i][j] = rhs[i][j];

  return *this;
}

rot_mat::~rot_mat() {}
