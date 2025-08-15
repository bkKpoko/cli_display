#include "mat3.h"
#include "rot_mat.h"
#include "vec3.h"
#include <cstdio>

int main(int argc, char *argv[]) {

  vec3<int> a{1, 2, 3};
  vec3<int> b = a;
  vec3<int> c(3);
  vec3<int> d(a);

  int p[4] = {6, 2, 3, 4};

  vec3<int> aa(p);

  // puts("vec3 tests");

  // a.print();
  // b.print();
  // c.print();
  // d.print();
  // aa.print();

  puts("mat3 tests");
  // double mp[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  // double mp1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  // Nmatrix<int> matrix_2{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  // mat3<int> mat_0;
  mat3<double> mat_p{{1., 2., 3.}, {4., 5., 6.}, {7., 8., 9.}};
  mat3<double> mat_3{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  // mat3<int> mat1(1);
  // mat3<int> mat2(matrix_2);

  // mat3<int> mat_a{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  // mat_0.print();
  // mat1.print();
  // mat2.print();
  // mat_a.print();
  // mat_p.print();

  // puts("fuck");
  mat3<double> mul(mat_3 * mat_p);
  mul.print();
  mul = mul + 9;
  mul.print();
  mul = mul - 9;
  mul.print();
  //
  // puts("rot_mat tests");
  // rot_mat r1;
  // rot_mat r2 = r1;
  // rot_mat x(AXIS::X, M_PI / 2);
  // rot_mat y(AXIS::Y, M_PI / 2);
  // rot_mat z(AXIS::Z, M_PI / 2);
  //
  // r1.print();
  // r2.print();
  // x.print(5);
  // y.print(5);
  // z.print(5);

  return 0;
}
