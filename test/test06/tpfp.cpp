#include "../../src/utils/strongC.h"
#include "../../src/utils/utils.h"
#include <iostream>
#include <limits.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>



using namespace std;

//g++ strongCdriver.cpp strongC.h strongC.cpp

int main(int argc, char *argv[]) {

  printf("TP rate test\n");
  char fold[] = "../../dataset/good_integral/validation";
  char fold1[] = "../../dataset/bad_integral/validation";
  char firgood[] = "../test04/output1.txt";
  char secgood[] = "../test04/output2.txt";
  char firbad[] = "../test05/output1.txt";
  char secbad[] = "../test05/output2.txt";
  //int T, vector<float> alpha, vectr<float> weakc_final
  
  printf("ready to test\n");
  int firstgoodinput = tprate(fold,firgood);
  int firstbadinput = fprate(fold1,firbad);
  tp2rate(firstgoodinput,secgood);
  fp2rate(firstbadinput,secbad);
  printf("Done\n");
}