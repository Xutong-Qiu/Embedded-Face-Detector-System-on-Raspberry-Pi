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

  printf("Strong C train test\n");
  vector<float> alpha;
  vector<WeakClassifier> weakc_final;
  
  auto* t = new strongC(2,alpha,weakc_final);
  printf("ready to train\n");
  char good [] = "../../dataset/good_integral/train/";
  char bad [] = "../../dataset/bad_integral/train/";
  t->train(good,bad);
  printf("Done\n");
}