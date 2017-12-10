#include <iostream>
#include <fstream>
#include "workflow.h"


int main(int argc, char* argv[]) {
    try {
        if (argc == 1) {
            std::ifstream conf;
            conf.open(argv[1]);
            wf::Workflow *a = new wf::Workflow(&conf);
            a->work();
            conf.close();
        } else {
            std::cout << "Wrong arguments";
        }
    } catch(wf::my_exception &e) {
        e.get_message();
    }

    return 0;
}