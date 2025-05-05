#include "BT.hpp"
#include <iostream>

int main() {
    BT Columbia_River;

    Columbia_River.setupRiver();

    // Can optionally save data structure to binary and load data structure from binary file.
    
    // Columbia_River.saveToBinary("binary.dat");
    // Columbia_River.loadFromBinary("binary.dat");

    Columbia_River.printRiver();

    Columbia_River.updatePosition();
    
    
    return 0;
}
