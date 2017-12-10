#include <gtest/gtest.h>
#include "../workflow.h"

TEST(test_workflow, work)
{
    std::ofstream cfg;
    cfg.open("cfg.txt");
    cfg << "desc" << std::endl;
    cfg << "csed" << std::endl;
    cfg.close();
    std::ifstream cfg;
    cfg.open("cfg.txt");
    wf::Workflow a = new wf::Workflow(&cfg);
    a.work;
    cfg.close();
    ASSERT_EQ(0, 0);
}

TEST(test_workflow, grep)
{
    std::ofstream cfg;
    cfg.open("cfg.txt");
    cfg << "desc" << std::endl;
    cfg << "1 = readfile in.txt" << std::endl;
    cfg << "2 = grep 1" << std::endl;
    cfg << "3 = writefile out.txt" << std::endl;
    cfg << "csed" << std::endl;
    cfg << "1 -> 2 -> 3" << std::endl;
    cfg.close();
    std::ofstream in;
    in.open("in.txt");
    in << 3;
    in << 2;
    in << 1;
    in.close();
    std::ifstream cfg;
    cfg.open("cfg.txt");
    wf::Workflow a = new wf::Workflow(&cfg);
    a.work;
    cfg.close();
    std::ifstream out;
    fin.open("out.txt");
    std::string s;
    int flag = 1;
    for (int i = 1;; i++) {
        if (out.eof()) {
            break;
        }
        getline(out, s);
        if (i > 1 || s != "1") {
            flag = 0;
            break;
        }
    }
    out.close();
    ASSERT_EQ(flag, 1);
}

TEST(test_workflow, sort)
{
    std::ofstream cfg;
    cfg.open("cfg.txt");
    cfg << "desc" << std::endl;
    cfg << "1 = readfile in.txt" << std::endl;
    cfg << "2 = sort" << std::endl;
    cfg << "3 = writefile out.txt" << std::endl;
    cfg << "csed" << std::endl;
    cfg << "1 -> 2 -> 3" << std::endl;
    cfg.close();
    std::ifstream cfg;
    cfg.open("cfg.txt");
    wf::Workflow a = new wf::Workflow(&cfg);
    a.work;
    cfg.close();
    std::ifstream out;
    fin.open("out.txt");
    std::string s;
    int flag = 1;
    for (int i = 1;; i++) {
        if (out.eof()) {
            break;
        }
        getline(out, s);
        if (s.stoi != i) {
            flag = 0;
            break;
        } else if (i > 3) {
            flag = 0;
            break;
        }
    }
    fin.close();
    ASSERT_EQ(flag, 1);
}

TEST(test_workflow, replace)
{
    std::ofstream cfg;
    cfg.open("cfg.txt");
    cfg << "desc" << std::endl;
    cfg << "1 = readfile in.txt" << std::endl;
    cfg << "2 = replace 1 5" << std::endl;
    cfg << "3 = writefile out.txt" << std::endl;
    cfg << "csed" << std::endl;
    cfg << "1 -> 2 -> 3" << std::endl;
    cfg.close();
    std::ifstream cfg;
    cfg.open("cfg.txt");
    wf::Workflow a = new wf::Workflow(&cfg);
    a.work;
    cfg.close();
    std::ifstream out;
    out.open("out.txt");
    std::string s;
    int flag = 1;
    for (int i = 1;; i++) {
        if (out.eof()) {
            break;
        }
        getline(out, s);
        if (i == 1 s.stoi != 3) {
            flag = 0;
            break;
        } else if (i == 2 s.stoi != 2) {
            flag = 0;
            break;
        } else if (i == 3 s.stoi != 5) {
            flag = 0;
            break;
        } else if (i > 3) {
            flag = 0;
            break;
        }
    }
    out.close();
    ASSERT_EQ(flag, 1);
}

TEST(test_workflow, grep)
{
    std::ofstream cfg;
    cfg.open("cfg.txt");
    cfg << "desc" << std::endl;
    cfg << "1 = readfile in.txt" << std::endl;
    cfg << "2 = grep 1" << std::endl;
    cfg << "3 = dump dump.txt" << std::endl;
    cfg << "4 = writefile out.txt" << std::endl;
    cfg << "csed" << std::endl;
    cfg << "1 -> 2 -> 3 -> 4" << std::endl;
    cfg.close();
    std::ofstream in;
    in.open("in.txt");
    in << 3;
    in << 2;
    in << 1;
    in.close();
    std::ifstream cfg;
    cfg.open("cfg.txt");
    wf::Workflow a = new wf::Workflow(&cfg);
    a.work;
    cfg.close();
    std::ifstream dump;
    dump.open("dump.txt");
    std::string s;
    int flag = 1;
    for (int i = 1;; i++) {
        if (out.eof()) {
            break;
        }
        getline(dump, s);
        if (i > 1 || s != "1") {
            flag = 0;
            break;
        }
    }
    dump.close();
    ASSERT_EQ(flag, 1);
}