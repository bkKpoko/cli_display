#include "mat3.h"
#include <cstdio>

int main(int argc, char *argv[]) {

  mat3<int> m1;
  puts("m1");
  m1.print();

  mat3<double> m2;
  m2.set_eye();
  m2 *= 3;
  puts("m2");
  m1.print();

  double p[9] = {2., 1.3, 1.2, 6., 1., 3.2, 4.2, 1.3, 7.6};
  mat3<double> m3 = p;
  mat3<double> m4(m3);
  puts("m3");
  m3.print();
  puts("m3.inv");
  m3.Inv();
  m3.print();

  puts("arithmetic operations");
  (m4 + m3).print();
  (m4 - m3).print();
  (m4 * m3).print();
  (m4 / m4).print();

  mat3<double> m5 = m3;
  m4 += 2;
  puts("m4");
  m4.print();
  m4 /= 3;
  m4.print();

  return 0;
}
