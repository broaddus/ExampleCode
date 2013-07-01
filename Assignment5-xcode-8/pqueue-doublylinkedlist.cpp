/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"
#include <iostream>

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	start = NULL; logicalLength = 0;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	while(start != NULL){
        Cell* temp; temp = start->next;
        Cell i = *start;
        i.next;
        delete start;
        start = temp;
    }
    logicalLength = 0;
}

int DoublyLinkedListPriorityQueue::size() {	
	return logicalLength;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
    return logicalLength == 0;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
    
    //Checks if first Cell in Queue
    if (isEmpty()){
        //cout << "start" << endl;
        start = new Cell; start->prev = NULL; start->next= NULL; start->str = value;
        logicalLength++; return;
    }
    
    //Checks Start Corner Case. NOTE: MIGHT NOT NEED.
    else if(start->str > value){
        //cout << "start" << endl;
        Cell* newStart = new Cell; newStart->str = value; newStart->next = start; newStart->prev = NULL; start->prev = newStart; 
        start = newStart;
        logicalLength++; return;
    }
    
    //Checks rest of it. Guaranteed not to be in Front.
    else{
        Cell* check = start;
        while(true){
            //Sees if Value is less than the Cell it is currently Checking
            if(check->str > value){
                Cell* nextCell = new Cell;
                nextCell->str = value; nextCell->next = check; nextCell->prev = check->prev;
                Cell* previousCell = check->prev;
                previousCell->next = nextCell; check->prev = nextCell;
                logicalLength++; return;
            }
            //At end of Priority Queue
            if(check->next == NULL){
                Cell* endCell = new Cell; endCell->str = value; endCell->next = NULL; endCell->prev = check;
                check->next = endCell; logicalLength++; return;
            }
            check = check->next;
        }
    }
    
}

//Works
string DoublyLinkedListPriorityQueue::peek() {
    if(isEmpty()){
        error("Out of Bounds"); 
    }
	return start->str;
}

//Works
string DoublyLinkedListPriorityQueue::dequeueMin() {
	string temp = peek();
    Cell* newStart = start->next;
    delete start;
    start = newStart;
    logicalLength--;
	return temp;
}

