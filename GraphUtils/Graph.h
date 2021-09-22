/*
GraphUtils - head file
Author: Yuzheng Cai
2021-09-21
------------------------------
C++ 11 
*/ 

#ifndef GRAPH_H
#define GRAPH_H
#include "Utils.h"

class Graph {

    public:

        // basic graph infomation
        Graph(char* inputGraphFilename);
        VertexID VN;                                                // |V| of graph
        EdgeID EN;                                                  // |E| of graph
        VertexID *inNeighbors, *outNeighbors;                       // neighbors of each vertex, length=EN
        EdgeID *inNeighborsLocator, *outNeighborsLocator;           // locate where to find the neighbors of a vertex, length=VN
        /*
        If V={0,1,2,3} and E={0->1, 0->2, 0->3, 1->2, 1->3, 2->3} then:
        outNeighbors = [1,2,3,2,3,3] and outNeighborsLocator = [0,3,5],
        which means the out-neighbors of vertex v are: outNeighbors[outNeighborsLocator[v]:outNeighborsLocator[v+1]].
        For example, the out-neighbors of vertex 0 are: outNeighbor[0:3], i.e., [1,2,3]
        */

        // check the graph is DAG or not
        bool isDAG();

        // transform the graph to a DAG
        void transformToDAG();
        void writeDAGToFile(string outputFilename);

        // DAG information
        VertexID DAGVN;                                             // |V| of DAG
        EdgeID DAGEN;                                               // |E| of DAG
        VertexID *DAGInNeighbors, *DAGOutNeighbors;                 // neighbors of each vertex, length=DAGEN
        EdgeID *DAGInNeighborsLocator, *DAGOutNeighborsLocator;     // locate where to find the neighbors of a vertex, length=DAGVN

    private:

        // load graph file
        char* graphFilename;
        void loadGraphFile();

        // check the graph is DAG or not
        short* state;
        bool DFS(VertexID u);

        // transform the graph to a DAG
        VertexID newId;                                             // new vertex id after condensing SCC
        bool* visited;						                        // mark those visited vertices
        bool* inStack;                                              // remember which vertex is in stack
        VertexID *stack, stackEnd;                                  // stack for Tarjan Algorithm
        VertexID order, *DFN, *LOW;                                 // used in Tarjan Algorithm
        VertexID* rawToDAG;                                         // match raw vertex id to new vertex id 
        VertexID curLocator, *DAGToRawLocator, *DAGToRaw;           // match new vertex id to raw vertex id
        void tarjan(VertexID u);                                    // Tarjan Algorithm

};


bool cmpVertexPair(pair<VertexID,VertexID>& a, pair<VertexID,VertexID>& b) {
    return a.second<b.second;
}

#endif