# Embedded Face Detection System (EFDS) and Training Algorithm Project

## Overview

This repository is dedicated to the development of an Embedded Face Detection System (EFDS) and its corresponding training algorithm. The project has been meticulously structured to facilitate the independent yet parallel development of its integral parts, namely the face detection algorithm and the training system.

## Build and Execution

To build and execute the components of this project:

1. Ensure you have a C++ compiler and MATLAB installed on your system.
2. Clone the repository to your local machine.
3. Run CMake.

## Final Remarks

The EFDS project illustrates a successful implementation of the Viola-Jones algorithm, which, while working in parallel with the design principles of neural networks, showcases the unique independent yet integrated functioning of strong classifiers.

We value the adaptability and parallel work approach that allowed us to overcome challenges and learn valuable lessons in collaborative software engineering.


The dataset is under /dataset. Positive and negative samples are stored in /dataset/good_integral and /dataset/bad_integral. Each of the folders contain three subfolders: test, validation, and train.

All the source code is under /src. Based on their code type, they are divided into three different subfolders: /actors, /graph, and /utils.

The structure of the project directory is shown below:

-dataset<br />
&ensp;-bad_integral<br />
&ensp;&ensp;-test<br /> 
&ensp;&ensp;-train<br />
&ensp;&ensp;-validation <br />
&ensp;-good_integral <br />
&ensp;&ensp;-test <br />
&ensp;&ensp;-train <br />
&ensp;&ensp;-validation <br />
&ensp;-dataset_processing_code <br />
&ensp;-raw_dataset <br />
-src <br />
&ensp;-actors <br />
&ensp;-graph <br />
&ensp;-utils <br />
-demo <br />
&ensp;-runme <br />
-test <br />
&ensp;-test01 <br />
&ensp;... <br />
<br />

To classify an image, you can go to the demo dir and put your image under the picture folder, then run runme. The script will convert your image to txt integral image and feed it into the graph. An output of 1 indicates that the program believes the input is a FACE, and 0 indicates that this image is believed to be an Not A FACE.<br />

