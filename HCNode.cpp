/*
 * Matthew Schwegler
 * CS100way
 *
 * HCNode:
 * Description: implements fucntions listed in the HCNode Header file
 */

#include "HCNode.hpp"

//destructor
HCNode::~HCNode()
{
    delete c0;
    delete c1;
}

/* OVREIDE < operator for the HCNode
 * class
 */
bool HCNode::operator<(const HCNode& other){

    //if counts are differen, compare the counts
    if(count != other.count){
        //reverses the order so smallar item is returned as having priority
        return count > other.count;
    }
    else{
        //use symbols to break tie if counts are equal
        return symbol < other.symbol;
    }
}
