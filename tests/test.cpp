#include "mat3.h"
#include "vec3.h"
#include <cstdio>

int main(int argc, char *argv[]) {

  vec3<int> a{1, 2, 3};
  vec3<int> b = a;
  vec3<int> c(3);
  vec3<int> d(a);

  int p[4] = {6, 2, 3, 4};

  vec3<int> aa(p);

  // vec3<double> bb{1, 2, 3, 4};

  a.print();
  b.print();
  c.print();
  d.print();
  aa.print();
  // bb.print();

  double mp[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  Nmatrix<int> matrix_2{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  mat3<int> mat_0;
  mat3<double> mat_p(mp);
  mat3<int> mat1(1);
  mat3<int> mat2(matrix_2);

  mat3<int> mat_a{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  mat_0.print();
  mat1.print();
  mat2.print();
  mat_a.print();
  mat_p.print();

  return 0;
}
