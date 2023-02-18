#include "WeakClassifier.h"
#include <math.h>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

struct score {
  float value;
  bool label;
  float weight;
};

static bool compare(const score &a, const score &b) {
  return a.value < b.value;
}

static std::string f2s(float f) {
  std::ostringstream ss;
  ss << f;
  std::string s(ss.str());
  return s;
}

WeakClassifier::WeakClassifier(int feature_pattern, int nrows, int ncols) {
  this->pattern = feature_pattern;
  this->nrows = nrows;
  this->ncols = ncols;
}

WeakClassifier::WeakClassifier(int feature_pattern, int nrows, int ncols, float thresh, int sign) {
  this->pattern = feature_pattern;
  this->nrows = nrows;
  this->ncols = ncols;
  this->thresh = thresh;
  this->sign = sign;
}

float WeakClassifier::Best_Thresh(float *fvalues, int fsize, int nfsize, float *weights) {
  score *scores = new score[fsize+nfsize];
  for (int i=0; i<fsize; i++) {
    scores[i].value = fvalues[i];
    scores[i].label = true;
    scores[i].weight = weights[i];
  }
  for (int j=0; j<nfsize; j++) {
    scores[j+fsize].value = fvalues[j+fsize];
    scores[j+fsize].label = false;
    scores[j+fsize].weight = weights[j+fsize];
  }
  std::sort(scores, scores+fsize+nfsize, compare);
  sum *ws = new sum[fsize+nfsize];
  float Tp = 0;
  float Tn = 0;
  if (scores[0].label == false) {
    Tn = scores[0].weight;
    ws[0].Sn = scores[0].weight;
    ws[0].Sp = 0;
  }
  else {
    Tp = scores[0].weight;
    ws[0].Sp = scores[0].weight;
    ws[0].Sn = 0;
  }
  for (int k=1; k<(fsize+nfsize); k++) {
    if (scores[k].label == false) {
      Tn += scores[k].weight;
      ws[k].Sn = ws[k-1].Sn + scores[k].weight;
      ws[k].Sp = ws[k-1].Sp;
    }
    else {
      Tp += scores[k].weight;
      ws[k].Sp = ws[k-1].Sp + scores[k].weight;
      ws[k].Sn = ws[k-1].Sn;
    }
  }
  float minError = 1;
  float Errorp;
  float Errorm;
  for (int l=0; l<(fsize+nfsize); l++) {
    Errorp = ws[l].Sp + Tn - ws[l].Sn;
    Errorm = ws[l].Sn + Tp - ws[l].Sp;
    if (Errorp < Errorm) {
      if (Errorp < minError) {
        minError = Errorp;
        this->thresh = scores[l].value;
        this->sign = -1;
      }
    }
    else {
     if (Errorm < minError) {
        minError = Errorm;
        this->thresh = scores[l].value;
        this->sign = 1;
      }
    }
  }
  delete[] scores;
  delete[] ws;
  return minError;
}

void WeakClassifier::getFeature(int *feature) {
  feature[0] = this->pattern;
  feature[1] = this->nrows;
  feature[2] = this->ncols;
}

//This function detects whether a feature is in presence using four parameters. It returns 0 if the feature is not detect, 1 if it is, and -1 if error.
int WeakClassifier::classify(vector<vector<int>> img) {
  return detect_feature(img, this->pattern, this->nrows, this->ncols, this->sign, this->thresh);
}

void WeakClassifier::scale(float s) {
  /*
  f->scale(s);
  this->thresh = (this->thresh)*pow(s, 2);
  */
}

std::string WeakClassifier::toString() {
  /*std::string s = f->toString()+" "+f2s(this->thresh);
  if (this->sign == -1) s += " 0";
  else s += " 1";
  return s;
  */
  return "to string";
}
