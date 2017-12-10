#include "workflow.h"

namespace wf {

    Workflow::Workflow(std::ifstream *conf) {
        Readfile * readfile = new Readfile();
        Writefile * writefile = new Writefile();
        Grep * grep = new Grep();
        Sort * sort = new Sort();
        Replace * replace = new Replace();
        Dump * dump = new Dump();
        commands = {{"readfile",  readfile},
                    {"writefile", writefile},
                    {"grep",      grep},
                    {"sort",      sort},
                    {"replace",   replace},
                    {"dump",      dump}
        };
        cfgParser parser(conf);
        parser.parseBlocks(&commands, &ids);
        parser.parseQueue(&queue);
    }

    Workflow::~Workflow() {
        for (auto it: commands) {
            delete it.second;
            it.second = nullptr;
        }
    }

    void Workflow::work() {
        std::vector<std::string> *text;
        for (int i = 0; i < queue.size(); i++) {
            if (ids[queue[i]] == "readfile") {
                text = commands.find(ids[queue[i]])->second->handleCommand(queue[i], nullptr);
            } else if (ids[queue[i]] == "writefile") {
                commands.find(ids[queue[i]])->second->handleCommand(queue[i], text);
            } else {
                text = commands.find(ids[queue[i]])->second->handleCommand(queue[i], text);
            }
        }
    }

    cfgParser::cfgParser(std::ifstream *conf) : cfg(conf) {}

    void cfgParser::parseBlocks(std::map<std::string, Command*> *commands, std::map<int, std::string> *ids) {
        std::string command;
        getline(*cfg, command);
        if (command != "desc") {
            throw my_exception("Bad");
        }
        for (;;) {
            int id;
            getline(*cfg, command);
            if (command == "csed") { break; }
            std::string Id = command.substr(0, command.find(" "));
            try {
                id = stoi(Id);
            } catch (std::exception &e) {
                throw my_exception("Bad");
            }
            if (command.substr(Id.length(), 3) != " = ") { throw my_exception("Bad"); }
            std::string command_name = command.substr(Id.length() + 3, command.find(" ", Id.length() + 3)
                                                                       - (Id.length() + 3));
            (*ids).insert({id, command_name});
            if (commands->count(command_name) && command_name != "sort" && command.size() !=
                                                                           (command_name.size() + Id.size() + 1)) {
                std::string command_args = command.substr(Id.length() + 3 + command_name.length() + 1, command.size());
                auto it = commands->find(command_name);
                it->second->parseCommand(id, command_args);
            } else if (command_name == "sort") {
                continue;
            } else {
                throw my_exception("Bad");
            }
        }
    }

    void cfgParser::parseQueue(std::vector<int> *queue) {
        std::string que;
        getline(*cfg, que);
        for (;;) {
            if (que == "") { break; }
            int id;
            std::string Id = que.substr(0, que.find(" "));
            try {
                id = stoi(Id);
            } catch (std::exception &e) {
                throw my_exception("Bad");
            }
            (*queue).push_back(id);
            if (que.length() >= 4 && que.substr(que.find(" "), 4) == " -> ") {
                que = que.substr(que.find(" ") + 4, que.length());
            } else if (que.length() == Id.length()) {
                break;
            } else {
                throw my_exception("Bad");
            }
        }
    }

    Command::~Command() {}

    std::vector<std::string> *Readfile::handleCommand(int id, std::vector<std::string> *text) {
        std::ifstream fin;
        fin.open(arguments[id]);
        std::vector<std::string> *new_text = new std::vector<std::string>;
        std::string s;
        for (;;) {
            if (!fin.eof()) {
                getline(fin, s);
                (*new_text).push_back(s);
            } else {
                break;
            }
        }
        fin.close();
        return new_text;
    }

    void Readfile::parseCommand(int id, std::string args) {
        for (int i = 0; i < args.length(); i++) {
            if (args[i] < 32 || args[i] > 126) {
                throw my_exception("Bad");
            }
        }
        Readfile::arguments.insert({id, args});
    }

    std::vector<std::string> *Writefile::handleCommand(int id, std::vector<std::string> *text) {
        std::ofstream fout;
        fout.open(arguments[id]);
        for (int i = 0; i < (*text).size(); i++) {
            fout << (*text)[i] << std::endl;
        }
        fout.close();
        return nullptr;
    }

    void Writefile::parseCommand(int id, std::string args) {
        for (int i = 0; i < args.length(); i++) {
            if (args[i] < 32 || args[i] > 126) {
                throw my_exception("Bad");
            }
        }
        Writefile::arguments.insert({id, args});
    }

    std::vector<std::string> *Grep::handleCommand(int id, std::vector<std::string> *text) {
        std::vector<std::string> *new_text = new std::vector<std::string>;
        std::string word = arguments[id];
        for (int i = 0; i < (*text).size(); i++) {
            if ((*text)[i].find(word) != std::string::npos) {
                new_text->push_back((*text)[i]);
            }
        }
        return new_text;
    }

    void Grep::parseCommand(int id, std::string args) {
        for (int i = 0; i < args.length(); i++) {
            if (args[i] == 8) {
                throw my_exception("Bad");
            }
        }
        Grep::arguments.insert({id, args});
    }

    std::vector<std::string> *Sort::handleCommand(int id, std::vector<std::string> *text) {
        std::string s1;
        std::string s2;
        for (int i = 0; i < (*text).size(); i++) {
            for (int j = (*text).size() - 1; j > i; j--) {
                s1 = (*text)[j - 1];
                s2 = (*text)[j];
                bool cmp = 1; // if 0 - s1 > s2
                for (int k = 0; k < s1.size(); k++) {
                    if (s1[k] < s2[k]) {
                        cmp = 0;
                        break;
                    }
                    if (k == s1.size() - 1 && s1[k] > s2[k] && s2.size() > s1.size()) {
                        cmp = 0;
                    }
                }
                if (cmp) {
                    s1 = (*text)[j - 1];
                    (*text)[j - 1] = (*text)[j];
                    (*text)[j] = s1;
                }
            }
        }
        return text;
    }

    void Sort::parseCommand(int id, std::string args) {
        if (args != "") {
            throw my_exception("Bad");
        }
    }

    std::vector<std::string> *Replace::handleCommand(int id, std::vector<std::string> *text) {
        std::string word1 = arguments[id].substr(0, arguments[id].find(" "));
        std::string word2 = arguments[id].substr(arguments[id].find(" ") + 1, arguments[id].size());
        for (int i = 0; i < (*text).size(); i++) {
            for (int j = 0; j < (*text)[i].size(); j++) {
                if ((*text)[i].find(word1) != std::string::npos) {
                    std::string before = (*text)[i].substr(0, (*text)[i].find(word1));
                    std::string after = (*text)[i].substr((*text)[i].find(word1) + word1.size(), (*text)[i].size());
                    (*text)[i] = before + word2 + after;
                } else {
                    break;
                }
            }
        }
        return text;
    }

    void Replace::parseCommand(int id, std::string args) {
        int backspaces = 0;
        for (int i = 0; i < args.length(); i++) {
            if (args[i] == ' ') {
                backspaces++;
            }
        }
        if (backspaces != 1) {
            throw my_exception("Bad");
        }
        Replace::arguments.insert({id, args});
    }

    std::vector<std::string> *Dump::handleCommand(int id, std::vector<std::string> *text) {
        std::ofstream fout;
        fout.open(arguments[id]);
        for (int i = 0; i < (*text).size(); i++) {
            fout << (*text)[i] << std::endl;
        }
        fout.close();
        return text;
    }

    void Dump::parseCommand(int id, std::string args) {
        for (int i = 0; i < args.length(); i++) {
            if (!((args[i] >= 65 && args[i] <= 90) || (args[i] >= 97 && args[i] <= 122) ||
                  (args[i] >= 48 && args[i] <= 57) || args[i] == 46)) {
                throw my_exception("Bad");
            }
        }
        Dump::arguments.insert({id, args});
    }

}