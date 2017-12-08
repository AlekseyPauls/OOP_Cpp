#include <iostream>
#include <fstream>
#include "workflow.h"


int main(int argc, char* argv[]) {
    if (argc == 1) {
        std::ifstream conf;
        conf.open(argv[1]);
        wf::Workflow *a = new wf::Workflow(&conf);
        a->work();
        conf.close();
    } else if (argc > 1 && argv[2] == "-i" && argv[4] == "-o") {
        std::ifstream conf;
        std::ifstream fin;
        std::ofstream fout;
        conf.open(argv[1]);
        fin.open(argv[3]);
        fout.open(argv[5]);
        wf::Workflow *a = new wf::Workflow(&conf, &fin, &fout);
        a->work();
        conf.close();
        fin.close();
        fout.close();
    } else {
        std::cout << "Wrong arguments";
    }

    return 0;
}