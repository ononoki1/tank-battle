#include "tank.h"
#include "control.h"
#include <vector>

list<Tank> tank;
int tank_id = 1;
_List_iterator<Tank> me;

void Tank::refresh() {
  vector<_List_iterator<Tank>> del;
  for (auto i = tank.begin(); i != tank.end(); i++)
    if (i->need_destroy) {
      del.push_back(i);
      if (i == me)
        kill_num = -1;
      else
        kill_num++;
    }
  for (auto &i : del)
    tank.erase(i);
  for (auto &i : tank)
    map[i.x][i.y] = i.id;
}

void Tank::fire() {
  switch (direction) {
  case UP:
    bullet.emplace_back(x, y - 1, direction, 1, 1);
    break;
  case DOWN:
    bullet.emplace_back(x, y + 1, direction, 1, 1);
    break;
  case LEFT:
    bullet.emplace_back(x - 1, y, direction, 1, 1);
    break;
  case RIGHT:
    bullet.emplace_back(x + 1, y, direction, 1, 1);
    break;
  default:
    break;
  }
}

void Tank::up() {
  direction = UP;
  if (y > 0 && old_map[x][y - 1] % type_num == 0 &&
      map[x][y - 1] % type_num == 0) {
    y--;
    map[x][y] = id;
  }
}
void Tank::down() {
  direction = DOWN;
  if (y < WID - 1 && old_map[x][y + 1] % type_num == 0 &&
      map[x][y + 1] % type_num == 0) {
    y++;
    map[x][y] = id;
  }
}
void Tank::left() {
  direction = LEFT;
  if (x > 0 && old_map[x - 1][y] % type_num == 0 &&
      map[x - 1][y] % type_num == 0) {
    x--;
    map[x][y] = id;
  }
}
void Tank::right() {
  direction = RIGHT;
  if (x < LEN - 1 && old_map[x + 1][y] % type_num == 0 &&
      map[x + 1][y] % type_num == 0) {
    x++;
    map[x][y] = id;
  }
}

void Tank::hurt(int harm) {
  blood -= harm;
  if (blood <= 0)
    need_destroy = true;
}

Tank::Tank(int x, int y, Key direction, int blood) {
  this->x = x;
  this->y = y;
  this->direction = direction;
  this->blood = blood;
  id = tank_id;
  tank_id += type_num;
  need_destroy = false;
  map[x][y] = id;
}

bool Tank::operator==(Tank t) const { return id == t.id; }
int Tank::getId() const { return id; }
int Tank::getBlood() const { return blood; }

void Tank::enemyMove() {
  if (x < me->x)
    right();
  else if (x > me->x)
    left();
  if (y < me->y)
    down();
  else if (y > me->y)
    up();
  if (x == me->x) {
    if (y < me->y) {
      if (direction != DOWN)
        down();
    } else if (direction != UP)
      up();
    fire();
  } else if (y == me->y) {
    if (x < me->x) {
      if (direction != RIGHT)
        right();
    } else if (direction != LEFT)
      left();
    fire();
  }
}