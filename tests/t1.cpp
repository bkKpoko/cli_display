#include <algorithm>
#include <cmath>
#include <cstdio>

#define SQR(a) (a) * (a)

int main(int argc, char *argv[]) {

  const int GRAYSCALE_SIZE = 6;
  int COLS = 100, LINES = 31;
  double aspect = (double)COLS / LINES;
  double aspect_font = 0.5;
  int pr = 0;
  for (int i = 0; i < COLS; ++i) {
    double x = double(i - 1) / (COLS - 1) * 2 - 1;
    x *= aspect * aspect_font;
    double dist = std::sqrt(SQR(x) + SQR(0));

    int color = (int)(1. / dist * (GRAYSCALE_SIZE));
    color = std::clamp(color, 0, GRAYSCALE_SIZE - 1);
    if (color != pr) {
      puts("");
    }
    printf("%i ", color);
    pr = color;
  }
  puts("");
  return 0;
}
