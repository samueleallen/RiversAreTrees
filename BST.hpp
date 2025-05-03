#ifndef BST_HPP
#define BST_HPP

#include <iostream>

class BSTNode {
public:
    std::string name;
    std::string description;
    BSTNode* parent;
    BSTNode* left;
    BSTNode* right;
    BSTNode();
    BSTNode(std::string insertName, std::string insertDesc);
    ~BSTNode();
};

class BST {
private:
    BSTNode* root;
    BSTNode* curr;
    std::string getInput();
    void printRiver(BSTNode* n, int upstream, bool mouth, char branch);
    void saveBST(BSTNode* n, std::ofstream& outfile);
    BSTNode* loadBST(std::ifstream& inFile);
    void insertNode(BSTNode* n, BSTNode* parent, bool insertLeft);
    void printRiver(BSTNode* node, bool isLeft, std::string indent);

public:
    BST();
    BST(BSTNode* n);
    ~BST();

    BSTNode* getRoot() {return root;};
    BSTNode* getCurr() {return curr;};
    bool saveToBinary(const std::string& fileName);
    bool loadFromBinary(const std::string& fileName);
    void printNodeInfo();
    void setupRiver();
    void printRiver();
    void updatePosition();
    std::string navigateRiver();
    
};

#endif
