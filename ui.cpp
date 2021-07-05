#include "ui.h"
#include "control.h"
#include "tank.h"
#include <iostream>

void print() {
  for (int i = 0; i < LEN; i++)
    for (int j = 0; j < WID; j++) {
      cursorLocate(i, j);
      cout << draw(i, j) << flush;
    }
  cursorLocate(LEN + 4, WID / 2 + 1);
  cout << me->getBlood() << "   " << flush;
}

string draw(int x, int y) {
  if (map[x][y] == 0)
    return " ";
  if (map[x][y] % type_num == 0)
    return "●";
  if (map[x][y] == 1)
    return "o";
  return "x";
}

void initUi() {
  cursorHide();
  clearAll();
  char bound = '-';
  cursorLocate(-1, -1);
  for (int i = -1; i < LEN + 1; i++)
    cout << bound << flush;
  cout << "\n" << flush;
  for (int i = 0; i < WID; i++) {
    cout << bound << flush;
    for (int j = 0; j < LEN; j++)
      cout << " " << flush;
    cout << bound << "\n" << flush;
  }
  for (int i = -1; i < LEN + 1; i++)
    cout << bound << flush;
  cursorLocate(LEN + 2, WID / 2);
  cout << "Blood:" << flush;
}

void cursorHide() { cout << "\033[?25l" << flush; }
void cursorShow() { cout << "\033[?25h" << flush; }
void cursorLocate(int x, int y) {
  cout << "\033[" << y + 2 << ";" << x + 2 << "H" << flush;
}
void clearLine(int y) {
  cout << "\033[" << y + 2 << ";1H" << flush;
  cout << "\033[K" << flush;
}
void clearAll() {
  for (int i = -1; i < 99; i++)
    clearLine(i);
}