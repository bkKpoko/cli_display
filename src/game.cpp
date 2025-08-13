#include "game.h"
#include "lin_alg.h"
#include <algorithm>
#include <ctime>
#include <ncurses.h>

#define CURSOR_TO_START() move(1, 1)
#define FPS 120

#define SQR(a) (a) * (a)

using pixel = wchar_t;
using Matrix = Nmatrix<pixel>;

WINDOW *wnd;
cchar_t vert, hor, top_left, bot_left, top_right, bot_right;

struct Screen {
  WINDOW *wnd_ptr;

  Matrix pixels;

  Screen(WINDOW *win) : wnd_ptr(win) {
    pixels = Matrix(LINES, COLS, GRAY0);
    redraw();
  }

  void redraw() {
    cchar_t pix;
    CURSOR_TO_START();

    wborder_set(wnd_ptr, &vert, &vert, &hor, &hor, &top_left, &top_right,
                &bot_left, &bot_right);
    for (size_t i = 1; i < LINES - 1; i++) {
      for (size_t j = 1; j < COLS - 1; j++) {
        setcchar(&pix, &pixels[i][j], WA_NORMAL, 0, NULL);
        mvwadd_wch(wnd_ptr, i, j, &pix);
      }
    }
    CURSOR_TO_START();
    refresh();
  }
};

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

  setcchar(&vert, &VERTICAL, WA_NORMAL, 0, NULL);
  setcchar(&hor, &HORIZONTAL, WA_NORMAL, 0, NULL);
  setcchar(&top_left, &ANGLE_L_T, WA_NORMAL, 0, NULL);
  setcchar(&bot_left, &ANGLE_L_B, WA_NORMAL, 0, NULL);
  setcchar(&top_right, &ANGLE_R_T, WA_NORMAL, 0, NULL);
  setcchar(&bot_right, &ANGLE_R_B, WA_NORMAL, 0, NULL);

  keypad(wnd, true);
  nodelay(wnd, true);
  curs_set(0);

  if (!has_colors()) {
    endwin();
    throw std::runtime_error("ERROR: Terminal does not support color.\n");
  }
  start_color();

  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  wbkgd(wnd, COLOR_PAIR(0));

  attron(A_BOLD);
  box(wnd, 0, 0);
  attroff(A_BOLD);

  return 0;
}

void run() {
  Screen screen(wnd);
  int t = 0;
  double aspect = (double)(COLS - 1) / (LINES - 1);
  double pixel_aspect = 0.5;

  pixel p = GRAY0;
  while (1) {
    t++;
    for (int i = 1; i < LINES - 1; i++) {
      for (int j = 1; j < COLS - 1; j++) {
        double x = double(j - 1) / (COLS - 1) * 2 - 1;
        double y = double(i - 1) / (LINES - 1) * 2 - 1;
        x *= aspect * pixel_aspect;
        x += sin(t * 1e-3);

        double dist = std::sqrt(SQR(x) + SQR(y));
        int color = int(1. / dist);
        color = std::clamp(color, 0, GRAYSCALE_SIZE - 1);

        p = GRAYSCALE[color];
        screen.pixels[i][j] = p;
      }
    }
    screen.redraw();
    nanosleep((const struct timespec[]){{0, (int)(1.0 / FPS * 5e7)}}, NULL);
  }
}

void close() { endwin(); }
