#ifndef BT_HPP
#define BT_HPP

#include <iostream>

class BTNode {
public:
    std::string name;
    std::string description;
    BTNode* parent;
    BTNode* left;
    BTNode* right;
    BTNode();
    BTNode(std::string insertName, std::string insertDesc);
    ~BTNode();
};

class BT {
private:
    BTNode* root;
    BTNode* curr;
    std::string getInput();
    void saveBT(BTNode* n, std::ofstream& outfile);
    BTNode* loadBT(std::ifstream& inFile);
    void userInsertion();
    void printRiver(BTNode* node, bool isLeft, std::string indent);

public:
    BT();
    BT(BTNode* n);
    ~BT();

    // for testing purposes
    void setCurr(BTNode* node) {curr = node;}

    void insertNode(BTNode* n, BTNode* parent, bool insertLeft);
    BTNode* getRoot() {return root;};
    BTNode* getCurr() {return curr;};
    bool saveToBinary(const std::string& fileName);
    bool loadFromBinary(const std::string& fileName);
    void printNodeInfo();
    void setupRiver();
    void printRiver();
    void updatePosition();
    std::string navigateRiver();
};

#endif
