#include "BST.hpp"
#include <cassert>

bool test_Info_Print(){
    // test cases: mouth is current node, dam is current node, tributary is current node, continuation of the columbia river is current node
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

    riverTree4.setCurr(river_contd);
    BSTNode* curr4 = riverTree4.getCurr();

    std::string expectedOutput1 = "Location: Columbia River Mouth\nDescription: Pacific Ocean, at Clatsop County, Oregon / Pacific County, Washington";
    std::string expectedOutput2 = "Location: Bonneville Dam\nDescription: At the time of its construction in the 1930s it was the largest water impoundment project of its type in the nation, able to withstand flooding on an unprecedented scale";
    std::string expectedOutput3 = "Location: White Salmon Tributary\nDescription: Originating on the slopes of Mount Adams, it flows into the Columbia Gorge near the community of Underwood.";
    std::string expectedOutput4 = "Location: Columbia River (Continued)\nDescription: Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America";

    std::string output1 = riverTree1.printNodeInfo();
    std::string output2 = riverTree2.printNodeInfo();
    std::string output3 = riverTree3.printNodeInfo();
    std::string output4 = riverTree4.printNodeInfo();

    assert(curr1 != nullptr);
    assert(output1 == expectedOutput1);
    assert(curr2 != nullptr);
    assert(output2 == expectedOutput2);
    assert(curr3 != nullptr);
    assert(output3 == expectedOutput3);
    assert(curr4 != nullptr);
    assert(output4 == expectedOutput4);

    return true;
}


bool test_Nav_River(){


    return false;
}

bool test_Update_Pos(){


    return false;
}

bool test_Setup(){




    return false;
}

int main(){

    std::cout << "Info Print Test: " <<(test_Info_Print() ? "Passed" : "Failed") << std::endl;
    test_Nav_River();
    test_Update_Pos();
    test_Setup();





}
