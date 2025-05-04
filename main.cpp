#include "BST.hpp"
#include <iostream>

int main() {
    BST Columbia_River;

    Columbia_River.setupRiver();

    // Can optionally save data structure to binary and load data structure from binary file.
    // If you are loading a data structure from the binary file, you should first comment out the setupRiver() line.
    
    // Columbia_River.saveToBinary("binary.dat");
    // Columbia_River.loadFromBinary("binary.dat");

    Columbia_River.printRiver();

    Columbia_River.updatePosition();
    
    
    return 0;
}
