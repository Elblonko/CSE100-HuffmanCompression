/*
 * Matthew Schwegler
 * CS100way
 *
 *
 * File HCTree.cpp
 * Description: implments the functions declared in the HCTree.hpp file
 *
 */

#include "HCTree.hpp"




using namespace std;

HCTree::~HCTree(){
    delete root;
}


/* 
 * Use the Huffman algorithm to build a Huffman coding trie.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION:  root points to the root of the trie,
 *  and leaves[i] points to the leaf node containing byte i.
 *
 */
void HCTree::build(const vector<int>& freqs){

    /*First the code must take in freqs and transform them
     * into HCTNode pointers in the leaves vector
     */

    for ( unsigned int i = 0; i < freqs.size(); i++){
        //ignore if there is no occurance of this character
        if(freqs[i] != 0){
            char ch = i;

            //generate new node
            HCNode* temp = new HCNode(freqs[i], ch);

            //inserts the new node without pointers asigned into leaves
            leaves[i] = temp;

        }
    }

    /* 
     * Now takes the leaves vector and put them in a priority
     * only add the leaves that have count values
     *
     */
    //create the proirity que using template and HCNode compare
    typedef priority_queue<HCNode*,vector<HCNode*>,HCNodePtrComp> huffpq;
    huffpq leavespq;

    //Loop inserts the nonnull nodes into the priority que
    for ( unsigned int i = 0; i < leaves.size(); i++){
        if( (leaves[i])){
            leavespq.push(leaves[i]);

            //increment the count variable
            count++;
        }
    }

    /*
     * Create a Huffman tree by taking the elements in the priority que
     * 2 at a time connecting them to a new node whos count is the sum
     * of both nodes but has NO SYMBOL and reinserting it in the tree
     * the final Node will be the root
     *
     */

    while( ! leavespq.empty() ){

        //set the root of the tree when one element remains
        if( leavespq.size() == 1){
            root = leavespq.top();
            leavespq.pop();
        }

        //More than two nodes in the que pop 2 create tree
        else{
            HCNode* first;
            HCNode* second;

            //Get with highest priority
            first = leavespq.top();
            leavespq.pop();

            //Get element with second highest priority
            second = leavespq.top();
            leavespq.pop();

            //create new node to be parent of two popped nodes with
            //count equal to firstcount = secondcount and symbol = null
            int sum = first->count + second->count;
            HCNode* parent = new HCNode(sum,0);

            //set parent pointers
            parent->c0 = first;
            parent->c1 = second;

            //set first and seconds parent pointers
            first->p = parent;
            second->p = parent;

            //finally reinset parent into the tree
            leavespq.push(parent);

        }

    }

    /*
    //FOR LEAVES DEBUG
    int leavecount = 0;
    for ( unsigned int i = 0; i < leaves.size(); i++){
    if( (leaves[i])){
    char ch = i;
    cerr << *leaves[i] << endl;
    cerr << "The above char is: " << ch << " with ASCII code: " << i << endl;
    leavecount++;
    }

    }
    */

    /*
    //FOR LEAVESPQ DEBUG
    cerr << "The Nodes after priority que are: " << endl;
    int pqcount = 0;
    while ( ! leavespq.empty() ){

//Creates a temp variable
HCNode* temp = leavespq.top();

//pops the element
leavespq.pop(); 

cerr << *temp << endl;

pqcount++;

}

if(leavecount != pqcount)
cerr << "The counts do not match" << endl;

//END OF DEBUG
*/


}

/**
 * Function writes an int byte by byte to
 * the given output stream
 *
 */
void HCTree::writeInt(ofstream& out, unsigned int num){

    unsigned char ch;

    //out.write( (char *)&num, sizeof(num) );
    ch = ( num >> 24) ;
    out.put(ch);
    ch = ( num >> 16) ;
    out.put(ch);
    ch = ( num >> 8 ); 
    out.put(ch);
    ch = ( num ) ;
    out.put(ch);

}


/* 
 * encodes the freqs vector to the output file to be reconstructed
 * by the decode function later.
 *
 */

void HCTree::encodeHuffman(const vector<int>& freqs, ofstream& out){

    //DEBUG
    //cout << "The count is: " << count << endl;
    writeInt(out, count); 

    //print every nonempty vector to find symbol first followed by count
    for ( unsigned int i = 0; i < freqs.size(); i++){

        //checks to see if freqs is empty
        if(freqs[i]){
            //write the symbol
            unsigned char ch = i;
            out.put(ch);



            //writes the integer representing count
            unsigned int num = freqs[i];

            //call to writeInt with num to output integer to file by byte
            writeInt(out, num);

            //DEBUG
            //cerr << "char is: " << ch << " num is: " << num << endl;
        }
    }

}


/*
 * encode takes in a symbol unsigned char for a byte
 * then looks to the huffman code tree to trace a path
 * to that symbol and prints the path out bit by bit
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const{

    //Uses recurse root too print out bits for PATH in in the tree 
    if(leaves[symbol]){
        recurseRoot(leaves[symbol], out);
    }


    return;
}

//need to chage so it prints to BitOutputStream probably use bitset
void HCTree::recurseRoot(HCNode* node, BitOutputStream& out) const{

    //if parent not null recurse
    if(node->p){
        recurseRoot(node->p, out);
    }
    else{
        //return -1 if root
        return;
    }

    //if node was left print 0
    if(node == node->p->c0){
        out.put(0);
        return;
    }
    else if (node == node->p->c1){
        out.put(1);
        return;
    }

    return;
}

/**
 * decodeHuffman in a file to read and a frequency vector
 * this function reads in the values needed to construct leaves
 * 
 * PRECONDITIONS istream is pointing to a file created by the 
 * compress.cpp file
 *
 * POSTCONDITIONS: freqs is returned filled with all the characters
 * inserted in the correct places
 */
void HCTree::decodeHuffman(ifstream &inputFile, vector<int> &freqs){

    //Holds temp character from input file
    unsigned char ch;
    unsigned int count;

    //get the count variable written to the file first
    count = ( inputFile.get() << 24) | ( inputFile.get() << 16) | ( inputFile.get() << 8) | ( inputFile.get());
    //DEBUG
    //cout << "The count is: " << count << endl;


    //Need to loop through the header file reading in symbols and counts in that order
    for (unsigned int i = 0; i < count; i++){

        //first get the symbol
        ch = inputFile.get();

        //try to get char by combining ints
        unsigned int sum = 0;
        sum = ( inputFile.get() << 24) | ( inputFile.get() << 16) | ( inputFile.get() << 8) | ( inputFile.get());


        //create the freqs vector in order to call build
        freqs[ch] = sum;

        //DEBUG
        //cerr << "Inserting sum: " << sum << " into symbol: " << ch << endl;


        //Check to see if there is an error while reading
        if( ! inputFile.good() ){
            break;
        }

    }
}


/** Return symbol coded in the next sequence of bits from the stream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
int HCTree::decode(BitInputStream& in) const{
    
    //Create HCNode to traverse the tree
    HCNode* temp = root;

    //now the path array should be filled in order
    //while path is not empty use its returnst to traverse Huff Tree
    while( ! in.isPathEmpty() ){
        bool p = in.getBit();

        //if statements to traverse the tree
        if(p){
            temp = temp->c1;
        }
        else{
            temp = temp->c0;
        }

        //now check if temp is a leaf
        if(temp->symbol){
            return temp->symbol;
        }
        
    }
    //return -1 to indicate there was an error
    return -1;

}






