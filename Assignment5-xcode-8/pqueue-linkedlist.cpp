/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"
#include <iostream>
#include "strlib.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	start = NULL;
    logicalLength = 0;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
    //Credit to OurQueue
    while(start != NULL){
        Cell* next = start->next;
        delete start;
        start = next;
    }
    logicalLength = 0;
}

int LinkedListPriorityQueue::size() {
	return logicalLength;
}

bool LinkedListPriorityQueue::isEmpty() {	
	return size() == 0;
}

void LinkedListPriorityQueue::enqueue(string value) {
    //Start
    if (isEmpty()) {
        start = new Cell; start->str = value; start->next = NULL;
        logicalLength++; return;
    }
    
    //Only 1 in Queue
    if(size() == 1){
        if(start->str > value){
            string temp = start->str;
            start->str = value;
            Cell* nextVal = new Cell; nextVal->next = NULL; nextVal->str = temp;
            start->next = nextVal;
        }
        else{
            Cell* nextVal = new Cell; nextVal->next = NULL; nextVal->str = value;
            start->next = nextVal;
        }
        logicalLength++;
        return;
    }
    //Checks Start
    if(start->str > value){
        Cell* newStart = new Cell; newStart->str = value; newStart->next = start;
        start = newStart; logicalLength++;
    }
    //Checks Rest of Que
    else{
        Cell* first = start;
        Cell* second = start->next;
        while(second != NULL){
            if (second->str > value){
                Cell* newCell = new Cell; newCell->str = value; newCell->next = second;
                first->next = newCell; logicalLength++; return;
            }
            //Checks End Case
            else if(second->next == NULL) {
                Cell* lastCell = new Cell; lastCell->str = value; lastCell->next = NULL;
                second->next = lastCell; logicalLength++; return;
            }
            first = second;
            second = second->next;
        }
    }
}

string LinkedListPriorityQueue::peek() {
    if(isEmpty()){
        error("Out of Bounds");
    }
	return start->str;
}

string LinkedListPriorityQueue::dequeueMin() {
    string front = peek();
    Cell* newStart = start->next;
    delete start;
    start = newStart;
    logicalLength--;
	return front;
}

