#ifndef read_config_h
#define read_config_h

extern "C" {
#include "welt_c_util.h"
#include "welt_c_fifo.h"
}

#include "welt_cpp_actor.h"
#include "welt_cpp_graph.h"
#include "../utils/utils.h"

#define READ_MODE_READ        1
#define ERROR     2

class read_config : public welt_cpp_actor{
public:
    read_config(welt_c_fifo_pointer out_fifo, char *file_name, int inT);
    ~read_config() override;

    bool enable() override;
    void invoke() override;

    void reset() override;

    void connect(welt_cpp_graph *graph) override;

private:
    welt_c_fifo_pointer out;
    char* file_name;
    /* each strongC has T weakC and each weakC has */
    int T;
    vector<float> weak_para;
    vector<float> total;                            //format: 
                                                    //i = 0, T
                                                    // i = 1-T+1, alpha
                                                    //i = T+1 - T+1+3*T, T weak C and each weak C has 3 parameters
    
	  //vector<float> alpha;                                  //final parameters, T
};

#endif
