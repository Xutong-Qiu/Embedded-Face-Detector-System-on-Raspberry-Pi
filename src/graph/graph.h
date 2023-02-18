#ifndef graph_h
#define graph_h

/*******************************************************************************
This is the dataflow graph for our classfier. It includes XXX strongC actors.
Each strongC has four edges. 
*******************************************************************************/

extern "C" {
#include "welt_c_basic.h"
#include "welt_c_fifo.h"
#include "welt_c_util.h"
}

#include "welt_cpp_actor.h"
#include "welt_cpp_graph.h"

#include "../actors/txt_img_read.h"
#include "../actors/result_write.h"
#include "../actors/classifier.h"
#include "../actors/read_config.h"
#include "../utils/strongC.h"
#include "../utils/utils.h"


/* The capacity of all FIFOs in the graph. */
#define BUFFER_CAPACITY (1024)

/* An enumeration of the actors in this application. */
#define ACTOR_IMREAD (0)
#define ACTOR_CLASSIFIER1 (1)
#define ACTOR_CLASSIFIER2 (2)
#define ACTOR_FILE_WRITE1 (3)
#define ACTOR_FILE_WRITE2 (4)
#define ACTOR_CONFIG_READ1 (5)
#define ACTOR_CONFIG_READ2 (6)
/* An enumeration of the edges in this application. The naming convention
for the constants is FIFO_<source actor>_<sink actor>. */
#define FIFO_IMREAD (0)
#define FIFO_CONFIG_READ1 (1)
#define FIFO_CONFIG_READ2 (2)
#define FIFO_IMG_CHANNEL1 (3)
#define FIFO_FILESINK1 (4)
#define FIFO_FILESINK2 (5)

/* The total numbers of graph elements in the application. */
#define ACTOR_COUNT (7)
#define FIFO_COUNT (6)

/* Graph class definition*/
class graph : public welt_cpp_graph{
public:

    /* Construct an instance of this dataflow graph. The arguments
    are, respectively, the name of the file that contains the input
    image, the name of the file that contains the threshold value
    (an integer), and the name of the file in which the output
    of the graph, which is a pixel count (integer), should be stored.
    */
  graph(char *in_img_file, char* input_config_file_name1,char* input_config_file_name2, char *out_file);

    ~graph();

    /* Scheduler for this graph */
    void scheduler() override;

    /*Set the value of the Iters parameter.*/
    void setIters(int num_iter);

    /*Set the value of the Iters parameter.*/
    int getIters();

private:
    char *img_file;
    char *config_file1;
    char *config_file2;
    char *output_file;
    int iterations;
};

#endif
