/*
 * Filename: graph.cpp
 * Description: Implements a graph class for a clustering variant
 *		of Kruskal's MST algorithm.
 *              
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <queue>
#include "graph.hpp"

using namespace std;

/*
 * Constructor of the graph
 */ 
Graph::Graph(void) {}

/*
 * Load the graph from a list of its edges and edge costs
 *
 * filename - input filename
 *
 * return true if file was loaded sucessfully, false otherwise
 */
bool Graph::loadFromFile(const char* filename) {

	// used to get each line from input file
	string line;

	// used for parsing line
	stringstream ss;

	// used for parsing line
	string temp;

	// number of vertices
	unsigned int numV;

	// input file stream
	ifstream* in = new ifstream(filename);

	// Raise an error if file can't be read
	if( in->eof() ){
		cerr << "Failed to read " << filename << "!\n";
		delete in;
		return false;
	}

	// store the total number of vertices and edges
	getline(*in, line);
	ss << line; // storing line into stringstream
	ss >> temp; // extract number of vertices
	stringstream(temp) >> numV; // store number vertices
	temp = ""; // clear temp	
	ss.str(""); // reset string stream to be empty
	ss.clear(); // reset error flags

	// create the vertex map
	for(unsigned int i = 1; i <= numV; ++i){
		Vertex* vertex = new Vertex(i);
		vertex->parent = vertex;
		vertex_map[i] = vertex;
	}	

	// to check if we parsed file correctly
	unsigned int edgeCount = 0;

	while(getline(*in, line)) {

		unsigned int source; // source label
		unsigned int dest; // destination label
		unsigned int weight; // edge weight

		ss << line; // storing line in stringstream
		ss >> temp; // extract source label
		stringstream(temp) >> source; // store source label
		temp = ""; // clear temp
		ss >> temp; // extract dest label
		stringstream(temp) >> dest; // store dest label
		temp = ""; // clear temp
		ss >> temp; // extract edge weight
		stringstream(temp) >> weight;	
		Vertex* sourceNode = vertex_map[source];
		Vertex* destNode = vertex_map[dest];
		pqEdge.push( make_pair( weight,
			new Edge(sourceNode, destNode, weight)) );

		// reset the string stream to be empty and
		// reset error flags
		ss.str("");
		ss.clear();

		// increment the edge count
		++edgeCount;

	}

	// check that you read in the correct number of edges
	// we have a complete graph on numV vertices
	if( edgeCount != (numV*(numV-1))/2 ){
		cerr << "Incorrect Parse!" << endl;
		delete in;
		exit(-1);
	}

	// no memory leaks here
	delete in;

	return true;

}

/*
 * Finds the representative of the connected component that the vertex n
 * is in and implements path compression. Path compression makes all the
 * vertices on a path from n to its parent, the direct children of the 
 * parent.
 *                          
 * n - Vertex* pointer representing vertex
 *                                    
 * returns a Vertex* pointer pointing to the representative of
 * the connected component that the vertex is in
 */

Vertex* Graph::find( Vertex* n ) { 

	if (n != n->parent) {
		n->parent = find(n->parent); 
	}                             
	return n->parent; 

} 

/*
 * Merges the connected components that the vertices u and v are in 
 *           
 * u -- Vertex* pointer representing a vertex
 * v -- Vertex* pointer representing a vertex in a different
 *      connected component than u
 *                               
 * Possibly changes the parent of u or v and may also change the
 * rank of u or v.     
 *                                              
 */

void Graph::merge(Vertex* u, Vertex* v) { 

	Vertex* uParent = find(u); 
	Vertex* vParent = find(v); 

	/* if two sets are unioned and have different ranks, the resulting set's 
	 * rank is the larger of the two. Attach the shorter tree to the root of 
	 * the taller tree. Thus, the resulting tree is no taller than the 
	 * original trees.
	 */  
	if (uParent->rank > vParent->rank) { 
		vParent->parent = uParent; 
	}    
	else { 
		uParent->parent = vParent; 
	}

	/* If two sets are unioned and have the same rank, the resulting set's 
	 * rank is one larger; When we attach the tree to the other tree, the
	 * resulting tree is taller by one node
	 */  
	if (uParent->rank == vParent->rank) { 
		++vParent->rank; 
	}
} 

/*
 * Clustering Variant of Kruskal's MST Algorithm
 * Returns the maximum spacing of a k-clustering.
 *            
 */

unsigned int Graph::cluster(unsigned int k) {

	// number of edges in minimum spanning tree
	// stop when there are k components
	unsigned int treeSize = vertex_map.size() - k + 1;

	// used to count number of edges in current MST
	unsigned int treeEdges = 0;

	// used to keep track of weight of edge added to MST
	unsigned int maxSpacing = 0;

	// while number of edges in tree is less than required size
	while( treeEdges < treeSize ) {

		// explore edge with lightest weight
		pair<unsigned int, Edge*> current = pqEdge.top();
		pqEdge.pop();

		// check if adding edge to tree would form a cycle
		Vertex* sourceParent = find((current.second)->source);
		Vertex* destParent = find((current.second)->dest);

		// if adding edge to tree would not form a cycle,
		// update the max spacing, increment the number of
		// tree edges and merge the source and destination
		// vertex into the same connected component.
		if( sourceParent != destParent ){
			maxSpacing = current.first;
			++treeEdges;
			merge( (current.second)->source, 
			       (current.second)->dest );    
		}

		// no memory leaks here
		delete current.second;
	}    

	// return the maximum spacing
	return maxSpacing;
}    


/*
 * Destructor: Iterate through the vertex map and delete all vertices
 *             Pop the remaining edges in the priority queue and delete them.
 */

Graph::~Graph() {

	for ( auto it = vertex_map.begin(); it != vertex_map.end(); ++it ){
		delete it->second;
	}
	while( !pqEdge.empty() ) {
		pair<unsigned int, Edge*> current = pqEdge.top();
		pqEdge.pop();
		delete current.second;
	}

}
