#include "game.h"
#include "lin_alg.h"
#include <algorithm>
#include <cstdio>
#include <ctime>
#include <fstream>
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
  int t = 0;

  for (size_t i = 0; i < vertices.size(); i++) {
    vertices[i].x -= 1.5;
    vertices[i].z += 7;
  }
  screen.create_object(vertices, trises);
  while (1) {
    t++;
    for (int i = 1; i < LINES - 1; i++) {
      for (int j = 1; j < COLS - 1; j++) {
        // double x = double(j - 1) / (COLS - 1) * 2 - 1;
        // double y = double(i - 1) / (LINES - 1) * 2 - 1;
        // x *= aspect * pixel_aspect;
        // x += sin(t * 1e-3);

        // double dist = std::sqrt(SQR(x) + SQR(y));
        // int color = int(1. / dist);
        // color = std::clamp(color, 0, GRAYSCALE_SIZE - 1);

        // p = GRAYSCALE[color];
        // screen.pixels[i][j] = p;
        // screen.pixels[i][j].ext_color = color;
      }
    }
    screen.redraw();
    nanosleep((const struct timespec[]){{0, (int)(1.0 / FPS * 5e7)}}, NULL);
  }
}

void close() { endwin(); }
