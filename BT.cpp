#include "BT.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>

BTNode::BTNode() {
    name = "Default Name";
    description = "Default Description";
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

BTNode::BTNode(std::string inputName, std::string inputDesc) {
    name = inputName;
    description = inputDesc;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

BTNode::~BTNode() {

}

BT::BT() {
    this->root = nullptr;
    this->curr = nullptr;
}

BT::BT(BTNode* root) {
    this->root = root;
    this->curr = root;
}

BT::~BT() {

}

std::string BT::getInput(){
    std::string userInput;
    std::cin >> userInput;
    for (int i = 0; i < userInput.length(); i++)
        userInput[i] = toupper(userInput[i]);
    return userInput;
}

/*
Prints the name and description of a node in our BT
*/
void BT::printNodeInfo() {
    std::cout << "Location: " << curr->name << std::endl;
    std::cout << "Description: " << curr->description << std::endl;
}

/*
Saves the entire tree representing our river to a binary file (Includes information about name and description)
*/
bool BT::saveToBinary(const std::string& filename) {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        return false;
    }

    saveBT(root, outFile);
    outFile.close();
    return true;
}

/*
Helper function to write a node and recursively saves its children to a binary file
*/
void BT::saveBT(BTNode* n, std::ofstream& outFile) {
    if (n == nullptr) {
        // Write a flag for null nodes
        bool isNull = true;
        outFile.write(reinterpret_cast<const char*>(&isNull), sizeof(bool));
        return;
    }

    // Write flag for non-null nodes
    bool isNull = false;
    outFile.write(reinterpret_cast<const char*>(&isNull), sizeof(bool));

    // Write name of node to binary file
    size_t nameLength = n->name.length();
    outFile.write(reinterpret_cast<const char*>(&nameLength), (sizeof(size_t)));
    outFile.write(n->name.c_str(), nameLength);

    // Write description of node to binary file
    size_t descLength = n->description.length();
    outFile.write(reinterpret_cast<const char*>(&descLength), (sizeof(size_t)));
    outFile.write(n->description.c_str(), descLength);

    // Recursively save both left and right subtrees
    saveBT(n->left, outFile);
    saveBT(n->right, outFile);
}

/*
Loads a BT from a binary file
*/
bool BT::loadFromBinary(const std::string& filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        return false;
    }

    // Load tree
    root = loadBT(inFile);
    curr = root;
    inFile.close();
    return true;
}

/*
Helper function to read a node and recursively readts its children from a binary file
*/
BTNode* BT::loadBT(std::ifstream& inFile) {
    // Read any null flags
    bool isNull;
    inFile.read(reinterpret_cast<char*>(&isNull), sizeof(bool));

    if (isNull) {
        return nullptr;
    }

    // Read name of node
    size_t nameLength;
    inFile.read(reinterpret_cast<char*>(&nameLength), sizeof(size_t));
    std::string name(nameLength, ' ');
    inFile.read(&name[0], nameLength);

    // Read description of node
    size_t descLength;
    inFile.read(reinterpret_cast<char*>(&descLength), sizeof(size_t));
    std::string description(descLength, ' ');
    inFile.read(&description[0], descLength);

    // Create node
    BTNode* n = new BTNode(name, description);

    // Recursively load left and right subtree
    n->left = loadBT(inFile);
    if (n->left != nullptr) {
        n->left->parent = n;
    }
    n->right = loadBT(inFile);
    if (n->right != nullptr) {
        n->right->parent = n;
    }
    return n;
}

/*
Reads user input from navigateRiver() and performs appropriate state changes
*/
void BT::updatePosition() {
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

        // User inserts a new node of their discretion
        else if (userChoice == "I") {
            userInsertion();
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
std::string BT::navigateRiver() {
    std::string userInput;
    printNodeInfo();
    if (curr == nullptr) {
        std::cout << "Error: Current Node is null" << std::endl;
        return "Q";
    }

    std::cout << "Enter 'Q' to quit at anytime." << std::endl;

    // Case 1: User is at the root (mouth of river)
    if (curr == root) {
        while (userInput != "L" && userInput != "R" && userInput != "Q" && userInput != "I") {
            if (curr->left != nullptr) {
                std::cout << "Insert (L) to travel to the left and arrive at " << curr->left->name << std::endl;
            }
            if (curr->right != nullptr) {
                std::cout << "Insert (R) to travel to the right and arrive at " << curr->right->name << std::endl;
            }
            std::cout << "Insert (I) to create a new location " << std::endl;
            userInput = getInput();
        }
        return userInput;
    } 
    // Case 2: Both children exist
    else if (curr->left != nullptr && curr->right != nullptr) {
        while (userInput != "L" && userInput != "R" && userInput != "B" && userInput != "Q" && userInput != "I") {
            std::cout << "Insert (L) to travel to the left and arrive at " << curr->left->name << std::endl;
            std::cout << "Insert (R) to travel to the right and arrive at " << curr->right->name << std::endl;
            std::cout << "Insert (B) to travel backwards and arrive back at " << curr->parent->name << std::endl;
            std::cout << "Insert (I) to create a new location " << std::endl;
            userInput = getInput();
        }
        return userInput;
    }
    // Case 3: Only the left child exists
    else if (curr->left != nullptr && curr->right == nullptr) {
        while (userInput != "L" && userInput != "B" && userInput != "Q" && userInput != "I") {
            std::cout << "Insert (L) to travel to the left and arrive at " << curr->left->name << std::endl;
            std::cout << "Cannot travel right." << std::endl;
            std::cout << "Insert (B) to travel backwards and arrive back at " << curr->parent->name << std::endl;
            std::cout << "Insert (I) to create a new location " << std::endl;
            userInput = getInput();
        }
        return userInput;
    }
    // Case 4: Only the right child exists
    else if (curr->right != nullptr && curr->left == nullptr) {
        while (userInput != "R" && userInput != "B" && userInput != "Q" && userInput != "I") {
            std::cout << "Cannot travel left." << std::endl;
            std::cout << "Insert (R) to travel to the right and arrive at " << curr->right->name << std::endl;
            std::cout << "Insert (B) to travel backwards and arrive back at " << curr->parent->name << std::endl;
            std::cout << "Insert (I) to create a new location " << std::endl;
            userInput = getInput();
        }
        return userInput;
    }
    // Case 5: Both children do not exist
    else {
        while (userInput != "B" && userInput != "Q" && userInput != "I") {
            std::cout << "Cannot travel left." << std::endl;
            std::cout << "Cannot travel right." << std::endl;
            std::cout << "Insert (B) to travel backwards and arrive back at " << curr->parent->name << std::endl;
            std::cout << "Insert (I) to create a new location " << std::endl;
            userInput = getInput(); 
        }
        return userInput;
    }
    
}

void BT::insertNode(BTNode* n, BTNode* parent, bool insertLeft) {
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
Asks the user for a name and description for a new node they wish to insert into existing river
*/
void BT::userInsertion() {
    std::string nodeName;
    std::string nodeDesc;
    std::string leftOrRight = "";
    bool isLeft = false;
    
    // Fetch user input about node data (Using getLine() in case user's input has spaces that cin won't read)
    // Have to clear input buffer so we don't have issues with reading newline characters
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter the name of a place you wish to insert: " << std::endl;
    std::getline(std::cin, nodeName);
    std::cout << "Enter the description for that place: " << std::endl;
    std::getline(std::cin, nodeDesc);
    
    while (leftOrRight != "R" && leftOrRight != "L") {
        // Only 3 cases we have to check since we only let a user call this function if they can insert:
        // Case 1: no children
        if (getCurr()->right == nullptr && getCurr()->left == nullptr) {
            std::cout << "Enter 'R' to insert to the right of your current location and 'L' to insert to the left: " << std::endl;
            leftOrRight = getInput();
        } 
        // Case 2: Only right child is null
        else if (getCurr()->right == nullptr && getCurr()->left != nullptr) {
            leftOrRight = "R";
        } 
        // Case 3: Only left child is null
        else {
            leftOrRight = "L";
        }
    }

    // If user input is set to be "L", set isLeft to be true, else it remains false
    if (leftOrRight == "L") {  
        isLeft = true;
    }

    BTNode* userInputNode = new BTNode(nodeName, nodeDesc);

    // Call insertnode
    insertNode(userInputNode, getCurr(), isLeft);
}


void BT::printRiver() {
    printRiver(root, true, "\t"); 
}

/*
Prints river information captured in nodes in our binary tree*/
void BT::printRiver(BTNode* node, bool isLeft, std::string indent) {
    if(node == nullptr) {
        return;
    }
    else if (node != nullptr) {
        std::cout << indent;

        // the current node is the mouth of the river
        if(node == root) {
            std::cout << "* ";
        }
        // the current node is the left child of its parent
        else if(isLeft) {
            std::cout << "|--";
        }
        // the current node is the right child of its parent
        else {
            std::cout << "\\__";
        }
        // print the name of the current node
        std::cout << node->name << std::endl;

        // recursively call each level of the tree w/ its river information
        printRiver(node->left, true, indent + (isLeft ? "|   " : "    "));
        printRiver(node->right, false, indent + (isLeft ? "|   " : "    "));
    }
}


/*
Inserts river information as nodes in our binary tree
*/
void BT::setupRiver() {
    BTNode* mouth = new BTNode("Columbia River Mouth", "Pacific Ocean, at Clatsop County, Oregon / Pacific County, Washington");

    // Some filler nodes for the Columbia River
    BTNode* river = new BTNode("Columbia River", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    BTNode* river2 = new BTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    BTNode* river3 = new BTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    BTNode* river4 = new BTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    BTNode* river5 = new BTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    BTNode* river6 = new BTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    BTNode* river7 = new BTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    BTNode* river8 = new BTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    BTNode* river9 = new BTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    BTNode* river10 = new BTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    BTNode* river11 = new BTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    BTNode* river12 = new BTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    BTNode* river13 = new BTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    BTNode* river14 = new BTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    BTNode* river15 = new BTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    BTNode* river16 = new BTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    BTNode* river17 = new BTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    BTNode* river18 = new BTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    BTNode* river19 = new BTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    BTNode* river20 = new BTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    BTNode* river21 = new BTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    BTNode* river22 = new BTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    BTNode* river23 = new BTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    BTNode* river24 = new BTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    BTNode* river25 = new BTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    BTNode* river26 = new BTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    BTNode* river27 = new BTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    BTNode* river28 = new BTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    BTNode* river29 = new BTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    BTNode* river30 = new BTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    BTNode* river31 = new BTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    BTNode* river32 = new BTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    BTNode* river33 = new BTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    BTNode* river34 = new BTNode("Columbia River (Continued)", "Fun fact: it is the largest river by volume flowing into the Pacific Ocean from North America");
    
    // Tributaries before Bonneville Dam
    BTNode* youngs = new BTNode("Youngs Tributary", "Length: 43km, Basin Size: 258km^2, Average Discharge: 14.7m^3/s.");
    BTNode* grays = new BTNode("Grays Tributary", "Length: 48km, Basin Size: 320km^2, Average Discharge: 15.9m^3/s");
    BTNode* elochoman = new BTNode("Elochoman Tributary", "The largest salmon (Chinook) ever caught in freshwater in Washington State was caught here by Mark Salmon on Oct 5, 1992, his catch weighed 68 lbs. and 4 ounces");
    BTNode* clatskanie = new BTNode("Clatskanie Tributary", "The river is named for the Tlatskanai, an Athabascan tribe of Native Americans who lived in the valley of the nearby Nehalem River at the time of the arrival of Europeans in the early 19th century.");
    BTNode* cowlitz = new BTNode("Cowlitz Tributary", "When the Cowlitz Salmon Hatchery began operation in 1968, it was the largest of its kind in the world. Currently, it produces nearly 13 million fish each year.");
    BTNode* kalama = new BTNode("Kalama Tributary", "It flows entirely within Cowlitz County, Washington");
    BTNode* lewis = new BTNode("Lewis Tributary", "The drainage basin of the Lewis River covers about 1,046 square miles");
    BTNode* lake = new BTNode("Lake Tributary", "Lake River, a slow, flat slough of the Columbia River, loses only 1 foot (30 cm) in elevation over its entire 11-mile course");
    BTNode* willamette = new BTNode("Willamette Tributary", "Originally created by plate tectonics about 35 million years ago and subsequently altered by volcanism and erosion, the river's drainage basin was significantly modified by the Missoula Floods at the end of the most recent ice age.");
    BTNode* washougal = new BTNode("Washougal Tributary", "Explorers Meriwether Lewis and William Clark referred to the Washougal River as the Seal River.");
    BTNode* sandy = new BTNode("Sandy Tributary", "In 1988, Congress added about 25 miles (40 km) of the Sandy to the National Wild and Scenic Rivers System.");

    BTNode* bonneville_dam = new BTNode("Bonneville Dam", "At the time of its construction in the 1930s it was the largest water impoundment project of its type in the nation, able to withstand flooding on an unprecedented scale");

    // Middle columbia (From bonneville dam to McNary Dam)
    BTNode* wind = new BTNode("Wind Tributary", "When Lewis and Clark passed by the river in October 29, 1805, they called it the ‘New Timbered River’ after the Oregon Ash trees in the area");
    BTNode* little_white_salmon = new BTNode("Little White Salmon Tributary", "Whitewater kayaking experts sometimes run a 4-mile (6.4 km) stretch of rapids in a steep canyon between the Cook–Underwood Road bridge and Drano Lake");
    BTNode* white_salmon = new BTNode("White Salmon Tributary", "Originating on the slopes of Mount Adams, it flows into the Columbia Gorge near the community of Underwood.");
    BTNode* hood = new BTNode("Hood Tributary", "The Hood River was formerly known as Dog River");
    BTNode* klickitat = new BTNode("Klickitat Tributary", "The Klickitat Trail follows the river on an abandoned railroad grade");
    BTNode* fifteenmile_creek = new BTNode("Fifteenmile Creek", "It was named fifteenmile because in pioneer days the main road crossed the creek about fifteen miles (24 km) from The Dalles");
    BTNode* deschutes = new BTNode("Deschutes Tributary", "The Deschutes provided an important route to and from the Columbia for Native Americans for thousands of years, and then in the 19th century for pioneers on the Oregon Trail.");
    BTNode* john_day = new BTNode("John Day Tributary", "In addition to wild spring chinook salmon and bass, the river furnishes habitat for Columbia River redband trout, bull trout, and westslope cutthroat trout");
    BTNode* willow_creek = new BTNode("Willow Creek", " Small and largemouth bass, black crappie, brown bullhead, bluegill, and pumpkinseed live in Willow Creek Lake");
    BTNode* umatilla = new BTNode("Umatilla Tributary", "The name Umatilla is derived from the Native American autonym of the people residing along its banks - the Umatilla, which called themselves Imatalamłáma - People from the Village Ímatalam");

    BTNode* mcnary_dam = new BTNode("McNary Dam", "As with some other dams, it has two additional turbines whose purpose is to power the dam itself. That is, this dam is entirely self-sustaining.");

    // Now need to continue to Spokane Tributary from mcnary dam

    BTNode* walla_walla = new BTNode("Walla Walla Tributary",   "Lewis and Clark, on their return expedition stopped at the mouth of the Walla Walla and stayed with the Walla Walla tribe for a portion of the journey");
    BTNode* snake = new BTNode("Snake Tributary", "About 1,080 miles (1,740 km) long, it is the largest tributary of the Columbia River, which is the largest North American river that empties into the Pacific Ocean.");
    BTNode* yakima = new BTNode("Yakima Tributary", "Lewis and Clark mention in their journals that the Chin-nâm pam (or the Lower Snake River Chamnapam Nation) called the river Tâpe têtt(also rendered Tapteete), possibly from the French tape-tête, meaning \"head hit\".");
    BTNode* crab_creek = new BTNode("Crab Creek Tributary", "It is sometimes referred to as the \"longest ephemeral stream in North America\".");
    BTNode* wenatchee = new BTNode("Wenatchee Tributary", "Water from the Wenatchee River and its tributaries has been diverted for irrigation since 1891, mainly for orchards.");
    BTNode* entiat = new BTNode("Entiat Tributary", "The river's name is derived from the Columbia-Moses (Salishan) term, meaning \"place of grassy water\"; another source states that it was called Enteatqua which means \"Rapid Water\" or \"Rushing Water.\" The name, spelled \"Entiat\", was selected for the river in 1958 by the Chelan County Public Utility District.");
    BTNode* chelan = new BTNode("Chelan Tributary", "Nearly the entire river's flow is diverted to the Lake Chelan Powerhouse, 3.9 miles (6.3 km) downstream near the river's mouth. Thus the Chelan River is almost always dry.");
    BTNode* methow = new BTNode("Methow Tributary", "The Methow's watershed is characterized by relatively pristine habitats, as much of the river basin is located in national forests and wildernesses.");
    BTNode* okanogan = new BTNode("Okanogan Tributary", "From Oroville the Okanogan River flows south through the Okanogan County, past Okanogan and Omak. It forms the western boundary of the Colville Indian Reservation.");
    BTNode* nespelem = new BTNode("Nespelem Tributary", "It is completely contained within Okanogan County and the Colville Indian Reservation. The name \"Nespelem\" is said to come from the Indian word nesilim, meaning \"flat land\".");
    BTNode* sanpoil = new BTNode("Sanpoil Tributary", "The name is from the Okanagan term [snpʕʷílx], meaning \"people of the gray country\", or \"gray as far as one can see\".");
    BTNode* spokane = new BTNode("Spokane River", "The Spokane River contains some of the highest concentrations of heavy metals of any river in the state, resulting from pollution coming from Lake Coeur D'Alene." );
    BTNode* spokane1 = new BTNode("Spokane River (Continued)", "The Spokane River contains some of the highest concentrations of heavy metals of any river in the state, resulting from pollution coming from Lake Coeur D'Alene." );
    BTNode* spokane2 = new BTNode("Spokane River (Continued)", "The Spokane River contains some of the highest concentrations of heavy metals of any river in the state, resulting from pollution coming from Lake Coeur D'Alene." );
    BTNode* spokane3 = new BTNode("Spokane River (Continued)", "The Spokane River contains some of the highest concentrations of heavy metals of any river in the state, resulting from pollution coming from Lake Coeur D'Alene." );
    BTNode* spokane4 = new BTNode("Spokane River (Continued)", "The Spokane River contains some of the highest concentrations of heavy metals of any river in the state, resulting from pollution coming from Lake Coeur D'Alene." );


    BTNode* little_falls = new BTNode("Little Falls Dam", " It was listed on the National Register of Historic Places in 1988");
    BTNode* long_lake_dam = new BTNode("Long Lake Dam", "Upon its completion in 1915, Long Lake Dam completely blocked salmon migrations to the upper portions of the Spokane River watershed, although much larger Grand Coulee Dam on the Columbia River extirpated salmon from the entire Spokane basin by 1942");
    BTNode* nine_mile_dam = new BTNode("Nine Mile Dam", "The dam was designed by the New York engineering firm of Sanderson & Porter, and originally constructed to satisfy the power needs of the Spokane and Inland Empire Railroad interurban trolley lines");
    BTNode* monroe_street_dam = new BTNode("Monroe Street Dam", "At completion, it was the largest concrete arch bridge in the U.S. and the third longest in the world");

    // Start at mouth of river, go to river only
    insertNode(mouth, nullptr, false);
    insertNode(river, mouth, true);

    // First split, go to Youngs Tributary or continue on river
    insertNode(youngs, river, true);
    insertNode(river2, river, false);

    // Second split and so on...
    insertNode(grays, river2, false);
    insertNode(river3, river2, true);

    insertNode(elochoman, river3, false);
    insertNode(river4, river3, true);

    insertNode(clatskanie, river4, true);
    insertNode(river5, river4, false);

    insertNode(cowlitz, river5, false);
    insertNode(river6, river5, true);

    insertNode(kalama, river6, false);
    insertNode(river7, river6, true);

    insertNode(lewis, river7, false);
    insertNode(river8, river7, true);

    insertNode(lake, river8, false);
    insertNode(river9, river8, true);

    insertNode(willamette, river9, true);
    insertNode(river10, river9, false);

    insertNode(washougal, river10, false);
    insertNode(river11, river10, true);

    insertNode(sandy, river11, true);

    // Made it to Bonneville Dam
    insertNode(bonneville_dam, river11, false);
    insertNode(river12, bonneville_dam, true);

    insertNode(wind, river12, false);
    insertNode(river13, river12, true);

    insertNode(little_white_salmon, river13, false);
    insertNode(river14, river13, true);

    insertNode(white_salmon, river14, false);
    insertNode(river15, river14, true);

    insertNode(hood, river15, true);
    insertNode(river16, river15, false);

    insertNode(klickitat, river16, false);
    insertNode(river17, river16, true);

    insertNode(fifteenmile_creek, river17, true);
    insertNode(river18, river17, false);

    insertNode(deschutes, river18, true);
    insertNode(river19, river18, false);

    insertNode(john_day, river19, true);
    insertNode(river20, river19, false);

    insertNode(willow_creek, river20, true);
    insertNode(river21, river20, false);
    
    insertNode(umatilla, river21, true);
    insertNode(river22, river21, false);
    insertNode(mcnary_dam, river22, true);

    insertNode(river23,mcnary_dam,false);
    // Continue on from McNary Dam

    insertNode(walla_walla,river23,true);
    insertNode(river24,river23,false);

    insertNode(snake,river24,true);
    insertNode(river25,river24,false);

    insertNode(yakima,river25,false);
    insertNode(river26,river25,true);

    insertNode(crab_creek,river26,true);
    insertNode(river27,river26,false);

    insertNode(wenatchee,river27,false);
    insertNode(river28,river27,true);

    insertNode(entiat,river28,false);
    insertNode(river29,river28,true);

    insertNode(chelan,river29,false);
    insertNode(river30,river29,true);

    insertNode(methow,river30,false);
    insertNode(river31,river30,true);

    insertNode(okanogan,river31,false);
    insertNode(river32,river31,true);

    insertNode(nespelem,river32,false);
    insertNode(river33,river32,true);

    insertNode(sanpoil,river33,false);
    insertNode(river34,river33,true);

    // Lastly, continue from Spokane river to Monroe Street Dam
    insertNode(spokane,river34,true);
    insertNode(little_falls, spokane, false);
    insertNode(spokane1, little_falls, true);
    insertNode(long_lake_dam, spokane1, false);
    insertNode(spokane2, long_lake_dam, true);
    insertNode(nine_mile_dam, spokane2, false);
    insertNode(spokane3, nine_mile_dam, true);
    insertNode(monroe_street_dam, spokane3, false);
    insertNode(spokane4, monroe_street_dam, true);
}
