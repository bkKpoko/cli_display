#include "rot_mat.h"
#include "mat3.h"
#include "quat.h"
#include <cmath>

rot_mat::rot_mat(const rot_mat &rhs) : mat3<double>(rhs) {
#ifdef DEBUG
  puts(__PRETTY_FUNCTION__);
  puts("shit");
#endif // DEBUG
}

rot_mat::rot_mat(const quat &quat) {
#ifdef DEBUG
  puts(__PRETTY_FUNCTION__);
#endif // DEBUG
  *this = quat.get_rotm();
}

rot_mat::rot_mat(AXIS axis, const double &angle) {
#ifdef DEBUG
  puts(__PRETTY_FUNCTION__);
#endif // DEBUG
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
#ifdef DEBUG
  puts(__PRETTY_FUNCTION__);
#endif // DEBUG
  if (this != &rhs)
    for (size_t i = 0; i < 3; i++)
      for (size_t j = 0; j < 3; j++) {
        this->operator[](i)[j] = rhs[i][j];
      }

  return *this;
}

rot_mat &rot_mat::operator=(const quat &rhs) {
#ifdef DEBUG
  puts(__PRETTY_FUNCTION__);
#endif // DEBUG
  *this = rhs.get_rotm();
  return *this;
}

rot_mat::~rot_mat() {}
