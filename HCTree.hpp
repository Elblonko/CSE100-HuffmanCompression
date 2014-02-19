#ifndef HCTREE_HPP
#define HCTREE_HPP

#include <queue>
#include <vector>
#include "HCNode.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"

using namespace std;

/** A 'function class' for use as the Compare class in a
 *  priority_queue<HCNode*>.
 *  For this to work, operator< must be defined to
 *  do the right thing on HCNodes.
 */
class HCNodePtrComp {
public:
    bool operator()(HCNode*& lhs, HCNode*& rhs) const {
        return *lhs < *rhs;
    }
};

/** A Huffman Code Tree class.
 *  Not very generic:  Use only if alphabet consists
 *  of unsigned chars.
 */
class HCTree {
private:
    HCNode* root;
    vector<HCNode*> leaves;
    unsigned int count;

    //private helper functions
    void recurseRoot(HCNode* node, BitOutputStream &out)const;

public:
    explicit HCTree() : root(0) {
        leaves = vector<HCNode*>(256, (HCNode*) 0);
        count = 0;
    }

    //destructor
    ~HCTree();



    /** Use the Huffman algorithm to build a Huffman coding trie.
     *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
     *  the frequency of occurrence of byte i in the message.
     *  POSTCONDITION:  root points to the root of the trie,
     *  and leaves[i] points to the leaf node containing byte i.
     */
    void build(const vector<int>& freqs);

    /** Write to the given BitOutputStream
     *  the sequence of bits coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    void encode(byte symbol, BitOutputStream& out) const;

    /**
     * Takes in the freqs vector previously crated and prints out nonempty
     * portions of the vector LETTER than COUNT to be decoded later.
     * PRECONDITION: freqs has been created and huffman tree has been
     * constructed.
     * POSTCONDITION: All nonempty symbols from input are outputed to
     * output file
     */
    void encodeHuffman(const vector<int>& freqs, ofstream& out);

    /**
     * Function takes an integet and a reference to an out stream
     * the function then writes the integer byte by byte to the output
     * stream
     *
     */
    void writeInt(ofstream& out, unsigned int num);

    /** Return symbol coded in the next sequence of bits from the stream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    int decode(BitInputStream& in) const;

    /**
     * decodeHuffman in a file to read and a frequency vector
     * this function reads in the values needed to construct leaves
     * 
     * PRECONDITIONS istream is pointing to a file created by the 
     * compress.cpp file
     *
     */
    void decodeHuffman(ifstream &inputFile, vector<int> &freqs);






};

#endif // HCTREE_HPP
