#pragma once

#include <string>
using namespace std;

string draw(int x, int y);
void initUi();
void cursorHide();
void cursorShow();
void cursorLocate(int x, int y);
void clearLine(int y);
void clearAll();
void print();