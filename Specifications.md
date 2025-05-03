# Rivers Are Trees

## Specifications

### Feature:
printNodeInfo()
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
insertNode()
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
### Feature:
setupRiver()
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

#### Assumptions:

#### Inputs:

#### Outputs:

#### State Changes:

#### Expected Cases & Behaviors:

### Feature:

#### Assumptions:

#### Inputs:

#### Outputs:

#### State Changes:

#### Expected Cases & Behaviors: