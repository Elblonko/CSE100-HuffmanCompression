#ifndef INPUTSTREAM_HPP
#define INPUTSTREAM_HPP

/*
 * Matthew Schwegler
 * CS100way
 *
 * BitInputStream.hpp
 * Descrpition: Outlines functions to be used by the BitInputStream class
 *              class will take an input and read it single bit by single
 *              bit.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <queue>

typedef unsigned char byte;

using namespace std;


class BitInputStream {
    //Instance variables 
    private:
        //ofstream object used for composition
        istream &in;
        //queue to create the path to travel to recreate the file
        queue<bool> path;
        //bitset object used to hold each bit passed in
        bitset<8> bits;
        //position in bitset
        int count;
        //total amount of bits to read in
        unsigned int expectedBits;

    public:
        //constructor
        BitInputStream(istream & is,queue<bool> queue, unsigned int expected )
            : in(is), path(queue) {
            bits.reset();
            count = 7;
            expectedBits = expected;
        }

        /*
         * Takes in a byte at a time using the in steam  
         * then iterates over them reading the input bit by bit
         *
         */
        void get();

        /*
         * Checks if in stream is at the end
         *
         */
        bool eof();

        /*
         * Get the path array from BitInputStream
         *
         */
        bool getBit();

        /*
         * Returns if the path queue is empty
         *
         */
        bool isPathEmpty();        


};

#endif
