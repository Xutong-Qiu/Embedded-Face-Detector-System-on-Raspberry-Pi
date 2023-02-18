#include "WeakClassifier.h"
#include <math.h>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <numeric>
#include <limits>
struct score {
  int value;
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

WeakClassifier::WeakClassifier(int feature_pattern, int nrows, int ncols,int rowpos,int colpos) {
  this->pattern = feature_pattern;
  this->nrows = nrows;
  this->ncols = ncols;
  this->rowpos = rowpos;
  this->colpos = colpos;
}

WeakClassifier::WeakClassifier(int feature_pattern, int nrows, int ncols,int rowpos,int colpos, float thresh, int sign) {
  this->pattern = feature_pattern;
  this->nrows = nrows;
  this->ncols = ncols;
  this->rowpos = rowpos;
  this->colpos = colpos;
  this->thresh = thresh;
  this->sign = sign;
}



float WeakClassifier::Best_Thresh(vector<int>fvalues, int fsize, int nfsize, vector<float>weights) {
  score *scores = new score[fsize+nfsize];
  for (int i=0; i<nfsize; i++) {
    scores[i].value = fvalues[i];
    scores[i].label = false;
    scores[i].weight = weights[i];
  }
  for (int j= nfsize; j<fsize+nfsize; j++) {
    scores[j].value = fvalues[j];
    scores[j].label = true;
    scores[j].weight = weights[j];
  }
  std::sort(scores, scores+fsize+nfsize, compare);
  
  for(int a = 0; a < fsize+nfsize;a++){
    //printf("Score value, label, weight is %d,%d,%f\n ",scores[a].value,scores[a].label,scores[a].weight);
    
  }
  
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
  
  float minError = numeric_limits<float>::max();
  float Errorp;
  float Errorm;
  int index = 0;
  int ps = 0;
  int fs =  0;
  //printf("%f,%f\n",Tn,Tp);
  for (int l=0; l<(fsize+nfsize); l++) {
    //printf("ws's sp is %f, sn is %f. Tn is %f,Tp is %f\n",ws[l].Sp, ws[l].Sn,Tn,Tp);
    Errorp = ws[l].Sp + Tn - ws[l].Sn;    //left
    Errorm = ws[l].Sn + Tp - ws[l].Sp;    //right
    if (Errorp < Errorm) {
      if (Errorp < minError) {
        //printf("Errorp is small, threshold would be %d\n",scores[l].value);
        index = l;
        minError = Errorp;
        this->thresh = scores[l].value;
        if(ps > fs){
          this->sign = 1;
       }else{
         this->sign = -1;
       }
      }
    }else {
     if (Errorm < minError) {
     //printf("Errorm is smaller, threshold would be scores[l].value\n");
        index = l;
        minError = Errorm;
        this->thresh = scores[l].value;
        if(ps > fs){
          this->sign = 1;
         }else{
           this->sign = -1;
         }
         //printf("update thresh and sign....................\n");
      }
    }
    
    if(scores[l].label == false){
      fs += 1;
    }else{
      ps += 1;
    }
    
  }
  
  //printf("Done with this train, %f,%d,%d,%d\n",this->thresh,ps,fs,index);
  //exit(1);
  delete[] scores;
  delete[] ws;
  return minError;
}

void WeakClassifier::getFeature(int *feature) {
  feature[0] = this->pattern;
  feature[1] = this->nrows;
  feature[2] = this->ncols;
}

int WeakClassifier::featurevalue(vector<vector<int>> img) {
  return feature_value(img,this->pattern, this->nrows, this->ncols,this->rowpos,this->colpos);
}


//This function detects whether a feature is in presence using four parameters. It returns 0 if the feature is not detect, 1 if it is, and -1 if error.
int WeakClassifier::classify(vector<vector<int>> img) {
  int i = detect_feature(img, this->pattern, this->nrows, this->ncols,this->rowpos,this->colpos, this->sign, this->thresh);
  if(i==-1){
    cout<< "Error in detecting feature!\n";
    exit(1);
  }
  return i;
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
