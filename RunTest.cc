/*
GraphUtils - Test
Author: Yuzheng Cai
2021-09-22
------------------------------
C++ 11 
*/ 

#include "GraphUtils/Graph.cc"

int main() {    

    // initialize the graph
    Graph* graph = new Graph("Datasets/Sample.graph");
    
    // check the graph is DAG or not
    if (graph->isDAG())
        cout<<"The graph is a DAG."<<endl;
    else
        cout<<"The graph is not a DAG."<<endl;

    // transform the graph to DAG and write to file
    graph->transformToDAG();
    graph->writeDAGToFile("Datasets/Sample.DAG");

    return 0;
}