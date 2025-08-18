#ifndef _GAME_H_
#define _GAME_H_

#include "lin_alg.h"
#include "vec3.h"
#include <iterator>
#include <ncurses.h>

#define GRAY0 L'·' // 0xB7
#define GRAY1 L'░' // 0x2591
#define GRAY2 L'▒' // 0x2592
#define GRAY3 L'▓' // 0x2593
#define GRAY4 L'█' // 0x2588

#define CURSOR_TO_START() move(1, 1)
#define FPS 120
#define SQR(a) (a) * (a)

const wchar_t HORIZONTAL = L'═'; // 0x2550
const wchar_t VERTICAL = L'║';   // 0x2551
const wchar_t ANGLE_L_T = L'╔';  // 0x2554
const wchar_t ANGLE_L_B = L'╚';  // 0x255A
const wchar_t ANGLE_R_B = L'╝';  // 0x255D
const wchar_t ANGLE_R_T = L'╗';  // 0x2557

const wchar_t TR_LEFT = L'╠';   // 0x2560
const wchar_t TR_TOP = L'╦';    // 0x2566
const wchar_t TR_BOTTOM = L'╩'; // x25669
const wchar_t TR_RIGHT = L'╣';  // 0x2563
const wchar_t CROSS = L'╬';     // 0x256C

const wchar_t GRAYSCALE[] = L" ·:!/r(l1Z4H9W8$@";
const int GRAYSCALE_SIZE = std::size(GRAYSCALE) - 2;

const int viewport_size = 1;
const int proj_plane_z = 1;
const double aspect = (double)(COLS - 1) / (LINES - 1);
const double font_aspect = 0.6;

using pixel = cchar_t;
using Matrix = Nmatrix<pixel>;

template <class T> Nvector<T> interpolate(T i0, T d0, T i1, T d1) {
  Nvector<T> v(i1 - i0 + 1);

  double a = (double)(d1 - d0) / (i1 - i0);
  double d = d0;
  for (int j = i0, i = 0; j < i1; i++, j++) {
    v[i] = (T)d;
    d += a;
  }
  return v;
}

using vertex3d = vec3<double>;

struct point {
  int x, y;
  double h;

  point();
  point(int x, int y, double h = 1.0);
  point(vertex3d v);
};

typedef struct {
  size_t v[3];
} triangle;

class model;

struct screen {
public:
  static screen &Instance(WINDOW *win);

  void redraw();
  void create_tr(triangle tr, Nvector<point> points);
  void create_line(point p0, point p1, pixel color = GRAY[GRAYSCALE_SIZE - 1]);
  void create_wf_tr(point p0, point p1, point p2,
                    pixel color = GRAY[GRAYSCALE_SIZE - 1]);
  void create_filled_tr(point p0, point p1, point p2,
                        pixel color = GRAY[GRAYSCALE_SIZE - 1]);
  void create_shaded_tr(point p0, point p1, point p2);
  void create_object(Nvector<vertex3d> v, Nvector<triangle> tr);
  void create_object(model m);

private:
  WINDOW *wnd_p;
  Matrix pixels;

  static inline cchar_t vert, hor;
  static inline cchar_t top_left, bot_left;
  static inline cchar_t top_right, bot_right;
  static inline cchar_t GRAY[GRAYSCALE_SIZE];

  screen(WINDOW *win);
  ~screen();
  static void init();

  screen(screen const &) = delete;
  screen &operator=(screen const &) = delete;
};

#endif // !_GAME_H_
