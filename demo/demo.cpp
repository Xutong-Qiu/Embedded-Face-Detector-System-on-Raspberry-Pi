#include "../src/graph/graph.h"
#include <iostream>


using namespace std;

int main(int argc, char *argv[]) {

  auto* g = new graph(argv[1],argv[2],argv[3], argv[4]);
  g->setIters(1);
  g->scheduler();
}