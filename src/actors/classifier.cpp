#include <iostream>

#include "classifier.h"

using namespace std;

// constructor
classifier::classifier(welt_c_fifo_pointer img_in, welt_c_fifo_pointer config_in, welt_c_fifo_pointer img_out, welt_c_fifo_pointer result_write, int T) {
    this->img_in = (welt_c_fifo_pointer)img_in;
    this->result_write = (welt_c_fifo_pointer)result_write;
    this->img_out = (welt_c_fifo_pointer)img_out;
    this->config = (welt_c_fifo_pointer)config_in;
    this->T = T;
}
//NOT implemented
bool classifier::enable() {
    bool result = false;

    switch (mode) {
        case CONFIG_MODE:
            result = false;
            break;
        case READ_MODE:
            result = false;
            break;
        case CLASSIFY_MODE:
            result = false;
            break;
        case TRUE_MODE:
            result = false;
            break;
        case FALSE_MODE:
            result = true;
            break;
        default:
            result = false;
            break;
    }
    return result;
}

void classifier::invoke() {

    switch (mode) {
        case CONFIG_MODE: {

            vector<float> alpha_in, weak_para;
            //welt_c_fifo_read(this->config, &T);
            welt_c_fifo_read(this->config, &alpha_in);
            welt_c_fifo_read(this->config, &weak_para);
            vector<float> alpha;
            for(int i =0 ;i < T; i++){
                //cout<<alpha_in[i]<<"  ";
                alpha.push_back(alpha_in[i]);
            }
                
            //cout<<endl;
            //for(int i =0 ;i < 5*T; i++)
                //cout<<weak_para[i]<<"  ";
            //cout<<endl;
            
            
            vector<WeakClassifier> weak;
            WeakClassifier* ele;
            for (int i = 0; i < 7*T; i+=7){
                ele = new WeakClassifier((int)weak_para[i],(int)weak_para[i+1],(int)weak_para[i+2],(int)weak_para[i+3],(int)weak_para[i+4],weak_para[i+5],(int)weak_para[i+6]);
                weak.push_back(*ele);
            }
            this->strongClassifier = new strongC(T, alpha, weak);
            //cout << "config mode done" << endl;
            mode = READ_MODE;
            break;
        }
        case READ_MODE:
            welt_c_fifo_read(img_in, &img);
            //cout << "in read mode" << endl;
            mode = CLASSIFY_MODE;
            break;
        case CLASSIFY_MODE:
           /* if(img == NULL){
                cout << "Img is NULL in classifier CLASSIFY MODE";
                exit(1);
            }*/
            //cout << "in classify mode" << endl;
            if(strongClassifier->test(*(this->img))){
            
                mode = TRUE_MODE;
            }else{
            
                mode = FALSE_MODE;
            }    
            break;
        case TRUE_MODE:
            int y;
            y = 1;
            welt_c_fifo_write(this->result_write,&y);
            welt_c_fifo_write(this->img_out,&this->img);
            //cout << "in true mode" << endl;
            mode = READ_MODE;
            break;
        case FALSE_MODE:
            int x;
            x = 0;
            welt_c_fifo_write(this->result_write,&x);
            //cout << "in false mode" << endl;
            mode = READ_MODE;
            break;
        default:
            mode = READ_MODE;
            break;
    }
}

void classifier::reset() {
    mode = CONFIG_MODE;
}

void classifier::connect(welt_cpp_graph *graph) {
    int port_index;
    int direction;

    /* output 1*/
    direction = GRAPH_OUT_CONN_DIRECTION;
    port_index = 0;
    graph->add_connection(this, port_index, direction);
    //cout << "in_image" << endl;


}

classifier::~classifier() {
    cout << "delete classifier actor" << endl;
}
