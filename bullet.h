#pragma once

#include "key.h"
#include <list>
using namespace std;

class Bullet {
private:
  int x, y;
  Key direction;
  int speed;
  bool need_destroy;
  int id;
  int harm;
  bool is_new;

public:
  Bullet(int x, int y, Key direction, int speed, int harm);
  void move();
  bool operator==(Bullet b) const;
  static void refresh();
};

extern list<Bullet> bullet;
extern int bullet_id;