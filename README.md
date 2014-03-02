Author Matthew Schwegler

Program Name: Huffman Compression.

Program Description:
This program is designed to take an input file and compress it using Huffmans coding algorithm. After compression the file can then be uncompressed using the compliment program.


How to use:

The program is broken into two executable files. A compression program to compress a A into file B and an uncompression program to uncompress file A to file B. Detailed examples listed below

Compress:

A program that takes 2 command line arguments of the form
./compress <FileToCompress> <FileToCompressInto>

Uncompress:

A program that takes 2 command line arguments of the form
./uncompress <FileToCompressInto> <FileToStoreUncompressedVersion>

Supporting Files Class Files:

HCNode
HCTree
BitInputStream
BitOutputStream
