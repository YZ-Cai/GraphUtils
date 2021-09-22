/*
GraphUtils - implementations
Author: Yuzheng Cai
2021-09-21
------------------------------
C++ 11 
*/ 

#include "Graph.h"


Graph::Graph(char* inputGraphFilename) {
    graphFilename = inputGraphFilename;
    loadGraphFile();
}


void Graph::loadGraphFile() {
    
    // open file, read in |V| and |E|
    freopen(graphFilename, "r", stdin);
    scanf("%d%d", &VN, &EN);

    // initialize arrays for storing neighbors
    inNeighbors = new VertexID[EN];
    inNeighborsLocator = new EdgeID[VN+1];
    outNeighbors = new VertexID[EN];
    outNeighborsLocator = new EdgeID[VN+1];

    // scanf the graph file line by line, read out-neighbors
    VertexID id, degree, neighbor;
    pair<VertexID, VertexID>* edges = new pair<VertexID, VertexID>[EN];
    EdgeID curLocator = 0;
    VertexID curId = 0;
    while (scanf("%d", &id)!=EOF) {
        while (curId<=id) {
            outNeighborsLocator[curId] = curLocator;
            curId++;
        }
        scanf("%d", &degree);
        while (degree) {
            scanf("%d", &neighbor);
            edges[curLocator] = {id, neighbor};
            outNeighbors[curLocator] = neighbor;
            curLocator++;
            degree--;
        }
    }
    while (curId<=VN) {
        outNeighborsLocator[curId] = curLocator;
        curId++;
    }
    
    // read in-neighbors
    sort(edges, edges+EN, cmpVertexPair);
    curLocator = 0;
    curId = 0;
    int i=0;
    id = 0;
    while (i<EN) {
        id = edges[i].second;
        while (curId<=id) {
            inNeighborsLocator[curId] = curLocator;
            curId++;
        }
        while (i<EN && edges[i].second==id) {
            inNeighbors[curLocator] = edges[i].first;
            curLocator++;
            i++;
        }
    }
    while (curId<=VN) {
        inNeighborsLocator[curId] = curLocator;
        curId++;
    }
    
    printf("Finish loading graph, |V|=%d, |E|=%d\n", VN, EN);
}


bool Graph::DFS(VertexID u) {
    state[u] = 1;
    for (EdgeID i=outNeighborsLocator[u]; i<outNeighborsLocator[u+1]; i++) {
        if (state[outNeighbors[i]]==1)
            return false;
        else 
            if (state[outNeighbors[i]]==0 && DFS(outNeighbors[i])==false)
                    return false;
        }
    state[u] = 2;
    return true;
}


bool Graph::isDAG() {
    state = new short[VN]();
    for (VertexID i=0; i<VN; i++)
        if (state[i]==0 && DFS(i)==false)
            return false;
    return true;
}


// tarjan algorithm to find SCCs
void Graph::tarjan(VertexID u){

    DFN[u]=LOW[u]=order;                            // DFN and LOW value by traversal order
    order++;
    visited[u] = true;
    stack[stackEnd] = u;
    stackEnd++;
    inStack[u] = true;

    for (VertexID i=outNeighborsLocator[u]; i<outNeighborsLocator[u+1]; i++){   
        VertexID& v = outNeighbors[i];
        if (visited[v]==false){                     // hasn't been visited
            tarjan(v);
            LOW[u] = min(LOW[u],LOW[v]);            // LOW should be the smallest among its childs
        } else if (inStack[v])                      // find a cycle         
            LOW[u] = min(LOW[u],DFN[v]);            // update LOW
    }
    
    int t;
    if (DFN[u]==LOW[u]){                            // a new SCC 
        DAGToRawLocator[newId] = curLocator;
        do {
            stackEnd--;
            t = stack[stackEnd];                    // old id belong to new id
            DAGToRaw[curLocator] = t; 
            curLocator++;                         
            inStack[t] = false;
            rawToDAG[t] = newId;                    // from old id to new id
        } while (t!=u);
        newId++;                                    // next new id
    }
}


// convert a graph with cycles into a DAG
void Graph::transformToDAG(){
    visited = new bool[VN]();                       // mark those visited vertices
    stack = new VertexID[VN];
    stackEnd = 0;                                  
    inStack = new bool[VN]();                       // remember which vertex is in stack
    DFN = new VertexID[VN];                         // vectors used in Tarjan Algorithm
    LOW = new VertexID[VN];                         // vectors used in Tarjan Algorithm            
    rawToDAG = new VertexID[VN];                    // matches from old id to new id in DAG
    curLocator = 0;
    DAGToRaw = new VertexID[VN];                    // matches from new id in DAG to old id
    DAGToRawLocator = new VertexID[VN+1];

    // run Tarjan to find SCCs
    order = 0;
    newId = 0;
    for (VertexID i=0; i<VN; i++)
        if (visited[i]==false) 
            tarjan(i);
    DAGToRawLocator[newId] = curLocator;
    DAGVN = newId;

    // DAG out-neighbors
    unordered_set<VertexID> tmp;
    curLocator = 0;
    DAGOutNeighbors = new VertexID[EN];
    DAGOutNeighborsLocator = new EdgeID[DAGVN+1];
    for (VertexID i=0; i<DAGVN; i++) {
        DAGOutNeighborsLocator[i] = curLocator;
        tmp.clear();
        for (VertexID j=DAGToRawLocator[i]; j<DAGToRawLocator[i+1]; j++) {
            VertexID& oldId = DAGToRaw[j];
            for (EdgeID k=outNeighborsLocator[oldId]; k<outNeighborsLocator[oldId+1]; k++)
                if (rawToDAG[outNeighbors[k]]!=i)
                    tmp.insert(rawToDAG[outNeighbors[k]]);
        }
        for (auto& each:tmp) {
            DAGOutNeighbors[curLocator] = each;
            curLocator++;
        }
    }
    DAGOutNeighborsLocator[DAGVN] = curLocator;
    DAGEN = curLocator;

    // DAG in-neighbors
    curLocator = 0;
    DAGInNeighbors = new VertexID[DAGEN];
    DAGInNeighborsLocator = new EdgeID[DAGVN+1];
    for (VertexID i=0; i<DAGVN; i++) {
        DAGInNeighborsLocator[i] = curLocator;
        tmp.clear();
        for (VertexID j=DAGToRawLocator[i]; j<DAGToRawLocator[i+1]; j++) {
            VertexID& oldId = DAGToRaw[j];
            for (EdgeID k=inNeighborsLocator[oldId]; k<inNeighborsLocator[oldId+1]; k++)
                if (rawToDAG[inNeighbors[k]]!=i)
                    tmp.insert(rawToDAG[inNeighbors[k]]);
        }
        for (auto& each:tmp) {
            DAGInNeighbors[curLocator] = each;
            curLocator++;
        }
    }
    DAGInNeighborsLocator[DAGVN] = curLocator;

    cout<<"Finish DAG transformation. DAG has "<<DAGVN<<" vertices and "<<DAGEN<<" edges."<<endl;
}


void Graph::writeDAGToFile(string outputFilename) {
    ofstream fout(outputFilename);
    fout<<DAGVN<<"\n"<<DAGEN<<endl;
    for (VertexID i=0; i<DAGVN; i++) {
        fout<<i<<"\t"<<DAGOutNeighborsLocator[i+1]-DAGOutNeighborsLocator[i];
        for (EdgeID j=DAGOutNeighborsLocator[i]; j<DAGOutNeighborsLocator[i+1]; j++)
            fout<<"\t"<<DAGOutNeighbors[j];
        fout<<endl;
    }
    fout.close();
    cout<<"Successfully write to file: "<<outputFilename<<endl;
}