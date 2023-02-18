#ifndef UTILS_H
#define UTILS_H
/*******************************************************************************
@ddblock_begin copyright

Copyright (c) 1997-2022
Maryland DSPCAD Research Group, The University of Maryland at College Park 

Permission is hereby granted, without written agreement and without
license or royalty fees, to use, copy, modify, and distribute this
software and its documentation for any purpose, provided that the above
copyright notice and the following two paragraphs appear in all copies
of this software.

IN NO EVENT SHALL THE UNIVERSITY OF MARYLAND BE LIABLE TO ANY PARTY
FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES
ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF
THE UNIVERSITY OF MARYLAND HAS BEEN ADVISED OF THE POSSIBILITY OF
SUCH DAMAGE.

THE UNIVERSITY OF MARYLAND SPECIFICALLY DISCLAIMS ANY WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE SOFTWARE
PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND THE UNIVERSITY OF
MARYLAND HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES,
ENHANCEMENTS, OR MODIFICATIONS.

@ddblock_end copyright
*******************************************************************************/

/*******************************************************************************
DESCRIPTION:
This is a header file of utility functions in image rotation application.
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <vector>
#include <iostream>
/*
extern "C" {
#include "welt_c_util.h"
#include "welt_c_fifo.h"
}
*/
using namespace std;

vector<vector<int> > read_txt_image (char * fileName, int nRows, int nCols);
vector<vector<int> > norm2integral (vector<vector<int>> img);
/* function prints a 2D vector out */
void print_grid (vector<vector<int>> srcGrid);

void write_txt_image(char * file_name, vector<vector<int>> grid);

/*
This function detects whether a feature is in presence using four parameters. It returns 0 if the feature is not detect, 1 if it is, and -1 if error.
Integral image: a 2D vector img represents the integral image.
Feature: pattern, number of rows, and number of column represent a feature. pattern is a number bewteen 1 and 5. w and l specify the width and lengh of the feature
p: polarity, can be 1 or -1
threshold: an integer
*/
int detect_feature(vector<vector<int>> img, int pattern, int nrows, int ncols, int p, int threshold);

#endif //UTILS_H
