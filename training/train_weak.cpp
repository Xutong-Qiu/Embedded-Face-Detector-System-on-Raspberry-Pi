#include <iostream>
#include <fstream>
#include <filesystem>
#include "utils.h"
#include "WeakClassifier.h"

using namespace std

int main()
{
  threshold = 0.8;
  polarity = 1;
  std::ofstream myfile;
  myfile.open("metrics.csv");
  myfile << "Pattern Type, True Positive Rate, True Negative Rate, False Positive Rate, False Negative Rate, Positive Efficiency, Negative Efficiency, Overall Efficiency";

  /* read in image vectors (loop through directory and save)*/
  std::vector<std::string> good_files;
  std::vector<std::string> bad_files;

  int num_good = 0;
  int num_bad = 0;

  std::string path = "../team1/dataset/raw_dataset/good_txt";
  for (const auto & entry : std::filesystem::directory_iterator(path)) {
      num_good = num_good + 1;
      good_files.push_back(entry.path());
  }

  std::string path = "../team1/dataset/raw_dataset/bad_txt";
  for (const auto & entry : std::filesystem::directory_iterator(path)) {
      num_bad = num_bad + 1;
      bad_files.push_back(entry.path());
  }

  std::vector<int> good[num_good];
  std::vector<int> bad[num_bad];

  int x = 0;
  for(string i : good_files) {
    good[x] = read_txt_image(i.c_str(), 24, 24);
    x = x + 1;
  }

  int y = 0;
  for(string i : good_files) {
    bad[y] = read_txt_image(i.c_str(), 24, 24);
    y = y + 1;
  }

  int p_one_x_param [12] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24};
  int p_one_y_param [24] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};

  int p_two_y_param [12] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24};
  int p_two_x_param [24] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};

  int p_three_x_param [8] = {3, 6, 9, 12, 15, 18, 21, 24};
  int p_three_y_param [24] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};

  int p_four_y_param [8] = {3, 6, 9, 12, 15, 18, 21, 24};
  int p_four_x_param [24] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};

  int p_five_y_param [12] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24};
  int p_five_x_param [12] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24};

  /* Testing metrics for pattern one analysis */
  for(int i = 0; i < sizeof(p_one_x_param); i = i + 1) {
    for(int j = 0; j < sizeof(p_one_y_param); j = j + 1) {
      WeakClassifier temp(1, i, j, threshold, polarity);
      float true_positive = 0;
      float true_negative = 0;
      float false_positive = 0;
      float false_negative = 0;
      for(int k = 0; k < num_good; k = k + 1) {
        int result = 0;
        result = temp.classify(good[k]);
        if(result > 0) {
          true_positive = true_positive + 1;
        } else {
          true_negative = true_negative + 1;
        }
      }
      for(int l = 0; l < num_bad; l = l + 1) {
        int result = 0;
        result = temp.classify(bad[l]);
        if(result > 0) {
          false_positive = false_positive + 1;
        } else {
          false_negative = false_negative + 1;
        }
      }
      float positive_rate_good = true_positive / num_good;
      float positive_rate_bad = false_positive / num_good;
      float negative_rate_good = true_negative / num_good;
      float negative_rate_bad = false_negative / num_good;
      float confirmation_efficiency = positive_rate_good / positive_rate_bad;
      float contradiction_efficiency = negative_rate_good / negative_rate_bad;
      float overall_efficiency = confirmation_efficiency / contradiction_efficiency;
      myfile << "1\n";
      myfile << positive_rate_bad;
      myfile << "\n";
      myfile << positive_rate_good;
      myfile << "\n";
      myfile << negative_rate_good;
      myfile << "\n";
      myfile << negative_rate_bad;
      myfile << "\n";
      myfile << confirmation_efficiency;
      myfile << "\n";
      myfile << contradiction_efficiency;
      myfile << "\n";
      myfile << overall_efficiency;
      myfile << "\n";
    }
  }

  /* Testing metrics for pattern two analysis */
  for(int i = 0; i < sizeof(p_two_x_param); i = i + 1) {
    for(int j = 0; j < sizeof(p_two_y_param); j = j + 1) {
      WeakClassifier temp(1, i, j, threshold, polarity);
      float true_positive = 0;
      float true_negative = 0;
      float false_positive = 0;
      float false_negative = 0;
      for(int k = 0; k < num_good; k = k + 1) {
        int result = 0;
        result = temp.classify(good[k]);
        if(result > 0) {
          true_positive = true_positive + 1;
        } else {
          true_negative = true_negative + 1;
        }
      }
      for(int l = 0; l < num_bad; l = l + 1) {
        int result = 0;
        result = temp.classify(bad[l]);
        if(result > 0) {
          false_positive = false_positive + 1;
        } else {
          false_negative = false_negative + 1;
        }
      }
      float positive_rate_good = true_positive / num_good;
      float positive_rate_bad = false_positive / num_good;
      float negative_rate_good = true_negative / num_good;
      float negative_rate_bad = false_negative / num_good;
      float confirmation_efficiency = positive_rate_good / positive_rate_bad;
      float contradiction_efficiency = negative_rate_good / negative_rate_bad;
      float overall_efficiency = confirmation_efficiency / contradiction_efficiency;
      myfile << "1\n";
      myfile << positive_rate_bad;
      myfile << "\n";
      myfile << positive_rate_good;
      myfile << "\n";
      myfile << negative_rate_good;
      myfile << "\n";
      myfile << negative_rate_bad;
      myfile << "\n";
      myfile << confirmation_efficiency;
      myfile << "\n";
      myfile << contradiction_efficiency;
      myfile << "\n";
      myfile << overall_efficiency;
      myfile << "\n";
    }
  }

  /* Testing metrics for pattern one analysis */
  for(int i = 0; i < sizeof(p_three_x_param); i = i + 1) {
    for(int j = 0; j < sizeof(p_three_y_param); j = j + 1) {
      WeakClassifier temp(1, i, j, threshold, polarity);
      float true_positive = 0;
      float true_negative = 0;
      float false_positive = 0;
      float false_negative = 0;
      for(int k = 0; k < num_good; k = k + 1) {
        int result = 0;
        result = temp.classify(good[k]);
        if(result > 0) {
          true_positive = true_positive + 1;
        } else {
          true_negative = true_negative + 1;
        }
      }
      for(int l = 0; l < num_bad; l = l + 1) {
        int result = 0;
        result = temp.classify(bad[l]);
        if(result > 0) {
          false_positive = false_positive + 1;
        } else {
          false_negative = false_negative + 1;
        }
      }
      float positive_rate_good = true_positive / num_good;
      float positive_rate_bad = false_positive / num_good;
      float negative_rate_good = true_negative / num_good;
      float negative_rate_bad = false_negative / num_good;
      float confirmation_efficiency = positive_rate_good / positive_rate_bad;
      float contradiction_efficiency = negative_rate_good / negative_rate_bad;
      float overall_efficiency = confirmation_efficiency / contradiction_efficiency;
      myfile << "1\n";
      myfile << positive_rate_bad;
      myfile << "\n";
      myfile << positive_rate_good;
      myfile << "\n";
      myfile << negative_rate_good;
      myfile << "\n";
      myfile << negative_rate_bad;
      myfile << "\n";
      myfile << confirmation_efficiency;
      myfile << "\n";
      myfile << contradiction_efficiency;
      myfile << "\n";
      myfile << overall_efficiency;
      myfile << "\n";
    }
  }

  /* Testing metrics for pattern one analysis */
  for(int i = 0; i < sizeof(p_four_x_param); i = i + 1) {
    for(int j = 0; j < sizeof(p_four_y_param); j = j + 1) {
      WeakClassifier temp(1, i, j, threshold, polarity);
      float true_positive = 0;
      float true_negative = 0;
      float false_positive = 0;
      float false_negative = 0;
      for(int k = 0; k < num_good; k = k + 1) {
        int result = 0;
        result = temp.classify(good[k]);
        if(result > 0) {
          true_positive = true_positive + 1;
        } else {
          true_negative = true_negative + 1;
        }
      }
      for(int l = 0; l < num_bad; l = l + 1) {
        int result = 0;
        result = temp.classify(bad[l]);
        if(result > 0) {
          false_positive = false_positive + 1;
        } else {
          false_negative = false_negative + 1;
        }
      }
      float positive_rate_good = true_positive / num_good;
      float positive_rate_bad = false_positive / num_good;
      float negative_rate_good = true_negative / num_good;
      float negative_rate_bad = false_negative / num_good;
      float confirmation_efficiency = positive_rate_good / positive_rate_bad;
      float contradiction_efficiency = negative_rate_good / negative_rate_bad;
      float overall_efficiency = confirmation_efficiency / contradiction_efficiency;
      myfile << "1\n";
      myfile << positive_rate_bad;
      myfile << "\n";
      myfile << positive_rate_good;
      myfile << "\n";
      myfile << negative_rate_good;
      myfile << "\n";
      myfile << negative_rate_bad;
      myfile << "\n";
      myfile << confirmation_efficiency;
      myfile << "\n";
      myfile << contradiction_efficiency;
      myfile << "\n";
      myfile << overall_efficiency;
      myfile << "\n";
    }
  }

  /* Testing metrics for pattern one analysis */
  for(int i = 0; i < sizeof(p_five_x_param); i = i + 1) {
    for(int j = 0; j < sizeof(p_five_y_param); j = j + 1) {
      WeakClassifier temp(1, i, j, threshold, polarity);
      float true_positive = 0;
      float true_negative = 0;
      float false_positive = 0;
      float false_negative = 0;
      for(int k = 0; k < num_good; k = k + 1) {
        int result = 0;
        result = temp.classify(good[k]);
        if(result > 0) {
          true_positive = true_positive + 1;
        } else {
          true_negative = true_negative + 1;
        }
      }
      for(int l = 0; l < num_bad; l = l + 1) {
        int result = 0;
        result = temp.classify(bad[l]);
        if(result > 0) {
          false_positive = false_positive + 1;
        } else {
          false_negative = false_negative + 1;
        }
      }
      float positive_rate_good = true_positive / num_good;
      float positive_rate_bad = false_positive / num_good;
      float negative_rate_good = true_negative / num_good;
      float negative_rate_bad = false_negative / num_good;
      float confirmation_efficiency = positive_rate_good / positive_rate_bad;
      float contradiction_efficiency = negative_rate_good / negative_rate_bad;
      float overall_efficiency = confirmation_efficiency / contradiction_efficiency;
      myfile << "1\n";
      myfile << positive_rate_bad;
      myfile << "\n";
      myfile << positive_rate_good;
      myfile << "\n";
      myfile << negative_rate_good;
      myfile << "\n";
      myfile << negative_rate_bad;
      myfile << "\n";
      myfile << confirmation_efficiency;
      myfile << "\n";
      myfile << contradiction_efficiency;
      myfile << "\n";
      myfile << overall_efficiency;
      myfile << "\n";
    }
  }
  myfile.close();

}
