#include "game.h"
#include "lin_alg.h"
#include "model.h"
#include "rot_mat.h"
#include <cstdio>
#include <ctime>
#include <ncurses.h>

WINDOW *wnd;

const double l = 1.;

Nvector<vertex3d> vertices = {vertex3d{l, l, l},    vertex3d{-l, l, l},
                              vertex3d{-l, -l, l},  vertex3d{l, -l, l},
                              vertex3d{l, l, -l},   vertex3d{-l, l, -l},
                              vertex3d{-l, -l, -l}, vertex3d{l, -l, -l}};

const Nvector<triangle> trises = {
    triangle{vec3<size_t>{0, 1, 2}}, triangle{vec3<size_t>{0, 2, 3}},
    triangle{vec3<size_t>{4, 0, 3}}, triangle{vec3<size_t>{4, 3, 7}},
    triangle{vec3<size_t>{5, 4, 7}}, triangle{vec3<size_t>{5, 7, 6}},
    triangle{vec3<size_t>{1, 5, 6}}, triangle{vec3<size_t>{1, 6, 2}},
    triangle{vec3<size_t>{4, 5, 1}}, triangle{vec3<size_t>{4, 1, 0}},
    triangle{vec3<size_t>{2, 6, 7}}, triangle{vec3<size_t>{2, 7, 3}}};

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
  start_color();
  init_pair(1, COLOR_BLACK, COLOR_BLUE);
  wbkgd(wnd, COLOR_PAIR(0));

  attron(A_BOLD);
  box(wnd, 0, 0);
  attroff(A_BOLD);

  return 0;
}

void run() {
  screen &screen = screen::Instance(wnd);

  model m1(vertices, trises);
  model m2(vertices, trises);
  model m3;

  m3.import_stl("mesh/monke.stl");
  m3.pos[2] = 4;
  m3.scale = 0.9;
  m1.pos[2] = 4;
  m1.pos[0] = -2;
  m1.scale = 0.5;

  m2.pos[2] = 5;
  m2.pos[0] = 2;
  m2.scale = 0.8;

  double t = 0;
  while (1) {
    t += 2e-3;
    m1.rotation = rot_mat(Y, t);
    m2.rotation = rot_mat(Z, t);
    m3.rotation = rot_mat(Y, t);
    screen.clear();
    // screen.create_object(m1);
    // screen.create_object(m2);
    screen.create_object(m3);
    screen.redraw();
    nanosleep((const struct timespec[]){{0, (int)(1.0 / FPS * 5e7)}}, NULL);
  }
}

void close() { endwin(); }
