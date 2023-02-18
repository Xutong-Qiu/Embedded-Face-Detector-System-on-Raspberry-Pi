#include "utils.h"

#include "strongC.h"
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

//tp and fp rate
int tp2rate(int inputnum,char* result){
  //check how many ones
  
  ifstream inStream;
  string r;
  int count = 0;
  inStream.open(result);
  if (inStream.fail()){
      cerr << "Could not open file \"" << result << "\"" << endl;  
  }
  while(getline(inStream,r)){
    if( stoi(r) == 1){
      count += 1;
    }
  }
  
  float rate = (float)count/inputnum;
  printf("There are %d input.\n",inputnum);
   printf("There are %d classified true faces.\n", count);
  printf("Truth positive rate is %f.\n",rate);
  
  return count;

}
int fp2rate(int inputnum,char* result){
  //check how many ones
  
  ifstream inStream;
  string r;
  int count = 0;
  inStream.open(result);
  if (inStream.fail()){
      cerr << "Could not open file \"" << result << "\"" << endl;  
  }
  while(getline(inStream,r)){
    if( stoi(r) == 1){
      count += 1;
    }
  }
  
  float rate = (float)count/inputnum;
  printf("There are %d input.\n",inputnum);
   printf("There are %d classified true faces.\n", count);
  printf("False positive rate is %f.\n",rate);
  
  return count;
  
}


int tprate(char* folder,char* result){
  DIR *dp;
  int truth = 0;
  struct dirent *ep;     
  dp = opendir (folder);

  if (dp != NULL)
  {
    while (ep = readdir (dp))
      truth++;

    (void) closedir (dp);
  }
  else
    perror ("Couldn't open the directory");
  truth = truth - 2;
  printf("There are %d faces.\n", truth);
  

  //check how many ones
  
  ifstream inStream;
  string r;
  int count = 0;
  inStream.open(result);
  if (inStream.fail()){
      cerr << "Could not open file \"" << result << "\"" << endl;  
  }
  while(getline(inStream,r)){
    if( stoi(r) == 1){
      count += 1;
    }
  }
  float rate = (float)count/truth;
   printf("There are %d classified true faces.\n", count);
  printf("Truth positive rate is %f.\n",rate);
  
  return count;
  
}


int fprate(char* folder,char* result){
  DIR *dp;
  int truth = 0;
  struct dirent *ep;     
  dp = opendir (folder);

  if (dp != NULL)
  {
    while (ep = readdir (dp))
      truth++;

    (void) closedir (dp);
  }
  else
    perror ("Couldn't open the directory");
  truth = truth - 2;
  printf("There are %d faces.\n", truth);
  

  //check how many ones
  
  ifstream inStream;
  string r;
  int count = 0;
  inStream.open(result);
  if (inStream.fail()){
      cerr << "Could not open file \"" << result << "\"" << endl;  
  }
  while(getline(inStream,r)){
    if( stoi(r) == 1){
      count += 1;
    }
  }
  float rate = (float)count/truth;
   printf("There are %d classified true faces.\n", count);
  printf("False positive rate is %f.\n",rate);
  
  return count;
  
}




vector<vector<int>> norm2integral (vector<vector<int>> img){
    vector<vector<int> > int_img(24, vector<int> (24, 0));
    if (img.size() != 24 || img[0].size() != 24){
        printf("Wrong img size!");
        return int_img;
    }
    for(int i = 0; i < 24; i++){
        for (int j = 0; j <24; j++){
            if(i==0 && j == 0){
                int_img[i][j] = img[i][j];
            }else if (i == 0){
                int_img[i][j] = img[i][j]+ int_img[i][j-1];
            }else if(j == 0){
                 int_img[i][j] = img[i][j]+ int_img[i-1][j];
            }else{
                int_img[i][j] = img[i][j]+int_img[i-1][j]+int_img[i][j-1]-int_img[i-1][j-1];
            }
        }
    }
    return int_img;

}
/*Given pattern 1 and a location, find pixel sum difference*/
int pattern1(vector<vector<int>> img, int i, int j, int nrows, int ncols){
    int lower = 0;
    int upper = 0;
    if(i>=nrows && j >=ncols){
        lower = img[i][j] - img[i][j-ncols] - img[i-nrows/2][j] + img[i-nrows/2][j-ncols]; 
        upper = img[i-nrows/2][j] - img[i-nrows/2][j-ncols] - img[i-nrows][j] + img[i-nrows][j-ncols];
    }else if(i < nrows && j < ncols){
        lower = img[i][j] - img[i-nrows/2][j]; 
        upper = img[i-nrows/2][j];
    }else if(i < nrows){
        lower = img[i][j] - img[i][j-ncols] - img[i-nrows/2][j] + img[i-nrows/2][j-ncols]; 
        upper = img[i-nrows/2][j] - img[i-nrows/2][j-ncols];
    }else if(j < ncols){
        lower = img[i][j] - img[i-nrows/2][j]; 
        upper = img[i-nrows/2][j] - img[i-nrows][j];
    }else{
        std::cout<<"error in pattern 1 detection!";
        return 0;
    }
    return lower - upper;

}

/*Given pattern 2 and a location, find pixel sum difference*/
int pattern2(vector<vector<int>> img, int i, int j, int nrows, int ncols){
    int left = 0;
    int right = 0;
    if(i>=nrows && j >=ncols){
        right = img[i][j] - img[i][j-ncols/2] - img[i-nrows][j] + img[i-nrows][j-ncols/2]; 
        left = img[i][j-ncols/2] - img[i-nrows][j-ncols/2] - img[i][j-ncols] + img[i-nrows][j-ncols];
    }else if(i < nrows && j < ncols){
        right = img[i][j] - img[i][j-ncols/2]; 
        left = img[i][j-ncols/2];
    }else if(i < nrows){
        right = img[i][j] - img[i][j-ncols/2]; 
        left = img[i][j-ncols/2] - img[i][j-ncols];
    }else if(j < ncols){
        right = img[i][j] - img[i][j-ncols/2] - img[i-nrows][j] + img[i-nrows][j-ncols/2]; 
        left = img[i][j-ncols/2] - img[i-nrows][j-ncols/2];
    }else{
        std::cout<<"error in pattern 2 detection!";
        return 0;
    }
    return left - right;
}

/*Given pattern 3 and a location, find pixel sum difference*/
int pattern3(vector<vector<int>> img, int i, int j, int nrows, int ncols){
    int up = 0;
    int mid = 0;
    int bottom = 0;
    if(i>=nrows && j >=ncols){
        bottom = img[i][j] - img[i][j-ncols] - img[i-nrows/3][j] + img[i-nrows/3][j-ncols]; 
        mid = img[i-nrows/3][j] - img[i-nrows/3][j-ncols] - img[i-nrows*2/3][j] + img[i-nrows*2/3][j-ncols];
        up = img[i-nrows*2/3][j] - img[i-nrows*2/3][j-ncols] - img[i-nrows][j] + img[i-nrows][j-ncols];
    }else if(i < nrows && j < ncols){
        bottom = img[i][j] - img[i-nrows/3][j] ; 
        mid = img[i-nrows/3][j] - img[i-nrows*2/3][j] ;
        up = img[i-nrows*2/3][j];
    }else if(i < nrows){
        bottom = img[i][j] - img[i][j-ncols] - img[i-nrows/3][j] + img[i-nrows/3][j-ncols]; 
        mid = img[i-nrows/3][j] - img[i-nrows/3][j-ncols] - img[i-nrows*2/3][j] + img[i-nrows*2/3][j-ncols];
        up = img[i-nrows*2/3][j] - img[i-nrows*2/3][j-ncols];
    }else if(j < ncols){
        bottom = img[i][j] - img[i-nrows/3][j]; 
        mid = img[i-nrows/3][j]  - img[i-nrows*2/3][j];
        up = img[i-nrows*2/3][j] - img[i-nrows][j];
    }else{
        std::cout<<"error in pattern 3 detection!";
        return 0;
    }
    return mid - up - bottom;
}

/*Given pattern 4 and a location, find pixel sum difference*/
int pattern4(vector<vector<int>> img, int i, int j, int nrows, int ncols){
    int left = 0;
    int mid = 0;
    int right = 0;
    if(i>=nrows && j >=ncols){
        right = img[i][j] - img[i][j-ncols/3] - img[i-nrows][j] + img[i-nrows][j-ncols/3]; 
        mid = img[i][j-ncols/3] - img[i-nrows][j-ncols/3] - img[i][j-ncols*2/3] + img[i-nrows][j-ncols*2/3];
        left = img[i][j-ncols*2/3] - img[i-nrows][j-ncols*2/3] - img[i][j-ncols] + img[i-nrows][j-ncols];
    }else if(i < nrows && j < ncols){
       right = img[i][j] - img[i][j-ncols/3]; 
        mid = img[i][j-ncols/3] - img[i][j-ncols*2/3];
        left = img[i][j-ncols*2/3];
    }else if(i < nrows){
        right = img[i][j] - img[i][j-ncols/3]  ; 
        mid = img[i][j-ncols/3] - img[i][j-ncols*2/3] ;
        left = img[i][j-ncols*2/3]- img[i][j-ncols] ;
    }else if(j < ncols){
        right = img[i][j] - img[i][j-ncols/3] - img[i-nrows][j] + img[i-nrows][j-ncols/3]; 
        mid = img[i][j-ncols/3] - img[i-nrows][j-ncols/3] - img[i][j-ncols*2/3] + img[i-nrows][j-ncols*2/3];
        left = img[i][j-ncols*2/3] - img[i-nrows][j-ncols*2/3];
    }else{
        std::cout<<"error in pattern 4 detection!";
        return 0;
    }
    return mid - left - right;
}

/*Given pattern 5 and a location, find pixel sum difference*/
int pattern5(vector<vector<int>> img, int i, int j, int nrows, int ncols){
    int upper_left = 0;
    int upper_right = 0;
    int bottom_right = 0;
    int bottom_left = 0;
    if(i>=nrows && j >=ncols){
        bottom_right = img[i][j] - img[i][j-ncols/2] - img[i-nrows/2][j] + img[i-nrows/2][j-ncols/2]; 
        bottom_left = img[i][j-ncols/2] - img[i][j-ncols] - img[i-nrows/2][j-ncols/2] + img[i-nrows/2][j-ncols];
        upper_right = img[i-nrows/2][j] - img[i-nrows/2][j-ncols/2] - img[i-nrows][j] + img[i-nrows][j-ncols/2];
        upper_left = img[i-nrows/2][j-ncols/2] - img[i-nrows/2][j-ncols] - img[i-nrows][j-ncols/2] + img[i-nrows][j-ncols];
    }else if(i < nrows && j < ncols){
        bottom_right = img[i][j] - img[i][j-ncols/2] - img[i-nrows/2][j] + img[i-nrows/2][j-ncols/2]; 
        bottom_left = img[i][j-ncols/2]  - img[i-nrows/2][j-ncols/2];
        upper_right = img[i-nrows/2][j] - img[i-nrows/2][j-ncols/2] ;
        upper_left = img[i-nrows/2][j-ncols/2];
    }else if(i < nrows){
        bottom_right = img[i][j] - img[i][j-ncols/2] - img[i-nrows/2][j] + img[i-nrows/2][j-ncols/2]; 
        bottom_left = img[i][j-ncols/2] - img[i][j-ncols] - img[i-nrows/2][j-ncols/2] + img[i-nrows/2][j-ncols];
        upper_right = img[i-nrows/2][j] - img[i-nrows/2][j-ncols/2];
        upper_left = img[i-nrows/2][j-ncols/2] - img[i-nrows/2][j-ncols];
    }else if(j < ncols){
        bottom_right = img[i][j] - img[i][j-ncols/2] - img[i-nrows/2][j] + img[i-nrows/2][j-ncols/2]; 
        bottom_left = img[i][j-ncols/2] - img[i-nrows/2][j-ncols/2];
        upper_right = img[i-nrows/2][j] - img[i-nrows/2][j-ncols/2] - img[i-nrows][j] + img[i-nrows][j-ncols/2];
        upper_left = img[i-nrows/2][j-ncols/2]  - img[i-nrows][j-ncols/2];
    }else{
        std::cout<<"error in pattern 5 detection!";
        return 0;
    }
    return bottom_right + upper_left - upper_right - bottom_left;
}


//return feature value
int feature_value(vector<vector<int>> img,int pattern, int nrows, int ncols,int rowpos, int colpos){
  if(nrows >24 || ncols > 24 || pattern < 1 || pattern > 5 ){
        std::cout<<"parameter error!feature_value\n";
        std::cout<<nrows<<"*"<<ncols<<endl;
        
        return -1;
    }
    
    if(pattern == 1){//vertical rectangle feature
        if(nrows%2!=0 || nrows == 0){
            std::cout<<"row number in pattern 1 has to be non-zero even!\n";
            return -1;
        }
        return pattern1(img, rowpos, rowpos, nrows, ncols);
                
    }else if(pattern == 2){//horizontal rectangle feature
        if(ncols%2!=0 || nrows == 0){
            std::cout<<"col number in pattern 2 has to be non-zero even!\n";
            return -1;
        }
        
        return pattern2(img, rowpos, rowpos, nrows, ncols);
    
    }else if(pattern == 3){//vertical-three-block rectangle feature
        if(nrows%3!=0 || nrows == 0){
            std::cout<<"row number in pattern 3 has to be non-zero multiple of 3!\n";
            return -1;
        }
        return pattern3(img, rowpos, rowpos, nrows, ncols);
                
    }else if(pattern == 4){//horizontal-three-block rectangle feature
        if(ncols%3!=0 || nrows == 0){
            std::cout<<"col number in pattern 4 has to be non-zero multiple of 3!\n";
            return -1;
        }
        return pattern4(img, rowpos, rowpos, nrows, ncols);
                
    }else if(pattern == 5){//four-block square feature
        if(ncols%2!=0 || nrows%2!=0 || nrows == 0){
            std::cout<<"col and row number in pattern 5 has to be non-zero multiple of 2!\n";
            return -1;
        }
        
        return pattern5(img, rowpos, rowpos, nrows, ncols);
                
    }
    
    return 0;



}




/*
This function detects whether a feature is in presence using four parameters. It returns 0 if the feature is not detect, 1 if it is, and -1 if error.
Integral image(img): a 2D vector img represents the integral image.
Feature: pattern, number of rows, and number of columns represent a feature. pattern is a number bewteen 1 and 5. nrows and ncols specify the width and lengh of the feature
p: polarity, can be 1 or -1, normally, use -1
threshold: an integer
*/


int detect_feature(vector<vector<int>> img, int pattern, int nrows, int ncols,int rp,int cp, int p, int threshold){
  //printf("%d,%d,%d,%d,%d,%d,%d,\n",pattern,  nrows,  ncols, rp, cp,  p,  threshold);
    if(nrows >24 || ncols > 24 || pattern < 1 || pattern > 5 || (p!=1 && p!=-1)){
        std::cout<<"parameter error!detect_fwture\n";
        std::cout<<nrows<<"*"<<ncols<<endl;
        
        return -1;
    }
    int difference = 0;
    if(pattern == 1){//vertical rectangle feature
        if(nrows%2!=0 || nrows == 0){
            std::cout<<"row number in pattern 1 has to be non-zero even!\n";
            return -1;
        }
        difference = pattern1(img, rp, cp, nrows, ncols);
                if(p*difference < p*threshold){
                    //std::cout<<"Feature 1 found, the difference is:"<<difference<<" at:"<<i<<","<<j;
                    //printf("\nthe value at that point is: %d\n", img[i][j]);
                    return 1;
                }
            
    }else if(pattern == 2){//horizontal rectangle feature
        if(ncols%2!=0 || nrows == 0){
            std::cout<<"col number in pattern 2 has to be non-zero even!\n";
            return -1;
        }
       
                difference = pattern2(img, rp, cp, nrows, ncols);
                if(p*difference < p*threshold){
                   // std::cout<<"Feature 2 found, the difference is:"<<difference<<" at:"<<i<<","<<j;
                   // printf("\nthe value at that point is: %d\n", img[i][j]);
                    return 1;
                }
           
    }else if(pattern == 3){//vertical-three-block rectangle feature
        if(nrows%3!=0 || nrows == 0){
            std::cout<<"row number in pattern 3 has to be non-zero multiple of 3!\n";
            return -1;
        }
        
                difference = pattern3(img, rp, cp, nrows, ncols);
                if(p*difference < p*threshold){
                   // std::cout<<"Feature 3 found, the difference is:"<<difference<<" at:"<<i<<","<<j;
                   // printf("\nthe value at that point is: %d\n", img[i][j]);
                    return 1;
                }
            
    }else if(pattern == 4){//horizontal-three-block rectangle feature
        if(ncols%3!=0 || nrows == 0){
            std::cout<<"col number in pattern 4 has to be non-zero multiple of 3!\n";
            return -1;
        }
        
                difference = pattern4(img, rp, cp, nrows, ncols);
                if(p*difference < p*threshold){
                    //std::cout<<"Feature 4 found, the difference is:"<<difference<<" at:"<<i<<","<<j;
                    //printf("\nthe value at that point is: %d\n", img[i][j]);
                    return 1;
                }
           
    }else if(pattern == 5){//four-block square feature
        if(ncols%2!=0 || nrows%2!=0 || nrows == 0){
            std::cout<<"col and row number in pattern 5 has to be non-zero multiple of 2!\n";
            return -1;
        }
       
                difference = pattern5(img, rp, cp, nrows, ncols);
                if(p*difference < p*threshold){
                  //  std::cout<<"Feature 5 found, the difference is:"<<difference<<" at:"<<i<<","<<j;
                  //  printf("\nthe value at that point is: %d\n", img[i][j]);
                    return 1;
                }else{
                     //std::cout<<"Feature 5 not detected\n";
                }
            
    }
    return 0;
}

vector<vector<int> > read_txt_image (char * fileName, int nRows, int nCols){
    vector<vector<int> > srcGrid(nRows, vector<int> (nCols, 9));
    FILE *filePtr = NULL;
    filePtr = fopen(fileName, "r");
    if (filePtr == NULL) {
        perror("fopen: ");
        exit(EXIT_FAILURE);
    }
    for (int iRow = 0; iRow < nRows; iRow++)
    {
        for (int iCol = 0; iCol < nCols;iCol++)
        {
            int data = 0;
            if (!fscanf(filePtr, "%d,", &data)){
                perror("fscanf: ");
            }
            srcGrid[iRow][iCol] = data;
        }
    }
    fclose(filePtr);
    return srcGrid;
}

void print_grid (vector<vector<int>> srcGrid){
    for (int iRow = 0; iRow < srcGrid.size(); iRow++){
        for (int iCol = 0; iCol < srcGrid[0].size(); iCol++){
            cout << srcGrid[iRow][iCol] << " ";
        }
        cout << endl;
    }
}

void write_txt_image(char * file_name, vector<vector<int>> grid){
    
    FILE *fp;
    fp = fopen((const char *)file_name, "w");
    
    for (auto pixel_line : grid) {
        for (auto it = pixel_line.begin(); it != pixel_line.end(); it++) {
            if (next(it)==pixel_line.end())
                fprintf(fp, "%d", *it);
            else
                fprintf(fp, "%d,", *it);
        }
        fprintf(fp, "\n");
    }
    
    
}
