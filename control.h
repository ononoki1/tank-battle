#pragma once

#define LEN 80
#define WID 30

extern int map[LEN][WID];
extern int old_map[LEN][WID];
extern const int type_num;
extern int kill_num;

void init();
void clearMap();
void moveMap();
void refresh();
void endJudge();
[[noreturn]] void mapUpdate();