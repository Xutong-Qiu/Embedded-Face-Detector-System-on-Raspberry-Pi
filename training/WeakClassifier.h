#ifndef WEAKCLASSIFIER_H
#define WEAKCLASSIFIER_H

#include <string>
#include <vector>
#include "utils.h"

struct sum {
 
  float Sn;
  
  float Sp;
};
/*Sign should be set to -1 if you want to use a postive threshold*/
class WeakClassifier {
  public:
  
    WeakClassifier(int feature_pattern, int nrows, int ncols);
    WeakClassifier(int feature_pattern, int nrows, int ncols, float thresh, int sign);
    float Best_Thresh(float *fvalues, int fsize, int nfsize, float *weights);
    void getFeature(int *feature);
    int classify(vector<vector<int>> img);
    void scale(float s);
    std::string toString();
  protected:
    int pattern = 0;
    int nrows = 0;
    int ncols = 0;
    float thresh = 0;
    int sign = 1;
};

#endif
