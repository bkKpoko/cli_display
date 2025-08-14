#include "game.h"
#include <ncurses.h>

// =========================================
// struct screen begin
// =========================================

screen &screen::Instance(WINDOW *win) {
  static screen s(win);
  return s;
}

screen::screen(WINDOW *win) : wnd_p(win) {
  init();
  wchar_t x = ' ';
  cchar_t tmp;
  setcchar(&tmp, &x, WA_NORMAL, 0, NULL);
  pixels = Matrix(LINES, COLS, tmp);
  wborder_set(wnd_p, &vert, &vert, &hor, &hor, &top_left, &top_right, &bot_left,
              &bot_right);
  redraw();
}

void screen::init() {
  for (size_t i = 0; i < GRAYSCALE_SIZE; i++) {
    setcchar(&GRAY[i], &GRAYSCALE[i], WA_NORMAL, 0, NULL);
  }

  setcchar(&vert, &VERTICAL, WA_NORMAL, 0, NULL);
  setcchar(&hor, &HORIZONTAL, WA_NORMAL, 0, NULL);
  setcchar(&top_left, &ANGLE_L_T, WA_NORMAL, 0, NULL);
  setcchar(&bot_left, &ANGLE_L_B, WA_NORMAL, 0, NULL);
  setcchar(&top_right, &ANGLE_R_T, WA_NORMAL, 0, NULL);
  setcchar(&bot_right, &ANGLE_R_B, WA_NORMAL, 0, NULL);
}

screen::~screen() {}

void screen::create_wf_tr(point p0, point p1, point p2, pixel color) {
  create_line(p0, p1, color);
  create_line(p1, p2, color);
  create_line(p2, p0, color);
}

void screen::redraw() {
  CURSOR_TO_START();
  for (size_t i = 1; i < LINES - 1; i++) {
    for (size_t j = 1; j < COLS - 1; j++) {
      mvwadd_wch(wnd_p, i, j, &pixels[i][j]);
    }
  }
  CURSOR_TO_START();
  refresh();
}

void screen::create_line(point p0, point p1, pixel color) {
  int dx = p1.x - p0.x;
  int dy = p1.y - p0.y;

  if (abs(dx) > abs(dy)) {
    if (dx < 0)
      SWAP(p0, p1);

    Nvector<int> ys = interpolate(p0.x, p0.y, p1.x, p1.y);
    for (int x = p0.x; x < p1.x; x++) {
      pixels[ys[x - p0.x]][x] = color;
    }
  } else {
    if (dy < 0)
      SWAP(p0, p1);

    Nvector<int> xs = interpolate(p0.y, p0.x, p1.y, p1.x);
    for (int y = p0.y; y < p1.y; y++) {
      pixels[y][xs[y - p0.y]] = color;
    }
  }
}

void screen::create_filled_tr(point p0, point p1, point p2, pixel color) {
  if (p1.y < p0.y)
    SWAP(p1, p0);
  if (p2.y < p0.y)
    SWAP(p2, p0);
  if (p2.y < p1.y)
    SWAP(p2, p1);

  Nvector<int> x01 = interpolate(p0.y, p0.x, p1.y, p1.x);
  Nvector<int> x12 = interpolate(p1.y, p1.x, p2.y, p2.x);
  Nvector<int> x02 = interpolate(p0.y, p0.x, p2.y, p2.x);

  x01.pop_back();
  Nvector<int> x012 = {x01, x12};

  int m = x012.size() / 2;
  Nvector<int> x_left;
  Nvector<int> x_right;
  if (x02[m] < x012[m]) {
    x_left = x02;
    x_right = x012;
  } else {
    x_left = x012;
    x_right = x02;
  }

  for (int y = p0.y; y < p2.y; y++) {
    for (int x = x_left[y - p0.y]; x < x_right[y - p0.y]; x++) {
      pixels[x][y] = color;
    }
  }
}

void screen::create_shaded_tr(point p0, point p1, point p2) {
  if (p1.y < p0.y)
    SWAP(p1, p0);
  if (p2.y < p0.y)
    SWAP(p2, p0);
  if (p2.y < p1.y)
    SWAP(p2, p1);

  Nvector<int> x01 = interpolate(p0.y, p0.x, p1.y, p1.x);
  Nvector<double> h01 = interpolate(double(p0.y), p0.h, double(p1.y), p1.h);

  Nvector<int> x12 = interpolate(p1.y, p1.x, p2.y, p2.x);
  Nvector<double> h12 = interpolate(double(p1.y), p1.h, double(p2.y), p2.h);

  Nvector<int> x02 = interpolate(p0.y, p0.x, p2.y, p2.x);
  Nvector<double> h02 = interpolate(double(p0.y), p0.h, double(p2.y), p2.h);

  x01.pop_back();
  Nvector<int> x012 = {x01, x12};

  h01.pop_back();
  Nvector<double> h012 = {h01, h12};

  int m = x012.size() / 2;
  Nvector<int> x_left, x_right;
  Nvector<double> h_left, h_right;

  if (x02[m] < x012[m]) {
    x_left = x02;
    h_left = h02;

    x_right = x012;
    h_right = h012;
  } else {
    x_left = x012;
    h_left = h012;

    x_right = x02;
    h_right = h02;
  }

  int xl, xr;
  Nvector<double> h_seg;
  for (int y = p0.y; y < p2.y; y++) {
    xl = x_left[y - p0.y];
    xr = x_right[y - p0.y];
    h_seg = interpolate(double(xl), h_left[y - p0.y], double(xr),
                        h_right[y - p0.y]);
    for (int x = xl; x < xr; x++) {
      // pixels[x][y] = GRAY[(int)(h_seg[x - xl] * GRAYSCALE_SIZE)];
    }
  }
}
// =========================================
// struct screen end
// =========================================

// =========================================
// struct point begin
// =========================================
point::point(int x, int y, double h) : x(x), y(y), h(h) {}

point::point(vertex3d v) {
  x = int((COLS - 1) * (0.5 + v.x * proj_plane_z / v.z) * font_aspect * aspect *
          viewport_size);
  y = int((LINES - 1) * (0.5 + v.y * proj_plane_z / v.z) * viewport_size);
  h = 1.0;
}

// =========================================
// struct point end
// =========================================
