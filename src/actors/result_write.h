#ifndef result_write_h
#define result_write_h

#include <fstream>
#include <string>
extern "C" {
#include "welt_c_util.h"
#include "welt_c_fifo.h"
}
#include "welt_cpp_actor.h"

/* Actor modes */
#define FILE_SINK_MODE_PROCESS (1)
#define FILE_SINK_MODE_COMPLETE (2)
#define FILE_SINK_MODE_ERROR (3)

class result_write : public welt_cpp_actor{
public:
    /*************************************************************************
    Construct a file sink actor with the specified input FIFO connection
    and the specified output file name. 
    *************************************************************************/
    result_write(welt_c_fifo_pointer in, char* file_name);

    /*Destructor*/
    ~result_write() override;

    bool enable() override;

    void invoke() override;

    /* Reset the actor so that the output file is re-opened for writing,
       discarding any previously written contents in the file.
    */
    void reset() override;

    void connect(welt_cpp_graph *graph) override;


private:
    char* file_name;
    ofstream outStream;
    int data;
    welt_c_fifo_pointer in;

};


#endif
