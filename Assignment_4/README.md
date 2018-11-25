# Assignment_4 Binary Search Tree

### Introduction ###

Two function in this program.
1. Implement a binary search tree. You can insert, delete, search, print in infix or level order at any time. 
2. Treasure hunt game. Read a file of nodes of a binary search tree. Enter the key number, treasure number, and bomb number(0~9). If the node number contains bomb number then delete that node and reconstruct the tree. After deletion and reconstruction first find the key and then find the treasure using shortest path. Key and treasure may be not found.


### How to use this program ###

Three option in the main menu.

1. Binary Search Tree

	Get into binary search tree program

	* (I)nsert a number

	Enter "i" or "I" if you want to insert a node in Binary Search Tree, you will be ask to enter a number (integer) you want to insert. If success you will see "Number [num] is inserted." on the screen. If the number you want to insert is already in BST, you will see "Error. Number [num] exists." on the screen.

	* (D)elete a number

	Enter "d" or "D" if you want to delete a node in BST, you will be ask to enter a number (integer) you want to delete. If the node you want to delete exist in BST, then the program will delete that node and replace that place with the smallest value in the right subtree from that node, after that you will see "Number [num] is deleted." If the node you want to delete doesn't exist, you will see "Number not found." on the screen.

	* (S)earch a number

	Enter "s" or "S" to search for specific number is in BST. You will be ask to enter a number (integer). If found you will see "BINGO! Number is found." on the screen. If not found, you will see "SORRY. Number is not found." on the screen.

	* (P)rint Infix and Level Order

	Enter "p" or "P" if you want to print out BST in current state. The first line of output is the traversal path of inorder traversal (LVR). The second line of output is the traversal path of level order traversal, traverse BST from root level by level.

	* (R)eturn

	Enter "r" or "R" if you want to exit Binary Search Tree program. This will take you back to the main menu

2. Treasure Hunter.

	* You will be ask to enter a file (.txt or .csv) with nodes in BST in the file and each line int the file is one node. If the file is in the same directory as this program then you just need to enter the filename then the program will understand. If the file is somewhere else then you need to give the whole path of the file so the program can fetch the file correctly. If file loading is successful then you will see "Load file success." on the screen. Otherwise the program will exit with error message "Assertion failed: (file!=NULL)".

	* After successfully loaded your file, you will be ask to enter three integer. A key number to open the treasure, a treasure number and a bomb number which is range from 0 to 9.

	* Then the program will delete all the nodes consist of bomb number and reconstruct the tree using the same method as Deletion in Binary Search Tree program, and then output every delete node message "Number [num] is deleted." on the screen if there are nodes to delete.

	* Then find the key from the root and at last find the treasutre. If the key isn't found. You will see "Not found key" on the screen. If the key is found but not found treasure, you will see "Adventurer only found the key.", the path of the key and "Not found treasure." on the screen. If the key and treasure has been found, then you will see "Adventurer successfully found the treasure." and the shortest path from root to key to treasure.

	* After the output the program will return back to the main menu.

3. Exit

	This is for exiting the whole program. 



