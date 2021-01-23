# CS202_HW4
The Fourth Homework of The CS 202 - Fundamental Structures of Computer Science II

Balanced Search Trees, Hashing and Graphs

The assignment is at the [cs202_hw4.pdf](cs202_hw4.pdf) file.

The report of the homework is at the [hw4.pdf](hw4.pdf) file.

findShortestPath: Breadth first search is used to find the shortest path.

	- A list is used for the output

	- A queue is used for the breadth first search.

	- A map is used to keep the path


findMST: Prim's algorithm is used to find the minimum spanning tree.

	- A list is used for the output

	- A list is used to mark the vertices as visited

	- A min heap is used to find the minimum cost edge and it is implemented by the priority_queue. This heap keeps passenger number and the pair of the airports as a pair.
