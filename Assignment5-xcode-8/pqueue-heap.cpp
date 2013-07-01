/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 * My Code is so beautiful. I'm the Code God. 
 */
 
#include "pqueue-heap.h"
#include "error.h"
#include <iostream>

HeapPriorityQueue::HeapPriorityQueue() {
	logicalLength = 0;
    array = new string[Starting_Array_Length];
    allocatedLength = Starting_Array_Length;
    array[0] = "DUMMY"; //Ignore. This is for math purposes.
}

HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] array;
    logicalLength = 0;
}

int HeapPriorityQueue::size() {
	return logicalLength;
}

bool HeapPriorityQueue::isEmpty() {
	return size() == 0;
}

void HeapPriorityQueue::increaseSpace(int position){
    if(position == allocatedLength){
        allocatedLength *= 2;
        string* newArray = new string[allocatedLength];
        for(int i = 0; i < position; i++){
            newArray[i] = array[i];
        }
        array = newArray;
    }
}

void HeapPriorityQueue::enqueue(string value) {
    int position = 1 + size();
    increaseSpace(position); //Checks if array needs to increase.
    array[position] = value;
    while(true){
        int parent = position/2;
        if(parent == 0) break;
        else if(value < array[parent]){
            //Switch Values
            string temp = array[parent];
            array[parent] = value;
            array[position] = temp;
            position = parent;
        }
        else break;
    }
    logicalLength++;
}

string HeapPriorityQueue::peek() {
    if(isEmpty()){
        error("Out of Bounds");
    }
	return array[1];
}

/*void HeapPriorityQueue::sortArrayElem(int n1, int n2, int & maxNum,int & minNum){
    if(array[n1] > array[n2]){
        minNum = n2;
        maxNum = n1;
    }
    else {
        minNum = n1;
        maxNum = n2;
    }
}*/


string HeapPriorityQueue::dequeueMin() {
    string top = peek(); 
    int position = 1;
    array[position] = array[logicalLength];
    logicalLength--;
    
    while(true){
        int child1 = position * 2;
        int child2 = position * 2 + 1;
        //No Child Below
        if(child1 > logicalLength) { break; }
        //One Child Below
        else if(child2 > logicalLength){
            //Sees if it can Swap with Child node
            if(top > array[child2]){
                string temp = array[position];
                array[position] = array[child1];
                array[child1] = temp;
            }
            break;
        }
        //Two Children Below
        else{
            int maxPos = 0; int minPos = 0;
            sortArrayElem(child1,child2,maxPos,minPos);
            if(array[position] > array[minPos]){
                string temp = array[position];
                array[position] = array[minPos];
                array[minPos] = temp;
                position = minPos;
            }
            else if(array[position] > array[maxPos]){
                string temp = array[position];
                array[position] = array[maxPos];
                array[maxPos] = temp;
                position = maxPos;
            }
            else {
                break;
            }
        }
        
    }
	return top;
}


