#include <iostream>
#include <fstream>
#include "module1.h"

using namespace std;

int main(int argc, char* argv[])
{
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    list<string> myList;
    string myString;

    if (fin.is_open() && fout.is_open())
    {
        /* Reading strings from input file to list container */
        while (not fin.eof())
        {
            getline(fin, myString);
            myList.push_back(myString);
        }
        /* Sorting strings */
        Module1::sort_strings(&myList);

        /* Writing strings from sorted list to output file */
        list<string>::iterator it;
        for (it = myList.begin(); it != myList.end(); it++)
        {
            if(!myList.empty())
            {
                fout << *it << endl;
            }
        }

        fin.close();
        fout.close();
    }

    return 0;
}