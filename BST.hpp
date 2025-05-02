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

    void insertNode(BSTNode* n, BSTNode* parent, bool insertLeft);

public:
    BST();
    BST(BSTNode* n);
    ~BST();

    BSTNode* getRoot() {return root;};
    BSTNode* getCurr() {return curr;};
    void printNodeInfo();
    void setupRiver();
    void updatePosition();
    std::string navigateRiver();
    
};

#endif