/*
 * Name: Matt Schwegler
 * CSE: cs100way
 * Compress.cpp
 *
 */

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <stdlib.h>
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
    ifstream inputFile;     //file to store the open passed in file
    //ofstream outputFile;    //file to store the output stream location

    //If statement to check number of arguments
    if(argc < 2)
    {
        cerr << "Incorrect number of arguments passed in please include <inputfile> and <outputfile>" <<endl;
        return 0;
    }
    //Create a vector to score ints based on ASCII value as index
    vector<int> freqs(256, 0);

    //Open the input stream as binary file dont forget to close inputFile.close()
    inputFile.open(argv[1], ios::binary);


    //Check to see file is open then reads it into memory using memblock
    if(inputFile.is_open())
    {
        //Holds temp character from input file
        unsigned char ch;

        while(1){
            ch = inputFile.get();

             //Check to see if there is an error while reading
            if( ! inputFile.good() ){
                break;
            }

            //inserts into the vector at ther ascii value index and increments the counter
            //freqs.insert(ch, (freqs[ch]) + 1 );
            freqs[ch] = (freqs[ch]) + 1;
        }

        //Check if loop stopped for a non EOF reason
        if (! inputFile.eof() ){
            cerr << "There was a problem reading the file." << endl; 
            return -1;
        }

        //TODO delete
        /*
        //Debug loop used to see what is printed from file
        while(1){
            char ch = inputFile.get();
            if(!inputFile.good() ) break;
            cerr << "That char is: " << ch << endl;
        }
        */
    }
    else{
        cout << "Was unable to open the passed in file" << endl;
        return 0;
    }
    //close input file
    inputFile.close();

    
    //TODO delete DEBUG to check whats in the above created array
    //check to see the contents of the array
    /*
    for ( int i = 0; i < freqs.size(); i++){
        if(freqs[i] != 0){
            char ch = i;
            cerr << "The ASCII is: " << ch << " The count is: " << freqs[i] << endl;
        }

    }
    */

    //Create the HCTree to build the tree with
    HCTree huff;
    //Build by calling huff.build
    huff.build(freqs);

    /*
     * huff is now a completed huffman search tree
     * now make a call to encode function reading the input
     * file again use this to trace that path and print them
     */
    //Open the input stream as binary file dont forget to close inputFile.close()
    inputFile.open(argv[1], ios::binary);
    //create ostream object to create BitOutputStream object with
    ofstream out(argv[2], ios::out | ios::binary);
    //create a queue to fill with the bit path
    queue<unsigned char> path;
        //create BitOutputStream object
    BitOutputStream bitOut(out, path);

    //Write each symbol in freqs to output file followed by count
    //TODO writing the '\n' symbol causes a new line, will have to check if this causes a problem
    //or reads correctly
    huff.encodeHuffman(freqs, out);


    //Check to see file is open then reads it into memory using memblock
    if(inputFile.is_open())
    {
        //Holds temp character from input file
        unsigned char ch;

        while(1){
            ch = inputFile.get();

            //make a call to encode
            huff.encode(ch, bitOut);

             //Check to see if there is an error while reading
            if( ! inputFile.good() ){
                break;
            }

        }
        
        //flush any remaining bits in bitOut
        bitOut.Bflush();

        //after encode call bitOut.path is filled with the array time to print to file
        bitOut.printToFile();

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
    //close output file
    out.close();

}
