# Assignment_5 Graph

### Introduction ###

Implementing three algorithms for finding shortest path in a weight graph

1. Kruskal: find shortest path to visit every node once in undirected graph. Always add the smallest weight of all the edges remaining, but if it will generate cycle while adding the edge then discard that edge. Do this until n-1 edges have been chosen, because n nodes in total, so at least n-1 edges can connect all the edges and no cycle generated.
2. Prim:  find shortest path to visit every node once in undirected graph. Given a starting node, add the edge base on one of the node that is reachable already and one isn't and also the weight is the smallest in this condition. Do this until n-1 edges have been chosen.
3. Dijkstra: find the shortest path from a starting node to all the other nodes in a directed graph with nonnegative weight. Choose the next node to visit by the smallest weight of all remaining unvisited nodes, and updates the shortest distance of all the other unvisited node while visiting the next node. Do this until all the nodes been visited. distance[ending node] is the answer

### How to use this program ###

Four options in the main menu:

1. Kruskal Algorithm
	
	* You will be ask to enter an input file (.txt) with total nodes and an adjacency matrix of the graph in the file.
	* If the file isn't found, the program will exit with error message "Assertion failed: (file!=NULL)"
	* The output is all the edges chosen step by step using Kruskal algorithm and the total minimum cost.

2. Prim Algorithm
	
	* You will be ask to enter a input file (.txt) with total nodes, an adjacency matrix of the graph, and a stating node for finding the path in the file.
	* If the file isn't found, the program will exit with error message "Assertion failed: (file!=NULL)"
	* The output is all the edges chosen step by step using Prim algorithm and the total minimum cost.

3. Dijkstra

	* You will be ask to enter a input file (.txt) with total nodes and a matrix that can represent a weighted directed graph.
	* If the file isn't found, the program will exit with error message "Assertion failed: (file!=NULL)"
	* You will be ask to enter the starting node and the ending node with one space between these two numbers.
	*  If the starting node isn't a node in the graph or the ending node isn't a node in the graph the output will be "Invalid starting/ending node". Else if there is no path from starting node to the ending node, the output will be "-1". Else the output will be the minimum cost from starting node to the ending node.