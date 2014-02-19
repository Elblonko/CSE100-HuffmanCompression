#include "BitOutputStream.hpp"




/*
 * Takes an int that represents a bit and converts in bitset
 * when bitset is full it writes to the output stream
 */
void BitOutputStream::put(int toBit){

    /*
     * condition to see if pos
     * is at 7 need to write bitset
     */
    if(count < 0){
        //call to BitOutPutStreams flush
        this->Bflush();  
    }

    //if bit is  to be 1
    if( toBit == 1 ){
        bits.set(count,1);
        count--;
        totalCount++;
    }
    //if bit is to be 0
    else if( toBit == 0 ){
        bits.set(count,0);
        count--;
        totalCount++;
    }
    //FOR DEBUGGING
    //cout << bits << endl;
}

/*
 * Method that outputs the bitset to file when called
 *
 */
void BitOutputStream::Bflush(){
    //uses the ofstream object to print to file
    unsigned long i = bits.to_ulong();
    unsigned char ch = static_cast<unsigned char>(i);
    //cout << bits << endl;
    path.push(ch);
    count = 7;

}

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
void BitOutputStream::printToFile(){
    
    //print totalCount to file get errors when try to include HCTree.hpp
    //writeInt(out, totalCount);
    unsigned char ch;
    unsigned int num = totalCount;

    //out.write( (char *)&num, sizeof(num) );
    ch = ( num >> 24) ;
    out.put(ch);
    ch = ( num >> 16) ;
    out.put(ch);
    ch = ( num >> 8 ); 
    out.put(ch);
    ch = ( num ) ;
    out.put(ch);

    //while path is not empty
    while( ! path.empty() ){
        //print char to file
        ch = path.front();
        out.put(ch);
        //pop char from the queue
        path.pop();
    }

    //DEBUG
    //cout << "The number of bits written is: " << num << endl;
}





