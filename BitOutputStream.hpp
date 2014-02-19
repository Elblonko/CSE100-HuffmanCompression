#ifndef OUTPUTSTREAM_HPP
#define OUTPUTSTREAM_HPP
/*
 * Matthew Schwegler
 * CS100way
 *
 * BitInputStream.hpp
 * Descrpition: Outlines functions to be used by the BitInputStream class
 *              class will take an input and read it single bit by single
 *              bit using a composition of the ofstream class.
 */


#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <queue>

typedef unsigned char byte;

using namespace std;


class BitOutputStream {
    //Instance variables 
    private:
        //ofstream object used for composition
        ostream &out;
        //queue to hold path of bits created in a buffer
        queue<unsigned char> path;
        //bitset object used to hold each bit passed in
        bitset<8> bits;
        //position in bitset
        int count;
        //Totalbits written
        unsigned int totalCount;

    public:
        //constructor
        BitOutputStream(ostream & os, queue<unsigned char> &queue) : out(os) , path(queue) {
            bits.reset();
            count = 7;
            totalCount = 0;
        }

        /*
         * writes a bit at a time to the object
         * when reaches 8th bit writes to output
         *
         */
        void put(int toBits);

        /*
         * flushes the buffer when called by printing
         * to the output file pointed to by the
         * ofstream object
         *
         */
        void Bflush();

        /*
         * printToFile: takes the char queue created by put
         * and prints it to the output file pointed to by out
         *
         * PRECONDITION: put has been called to fill path
         *
         * POSTCONDITION: path is empty and written to output file,
         * the bytes are preceeded by the totalCount to know how many bits
         * to read
         *
         */
        void printToFile();



};

#endif
