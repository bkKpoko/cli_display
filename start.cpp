#include <cstdio>
#include <cstdlib> // For system()
#include <string>

#include "params.h"

void run() {
  std::string s = "gnome-terminal ";
  s += "--geometry=";
  s += std::to_string(WIDTH) + "x" + std::to_string(HEIGHT + 1);
  s += " -- ";
  s += PROG_NAME;
  puts(s.c_str());

  system(s.c_str());
}

int main(int argc, char *argv[]) {
  run();
  return 0;
}
