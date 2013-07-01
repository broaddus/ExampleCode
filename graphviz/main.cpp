/******************************************************
 * File: main.cpp
 * Author: Payton Broaddus
 *
 * This 
 */

#include <iostream>
#include "GraphVisualizer.h"
#include <fstream>
#include <cmath>
#include <ctime>
#include <sstream>
#include <string>

using namespace std;

int numOfNodes;
double runtime;
const static double kRepel = 0.001;
const static double kAttract = 0.005;

SimpleGraph graph;
const double kPi = 3.14159265358979323;


void Welcome() {
	cout << "Welcome to CS106L GraphViz!" << endl;
	cout << "This program uses a force-directed graph layout algorithm" << endl;
	cout << "to render sleek, snazzy pictures of various graphs." << endl;
	cout << endl;
}

//Moves the Nodes 
void applyForce(){
    //Vectors that hold how far delta is supposed to the node with the same index number
    vector<double> deltaX;
    vector<double> deltaY;
    
    //Puts Zero as initial Value for all;
    for(int i = 0; i < numOfNodes; i++){
        deltaX.push_back(0);
        deltaY.push_back(0);
    }
    
    //Repulsive Force
    for(int i = 0; i < numOfNodes - 1; i++){
        Node n0 = graph.nodes.at(i);
        for(int j = i + 1; j < numOfNodes; j++){
            
            Node n1 = graph.nodes.at(j);
        
            double fRepel = kRepel/(1.0*(sqrt((n1.y - n0.y)*(n1.y - n0.y) + (n1.x - n0.x)*(n1.x - n0.x))));
            //cout << "fRepel: " << fRepel << endl;
            double theta = atan2(n1.y - n0.y, n1.x - n0.x);
            //cout << "theta: " << theta << endl;
            
            deltaX.at(i) -= fRepel * cos(theta);
            deltaY.at(i) -= fRepel * sin(theta);
            
            deltaX.at(j) += fRepel * cos(theta);
            deltaY.at(j) += fRepel * sin(theta);
        }
    }
    //Attractive Force
    for(int i = 0; i < graph.edges.size(); i++){
        Node n0 = graph.nodes.at((int) graph.edges.at(i).start);
        Node n1 = graph.nodes.at((int) graph.edges.at(i).end);
        double fAttract = kAttract * ((n1.x-n0.x)*(n1.x-n0.x) + (n1.y-n0.y)*(n1.y-n0.y));
        double theta = atan2(n1.y - n0.y, n1.x - n0.x);
        
        deltaX.at((int) graph.edges.at(i).start) += fAttract * cos(theta);
        deltaY.at((int) graph.edges.at(i).start) += fAttract * sin(theta);
        
        deltaX.at((int) graph.edges.at(i).end) -= fAttract * cos(theta);
        deltaY.at((int) graph.edges.at(i).end) -= fAttract * sin(theta);
        

    }
 
    for(int i = 0; i < numOfNodes; i++){

        graph.nodes.at(i).x += deltaX.at(i);

        graph.nodes.at(i).y += deltaY.at(i);
       // cout << "Delta Y: " << deltaX.at(i) << endl;
       // cout << "New Y: " << graph.nodes.at(i).x << endl;1
    }
        
    //Clear Delta and replace each with zero.
    for(int i = 0; i < numOfNodes; i++){
        deltaX.at(i) = 0;
        deltaY.at(i) = 0;
    }
    
    
    
}


void cleanGraph(){
    cout << "cleanGraph" << endl;
        time_t startTime = time(NULL);
    InitGraphVisualizer();
    DrawGraph(graph);
    while(true){
        applyForce();
        DrawGraph(graph);
        
        double elapsedTime = difftime(time(NULL), startTime);
        if(elapsedTime >= runtime){
            
            break;
        }
    }
    
}
////getLine is from the Stanford Library. All credit goes to Stanford. Simpio.h.
string getLine(string prompt) {
    string line;
    cout << prompt;
    getline(cin, line);
    return line;
}


//getInteger is from the Stanford Library. All credit goes to Stanford. Simpio.h.
int getInteger(string prompt) {
    int value;
    string line = "";
    while (true) {
        cout << prompt;
        getline(cin, line);
        istringstream stream(line);
        stream >> value >> ws;
        if (!stream.fail() && stream.eof()) break;
        cout << "Illegal integer format. Try again." << endl;
        if (prompt == "") prompt = "Enter an integer: ";
    }
    return value;
}

//Sets up the nodes and edges vectors and puts them in the simplegraph. WORKS!!! NOW IT WORKS!!!
void setUp(vector<int>& nums){
    
    vector<Node> tempnodes;
    vector<Edge> tempedges;
    
    //Creates the Nodes
    for(int i = 0; i < numOfNodes; i++){
        Node tempnode;
        tempnode.x = cos(2.0 * kPi * (1.0 *i)/(1.0*numOfNodes));
        tempnode.y = sin(2.0 * kPi * (1.0 *i)/(1.0*numOfNodes));
        tempnodes.push_back(tempnode);
    }
    
    graph.nodes = tempnodes;
    
    //Creates the Edges
    
    for(int i = 1; i < nums.size(); i += 2){
        Edge tempedge;
        tempedge.start = (size_t) nums[i];
        tempedge.end = (size_t) nums[i+1];
        tempedges.push_back(tempedge);
    }
    
    graph.edges = tempedges;
    
}

void run(){
    string file;
    ifstream input;
    
        
    while(true){
        file = getLine("Input file name: ");
        input.open(file.c_str());
        if(input.is_open()){
            break;
        }
        else{
            cout << "that doesn't work" << endl;
        }
    }
    
    runtime = getInteger("Input run time: ");


    
    int temp;
    vector<int> numbers;
    while(input >> temp){
        if(cin.fail()){
            break;
        }
        numbers.push_back(temp);
    }
    
    
    numOfNodes = numbers.at(0);
    
    setUp(numbers);
    cleanGraph();

}




int main() {
	Welcome();
    while (true){
        run();
    }
   	return 0;
}
