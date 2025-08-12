#include "lin_alg.h"
#include "params.h"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cwchar>
#include <iostream>
#include <string>

#define SCREEN_CLEAR() wprintf(L"\033[H\033[J")
#define SCREEN_GOTO_TOPLEFT() wprintf(L"\033[0;0H")
#define SCREEN_HIDE_CURSOR() wprintf(L"\e[?25l")
#define SCREEN_SHOW_CURSOR() wprintf(L"\e[?25h")
#define FPS 120

#define UI_HEIGHT 5
#define UI_WIDTH 20
#define SQR(a) (a) * (a)

using pixel = wchar_t;
using Matrix = Nmatrix<pixel>;

struct Rect {
  int x, y;
  int size_x, size_y;

  Matrix pixels;

  Rect(int x_pos, int y_pos, int size_x, int size_y, bool add_frame = false)
      : x(x_pos), y(y_pos), size_x(size_x), size_y(size_y) {
    pixels = Matrix(size_y, size_x, GRAY1);
    if (add_frame)
      if (size_x > 1 && size_y > 1)
        create_frame();
  }

  void create_frame() {
    for (int j = 0; j < size_x; j++) {
      pixels[0][j] = HORIZONTAL;
      pixels[size_y - 1][j] = HORIZONTAL;
    }
    for (int i = 0; i < size_y; i++) {
      pixels[i][0] = VERTICAL;
      pixels[i][size_x - 1] = VERTICAL;
    }
    pixels[0][0] = ANGLE_L_T;
    pixels[0][size_x - 1] = ANGLE_R_T;
    pixels[size_y - 1][0] = ANGLE_L_B;
    pixels[size_y - 1][size_x - 1] = ANGLE_R_B;
  }
};

struct Screen {
  int n_rows, n_cols;
  double aspect;
  double font_aspect;

  Matrix pixels;

  Screen(int r = 9 * 5, int c = 16 * 8)
      : n_rows(r), n_cols(c), aspect(double(c) / r), font_aspect(FONT_ASPECT) {
    pixels = Matrix(r, c, GRAY0);
    SCREEN_HIDE_CURSOR();
    redraw();
  }

  void write_str_ui(std::string str) {
    if (str.size() > UI_WIDTH) {
      return;
    }
    int y_c = UI_HEIGHT / 2;

    int str_pos = (UI_WIDTH - str.size()) / 2;
    for (size_t i = 0; i < str.size(); i++) {
      pixels[y_c][str_pos + i] = str[i];
    }
  }

  void draw_ui() {
    for (size_t i = 0; i < UI_HEIGHT; i++) {
      pixels[i][UI_WIDTH - 1] = VERTICAL;
    }
    for (size_t i = 0; i < UI_WIDTH; i++) {
      pixels[UI_HEIGHT - 1][i] = HORIZONTAL;
    }
    for (size_t i = 1; i < UI_HEIGHT - 1; i++) {
      for (size_t j = 1; j < UI_WIDTH - 1; j++) {
        pixels[i][j] = GRAY1;
      }
    }

    write_str_ui("HOI MATES");

    pixels[0][UI_WIDTH - 1] = TR_TOP;
    pixels[UI_HEIGHT - 1][0] = TR_LEFT;
    pixels[UI_HEIGHT - 1][UI_WIDTH - 1] = ANGLE_R_B;
  }

  void draw_frame() {
    Rect r(0, 0, WIDTH, HEIGHT);
    r.pixels = pixels;
    r.create_frame();
    draw_rect(r);
    draw_ui();
  }

  void redraw() {
    draw_frame();
    wprintf(L"%ls", pixels[0]);
    SCREEN_GOTO_TOPLEFT();
  }

  void draw_rect(Rect &r) {
    if (r.x < 0 || r.y < 0 || r.x + r.size_x > n_cols ||
        r.y + r.size_y > n_rows)
      return;

    for (size_t i = 0; i < r.size_y; i++) {
      for (size_t j = 0; j < r.size_x; j++) {
        pixels[r.y + i][r.x + j] = r.pixels[i][j];
      }
    }
  }
};

struct Circle {
  double x, y;
  double r;

  void draw(Matrix &screen) {}
};

int main(int argc, char *argv[]) {
  std::setlocale(LC_ALL, "");
  Screen screen(HEIGHT, WIDTH);
  int screen_center_x = WIDTH / 2;
  int screen_center_y = HEIGHT / 2;

  Circle c{0, 0, 5};

  int t = 0;
  int dt = 1;
  int s = 5;
  pixel p = GRAY0;
  double aspect = (double)WIDTH / HEIGHT;
  double pixel_aspect = 0.5;

  Rect r(5, HEIGHT - 6, 2, 2, true);
  while (1) {
    t++;
    for (int i = 1; i < HEIGHT - 1; i++) {
      for (int j = 1; j < WIDTH - 1; j++) {
        float x = double(j) / (WIDTH - 1) * 2 - 1;
        float y = double(i) / (HEIGHT - 1) * 2 - 1;
        x *= aspect * pixel_aspect;
        x += sin(t * 1e-3);

        double dist = std::sqrt(SQR(x) + SQR(y));
        int color = int(1. / dist);
        color = std::clamp(color, 0, GRAYSCALE_SIZE - 1);

        p = GRAYSCALE[color];
        screen.pixels[i][j] = p;
      }
    }
    // screen.draw_frame();

    screen.draw_rect(r);

    screen.redraw();
    nanosleep((const struct timespec[]){{0, (int)(1.0 / FPS * 5e7)}}, NULL);
    // std::cin >> s;
  }
  return 0;
}
