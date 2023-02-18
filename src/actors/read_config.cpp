#include <iostream>

#include "read_config.h"

#define MAX_FIFO_COUNT 1

using namespace std;

// constructor
read_config::read_config(welt_c_fifo_pointer out_fifo, char *file_name, int inT) {
    this->out = (welt_c_fifo_pointer)out_fifo;
    this->actor_set_max_port_count(MAX_FIFO_COUNT);
    this->mode = READ_MODE_READ;
    this->file_name = file_name;
    this->T = inT;
}

bool read_config::enable() {
    bool result = false;

    switch (mode) {
        case READ_MODE_READ:
            result = (welt_c_fifo_population(out) < welt_c_fifo_capacity(out));
            break;
        case ERROR:
            result = false;
            break;
        default:
            result = false;
            break;
    }
    return result;
}

void read_config::invoke() {

    switch (mode) {
        case READ_MODE_READ: {      //config format:   first line is T alpha. Starting from the second line to the end, 
                                      //each line is one weak C and config sequence is f,nrowl,ncol,theta,p
                                      

            //total[0] = (float)T;
            
            float data = 0.0;
            FILE *filePtr = NULL;
            
            filePtr = fopen(file_name, "r");
            if (filePtr == NULL) {
                perror("fopen: ");
                exit(EXIT_FAILURE);
            }
            
            for(int i = 0; i< T;i++){
              if (!fscanf(filePtr, "%f,", &data)){
                    perror("fscanf error for the first line: ");
                }
                total.push_back(data);    //first line is alpha
            }
            welt_c_fifo_write(this->out, &total);
            
            //for(int i =0 ;i < total.size(); i++)
              //  cout<<total[i]<<"  ";
            //cout<<endl<<"  ";
            
            for (int iRow = 1; iRow < T+1; iRow++)
            {
                for (int iCol = 0; iCol < 7;iCol++)
                {
                    
                    if (!fscanf(filePtr, "%f,", &data)){
                        perror("fscanf: ");
                    }
                    weak_para.push_back(data);  
                }
            }
            
            //for(int i =0 ;i < 7; i++)
            //    cout<<weak_para[i]<<"  ";
                
            welt_c_fifo_write(this->out, &weak_para);
            
            break;
        }
        case ERROR:
            mode = ERROR;
            break;
        default:
            mode = ERROR;
            break;
    }
}

void read_config::reset() {
    mode = READ_MODE_READ;
}

void read_config::connect(welt_cpp_graph *graph) {
    int port_index;
    int direction;

    /* output 1*/
    direction = GRAPH_OUT_CONN_DIRECTION;
    port_index = 0;
    graph->add_connection(this, port_index, direction);
    //cout << "in_image" << endl;


}

read_config::~read_config() {
    cout << "delete read config actor" << endl;
}

