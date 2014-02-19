#include "BitInputStream.hpp"




/*
 * Takes an int that represents a bit and converts in bitset
 * when bitset is full it writes to the output stream
 */
void BitInputStream::get(){

    //use is stream to get a char from the inputfile
    unsigned char ch = in.get();
    bits = ch;
    
    /*
    //DEBUG Make sure bits and ch match
    printf("%0x\n", ch);
    cout << "The bits are: " << bits << endl;
    */

    for (int i = 7; i >=0; i--)
    {
        //check if expectedBits are more than 0
        if(expectedBits <= 0){
            break;
        }
        else if(bits.test(i)){
            path.push(1);
            expectedBits--;
        }
        else{
            path.push(0);
            expectedBits--;
        }
    }

    //DEBUG
}


bool BitInputStream::eof(){
    return in.eof();
}

bool BitInputStream::getBit(){
    bool bit = path.front();
    path.pop();
    return bit;
}

bool BitInputStream::isPathEmpty(){
    return path.empty();
}
