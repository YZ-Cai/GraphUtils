# Description of GraphUtils

<br/>

GraphUtils contains some basic functions for processing directed graphs, which includes:

- load a graph from file
- check a graph is DAG or not
- transform a graph into a DAG
- output a graph to file
- to be continued...

<br/>

## 1. Input Graph

An input graph file example (Datasets/Sample.graph):

```
7
8
0	2	1	5
1	1	2
2	2	3	4
3	1	1
4	1	0
5	0
6	1	0
```

The first line is the number of vertices (N), while the second line is the number of the edges (M).

The follows N lines are the out-degree and out-neighbors of each vertice. For example, the third line is for vertex "0", and its out-degree is 2, its out-neighbors are "1" and "5".

<br/>

## 2. Functions of GraphUtils

- **Load in graph**

  ```c++
  Graph(char* inputGraphFilename)
  ```

- **Check the graph is DAG or not**

  ```c++
  bool isDAG()
  ```

  Return True if the graph is a DAG.

- **Transform the graph to DAG**

  ```c++
  void transformToDAG()
  ```

- **Write the DAG to file**

  ```c++
  void writeDAGToFile(string outputFilename)
  ```

<br/>

## 3. A Demo for Testing

- **Test codes in "RunTest.cc":**

  ```c++
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
  ```

- **Run Test codes:**

  1. Please run the "make" command to compile first.

  2. Run the executable file "RunTest". Note that for linux, the size of running stack may need to extend before running the program, for example, set to 2048 MB:

     ```
     ulimit -s 2097152 
     ```

  3. Output of command lines:

     ```
     Finish loading graph, |V|=3, |E|=2
     The graph is a DAG.
     Finish DAG transformation. DAG has 3 vertices and 2 edges.
     Successfully write to file: Datasets/Sample.DAG
     ```

     Also, in folder "DataSets", there is a file named "Sample.DAG", which is the corresponding DAG generated from input graph.

