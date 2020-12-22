## Team Members: Hrishikesh Deshmukh, Sabar Nimmagadda, Lloyd Quadros, Bobby Wang

### Overview
We used the OpenFlights dataset with flight routes and airports from 2014, and loaded its data files into a directed graph.  The data and its format can be found here: https://raw.githubusercontent.com/jpatokal/openflights/master/data/airports.dat.  Due to the immense size of the dataset, our team utilized data points from index 3411 to 3884.  Additional information can be found at https://openflights.org/data.html.  We then used the graph as the data structure to implement our three algorithms.  

1. Breadth First Search: Traversal algorithm from starting node through neighboring nodes/vertices of the same depth.
2. Dijkstra's Algorithm: Shortest path algorithm between two points A and B.
3. Landmark Path Algorithm: Complex algorithm to find shortest path from A to B through a distinct point C.

Additional auxilliary functions include insertVertex and removeVertex, which allow the user to add or remove airports in the graph data structure.

### Compiling Our Code
Remember to type `git pull origin master` into the terminal to ensure your local codebase is up to date.  Then, simply type `make` in the terminal and then type `./finalproj` to compile the files and run the contents of `main.cpp`.  Review the contents of `Makefile` if you would like any additional information. In `main.cpp`, the following functions can be run:

1. Graph(std::string fileName);
2. void insertVertex(double latitude, double longit, string name);
3. void removeVertex(string airportName);
4. std::vector<std::string> BFS(std::string start);
5. std::unordered_map<std::string, std::pair<std::string, double>> Dijkstra(std::string source);
6. std::string landmarkPathAlgorithm(std::string start, std::string landmark, std::string destination);

### Testing Our Code
Once again, type `git pull origin master` to maintain a current codebase.  Afterwards, type `make test` into the terminal followed by `./test` to run our customized test bench and all of its assertions.  Review or edit the contents of `tests.cpp` to to examine or modify the test bench.

### Input Format
Run each individual function **one at a time** in `main.cpp` to analyze how each function works.  Since these algorithms all write output to a file, it is important to run these functions one at a time since many of these functions are called within each other. If you call one function, and then another immediately after, the output of the first function may or may nor be changed! Data points can be added in `main.cpp` using the `insertVertex()` function. Additionally, the proper format for adding data points in our dataset seen in `Airports.txt` is demostrated here: https://openflights.org/data.html.  For example, a sample entry in our `Airports.txt` file looks like this: 
*507,"London Heathrow Airport","London","United Kingdom","LHR","EGLL",51.4706,-0.461941,83,0,"E","Europe/London","airport","OurAirports"*.


## Thank you!

