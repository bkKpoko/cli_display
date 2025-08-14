#include "game.h"
#include <cstdio>
#include <ncurses.h>
#include <stdexcept>
#include <unistd.h>

WINDOW *wnd;

struct {
  vec2i pos;
  char disp_char;
} player;

int init() {
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

  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  wbkgd(wnd, COLOR_PAIR(0));

  attron(A_BOLD);
  box(wnd, 0, 0);
  attroff(A_BOLD);

  return 0;
}

void run() {
  player.disp_char = '#';
  player.pos = {10, 5};

  mvaddch(player.pos.y, player.pos.x, player.disp_char);

  move(LINES / 2, COLS / 2);
  addstr("AHOI MATES! IT'S BLOODY NCURSESW");
  refresh();
  int in_char;
  bool exit_requested = false;
  while (1) {
    in_char = wgetch(wnd);
    mvaddch(player.pos.y, player.pos.x, ' ');

    switch (in_char) {
    case 'q':
      exit_requested = true;
      break;
    case KEY_UP:
    case 'w':
      player.pos.y -= 1;
      break;
    case KEY_DOWN:
    case 's':
      player.pos.y += 1;
      break;
    case KEY_LEFT:
    case 'a':
      player.pos.x -= 1;
      break;
    case KEY_RIGHT:
    case 'd':
      player.pos.x += 1;
      break;
    default:
      break;
    }
    mvaddch(player.pos.y, player.pos.x, player.disp_char);
    refresh();
    if (exit_requested)
      break;
    usleep(10000);
  }
}

void close() { endwin(); }

int main(int argc, char *argv[]) {
  if (init() == 0) {
    run();
  }
  close();
  return 0;
}
