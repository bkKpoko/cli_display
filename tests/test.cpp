#include "vec3.h"
#include <cstdio>

int main(int argc, char *argv[]) {

  vec3<int> a{1, 2, 3};
  vec3<int> b = a;
  vec3<int> c(3);
  vec3<int> d(a);

  vec3<double> aa{1, 2, 3};
  vec3<double> ab = aa;
  vec3<double> ac(3);
  vec3<double> ad(aa);

  vec3<double> bb{1, 2, 3, 4};

  a.print();
  b.print();
  c.print();
  d.print();
  aa.print();
  ab.print();
  ac.print();
  ad.print();
  bb.print();

  return 0;
}
