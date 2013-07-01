/*
 * File: InverseGenetics.cpp
 * --------------------------
 * Name: Payton Broaddus
 * Section: Rahul Pandey
 * This file is the starter project for the Inverse Genetics problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
#include "console.h"
#include "stack.h"
#include "simpio.h"
using namespace std;

//Updates a output vector to contain all RNA strands of the given protien. Uses recursion.
void getAllRNAStrandsFor(string protein,Stack<string> strandparts, Vector<string> & output, Map<char, Set<string> >& codons){
    if(protein == ""){
        string rnaStrand;
        while(!strandparts.isEmpty()){
            string temp = strandparts.pop();
            rnaStrand += temp;
        }
        output.add(rnaStrand);
    }
    else{
        Set<string> next = codons.get(protein[protein.size()-1]);
        string newprotein = protein.substr(0,protein.size()-1);
        foreach(string str in next){
            strandparts.push(str);
            getAllRNAStrandsFor(newprotein, strandparts, output,codons);
            strandparts.pop();
        }
    }
}



/* Function: listAllRNAStrandsFor(string protein,
 *                                Map<char, Set<string> >& codons);
 * Usage: listAllRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, lists all possible RNA strands that could generate
 * that protein
 */
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons){
    Vector<string> outputs;
    Stack<string> strand;
    getAllRNAStrandsFor(protein,strand,outputs,codons);
    for(int i = 0; i < outputs.size() ; i++){
        cout << outputs.get(i) << endl;
    }
    
}





/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
Map<char, Set<string> > loadCodonMap();

int main() {
    /* Load the codon map. */
    Map<char, Set<string> > codons = loadCodonMap();
    while (true){
        string str;
        str = getLine("Input: ");
        //Display the RNA strands for input protein
        listAllRNAStrandsFor(str, codons);
    }
    
    return 0;
}





/* You do not need to change this function. */
Map<char, Set<string> > loadCodonMap() {
    ifstream input("codons.txt");
    Map<char, Set<string> > result;
    
    /* The current codon / protein combination. */
    string codon;
    char protein;
    
    /* Continuously pull data from the file until all data has been
     * read.
     */
    while (input >> codon >> protein) {
        result[protein] += codon;
    }
    
    return result;
}
