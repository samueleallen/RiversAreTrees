#include "BST.hpp"
#include <iostream>

int main() {
    BST Columbia_River;

    Columbia_River.setupRiver();
    // Columbia_River.saveToBinary("binary.dat");
    // Columbia_River.loadFromBinary("binary.dat");

    Columbia_River.printRiver();

    Columbia_River.updatePosition();
    
    
    return 0;
}
