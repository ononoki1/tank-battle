#include "control.h"
#include "key.h"
#include <thread>
using namespace std;

int main() {
  init();
  thread mapProcess(mapUpdate);
  mapProcess.detach();
  thread keyProcess(keyUpdate);
  keyProcess.detach();
  thread judgeProcess(endJudge);
  judgeProcess.join();
  return 0;
}