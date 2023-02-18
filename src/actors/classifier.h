#ifndef classifier_h
#define classifier_h

extern "C" {
#include "welt_c_util.h"
#include "welt_c_fifo.h"
}

#include "welt_cpp_actor.h"
#include "welt_cpp_graph.h"
#include "../utils/utils.h"
#include "../utils/strongC.h"
#include "../utils/WeakClassifier.h"

#define CONFIG_MODE        0
#define READ_MODE     2
#define CLASSIFY_MODE     3
#define TRUE_MODE     4
#define FALSE_MODE     5
class classifier : public welt_cpp_actor{
public:
    classifier(welt_c_fifo_pointer img_in, welt_c_fifo_pointer config_in,
            welt_c_fifo_pointer img_out, welt_c_fifo_pointer result_write, int T);
    ~classifier() override;

    bool enable() override;
    void invoke() override;

    void reset() override;

    void connect(welt_cpp_graph *graph) override;

private:
    welt_c_fifo_pointer img_out;
    welt_c_fifo_pointer result_write;
    welt_c_fifo_pointer config;
    welt_c_fifo_pointer img_in;
    strongC *strongClassifier;
    vector<vector<int>> *img;
    int T;
};

#endif

