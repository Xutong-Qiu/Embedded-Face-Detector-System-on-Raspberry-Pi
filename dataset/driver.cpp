#include "utils.h"
#include <iostream>

using namespace std;


int main() {
  char name[14] = "face00001.txt";
  vector<vector<int>> test_img = read_txt_image (name, 24, 24);
  vector<vector<int>> integral = norm2integral (test_img);
  char name1[56] = "1.txt";
  write_txt_image(name1, integral);
  cout<<detect_feature(integral, 1, 2, 1, 1, 10);
  return 0;
}