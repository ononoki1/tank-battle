#pragma once

enum Key { NONE, UP, DOWN, LEFT, RIGHT, SPACE };

int keyHit();
Key direction();
[[noreturn]] void keyUpdate();