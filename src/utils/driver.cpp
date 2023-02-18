#include "utils.h"
#include <iostream>
#include "WeakClassifier.h"
using namespace std;


int main(int argc, char *argv[]) {
  vector<vector<int>> test_img = read_txt_image (argv[1], 24, 24);
  WeakClassifier* w = new WeakClassifier(4,5,24,-6600,-1);
  //1,8,24,2000,-1
  int a = w->classify(test_img);
  cout << a<<endl;
  //write_txt_image(argv[2], integral);
  //cout<<detect_feature(integral, 1, 2, 1, 1, 10);
  return 0;
}