# Assignment_6 Sorting

### Introduction ###

Implementing three sorting algorithms to sort the data.

1. Selection Sort: From the unsorted list, each time choose the smallest and swap to the right position in the list 
2. Bubble Sort: Always compare with the neighbor if j>j+1 than do swap, so after the first round the largest will be in the right position(last location) in the list
3. Insertion Sort: assume n-1 are sorted, insert element n bysearching in n-1 sorted list, and after insertion the sorted list expanded to n elements
4. Quick Sort: pick a pivot compare from the beginning of the list (i) and the last of the list (j) at the same time with the pivot, if i>pivot and j< pivot, then swapthe two element, then the original list will be partitioned into left list and right list. Elements in left list are all smaller than the pivot, and the elements in the right list are all larger than the pivot. Pick a new pivot in the left list and right list each repeat the procedure above until the list is sorted.

### How to use this program ###

Two options in the menu

1. Do Sorting
	* You will be asked to enter a file with format `.txt`. Inside the data file is a list of data you want to be sorted.
	* The outout will contain four section
		1. input data (unsorted)
		2. selection sort result: output all the step of doing selection sort, one step per line, until the list is sorted the last line is the step count it takes using selection sort to sort the data
		3.  bubble sort result: output all the step of doing bubble sort, one step per line, until the list is sorted, the last line is the step count it takes using bubble sort to sort the data
		4. insertion sort result: output all the step of doing insertion sort, one step per line, until the list is sorted the last line is the step count it takes using insertion sort to sort 
		the data
		5. quick sort result: output all the step of doing quick sort, one step per line, until the list is sorted
2. Exit
	Choose this option if you want to exit the program
