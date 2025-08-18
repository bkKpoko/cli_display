#include "game.h"
#include "lin_alg.h"
#include "model.h"
#include "rot_mat.h"
#include <algorithm>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ncurses.h>
#include <vector>

WINDOW *wnd;

const double l = 1.;

Nvector<vertex3d> vertices = {vertex3d{l, l, l},    vertex3d{-l, l, l},
                              vertex3d{-l, -l, l},  vertex3d{l, -l, l},
                              vertex3d{l, l, -l},   vertex3d{-l, l, -l},
                              vertex3d{-l, -l, -l}, vertex3d{l, -l, -l}};

const Nvector<triangle> trises = {
    triangle{0, 1, 2}, triangle{0, 2, 3}, triangle{4, 0, 3}, triangle{4, 3, 7},
    triangle{5, 4, 7}, triangle{5, 7, 6}, triangle{1, 5, 6}, triangle{1, 6, 2},
    triangle{4, 5, 1}, triangle{4, 1, 0}, triangle{2, 6, 7}, triangle{2, 7, 3}};

int init();
void run();
void close();

int main(int argc, char *argv[]) {
  if (init() == 0)
    run();
  close();
  return 0;
}

int init() {
  std::setlocale(LC_ALL, "");
  wnd = initscr();
  cbreak();
  noecho();
  clear();
  refresh();

  keypad(wnd, true);
  nodelay(wnd, true);
  curs_set(0);

  if (!has_colors()) {
    endwin();
    throw std::runtime_error("ERROR: Terminal does not support color.\n");
  }
  // start_color();
  // init_pair(1, COLOR_BLACK, COLOR_BLUE);
  // wbkgd(wnd, COLOR_PAIR(0));

  attron(A_BOLD);
  box(wnd, 0, 0);
  attroff(A_BOLD);

  return 0;
}

void run() {
  screen &screen = screen::Instance(wnd);
  double t = 0;
  int s;

  model m1(vertices, trises);
  model m2(vertices, trises);
  m1.pos[2] = 4;
  m1.pos[0] = -2;
  m1.scale = 0.5;

  m2.pos[2] = 5;
  m2.pos[0] = +2;
  m2.scale = 0.8;
  // std::cin >> s;
  while (1) {
    t += 0.001;
    m1.rotation = rot_mat(Y, t);
    m2.rotation = rot_mat(Z, t);
    screen.clear();
    screen.create_object(m1);
    screen.create_object(m2);
    screen.redraw();
    nanosleep((const struct timespec[]){{0, (int)(1.0 / FPS * 5e7)}}, NULL);
  }
}

void close() { endwin(); }
