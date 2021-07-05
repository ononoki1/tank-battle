#include "control.h"
#include "enemy.h"
#include "tank.h"
#include "ui.h"
#include <iostream>
#include <random>
#include <unistd.h>

int map[LEN][WID];
int old_map[LEN][WID];
const int type_num = 2;
int kill_num = 0;
int need_kill = 2;

[[noreturn]] void mapUpdate() {
  int time = 0;
  random_device device;
  mt19937_64 engine{device()};
  uniform_int_distribution<int> len(0, LEN - 1), wid(0, WID - 1),
      direction(UP, RIGHT);
  while (true) {
    time++;
    if (time % 20 == 0)
      enemyAi();
    if (time % 200 == 0) {
      need_kill++;
      tank.emplace_back(len(engine), wid(engine), (Key)direction(engine), 10);
    }
    refresh();
    print();
    usleep(10000);
  }
}

void init() {
  random_device device;
  mt19937_64 engine{device()};
  uniform_int_distribution<int> len(0, LEN - 1), wid(0, WID - 1),
      direction(UP, RIGHT);
  for (int i = 0; i < LEN; i++)
    for (int j = 0; j < WID; j++) {
      old_map[i][j] = 0;
      map[i][j] = 0;
    }
  tank.emplace_back(len(engine), wid(engine), (Key)direction(engine), 20);
  tank.emplace_back(len(engine), wid(engine), (Key)direction(engine), 10);
  tank.emplace_back(len(engine), wid(engine), (Key)direction(engine), 10);
  me = tank.begin();
  initUi();
}

void refresh() {
  moveMap();
  clearMap();
  Bullet::refresh();
  Tank::refresh();
}

void endJudge() {
  while (true) {
    if (kill_num == -1) {
      cursorShow();
      clearAll();
      cursorLocate(-1, -1);
      cout << "You lose." << endl;
      return;
    } else if (kill_num == need_kill) {
      cursorShow();
      clearAll();
      cursorLocate(-1, -1);
      cout << "You win." << endl;
      return;
    }
  }
}

void moveMap() {
  for (int i = 0; i < LEN; i++)
    for (int j = 0; j < WID; j++)
      old_map[i][j] = map[i][j];
}
void clearMap() {
  for (auto &i : map)
    for (auto &j : i)
      j = 0;
}