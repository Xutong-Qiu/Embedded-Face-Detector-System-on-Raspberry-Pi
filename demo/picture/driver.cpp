#include "../../src/utils/utils.h"
#include <iostream>

using namespace std;


int main(int argc, char *argv[]) {
  vector<vector<int>> test_img = read_txt_image (argv[1], 24, 24);
  vector<vector<int>> integral = norm2integral (test_img);
  write_txt_image(argv[2], integral);
  return 0;
}