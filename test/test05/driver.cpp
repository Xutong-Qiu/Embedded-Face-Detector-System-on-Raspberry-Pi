#include "../../src/graph/graph.h"
#include <iostream>


using namespace std;

//g++ strongCdriver.cpp strongC.h strongC.cpp

int main(int argc, char *argv[]) {
    /*
  printf("Strong C object test\n");
  vector<float> alpha{0.3,0.5};
  vector<float> weakc_final{1.0,3.0,0.9,1.0,2.0,0.4};
  
  
  //int T, vector<float> alpha, vectr<float> weakc_final
  auto* t = new strongC(2,alpha,weakc_final);
  vector<vector<int>> input{{1, 2},{4, 5},{7, 8}};
  printf("ready to test\n");
  t->test(input);
  */

  auto* g = new graph(argv[1],argv[2],argv[3], argv[4]);
  g->setIters(1);
  g->scheduler();
}