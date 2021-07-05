#include "key.h"
#include "tank.h"
#include <fcntl.h>
#include <iostream>
#include <termios.h>
#include <unistd.h>
using namespace std;

[[noreturn]] void keyUpdate() {
  while (true) {
    switch (direction()) {
    case NONE:
      break;
    case UP:
      me->up();
      break;
    case DOWN:
      me->down();
      break;
    case LEFT:
      me->left();
      break;
    case RIGHT:
      me->right();
      break;
    case SPACE:
      me->fire();
      break;
    }
  }
}

//上 27,91,65 1
//下 27,91,66 2
//左 27,91,68 3
//右 27,91,67 4
//空格 32 5

Key direction() {
  int key = keyHit();
  if (key == 32)
    return SPACE;
  if (key != 27)
    return NONE;
  if (keyHit() != 91)
    return NONE;
  key = keyHit();
  if (key == 65)
    return UP;
  else if (key == 66)
    return DOWN;
  else if (key == 68)
    return LEFT;
  else if (key == 67)
    return RIGHT;
  else
    return NONE;
}

int keyHit() {
  termios old_t{}, new_t{};
  int ch, old_f;
  tcgetattr(STDIN_FILENO, &old_t);
  new_t = old_t;
  new_t.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &new_t);
  old_f = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, old_f | O_NONBLOCK);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &old_t);
  fcntl(STDIN_FILENO, F_SETFL, old_f);
  if (ch != EOF) {
    ungetc(ch, stdin);
    return getchar();
  }
  return 0;
}