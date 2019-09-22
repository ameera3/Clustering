# Change the CXX variable assignment at your own risk.
CXX ?= g++ 
CXXFLAGS=-std=c++11 -Wall 
LDFLAGS=-g

all: cluster   

cluster: graph.o

graph.o: graph.hpp vertex.hpp edge.hpp  

clean:
		rm -f cluster *.o core* *~
