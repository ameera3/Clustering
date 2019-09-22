/*
 * Filename: graph.hpp
 * Description: Implements a graph class for a clustering
 *		variant of Kruskal's MST algorithm.
 *		
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <unordered_map>
#include <queue>
#include "vertex.hpp"
#include "edge.hpp"

using namespace std;

/* 
 * Class name: Graph
 * Instance Variables: vertex_map (unordered map of vertex names and
 *				   corresponding vertex pointers)
 *                     pqEdge (a priority queue of edge pointers and 
 *                             their weights)
 * Description: Implements a Graph class for a clustering variant of 
 *              Kruskal's MST algorithm.                   
 * Public Methods: constructor, destructor, loadfromFile, cluster, find, merge
 * Private Methods: None                    
*/

class Graph {

public:

    // Unordered map of vertex labels and corresponding vertex pointers
    unordered_map<unsigned int,Vertex*> vertex_map;

    // Priority Queue of edges
    priority_queue< pair<int, Edge*>, vector<pair<int, Edge*>>,
	greater<pair<int, Edge*>> > pqEdge;

    /**
     * Constuctor of the graph
     */
    Graph(void);

    /*
     * Load the graph from a list of its edges and edge costs
     *
     * filename - input filename
     *
     * return true if file was loaded sucessfully, false otherwise
     */
    bool loadFromFile(const char* filename);

    /* Destructor */
    ~Graph();

    /*
     * Clustering Variant of Kruskal's MST Algorithm
     * 
     * returns the maximum spacing of a k-clustering
     */ 
    unsigned int cluster(unsigned int k);

    /*
     * Finds the representative of the connected component that the vertex n
     * is in and implements path compression. Path compression makes all the
     * actors on a path from n to its parent, the direct children of the 
     * parent.
     *
     * n - Vertex* pointer representing n
     *
     * returns a Vertex* pointer pointing to the representative of
     * the connected component that the vertex n is in
     */ 

    Vertex* find( Vertex* n );

    /*
     * Merges the connected components that the vertices u and v are in 
     *
     * u -- Vertex* pointer 
     * v -- Vertex* pointer representing a vertex in a different
     *      connected component than u
     *
     * Possibly changes the parent of u or v and may also change the
     * rank of u or v.     
     *
     */ 
    void merge(Vertex* u, Vertex* v); 

};


#endif // GRAPH_HPP
