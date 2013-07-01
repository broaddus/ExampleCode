/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: Payton Broaddus
 * Section: Rahul Pandey
 */

#include <iostream>
#include <string>
#include "simpio.h"
#include "console.h"
using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string. */

bool isSubsequence(string text, string subsequence){
    if(subsequence == "") return true; //least number of lines possible!!!!
    else if(text.size() == 0) return false;
    else if(text.at(0) == subsequence.at(0)) return isSubsequence(text.substr(1),subsequence.substr(1));
    else return isSubsequence(text.substr(1),subsequence);
}



int main() {
    while(true){
        string text = getLine("Enter Text: ");
        string subsequence = getLine("Enter subsequence: ");
        if(isSubsequence(text,subsequence)){
            cout << "Works" << endl;
        }
        else{
            cout << "Fails" << endl;
        }
                              
    }
    return 0;
}
