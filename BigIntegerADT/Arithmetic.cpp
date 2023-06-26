// -----------------------------------------------------------------------------
//  Arithmetic.cpp
//  Aryan Patel
// -----------------------------------------------------------------------------

#include<iostream>
#include<fstream>
#include<string>
#include"BigInteger.h"
using namespace std;

int main(int argc, char **argv) {
    ifstream input;
    ofstream output;
    // check command line for correct number of arguments
    if( argc != 3 ){
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }
    // open files for reading and writing 
    input.open(argv[1]);
    if( !input.is_open() ){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }
    output.open(argv[2]);
    if( !output.is_open() ){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }
    // read in lines of the input file.
    string line;
    getline(input, line);
    BigInteger A = BigInteger(line);
    getline(input, line);
    getline(input, line);
    BigInteger B = BigInteger(line);
    
    output << A << std::endl << std::endl;
    output << B << std::endl << std::endl;
    output << A + B << std::endl << std::endl;
    output << A - B << std::endl << std::endl;
    output << A - A << std::endl << std::endl;
    output << A.mult(BigInteger("3")) - B.mult(BigInteger("2")) << std::endl << std::endl;
    output << A * B << std::endl << std::endl;
    output << A.mult(A) << std::endl << std::endl;
    output << B.mult(B) << std::endl << std::endl;
    output << (A * A * A * A).mult(BigInteger("9")) + (B * B * B * B * B).mult(BigInteger("16")) << std::endl << std::endl;

    return(EXIT_SUCCESS);
}
 
