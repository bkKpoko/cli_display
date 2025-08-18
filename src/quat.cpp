#include "quat.h"
#include "rot_mat.h"
#include <cassert>

quat::quat() : data(4, 0.) {
#ifdef DEBUG
  puts(__PRETTY_FUNCTION__);
#endif // DEBUG
  data[0] = 1;
}

quat::quat(const double &a) : data(4, a) {
#ifdef DEBUG
  puts(__PRETTY_FUNCTION__);
#endif // DEBUG
}

quat::quat(const double *a) : data(4, a) {
#ifdef DEBUG
  puts(__PRETTY_FUNCTION__);
#endif // DEBUG
}

quat::quat(const quat &rhs) : data(rhs.data) {
#ifdef DEBUG
  puts(__PRETTY_FUNCTION__);
#endif // DEBUG
}

quat::quat(const Nvector<double> &rhs) {
#ifdef DEBUG
  puts(__PRETTY_FUNCTION__);
#endif // DEBUG
  assert(rhs.size() == 4);
  data = rhs;
}

quat::quat(const std::initializer_list<double> list) {
#ifdef DEBUG
  puts(__PRETTY_FUNCTION__);
#endif // DEBUG
  assert(list.size() == 4);
  data = Nvector<double>(list);
}

quat &quat::operator=(const Nvector<double> &rhs) {
#ifdef DEBUG
  puts(__PRETTY_FUNCTION__);
#endif // DEBUG
  assert(rhs.size() == 4);
  this->data = rhs;
  return *this;
}

quat &quat::operator=(const quat &rhs) {
#ifdef DEBUG
  puts(__PRETTY_FUNCTION__);
#endif // DEBUG
  if (this != &rhs)
    this->data = rhs.data;
  return *this;
}

double &quat::operator[](const int i) {
#ifdef DEBUG
  puts(__PRETTY_FUNCTION__);
#endif // DEBUG
  return data[i];
}

const double &quat::operator[](const int i) const {
#ifdef DEBUG
  puts(__PRETTY_FUNCTION__);
#endif // DEBUG
  return data[i];
}

void quat::set(const int i, const double &a) { data[i] = a; }

void quat::print(const int prec) const { data.print(prec); }

rot_mat quat::get_rotm() const {
  // | 1 - 2(y^2 + z^2)   2(xy - wz)      2(xz + wy)     |
  // | 2(xy + wz)      1 - 2(x^2 + z^2)   2(yz - wx)     |
  // | 2(xz - wy)      2(yz + wx)      1 - 2(x^2 + y^2) |

#ifdef DEBUG
  puts(__PRETTY_FUNCTION__);
#endif // DEBUG
  rot_mat rm;
  rm.set(0, 0, 1 - 2 * (y() * y() + z() * z()));
  rm.set(0, 1, 2 * (x() * y() - w() * z()));
  rm.set(0, 2, 2 * (x() * z() + w() * y()));
  rm.set(1, 0, 2 * (x() * y() + w() * z()));
  rm.set(1, 1, 1 - 2 * (x() * x() + z() * z()));
  rm.set(1, 2, 2 * (y() * z() - w() * x()));
  rm.set(2, 0, 2 * (x() * z() - w() * y()));
  rm.set(2, 1, 2 * (y() * z() + w() * x()));
  rm.set(2, 2, 1 - 2 * (x() * x() + y() * y()));

  return rm;
}

const double &quat::x() const { return data[0]; }

const double &quat::y() const { return data[1]; }

const double &quat::z() const { return data[2]; }

const double &quat::w() const { return data[3]; }

quat::~quat() {}
