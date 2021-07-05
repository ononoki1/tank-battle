#pragma once

#include "bullet.h"
#include "key.h"

class Tank {
private:
  int x, y;
  Key direction;
  int blood;
  int id;
  bool need_destroy;

public:
  Tank(int x, int y, Key direction, int blood);
  void up();
  void down();
  void left();
  void right();
  static void refresh();
  void fire();
  void hurt(int harm);
  bool operator==(Tank t) const;
  int getId() const;
  void enemyMove();
  int getBlood() const;
};

extern list<Tank> tank;
extern int tank_id;
extern _List_iterator<Tank> me;