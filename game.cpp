#include "params.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#define SCREEN_CLEAR() printf("\033[H\033[J")
#define SCREEN_GOTO_TOPLEFT() printf("\033[0;0H")
#define SCREEN_HIDE_CURSOR() printf("\e[?25l")
#define SCREEN_SHOW_CURSOR() printf("\e[?25h")
#define FPS 120

using pixel = char;

void draw_frame(char *screen) {
  char pixel = ' ';
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (i == 0 || i == HEIGHT - 1)
        pixel = '=';
      if (j == 0 || j == WIDTH - 1)
        pixel = '|';

      screen[i * WIDTH + j] = pixel;
      pixel = '.';
    }
  }
}

int main(int argc, char *argv[]) {
  pixel *screen = new pixel[WIDTH * HEIGHT + 1];

  screen[WIDTH * HEIGHT] = '\0';

  int t = 0;
  int dt = 1;
  int s = 5;
  SCREEN_HIDE_CURSOR();
  char pixel = ' ';
  while (1) {
    t += dt;
    // draw_frame(screen);
    for (int i = 0; i < HEIGHT; i++) {
      for (int j = 0; j < WIDTH; j++) {
        double x = 40, y = 12;
        x += 50 * sin(t * 0.001);
        y += 50 * sin(t * 0.001);
        if (i == 0 || i == HEIGHT - 1)
          pixel = '=';
        else if (j == 0 || j == WIDTH - 1)
          pixel = '|';
        else if (std::abs(y - i) < s && std::abs(x - j) < s)
          pixel = '#';
        else
          pixel = '.';
        screen[i * WIDTH + j] = pixel;
      }
    }

    printf("%s", screen);
    SCREEN_GOTO_TOPLEFT();
    nanosleep((const struct timespec[]){{0, (int)(1.0 / FPS * 1e8)}}, NULL);
  }

  return 0;
}
