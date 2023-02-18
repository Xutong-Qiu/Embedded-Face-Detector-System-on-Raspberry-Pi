#include "utils.h"
#include <stdio.h>
#include <iostream>


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
    return right - left;
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
    return up + bottom - mid;
}

/*Given pattern 3 and a location, find pixel sum difference*/
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
    return left+right-mid;
}

/*Right now the default computation is black - white*/
int detect_feature(vector<vector<int>> img, int pattern, int nrows, int ncols, int p, int threshold){
    if(nrows >24 || ncols > 24 || pattern < 1 || pattern > 5 || (p!=1 && p!=-1)){
        std::cout<<"parameter error!";
        return -1;
    }
    int difference = 0;
    if(pattern == 1){//vertical rectangle feature
        if(nrows%2!=0 || nrows == 0){
            std::cout<<"row number in pattern 1 has to be non-zero even!\n";
            return -1;
        }
        for(int i = -1+nrows; i < 24; i++){
            for(int j = -1+ncols; j< 24; j++){
                difference = pattern1(img, i, j, nrows, ncols);
                if(difference >= threshold){
                    std::cout<<"Feature 1 found, the difference is:"<<difference<<" at:"<<i<<","<<j;
                    printf("\nthe values are: %d\n", img[i][j]);
                    return 1;
                }
            }
        }
    }else if(pattern == 2){//horizontal rectangle feature
        if(ncols%2!=0 || nrows == 0){
            std::cout<<"col number in pattern 2 has to be non-zero even!\n";
            return -1;
        }
        for(int i = -1+nrows; i < 24; i++){
            for(int j = -1+ncols; j< 24; j++){
                difference = pattern2(img, i, j, nrows, ncols);
                if(difference >= threshold){
                    std::cout<<"Feature 2 found, the difference is:"<<difference<<" at:"<<i<<","<<j;
                    printf("\nthe values are: %d\n", img[i][j]);
                    return 1;
                }
            }
        }
    }else if(pattern == 3){//vertical-three-block rectangle feature
        if(nrows%3!=0 || nrows == 0){
            std::cout<<"row number in pattern 3 has to be non-zero multiple of 3!\n";
            return -1;
        }
        for(int i = -1+nrows; i < 24; i++){
            for(int j = -1+ncols; j< 24; j++){
                difference = pattern3(img, i, j, nrows, ncols);
                if(difference >= threshold){
                    std::cout<<"Feature 3 found, the difference is:"<<difference<<" at:"<<i<<","<<j;
                    printf("\nthe values are: %d\n", img[i][j]);
                    return 1;
                }
            }
        }
    }else if(pattern == 4){//horizontal-three-block rectangle feature
        if(ncols%3!=0 || nrows == 0){
            std::cout<<"col number in pattern 4 has to be non-zero multiple of 3!\n";
            return -1;
        }
        for(int i = -1+nrows; i < 24; i++){
            for(int j = -1+ncols; j< 24; j++){
                difference = pattern2(img, i, j, nrows, ncols);
                if(difference >= threshold){
                    std::cout<<"Feature 4 found, the difference is:"<<difference<<" at:"<<i<<","<<j;
                    printf("\nthe values are: %d\n", img[i][j]);
                    return 1;
                }
            }
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
                //std::cout<<srcGrid[1].size()<<endl;
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
