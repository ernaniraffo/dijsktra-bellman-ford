# Dijkstra-and-Bellman-Ford
Solves Single Source Shortest Paths problem using Dijkstra's and Bellman-Ford's algorithms. When a negative edge weight is detected by the ```FindPath``` program, it will use the Bellman-Ford algorithm instead of Dijkstra's.

## Building
* ```make``` or ```make FindPath``` - builds ```FindPath``` executable.
* ```make GraphTest``` - builds ```GraphTest``` executable.
* ```make PriorityQueueTest``` - builds ```PriorityQueueTest``` executable.
* ```make ListTest``` - builds ```ListTest``` executable.

## Running
To run ```FindPath```, provide an input file and output file in the command line:
```$ ./FindPath infile outfile```

## To do:
- [x] Finish Graph ADT
- [x] Test ADTs
- [x] Makefile
- [x] Write main program
- [ ] Test more complicated graphs
