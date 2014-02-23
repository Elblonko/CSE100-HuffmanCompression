/*
 * Name: Matt Schwegler
 * CSE: cs100way
 * Uncompress.cpp
 *
 * Description: the compliment program to compress.cpp, this is the main
 *              file designed to take a compressed file as input and output
 *              the original file prior to compression. This does this using
 *              the BitInputStream and HCTree classes.
 *
 */

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <queue>
#include "HCNode.hpp"
#include "HCTree.hpp"



using namespace std;
using std::ofstream;
/*
 * main takes in two arguments input file and output file
 * these will be stored in argv[1] and argv[2] respectively
 */
int main(int argc, const char* argv[])
{   
    //input stream
    ifstream inputFile;

    //Create an HCTree object to construct and access HCtree
    HCTree huff;
    //create a vector of ints to store the path
    queue<bool> path;
    //If statement to check number of arguments

    if(argc < 2)
    {
        cerr << "Incorrect number of arguments passed in please include <inputfile> and <outputfile>" <<endl;
        return 0;
    }
    //Create a vector to score ints based on ASCII value as index
    vector<int> freqs(256, 0);

    cerr << "Uncompressing file:" << argv[1] << "...............";

    //Open the input stream as binary file dont forget to close inputFile.close()
    //GET FILE SIZE
    inputFile.open(argv[1], ifstream::in | ios::binary);
    inputFile.seekg(0, inputFile.end);
    double infileSize = inputFile.tellg();
    //set file back to beggining
    inputFile.seekg(0, inputFile.beg);

    ofstream out(argv[2], ios::out | ios::binary);

    //Check to see file is open then reads it into memory using memblock
    if(inputFile.is_open())
    {   

        //call decodeHuffman will fill freqs in order to call build
        huff.decodeHuffman(inputFile,freqs);

        //Build the tree using freqs
        huff.build(freqs);

        //Now read in the totalCount variable to pass into bitInputStream
        unsigned int expectedBits = ( inputFile.get() << 24) | ( inputFile.get() << 16) | 
            ( inputFile.get() << 8) | ( inputFile.get());

        //Create the BitInputStream Object
        BitInputStream Bin(inputFile, path, expectedBits);

        //loop over expectedbits until eof filling the path array
        while( ! Bin.eof() ){
            Bin.get();
        }

        //CASE OF COMPRESSING A SINGLE CHARACTER
        //If path is initially empty tree has only a root
        if( Bin.isPathEmpty() ) {
            //loop through freqs and print count
            for ( unsigned int i = 0; i < freqs.size(); i++){

                //checks to see if freqs is empty
                if(freqs[i]){
                    int num = freqs[i];
                    for (int j = 0; j < num; j++){
                        char c = (char)i;
                        out.put(c);
                    }


                }
            }
        }

        //with full path array call decode until path is empty
        while( ! Bin.isPathEmpty() ){       
            int decodeRet = huff.decode(Bin);

            if(decodeRet == -1){
                cerr << "Decode returned -1 check for error" << endl;
            }

            //now print the symbol to the ofstream
            unsigned char symbol = (unsigned char)decodeRet;
            out.put(symbol);

            //DEBUG
            //cout << "The symbol found was: " << symbol << endl;

        }


        //Check if loop stopped for a non EOF reason
        if (! inputFile.eof() ){
            cerr << "There was a problem reading the file." << endl; 
            return -1;
        }

    }
    else{
        cout << "Was unable to open the passed in file" << endl;
        return 0;
    }
    //close input file
    inputFile.close();
    out.close();

    cout << "Done!" << endl;

    //Open the input stream as binary file dont forget to close inputFile.close()
    //GET FILE SIZE
    inputFile.open(argv[2], ifstream::in | ios::binary);
    inputFile.seekg(0, inputFile.end);
    double outfileSize = inputFile.tellg();
    //set file back to beggining
    inputFile.seekg(0, inputFile.beg);

    cout  << "Uncompression ratio: " << outfileSize/infileSize << endl;

    inputFile.close();




}

