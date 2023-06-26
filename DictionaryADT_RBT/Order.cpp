// -----------------------------------------------------------------------------
//  Order.cpp
//  Aryan Patel
// -----------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<string>
#include"Dictionary.h"

using namespace std;

int main(int argc, char * argv[]){
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
    // Read input file and insert strings into dictionary
    Dictionary dict;
    string line;
    int lineNum = 1;
    while (getline(input, line)){
        dict.setValue(line, lineNum);
        lineNum++;
    }
    // Write dictionary to output file
    output << dict.to_string() << endl;
    output << dict.pre_string() << endl;
    // Close file streams
    input.close();
    output.close();
    return (EXIT_SUCCESS);
}