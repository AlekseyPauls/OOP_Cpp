#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "my_exeption.h"

namespace wf {

    class Command {
    public:
        std::map<int, std::string> arguments;

        ~Command();

        virtual std::vector<std::string> *handleCommand(int id, std::vector<std::string> *text) = 0;

        virtual void parseCommand(int id, std::string args) = 0;
    };

    class cfgParser {
        std::ifstream *cfg;
    public:
        cfgParser(std::ifstream *conf);

        void parseBlocks(std::map<std::string, Command*> *commands, std::map<int, std::string> *ids);

        void parseQueue(std::vector<int> *queue);
    };

    class Workflow {
    private:
        std::map<std::string, Command*> commands;
        std::vector<int> queue;
        std::map<int, std::string> ids;
    public:
        Workflow(std::ifstream *conf);

        Workflow(std::ifstream *conf, std::ifstream *fin, std::ifstream *fout);

        ~Workflow();

        void work();
    };

    class Readfile : public Command {
        std::vector<std::string> *handleCommand(int id, std::vector<std::string> *text);

        void parseCommand(int id, std::string args);
    };

    class Writefile : public Command {
        std::vector<std::string> *handleCommand(int id, std::vector<std::string> *text);

        void parseCommand(int id, std::string args);
    };

    class Grep : public Command {
        std::vector<std::string> *handleCommand(int id, std::vector<std::string> *text);

        void parseCommand(int id, std::string args);
    };

    class Sort : public Command {
        std::vector<std::string> *handleCommand(int id, std::vector<std::string> *text);

        void parseCommand(int id, std::string args);
    };

    class Replace : public Command {
        std::vector<std::string> *handleCommand(int id, std::vector<std::string> *text);

        void parseCommand(int id, std::string args);
    };

    class Dump : public Command {
        std::vector<std::string> *handleCommand(int id, std::vector<std::string> *text);

        void parseCommand(int id, std::string args);
    };

}