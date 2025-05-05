# Rivers Are Trees

## Program Specifications

### Feature:
printNodeInfo()
#### Purpose:
Prints the information stored about the current node user is at
#### Assumptions:
The current node we are at is not null
#### Inputs:
none
#### Outputs:
Two print statements about the location and description of a place along the river
#### State Changes:
none
#### Expected Cases & Behaviors:
When called, print the current location and description of location of the node the user is at
### Feature:
navigateRiver()
#### Purpose:
Fetches user input representing the path they wish to traverse or whether they wish to quit or insert a new node.
#### Assumptions:
A binary search tree exists
#### Inputs:
none
#### Outputs:
A string representing the user's path they wish to go
#### State Changes:
Updates our userInput variable
#### Expected Cases & Behaviors:
5 cases:
 1. User is at the root (mouth of river)
    * User must input either 'L', 'R', or 'Q'
 2. Both children exist
    * User must User must input either 'L', 'R', 'Q', or 'B'
 3. Only the left child exists
    * User must input either 'L', 'B', or 'Q'
 4. Only the right child exists
    * User must input either 'R', 'B', or 'Q'
 5. No children exist
    * User must input either 'B' or 'Q'

### Feature:
updatePosition()
#### Purpose:
Updates the current position of a user in the river by looking at the output from navigateRiver()
#### Assumptions:
A binary search tree exists
#### Inputs:
none
#### Outputs:
none
#### State Changes:
Updates current node
#### Expected Cases & Behaviors:
Calls navigateRiver() and updates current position based on if user entered:
 * L: move to the left subtree
 * R: move to the right subtree
 * B: move to the parent node
 * Q: quit the program

### Feature:
setupRiver()
#### Purpose:
Sets up a binary search tree represetning the Columbia River
#### Assumptions:
A binary search tree exists
#### Inputs:
none
#### Outputs:
none
#### State Changes:
Inserts nodes into our BST representing the Columbia River
#### Expected Cases & Behaviors:
Creates a binary search tree representing the Columbia River with tributaries and dams
### Feature:
userInsertion()
#### Purpose:
Allows the user to insert a new node into the river.
#### Assumptions:
A binary search tree exists
#### Inputs:
none. However, it does importantly take input from the user
#### Outputs:
none
#### State Changes:
Inserts a new node into the existing binary search tree
#### Expected Cases & Behaviors:
Asks user for the name of the node they wish to insert and a description. Will then insert node into the desired place based upon the following cases listed.

3 cases to check:
 1. User is at a node with zero children:
   * Can therefore insert to the left or right, so we must ask the user what they prefer. We then create the new node and insert it to the desired position.
 2. User is at a node with only a left child:
   * Can therefore insert only to the right, so we create the node and insert it to the right.
 3. User is at a node with only a right child:
   * Can therefore insert only to the left, so we create the node and insert it to the left.

### Feature:
saveToBinary()
#### Purpose:
Saves the current binary search tree to a binary file
#### Assumptions:
A binary search tree exists
#### Inputs:
A constant string reference representing the name of the binary file
#### Outputs:
A boolean value representing whether the file was successfully opened for writing and whether the save worked or not.
#### State Changes:
Creates a binary file
#### Expected Cases & Behaviors:
 * If the filename is valid, we call saveBST, then close the stream and return true.
 * If the filename is not valid and ofstream cannot be opened, we return false.

### Feature:
saveBST()
#### Purpose:
A private recursive helper function to save a BST
#### Assumptions:
 * outFile is a valid object ready for writing
 * Nodes contain both a valid name and description
#### Inputs:
A pointer to the root of a given subtree and a reference to the open binary output file stream.
#### Outputs:
None
#### State Changes:
Writes binary data to the outFile stream
#### Expected Cases & Behaviors:
If node is null: Writes isNull flag to be true, write flag to oufile and return.  
If node is not null: Writes isNull flag as false, then saves name and description of node to binary file. Lastly, it calls saveBST() on its left subtree and then its right subtree.

### Feature:
loadFromBinary()
#### Purpose:
Reads from a binary file and loads the data structure into the binary search tree object
#### Assumptions:
 * A binary search tree exists
#### Inputs:
A string reference representing the file name/path
#### Outputs:
A boolean value representing whether the loading was successful or not
#### State Changes:
Overwrites the current binary search tree and updates the nodes appropriately.
#### Expected Cases & Behaviors:
 * If fileName is valid, open an ifstream and calls loadBST() and sets the root and current node.
 * If the file could not be opened, return false.
### Feature:
loadBST()
#### Purpose:
A private recursive function to load a BST
#### Assumptions:
inFile is a valid ifstream object opened in binary mode and ready for reading.
#### Inputs:
A reference to the open binary input file stream
#### Outputs:
A BSTNode pointer to the root of the newly constructed BST.
#### State Changes:
Creates new BSTNode objects and sets names/descriptions accordingly
#### Expected Cases & Behaviors:
If the node is null: reads the isNull flag and returns nullptr
If the node is not null: reads the name and description and creates a new BSTNode with the read name and description. 
   * Then recursively calls loadBST on the left subtree. Next, it assigns the result to the new node's left pointer. If the left child is not nullptr, we set its parent pointer to the current node.
   * Then recursively calls loadBST on the right subtree. Next, it assigns the result to the new node's right pointer. If the right child is not nullptr, we set its parent pointer to the current node.

## Class Specifications
### Feature:
insertNode()
#### Purpose:
Inserts a node into our binary search tree at a specific location.
#### Assumptions:
A binary search tree exists
#### Inputs:
Pointer to a node to be inserted, pointer to a parent node, and a boolean value representing if the node is to be inserted to the left or right
#### Outputs:
none
#### State Changes:
A new node will be inserted into the BST.
#### Expected Cases & Behaviors:
 * If the passed node pointer is null, return nullptr.
 * If the root is nullptr, set the passed node to be our new root
 * If the boolean value tells us to insert to the left and the parent's left subtree is empty, insert the node to the left of the parent. 
 * If the boolean value tells us to insert to the right and the parent's lright subtree is empty, insert the node to the right of the parent. 
 * Else, return.