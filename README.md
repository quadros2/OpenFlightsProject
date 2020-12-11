# CS 225 Final Project: hcd3-quadros2-sabarn2-tianren3
## Team Members: Hrishikesh Deshmukh, Sabar Nimmagadda, Lloyd Quadros, Bobby Wang

### Overview
Our group used the OpenFlights dataset with flight routes and airports from 2014, and loaded its data files into a directed graph.  The data and its format can be found here: https://raw.githubusercontent.com/jpatokal/openflights/master/data/airports.dat.  Due to the immense size of the dataset, our team utilized data points from index 3411 to 3884.  Additional information can be found at https://openflights.org/data.html.  We then used the directed graph as the data structure to implement our three algorithms.  

1. Breadth First Search: Traversal algorithm from starting node through neighboring nodes/vertices of the same depth.
2. Dijkstra's Algorithm: Shortest path algorithm between two points A and B.
3. Landmark Path Algorithm: Complex algorithm to find shortest path from A to B through a distinct point C.

### Compiling Our Code
Remember to type `git pull origin master` into the terminal to ensure your local codebase is up to date.  Then, simply type `make` in the terminal and then type `./finalproj` to compile the files and run the contents of main.cpp.  Review the contents of Makefile if you would like any additional information.

### Testing Our Code
Once again, type `git pull origin master` to maintain a current codebase.  Afterwards, type `make test` into the terminal followed by `./test` to run our customized test bench and all of its assertions.  Review or edit the contents of tests.cpp to to examine or modify the test bench.

### Input Format
  

