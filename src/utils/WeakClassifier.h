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
  
    WeakClassifier(int feature_pattern, int nrows, int ncols,int rowpos,int colpos);
    WeakClassifier(int feature_pattern, int nrows, int ncols,int rowpos,int colpos, float thresh, int sign);
    float Best_Thresh(vector<int> fvalues, int fsize, int nfsize, vector<float>weights);
    void getFeature(int *feature);
    int classify(vector<vector<int>> img);
    int featurevalue(vector<vector<int>> img);
    //int create_feature(vector<WeakClassifier> weak_grid,int pattern, int nrows, int ncols);
    void scale(float s);
    std::string toString();
  //protected:
    int pattern = 0;  //{1,2,3,4,5}
    int nrows = 0;   //[1,24]
    int ncols = 0;   //[1,24]
    int rowpos = 0;  // [0,23]
    int colpos = 0;  //[0,23]
    int thresh = 146;
    int sign = -1;    //{-1,1}
};

#endif
