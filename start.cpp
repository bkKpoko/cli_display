#include <cstdio>
#include <cstdlib> // For system()
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

void run() {
  int WIDTH, HEIGHT;
  std::string PROG_NAME;
  std::ifstream file("parameters/parameters");
  if (!file.is_open()) {
    throw std::runtime_error("No file with params\n");
  }
  file >> WIDTH;
  file >> HEIGHT;
  file.ignore();
  std::getline(file, PROG_NAME);
  file.close();

  std::string s = "gnome-terminal ";
  s += "--geometry=";
  s += std::to_string(WIDTH) + "x" + std::to_string(HEIGHT);
  s += " -- ";
  s += PROG_NAME;
  puts(s.c_str());

  int x = system(s.c_str());
}

int main(int argc, char *argv[]) {
  run();
  return 0;
}
