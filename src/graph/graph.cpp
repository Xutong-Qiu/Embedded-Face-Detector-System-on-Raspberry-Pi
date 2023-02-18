
#include <iostream>
#include "graph.h"

using namespace std;

graph::graph(char *in_img_file,char* input_config_file_name1, char* input_config_file_name2, char *out_file_name) {
    /* input/output files */
    img_file = in_img_file;
    config_file1 = input_config_file_name1;
    config_file2 = input_config_file_name2;
    output_file = out_file_name;

    /*Set default number of graph iterations*/
    iterations = 1;

    /* the number of actors in this graph */
    actor_count = ACTOR_COUNT;

    /* the number of fifos in this graph */
    fifo_count = FIFO_COUNT;

    /* Initialize fifos. */
    int token_size;
    token_size = sizeof(void *);
    /* Reserve spaces for fifos in the graph*/
    fifos.reserve(fifo_count);

    /* create new fifos and put them into the graph class */
    fifos[FIFO_IMREAD] =((welt_c_fifo_pointer)welt_c_fifo_new(BUFFER_CAPACITY, token_size,FIFO_IMREAD));
    fifos[FIFO_CONFIG_READ1] =((welt_c_fifo_pointer)welt_c_fifo_new(BUFFER_CAPACITY, token_size,FIFO_CONFIG_READ1));
    fifos[FIFO_CONFIG_READ2] =((welt_c_fifo_pointer)welt_c_fifo_new(BUFFER_CAPACITY, token_size,FIFO_CONFIG_READ2));
    fifos[FIFO_IMG_CHANNEL1] =((welt_c_fifo_pointer)welt_c_fifo_new(BUFFER_CAPACITY, token_size, FIFO_IMG_CHANNEL1));
    fifos[FIFO_FILESINK1] =((welt_c_fifo_pointer)welt_c_fifo_new( BUFFER_CAPACITY, token_size, FIFO_FILESINK1));
    fifos[FIFO_FILESINK2] =((welt_c_fifo_pointer)welt_c_fifo_new( BUFFER_CAPACITY, token_size, FIFO_FILESINK2));

            
    /***************************************************************************
    Create actors in the actors vector and put descriptions
    for each actor in the descriptions vector.
    ***************************************************************************/


    actors.reserve(actor_count);
    descriptors.reserve(actor_count);

    actors[ACTOR_IMREAD]=(new txt_img_read(fifos[FIFO_IMREAD],img_file, 24, 24, ACTOR_IMREAD));
    descriptors[ACTOR_IMREAD] =((char*)"actor img read");

    actors[ACTOR_CONFIG_READ1]=new read_config(fifos[FIFO_CONFIG_READ1],input_config_file_name1, 4);
    descriptors[ACTOR_CONFIG_READ1] =((char*)"actor config file read 1");

    actors[ACTOR_CONFIG_READ2]=new read_config(fifos[FIFO_CONFIG_READ2],input_config_file_name2,15);
    descriptors[ACTOR_CONFIG_READ2] =((char*)"actor config file read 2");
    
    
    actors[ACTOR_CLASSIFIER1] =(new classifier(fifos[FIFO_IMREAD], fifos[FIFO_CONFIG_READ1], fifos[FIFO_IMG_CHANNEL1], fifos[FIFO_FILESINK1], 4));
    descriptors[ACTOR_CLASSIFIER1] =((char*)"actor classifier 1");
    
    actors[ACTOR_CLASSIFIER2] =(new classifier(fifos[FIFO_IMG_CHANNEL1], fifos[FIFO_CONFIG_READ2], fifos[FIFO_IMG_CHANNEL1], fifos[FIFO_FILESINK2], 15));
    descriptors[ACTOR_CLASSIFIER2] =((char*)"actor classifier 2");

    actors[ACTOR_FILE_WRITE1]= new result_write(fifos[FIFO_FILESINK1],output_file);
    descriptors[ACTOR_FILE_WRITE1] = ((char*)"actor file sink1");

    actors[ACTOR_FILE_WRITE2]= new result_write(fifos[FIFO_FILESINK2],output_file);
    descriptors[ACTOR_FILE_WRITE2] = ((char*)"actor file sink2");
}

void graph::scheduler() {
    int i;
    int iter;

    for (iter=0; iter<getIters(); iter++) {
        actors[ACTOR_FILE_WRITE1]->reset(); 
        actors[ACTOR_FILE_WRITE2]->reset();

        actors[ACTOR_CONFIG_READ1]->invoke();
        
        actors[ACTOR_IMREAD]->invoke();
        
        for(int i = 0; i< 3; i++){
            actors[ACTOR_CLASSIFIER1]->invoke();
        }

        if(actors[ACTOR_CLASSIFIER1]->enable()){
            actors[ACTOR_CLASSIFIER1]->invoke();
            actors[ACTOR_FILE_WRITE1]->invoke();
        }else{
            actors[ACTOR_CLASSIFIER1]->invoke();
            //actors[ACTOR_FILE_WRITE1]->invoke();       
            actors[ACTOR_CONFIG_READ2]->invoke();
            for(int i = 0; i< 4; i++){
                actors[ACTOR_CLASSIFIER2]->invoke();
            }  
            actors[ACTOR_FILE_WRITE2]->invoke();
            
        }
               
    }
    for (i=0; i<ACTOR_COUNT; i++) {
        //delete actors[i];
    }
    
}

void graph::setIters(int num_iter) {
    iterations = num_iter;
}
int graph::getIters() {
    return iterations;
}

/* destructor */
graph::~graph() {
}
