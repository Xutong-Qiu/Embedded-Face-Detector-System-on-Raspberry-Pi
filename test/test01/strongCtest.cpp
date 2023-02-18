#include "../../src/utils/strongC.h"
#include "../../src/utils/utils.h"

#include <iostream>
#include <limits.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#define T 2


using namespace std;

//g++ strongCdriver.cpp strongC.h strongC.cpp

int main(int argc, char *argv[]) {

  printf("Strong C object test\n");
  vector<float> alpha{0.3,0.5};
  vector<WeakClassifier> weakc_final;
  WeakClassifier *w = new WeakClassifier(1,2,2);
  WeakClassifier *w1 = new WeakClassifier(1,2,1);
  weakc_final.push_back(*w);
  weakc_final.push_back(*w1);
  
  //int T, vector<float> alpha, vectr<float> weakc_final
  auto* t = new strongC(2,alpha,weakc_final);
  vector<vector<int>> input{{1, 2},{4, 5},{7, 8}};
  printf("ready to test\n");
  t->test(input);
  printf("Done\n");
}