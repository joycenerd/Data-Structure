# Assignment_2 Stack and Queues-- Rats in a Maze

## Introduction ##

This is a typical mazing problem. There will be two rats in the maze. Rat A start at the first grid, and rat B start at the last grid. If the grid is 0 than the rat can walk but if it's 1 then this represent barrier. The two rat will follow specific finding method to find the way out of maze. rat A --> the last gird, rat B --> the first grid. While they're fiding their way print out the whole path of the two rats until one reach the exit. Using stack to record the whole process is the mainpoint of this assignment.

## How to use this program ##

1. Put the maze.txt and the source code in the same folder, so the program can recognize the maze.txt file
2. Run the program in the terminal
``` 
$ cd [folder]
$ gcc main.c
$ ./a.out
```
3. Then the ouput will be in the same folder called result.txt
4. The format of the result.txt the two rat take turn output their path. First ratA, then ratB ... until one of the rat go out of the maze.