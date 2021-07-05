#include "enemy.h"

void enemyAi() {
  for (auto i = tank.begin(); i != tank.end(); i++) {
    if (i == me)
      continue;
    i->enemyMove();
  }
}