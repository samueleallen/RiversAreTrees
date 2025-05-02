#include "BST.hpp"
#include <iostream>

BSTNode::BSTNode() {
    name = "Default Name";
    description = "Default Description";
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

BSTNode::BSTNode(std::string inputName, std::string inputDesc) {
    name = inputName;
    description = inputDesc;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

BSTNode::~BSTNode() {

}

BST::BST() {
    this->root = nullptr;
    this->curr = nullptr;
}

BST::BST(BSTNode* root) {
    this->root = root;
    this->curr = root;
}

BST::~BST() {

}

/*
Prints the name and description of a node in our BST
*/
void BST::printNodeInfo() {
    std::cout << "Location: " << curr->name << std::endl;
    std::cout << "Description: " << curr->description << std::endl;
}

/*
Reads user input from navigateRiver() and performs appropriate state changes
*/
void BST::updatePosition() {
    std::string userChoice = "";
    while (userChoice != "Q") {
        userChoice = navigateRiver();
        
        // Traverse left if user  input is 'L'
        if (userChoice == "L") {
            curr = curr->left;
        }

        // Traverse right if user input is 'R'
        else if (userChoice == "R") {
            curr = curr->right;
        }

        // Traverse to parent if user input is 'B'
        else if (userChoice == "B") {
            curr = curr->parent;
        }

        // Quit program if user input is 'Q'
        else {
            return;
        }
    }
    return;
}

/*
Navigates through the river based on user's input from menu
*/
std::string BST::navigateRiver() {
    std::string userInput;
    
    if (curr == nullptr) {
        std::cout << "Error: Current Node is null" << std::endl;
        return "Q";
    }

    // Print current node info
    printNodeInfo();
    std::cout << "Enter 'Q' to quit at anytime." << std::endl;

    // Case 1: User is at the root (mouth of river)
    if (curr == root) {
        while (userInput != "L" && userInput != "R" && userInput != "Q") {
            if (curr->left != nullptr) {
                std::cout << "Insert (L) to travel to the left and arrive at " << curr->left->name << std::endl;
            }
            if (curr->right != nullptr) {
                std::cout << "Insert (R) to travel to the right and arrive at " << curr->right->name << std::endl;
            }
            std::cin >> userInput;
        }
        return userInput;
    } 
    // Case 2: Both children exist
    else if (curr->left != nullptr && curr->right != nullptr) {
        while (userInput != "L" && userInput != "R" && userInput != "B" && userInput != "Q") {
            std::cout << "Insert (L) to travel to the left and arrive at " << curr->left->name << std::endl;
            std::cout << "Insert (R) to travel to the right and arrive at " << curr->right->name << std::endl;
            std::cout << "Insert (B) to travel backwards and arrive back at " << curr->parent->name << std::endl;
            std::cin >> userInput;
        }
        return userInput;
    }
    // Case 3: Only the left child exists
    else if (curr->left != nullptr && curr->right == nullptr) {
        while (userInput != "L" && userInput != "B" && userInput != "Q") {
            std::cout << "Insert (L) to travel to the left and arrive at " << curr->left->name << std::endl;
            std::cout << "Cannot travel right." << std::endl;
            std::cout << "Insert (B) to travel backwards and arrive back at " << curr->parent->name << std::endl;
            std::cin >> userInput;
        }
        return userInput;
    }
    // Case 4: Only the right child exists
    else if (curr->right != nullptr && curr->left == nullptr) {
        while (userInput != "R" && userInput != "B" && userInput != "Q") {
            std::cout << "Cannot travel left." << std::endl;
            std::cout << "Insert (R) to travel to the right and arrive at " << curr->right->name << std::endl;
            std::cout << "Insert (B) to travel backwards and arrive back at " << curr->parent->name << std::endl;
            std::cin >> userInput;
        }
        return userInput;
    }
    // Case 5: Both children do not exist
    else {
        while (userInput != "B" && userInput != "Q") {
            std::cout << "Cannot travel left." << std::endl;
            std::cout << "Cannot travel right." << std::endl;
            std::cout << "Insert (B) to travel backwards and arrive back at " << curr->parent->name << std::endl;
            std::cin >> userInput;
        }
        return userInput;
    }
    
}

void BST::insertNode(BSTNode* n, BSTNode* parent, bool insertLeft) {
    if (n == nullptr) { // If passed node is null, return
        return;
    } 
    if (root == nullptr) { // If the root is null, set root to be our node
        root = n;
        curr = root;
        return;
    }
    n->parent = parent;
    // Check if we are to insert node to right
    if (!insertLeft && parent->right == nullptr) {
        // if we are to insert node to the right and the right child's spot is empty
        parent->right = n;

    } else if (insertLeft && parent->left == nullptr) {
        // else if we are to insert node to the left and the left child's spot is empty
        parent->left = n;
    } 
}

/*
Inserts river information as nodes in our binary search tree*/
void BST::setupRiver() {
    BSTNode* mouth = new BSTNode("Columbia River Mouth", "Pacific Ocean, at Clatsop County, Oregon / Pacific County, Washington");
    
    // Tributaries before Bonneville Dam
    // Youngs tributary (left child)
    BSTNode* youngs = new BSTNode("Youngs Tributary", "Length: 43km, Basin Size: 258km^2, Average Discharge: 14.7m^3/s.");
    
    // Grays tributary (right child)
    BSTNode* grays = new BSTNode("Grays Tributary", "Length: 48km, Basin Size: 320km^2, Average Discharge: 15.9m^3/s");

    insertNode(mouth, nullptr, false);
    insertNode(youngs, mouth, true);
}