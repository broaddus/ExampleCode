/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */


#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include "pqueue.h"
#include "random.h"
using namespace std;
const int MAX_KEY = 100;

/* Function: shortestPath
 *
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */
Vector<Loc>
shortestPath(Loc start, Loc end,
             Grid<double>& world,
             double costFn(Loc one, Loc two, Grid<double>& world),
             double heuristic(Loc start, Loc end, Grid<double>& world)){
    //Create TrailGrid
    TrailNode temp;
    temp.state = GRAY;
    Loc tempPos;
    Grid<TrailNode> tg; //TrailGrid
    tg.resize(world.numRows(), world.numCols());
    for(int i = 0; i < world.numRows(); i++){
        for(int j = 0; j < world.numCols(); j++){
            tempPos.row = i;
            tempPos.col = j;
            temp.position = tempPos;
            tg[i][j] = temp;
        }
    }
    //Create First TrailNode
    TrailNode begin;
    begin.state = YELLOW;
    begin.minDistance = 0;
    begin.position = start;
    tg[start.row][start.col] = begin;
    
    //Create Priority Queue
    PriorityQueue<TrailNode> pq;
    pq.enqueue(begin, begin.minDistance);
    
    //Dijkstra's Algorithm
    TrailNode curr;
    while(true){
        if(pq.size() == 0){
            error("No Path Possible");
        }
        curr = pq.dequeue();
        curr.state = GREEN;
        colorCell(world, curr.position, curr.state);
        if(curr.position == end) {
            break;
        }
        int y = curr.position.col; int x = curr.position.row;
        //Iterate over Nodes around current position whilst ignoring current node.
        for(int xdel = -1; xdel < 2; xdel++){
            for(int ydel = -1; ydel < 2; ydel++){
                int newy = y + ydel; int newx = x + xdel;
                //Check that new Node is inside Grid and that it isn't on the current Node
                if(tg.inBounds(newx, newy) && !(xdel == 0 && ydel == 0)){
                    TrailNode temp = tg[newx][newy];
                    //Node isn't in priority queue
                    if(temp.state == GRAY){
                        colorCell(world, temp.position, YELLOW);
                        temp.state = YELLOW;
                        temp.prev = curr.position;
                        temp.minDistance = curr.minDistance + costFn(curr.position,temp.position,world);
                        pq.enqueue(temp, temp.minDistance + heuristic(temp.position,end,world));
                        
                    }
                    //Node is already in the priority queue.
                    else if(temp.state == YELLOW && temp.minDistance >= curr.minDistance + costFn(curr.position,temp.position,world)){
                        temp.minDistance = curr.minDistance + costFn(curr.position,temp.position,world);
                        temp.prev = curr.position;
                        pq.enqueue(temp, temp.minDistance + heuristic(temp.position,end,world));
                    }
                    tg[newx][newy] = temp;
                }
            }
        }
    }
    Vector<Loc> path;
    Stack<Loc> reversePath;
    Loc node = end;
    while(true){
        colorCell(world, node, GREEN);
        if(node.col == start.col && node.row == start.row) {
            reversePath.push(start);
            break;
        }
        else{
            reversePath.push(tg.get(node.row, node.col).position);
            node = tg.get(node.row, node.col).prev;
        }
    }
    while(!reversePath.isEmpty()){
        path.add(reversePath.pop());
    }
    
    return path;
}

struct Cluster {
    int key; //Unique ID value for Cluster
    Set<Loc> * nodes;
    Set<Edge> * edges;
};

//This will break with size 1. But no graphs of size 1 anyway.
void constructGraph(int numRows,int numCols, Map<Loc, Cluster> & graph, PriorityQueue<Edge> & pq){
    //Set up Grid
    Loc connected;
    Edge edge;
    for(int row = 0; row < numRows;row++){
        for(int col = 0; col < numCols;col++){
            Loc curr;
            Cluster clus;
            curr.col = col; curr.row = row;
            clus.key = row * numRows + col;
            Set<Loc> * loc = new Set<Loc>();
            Set<Edge> * edges = new Set<Edge>();
            loc->add(curr);
            clus.nodes = loc; //Dynamic Allocation. Delete later during merge.
            clus.edges = edges; //Dynamic Allocation. Delete later during merge.
            graph.put(curr, clus);
            
            //Set up the Priority Queue with Locs
            if(row < numRows - 1){
                connected.col = col; connected.row = row + 1;
                edge.start = curr;
                edge.end = connected;
                pq.enqueue(edge, randomInteger(0, MAX_KEY));
            }
            if(col < numCols - 1){
                connected.col = col + 1; connected.row = row;
                edge.start = curr;
                edge.end = connected;
                pq.enqueue(edge, randomInteger(0, MAX_KEY));

            }
        }
    }
}

Set<Edge> createMaze(int numRows, int numCols) {
    Map<Loc,Cluster> graph;
    PriorityQueue<Edge> pq;
    constructGraph(numRows,numCols,graph,pq);
    cout << numRows*numCols << endl;
    foreach(Loc l in graph){
        Cluster c = graph[l];
        cout << c.edges->size() << " : ";
    }
    cout << endl;
    while(pq.size() != 0){
        Edge e1 = pq.dequeue();
        Cluster c1 = graph.get(e1.start);
        Cluster c2 = graph.get(e1.end);
        //Aren't in same cluster.
        if (c1.key != c2.key) {
            //Merge
            Cluster merge;
            Set<Loc> locs = *c1.nodes + *c2.nodes;
            Set<Edge> edges = *c1.edges + *c2.edges;
            Set<Loc> * locPointer = new Set<Loc>();
            locPointer->operator=(locs);
            Set<Edge> * edgePointer = new Set<Edge>();
            edgePointer->operator=(edges);
            edgePointer->add(e1); //Adds edge connecting them
            merge.edges = edgePointer;
            merge.nodes = locPointer;
            merge.key = c1.key;
            foreach(Loc l in locs){
                //Memory Problems. Happy Summer.
                /*
                if(graph[l].nodes != NULL){
                    delete graph[l].nodes;
                }
                if(graph[l].edges != NULL){
                    delete graph[l].edges;
                }
                graph[l].edges = NULL;
                graph[l].nodes = NULL;
                 */
                graph[l] = merge;
            }
        }
    }
    foreach(Loc l in graph){
        return *graph[l].edges;
    }
    return Set<Edge>();
}
