#include "../../src/utils/utils.h"
#include "../../src/utils/WeakClassifier.h"
#include <iostream>
#include <limits.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <numeric>

#define WEAK 1103
#define T 2


using namespace std;

//  g++ strongCdriver.cpp utils.h utils.cpp WeakClassifier.h WeakClassifier.cpp




int main(int argc, char *argv[]) {  //fake train alg
  //strongC s = strongC("../../dataset/good_integral/train/","../../dataset/bad_integral/train/");
  char good [] = "../../dataset/good_integral/train/";
  char bad [] = "../../dataset/bad_integral/train/";
  /*test by first output the dir name*/
  int l = 1319;  //good
  int m = 2772;  //bad
  string fname;
  //org_classifiers.csv
  //second_strongc.csv
  //hand_classifiers.csv
  fname = "../../training/org_classifiers.csv";
  DIR *dir;
  struct dirent *ent;
  printf("start");
  vector<vector<vector<int>>> image_list(m+l , vector< vector<int> > (24, vector<int> (24,0) ) );
  vector<float>alpha;
  
  
  int count = 0;
  if ((dir = opendir (good)) != NULL) {
  
    
    while ((ent = readdir (dir)) != NULL) {
    
      if(strcmp(ent->d_name,".") == 0 || strcmp(ent->d_name, "..") == 0){    //skip . .. file
        continue;
      }
      
        char *temp = (char *)malloc(strlen(good) + strlen(ent->d_name) + 1);
				strcpy(temp, good);
				strcat(temp, ent->d_name);
        
       vector<vector<int>> src = read_txt_image(temp, 24, 24);
       for (int iRow = 0; iRow < src.size(); iRow++){
        for (int iCol = 0; iCol < src[0].size(); iCol++){
            image_list[count][iRow][iCol] = src[iRow][iCol];
        }
        
       }
       
       count ++;
       free(temp);
      
    }
    closedir (dir);
  } else {
    /* could not open directory */
    fprintf(stderr, "Can not open %s\n",good);
    
    return EXIT_FAILURE;
  }
  
  if ((dir = opendir (bad)) != NULL) {
  
    
    while ((ent = readdir (dir)) != NULL) {
    
      if(strcmp(ent->d_name,".") == 0 || strcmp(ent->d_name, "..") == 0){    //skip . .. file
        continue;
      }
      char *temp = (char *)malloc(strlen(bad) + strlen(ent->d_name) + 1);
				strcpy(temp, bad);
				strcat(temp, ent->d_name);
        
       vector<vector<int>> src = read_txt_image(temp, 24, 24);
       for (int iRow = 0; iRow < src.size(); iRow++){
        for (int iCol = 0; iCol < src[0].size(); iCol++){
            image_list[count][iRow][iCol] = src[iRow][iCol];
        }
        
       }
       
       count ++;
       free(temp);
      
    }
    closedir (dir);
  } else {
    /* could not open directory */
    fprintf(stderr, "Can not open %s\n",bad);
    
    return EXIT_FAILURE;
  }
  printf("Initialized %d images\n",m+l);
  /***************************Now we initialize weights*/
  
  vector<vector<float>> weights(T,vector<float>(m+l,0.0));		//number of total image
	for(int i = 0; i< m+l;i++){
		if(i<m){
       //printf("%f\n",(float)1/(2*m));
			weights[0][i] = (float)1/(2*m);
		}else{
			weights[0][i] = (float)1/(2*l);
		}
	}
 printf("Initialized weights\n");
 printf("Now we start training weak classifier\n");
 /****************************************************/
 
 //a vector of weak classifier
 vector<WeakClassifier> weak_grid;
 
 
 //read in parameters from csv file, but skip the first line
 
 vector<vector<string>> content;
 vector<string> row;
 string line, word;
 fstream file (fname, ios::in);
	int x = 1;
 if(file.is_open()){
   getline(file, line);    //skip first line
 }else{
   cout<<"Cannot open the file\n";
 }
 
 
  for(int i = 0 ; i< WEAK; i++){		//a fix number of total weak classifier

		
		if(file.is_open()){
  		if(getline(file, line)){
  			row.clear();
   
  			stringstream str(line);
        vector<int> config;            //config for each weak c
  			while(getline(str, word, ',')){
          
          stringstream num(word);
          
          num >> x;
          config.push_back(x);
        }
        printf("%d,%d,%d\n",config[0],config[1],config[2]);
        //use weakclassifier as a feature wrapper
        WeakClassifier *w = new WeakClassifier(config[0],config[1],config[2]);
        weak_grid.push_back(*w);
  			
  		}
	  }else{
  		cout<<"Could not open the file\n";
    }
   
		//train weak classifier?
  }
  //printf("Output: %d\n",weak_grid[1].classify(image_list[0]));     
  printf("Done with initializing weak classifiers\n");
  //Now, start training ***************************************************
  //some temp variables
  int y = 0;
 
  vector<WeakClassifier> weakc_final;
  float sum = 0.0;
  int mark = 0;
  float best = 0.0;
  float errorsum = 0.0;
  cout<<"Start looping...\n";
  
  
  for(int a = 0 ; a< T; a++){				//big loop, go over T classfier to train it
	printf("Loop %d\n",a);
	//1.Normalize the weights 
	sum = accumulate( weights[a].begin(),  weights[a].end(), 0.0);
 printf("sum is %f\n",sum);
	for(int i = 0; i<m+l;i++){
		weights[a][i] = (weights[a][i])/sum;
	}
	
  //1.5 train weak c
  for(int k = 0; k< WEAK-a;k++){
    vector<float> fvalue;
    
    for(int j = 0; j< m+l;j++){
      fvalue.push_back(weak_grid[k].featurevalue(image_list[j]));
      //printf("%d ",w.featurevalue(image_list[j]));
    }
   weak_grid[k].Best_Thresh(fvalue, l, m, weights[a]);   //this function will update the thresh and p in the Best_Thresh function???
    
  }
   for(auto w:weak_grid){
     printf("%d,%d,%d,%f,%d\n",w.pattern,w.nrows,w.ncols,w.thresh,w.sign);
   
   }
 
	//2.find the best weak classifier with the minimum weighted error
	best = numeric_limits<float>::max(); //minimum weighted error
	mark = 0; 		//keep track of the best classifier
	//go over each rest available feature(classifier)
	for(int j = 0; j< WEAK-a;j++){    
	  int notequal = 0;
		errorsum = 0.0;
	printf("check:%d,%f\n",j,errorsum);
		//go over every image and calculate the sum
		for(int i = 0; i< m+l;i++){
      if(i < m){
        y = 0;
      }else{
        y = 1;
      }
     // float adder = weights[a][i]*abs(weak_grid[j].classify(image_list[i]) - y);
      
      //printf("image is %d, weakc is %d,a is %d,weights:%f,classified as %d\n",i,j,a,weights[a][i],weak_grid[j].classify(image_list[i]));
     // printf("sum is %f, adder is %f\n",errorsum,adder);
      
			errorsum = errorsum + weights[a][i]*abs(weak_grid[j].classify(image_list[i]) - y);		
			//printf("errorsum is %f\n",errorsum);
      
      //use to debug inf problem
      //if(adder < 0.0){
      //   exit(1);
      //}
      
		}
		//update best min classifier
  //printf("best is %f, errorsum is %f\n",best,errorsum);
   printf("For weakc %d,errorsum is %f\n",j,errorsum);
   errorsum = errorsum/(m+l);
		if(errorsum < best){
			  printf("smaller than best, at %d. Best was %f\n",j,best);
				best = errorsum;
				mark = j;
        
		}
	}
	//printf("mark is %d\n",mark);
	
	//3.finalize the f,p,theta for current classifier,mark would hold the best weak classifier out of 180,000 weak classifiers
 
 //cout << "Remove weakc:"<< mark <<" from the grid. Old weak_grid size is "<< weak_grid.size()<< " Old weakc_final size is "<<weakc_final.size()<<'\n';
	//printf("Put weak classifier %d into the final list.\n",mark);
  weakc_final.push_back(weak_grid[mark]);
	
	//remove this weak classifier from the weak_grid
 
 
	weak_grid.erase(weak_grid.begin() + mark);
	
	cout << "Done, now weak grid size is " << weak_grid.size()<<", weakc_final size is "<< weakc_final.size()<< '\n';
	
	
	//4.update the weights grid for next weak classifier
	
	float b = best/(1-best);
	float p = 10;
 
	//skip the last column of weights update
  if(a+1 == T){
  alpha.push_back(log(1/b));
         continue;
  }
 
	for(int i = 0; i <m+l;i++ ){
     
		if( i < m){
      y = 0;      //not face
    }else{
      y = 1;       //is face
    }
		if(weakc_final[a].classify(image_list[i]) == y){    //classfied correctly
			p = b;
		}else{                      //not correct
			p = 1.0;
			
		}
   //printf("a is %d, i is %d\n",a,i);
   //printf("1 is %f",weights[a+1][i]);
   //printf("2 is %f",weights[a][i]);
   //printf("3 is %f\n",p);
	 weights[a+1][i] = weights[a][i] * p;
	 //printf("old w is %f, new w is %f\n",weights[a+1][i],weights[a][i]); 
	}
	printf("Update weights done.\n");
	//save alpha for each weak classifier
	alpha.push_back(log(1/b));
  printf("For weakc %d, alpha is %f,b is %f,best is %f\n",a,alpha[a],b,best);
//  printf("For weakc %d, alpha is %f,feature is %d, nrowl is %d, ncols is %d, thershold is %f, p is %d",a,log(1/b),weakc_final[a].pattern,weakc_final[a].nrows,weakc_final[a].ncols,weakc_final[a].thresh,weakc_final[a].sign);
	}
  //done with training
	//Total of T weak classifiers
 
 
 //save alpha and weakclassifier parameters
 //Format: First line will be T number as T alpha
 //Then there are T rows, each row as one weak classifier, with feature pattern, nrowl, ncol, threth,p
 ofstream outStream("output.txt");
 //alpha
  for(int i = 0; i<T;i++ ){
      outStream << alpha[i];
      outStream << ' ';
    }
    outStream << '\n';
    for(int i = 0;i<T;i++){
      outStream << weakc_final[i].pattern;
      outStream << ' ';
      outStream << weakc_final[i].nrows;
      outStream << ' ';
      outStream << weakc_final[i].ncols;
      outStream << ' ';
      outStream << weakc_final[i].thresh;
      outStream << ' ';
      outStream << weakc_final[i].sign;
      
      outStream << '\n';
    }
    
    outStream.close();
  
  
  
//    g++ strongCdriver.cpp utils.h utils.cpp WeakClassifier.h WeakClassifier.cpp
}