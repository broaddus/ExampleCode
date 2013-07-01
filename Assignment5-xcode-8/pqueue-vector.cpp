/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"
#include "strlib.h"

VectorPriorityQueue::VectorPriorityQueue() {
}

VectorPriorityQueue::~VectorPriorityQueue() {
	array.clear();
}

int VectorPriorityQueue::size() {
	return array.size();
}

bool VectorPriorityQueue::isEmpty() {
    return size() == 0;
}

void VectorPriorityQueue::enqueue(string value) {
    if(value == "") return; //No
	//Find Place in array
    for(int i = 0; i < size(); i++){
        //Checks if front letters
        if(toLowerCase(array[i]) >= toLowerCase(value)){
            array.insert(i, value); return;
        }
    }
    array.push_back(value);
}

string VectorPriorityQueue::peek() {
	if(isEmpty()){
        error("Error out of bounds");
    }
	return array[0];
}

string VectorPriorityQueue::dequeueMin() {
	string min = peek();
    array.remove(0);
	return min;
}

