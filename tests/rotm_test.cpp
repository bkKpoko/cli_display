#include "rot_mat.h"
#include <cstdio>

int main(int argc, char *argv[]) {

  rot_mat r1;
  puts("r1");
  r1.print();

  rot_mat r2(X, M_PI / 2);
  puts("r2");
  r2.print();

  quat q;
  puts("r3");
  rot_mat r3(q);
  puts("r3");
  r3.print();

  return 0;
}
