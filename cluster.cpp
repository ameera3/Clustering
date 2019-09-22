/* Filename: cluster.cpp
 * Description: The command line program cluster.cpp takes in one parameter, 
 *              an input filename. The input file specified by the input
 *		filename should describe a distance function (equivalently 
 *		a list of the edges of a complete graph and their edge costs. 
 * 		The program will output the maximum spacing of a 4-clustering. 
 */

#include <iostream>
#include "graph.hpp"

using namespace std;

// argv index of input file
#define IN_IDX 1

// expected number of arguments
#define EXPECTED_ARGS 2

// number of clusters
#define CLUSTERS 4

int main(int argc, char** argv) {

	if(argc != EXPECTED_ARGS ){
		cout << "This program expects 2 arguments!" << endl;
		return(-1);
	}

	// create a new instance of Graph
	Graph* G = new Graph();

	// read input file and create vertex map and edge priority queue
	G->loadFromFile(argv[IN_IDX]);

	// run the clustering variant of Kruskal's MST algorithm
	unsigned int maxSpacing = G->cluster(CLUSTERS);

	// Return the max spacing
	cout << "Max Spacing: " << maxSpacing << endl;

	// no memory leaks here
	delete G;

}


