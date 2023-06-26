// -----------------------------------------------------------------------------
//  WordFrequency.cpp
//  Aryan Patel
// -----------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include"Dictionary.h"

using namespace std;

// Main function!
int main(int argc, char *argv[]) {
    ifstream input;
    ofstream output;
    // check command line for correct number of arguments
    if( argc != 3){
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }
    // open files for reading and writing 
    input.open(argv[1]);
    if( !input.is_open()){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }
    output.open(argv[2]);
    if( !output.is_open()){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }
    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
    Dictionary Dict;
    string line;
    for (string line; getline(input, line);){
        size_t len = line.length();
        int start = min(line.find_first_not_of(delim, 0), len);
        int finish = min(line.find_first_of(delim, start), len);
        string tok = line.substr(start, finish - start);
        for (; tok != ""; start = min(line.find_first_not_of(delim, finish + 1), len), finish = min(line.find_first_of(delim, start), len), tok = line.substr(start, finish - start)){
            transform(tok.begin(), tok.end(), tok.begin(), ::tolower);
            if (Dict.contains(tok)){
                int& count = Dict.getValue(tok);
                count++;
            }
            else{
                Dict.setValue(tok, 1);
            }
        }
    }
    output << Dict;
    return (EXIT_SUCCESS);
}
