#include "bullet.h"
#include "control.h"
#include "tank.h"
#include <vector>

list<Bullet> bullet;
int bullet_id = 2;

void Bullet::refresh() {
  vector<_List_iterator<Bullet>> del;
  for (auto i = bullet.begin(); i != bullet.end(); i++) {
    if (i->is_new)
      i->is_new = false;
    else
      i->move();
    if (i->need_destroy)
      del.push_back(i);
  }
  for (auto &i : del)
    bullet.erase(i);
  del.clear();
  vector<int> id, harm;
  for (auto i = bullet.begin(); i != bullet.end(); i++)
    if (old_map[i->x][i->y] % type_num == 1) {
      id.push_back(old_map[i->x][i->y]);
      harm.push_back(i->harm);
      del.push_back(i);
    }
  for (auto &i : del)
    bullet.erase(i);
  for (int i = 0; i < id.size(); i++)
    for (auto &j : tank)
      if (id[i] == j.getId()) {
        j.hurt(harm[i]);
        break;
      }
  for (auto &i : bullet)
    map[i.x][i.y] = i.id;
}

Bullet::Bullet(int x, int y, Key direction, int speed, int harm) {
  this->x = x;
  this->y = y;
  this->direction = direction;
  this->speed = speed;
  this->harm = harm;
  if (x < 0 || x > LEN - 1 || y < 0 || y > WID - 1)
    need_destroy = true;
  else
    need_destroy = false;
  id = bullet_id;
  bullet_id += type_num;
  map[x][y] = id;
  is_new = true;
}

void Bullet::move() {
  switch (direction) {
  case UP:
    y -= speed;
    break;
  case DOWN:
    y += speed;
    break;
  case LEFT:
    x -= speed;
    break;
  case RIGHT:
    x += speed;
    break;
  default:
    break;
  }
  if (x < 0 || x > LEN - 1 || y < 0 || y > WID - 1)
    need_destroy = true;
}

bool Bullet::operator==(Bullet b) const { return id == b.id; }