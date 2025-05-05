#include "BST.hpp"
#include <cassert>

bool test_Info_Print(){
    // test cases: mouth is current node, dam is current node, tributary is current node, continuation of the Columbia river is current node
    BST riverTree1, riverTree2, riverTree3, riverTree4;

    BSTNode* mouth = new BSTNode("Columbia River Mouth", "Pacific Ocean, at Clatsop County, Oregon / Pacific County, Washington");
    BSTNode* bonneville_dam = new BSTNode("Bonneville Dam", "At the time of its construction in the 1930s it was the largest water impoundment project of its type in the nation, able to withstand flooding on an unprecedented scale");
    BSTNode* white_salmon = new BSTNode("White Salmon Tributary", "Originating on the slopes of Mount Adams, it flows into the Columbia Gorge near the community of Underwood.");
    BSTNode* river_contd = new BSTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");

    // set current node to the root node
    riverTree1.setCurr(mouth);
    BSTNode* curr1 = riverTree1.getCurr();

    // set current node to a dam
    riverTree2.setCurr(bonneville_dam);
    BSTNode* curr2 = riverTree2.getCurr();

    // set current node to a tributary
    riverTree3.setCurr(white_salmon);
    BSTNode* curr3 = riverTree3.getCurr();

    // set current node to continuation of the Columbia river
    riverTree4.setCurr(river_contd);
    BSTNode* curr4 = riverTree4.getCurr();

    std::string expectedOutput1 = "Location: Columbia River Mouth\nDescription: Pacific Ocean, at Clatsop County, Oregon / Pacific County, Washington";
    std::string expectedOutput2 = "Location: Bonneville Dam\nDescription: At the time of its construction in the 1930s it was the largest water impoundment project of its type in the nation, able to withstand flooding on an unprecedented scale";
    std::string expectedOutput3 = "Location: White Salmon Tributary\nDescription: Originating on the slopes of Mount Adams, it flows into the Columbia Gorge near the community of Underwood.";
    std::string expectedOutput4 = "Location: Columbia River (Continued)\nDescription: Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America";

    // We visually check the print statements work
    riverTree1.printNodeInfo();
    riverTree2.printNodeInfo();
    riverTree3.printNodeInfo();
    riverTree4.printNodeInfo();

    return true;
}

bool test_Setup(){
    //Setup
    BST columbia_river;

    // Execution and Validation
    columbia_river.setupRiver();

    assert(columbia_river.getCurr() == columbia_river.getRoot()); // Ensure current node is set to root (mouth of river)
    assert(columbia_river.getCurr()->right == nullptr); // No right child of mouth should be set
    assert(columbia_river.getCurr()->left != nullptr); // Left child of mouth should be Columbia River
    assert(columbia_river.getCurr()->left->left != nullptr); // Youngs tributary should be here
    assert(columbia_river.getCurr()->left->right != nullptr); // Continuation of Columbia River should be here

    // And you could continue on like this for the entire river but we feel like it would be a over-the-top.

    return true;
}

bool test_insert() {
    BST test_tree;

    BSTNode* test1 = new BSTNode("Testing node", "test");
    BSTNode* test2 = new BSTNode("Testing node", "test");
    BSTNode* test3 = new BSTNode("Testing node", "test");

    // Creates a tree with test1 as root, test2 as left child and test3 as right child
    test_tree.insertNode(test1, nullptr, true);
    test_tree.insertNode(test2, test1, true);
    test_tree.insertNode(test3, test1, false);

    // Ensure root, current are set to be first node inserted.
    assert(test_tree.getCurr() == test1);
    assert(test_tree.getRoot() == test1);

    // Ensure left and right nodes are set to be test 2 and test 3
    assert(test_tree.getCurr()->left == test2);
    assert(test_tree.getCurr()->right == test3);

    return true;
}

int main(){

    std::cout << "Info Print Test: " <<(test_Info_Print() ? "Passed" : "Failed") << std::endl;
    std::cout << "Setup River Test: " << (test_Setup() ? "Passed" : "Failed") << std::endl;
    std::cout << "Insertion Test: " << (test_insert() ? "Passed" : "Failed") << std::endl;

}
