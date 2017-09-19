#include <iostream>
#include <fstream>
#include "module1.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Invalid number of arguments" << endl;
    }
    else {
        ifstream fin(argv[1]);
        ofstream fout(argv[2]);
        list<string> myList;
        string myString;

        if (fin.is_open() && fout.is_open()) {
            /* Reading strings from input file to list container */
            while (!fin.eof()) {
                getline(fin, myString);
                myList.push_back(myString);
            }

            /* Sorting strings */
            Module1::sort_strings(&myList);

            /* Writing strings from sorted list to output file */
            list<string>::iterator it;
            for (auto& it : myList) {
                fout << it << endl;
            }

            fin.close();
            fout.close();
        } else {
            cout << "Can`t open the file";
        }
    }

    return 0;
}