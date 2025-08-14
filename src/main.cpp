#include "game.h"
#include "lin_alg.h"
#include <algorithm>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <ncurses.h>
#include <vector>

WINDOW *wnd;

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

  wchar_t f_c = '#';
  pixel f_p;
  setcchar(&f_p, &f_c, WA_NORMAL, 0, NULL);

  wchar_t b_c = '/';
  pixel b_p;
  setcchar(&b_p, &b_c, WA_NORMAL, 0, NULL);

  wchar_t c_c = '.';
  pixel c_p;
  setcchar(&c_p, &c_c, WA_NORMAL, 0, NULL);

  const vertex3d vA{-2, -0.5, 5};
  const vertex3d vB{-2, 0.5, 5};
  const vertex3d vC{-1, 0.5, 5};
  const vertex3d vD{-1, -0.5, 5};

  const vertex3d vAb{-2, -0.5, 7};
  const vertex3d vBb{-2, 0.5, 7};
  const vertex3d vCb{-1, 0.5, 7};
  const vertex3d vDb{-1, -0.5, 7};

  screen.create_line(point(vAb), point(vBb), b_p);
  screen.create_line(point(vBb), point(vCb), b_p);
  screen.create_line(point(vCb), point(vDb), b_p);
  screen.create_line(point(vDb), point(vAb), b_p);

  screen.create_line(point(vA), point(vAb), c_p);
  screen.create_line(point(vB), point(vBb), c_p);
  screen.create_line(point(vC), point(vCb), c_p);
  screen.create_line(point(vD), point(vDb), c_p);

  screen.create_line(point(vA), point(vB));
  screen.create_line(point(vB), point(vC));
  screen.create_line(point(vC), point(vD));
  screen.create_line(point(vD), point(vA));

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
