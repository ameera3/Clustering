/*
 * Filename: vertex.hpp
 * Description: Implements a vertex class for a graph on 
 *              which we will apply a clustering variant 
 *              of Kruskal's MST algorithm. 
 */

#ifndef VERTEX_HPP
#define VERTEX_HPP
#include <iostream>
#include <iomanip>
using namespace std;

/* 
 * Class name: Vertex
 * Instance Variables: name (unsigned int containing vertex's label)
 *                     rank ("Initially a set has one element and a rank of 
 *                           zero. If two sets are unioned and have the same 
 *                           rank, the resulting set's rank is one larger; 
 *                           otherwise, if two sets are unioned and have 
 *                           different ranks, the resulting set's rank is the 
 *                           larger of the two. Ranks are used instead of 
 *                           height or depth b/c path compression will change 
 *                           the trees' heights over time." - Wikipedia)
 *                     parent (the representative of the connected component
 *                             the vertex is in)
 *                     
 * Description: Implements a vertex class for a graph on which we will apply
 *		a clustering variant of Kruskal's MST algorithm.
 * Public Methods: constructor
 * Private Methods: None                    
*/

class Vertex {

    public:

        // vertex label
        unsigned int name;

        // rank of node
        unsigned int rank;

        // representative of the connected component the actor
        // is in
        Vertex* parent;

        // Constructor that constructs a node with the given label.
        Vertex(unsigned int& label) :
            name(label), rank(0), parent(nullptr) {} 

};

/* Overload operator<< to print a Vertex's fields to an ostream. */
inline ostream & operator <<(ostream& stm, const Vertex& v) {
    stm << '[';
    stm << setw(10) << &v;                   // Vertex address
    stm << "; n:" << v.name;                 // Vertex name
    stm << "; p:" << setw(10) << v.parent;   // Vertex parent
    stm << "; r:" << v.rank;                 // Vertex rank
    stm << ']';
    return stm;
}

#endif // VERTEX_HPP
