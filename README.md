# Clustering

## Usage
To compile, type "make". To run the program, type "./cluster clustering1.txt"

## Introduction
The command line program cluster.cpp takes in one parameter, an input filename. 
The input file specified by the input filename should describe a distance 
function (equivalently a list of the edges of a complete graph and their edge costs). 
Specifically, the input filename should have the format

[number_of_nodes]

[edge 1 node 1] [edge 1 node 2] [edge 1 cost]

[edge 2 node 1] [edge 2 node 2] [edge 2 cost]

...

The program will output the maximum spacing of a 4-clustering by running a variant
of Kruskal's MST algorithm. To efficiently check if adding an edge to the MST would
create a cycle, we use a [union-find data structure](https://en.wikipedia.org/wiki/Disjoint-set_data_structure).
