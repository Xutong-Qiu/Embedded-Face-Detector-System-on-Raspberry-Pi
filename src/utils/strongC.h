#ifndef strongC_h
#define strongC_h

#include <stdio.h>
#include "WeakClassifier.h"
#include <vector>

using namespace std;

class strongC{
	
public:

  strongC( int T, vector<float> alpha, vector<WeakClassifier> weakc_final);
  
  int test(vector<vector<int>> img);
  void train(char* good ,char* bad);
	~strongC();
	
	
	
	
private:
	int T = 0;
	int m = 0;							//number of negatives
	int l = 0;							//number of positives
 
	vector<WeakClassifier> weakc_final;                            
	vector<float> alpha;                                  //final parameters, T
};

#endif