#ifndef _QUAT_H_
#define _QUAT_H_

#include "lin_alg.h"

class rot_mat;

class quat {
private:
  Nvector<double> data;

public:
  quat();
  quat(const double &a);
  quat(const double *a);
  quat(const Nvector<double> &rhs);
  quat(const quat &quat);
  quat(const std::initializer_list<double> list);

  quat &operator=(const Nvector<double> &rhs);
  quat &operator=(const quat &rhs);

  inline double &operator[](const int i);
  inline const double &operator[](const int i) const;

  void set(const int i, const double &a);
  void print(const int prec = 2) const;
  rot_mat get_rotm() const;

  const double &x() const;
  const double &y() const;
  const double &z() const;
  const double &w() const;

  ~quat();
};
#endif // _QUAT_H_
