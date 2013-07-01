/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: Payton Broaddus
 * Section: Rahul Pandey
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
#include "random.h"

using namespace std;

const int totalHospitals = 2;
const int totalNumOfHospitalsGenerated = 10;
const char STARTINGCHAR = 'a';
const char ENDINGCHAR = 'd';
const double chanceOfHavingCity = 0.1;

//Function finds the vector of hospitals the cover the most cities. 
void findMaxCity(Set<string> & locations,Vector<Set<string> > & cities,Vector<Set<string> > & hospitalsChosen,int index, int numHospital,Set<string> & citiesSeen){
    if(numHospital == 0 || index < 0) return;
    else {
        int newNumOfHospitalChoicesLeft = numHospital - 1;
        
        //Don't add to list with current hospital.
        Vector<Set<string> > cityWithoutHospital = hospitalsChosen;
        Set<string> citiesSeenWithoutHospital = citiesSeen;
        findMaxCity(locations,cities, cityWithoutHospital, index - 1, numHospital, citiesSeenWithoutHospital);
        
        
        
        //Add to list with the current hospital.
        Vector<Set<string> > cityWithHospital = hospitalsChosen;
        Set<string> citiesWithNewHospital = cities.get(index);
        cityWithHospital.add(citiesWithNewHospital);
        Set<string> citiesSeenWithNewHospital = citiesSeen;
        
        //Check go through citieswithNewHospital and add any cities not seen in the cities.
        foreach(string str in citiesWithNewHospital){
            if(!citiesSeen.contains(str)){
                citiesSeenWithNewHospital.add(str);
            }
        }
        findMaxCity(locations,cities, cityWithHospital, index - 1, newNumOfHospitalChoicesLeft, citiesSeenWithNewHospital);
        

        
        //Base Case
        //Result gets the hospital list with more cities in it.
        if(citiesSeenWithNewHospital.size() <= citiesSeenWithoutHospital.size()){
            hospitalsChosen = cityWithoutHospital;
            citiesSeen = citiesSeenWithoutHospital;
        }
        else{
            hospitalsChosen = cityWithHospital;
            citiesSeen = citiesSeenWithNewHospital;
        }
        
        
        
    }
}




/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */


bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result){

    int index = locations.size() - 1;
    Set<string> citiesSeen;
    findMaxCity(cities,locations,result,index,numHospitals,citiesSeen);
    if(cities.size() == citiesSeen.size()){
        cout << "All cities could be covered" << endl;
    }
    else {
        cout << "Not all cities could be covered" << endl; cout << "Max Number of cities that could be covered: " << citiesSeen.size() << endl;
        for (int i = 0; i < result.size(); i++){
            Set<string> temp = result.get(i);
            cout << "Cities hospital covers: " ;
            foreach(string str in temp){
                cout << str + " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    
    if(citiesSeen.size() == cities.size()){
        return true;
    }
    else{
        return false;
    }
}

//Fills a set  with cities.
void setUpCities(Set<string> & cities){
    for(char a = STARTINGCHAR; a < ENDINGCHAR + 1 ; a++){
        string str; str += a;
        cities.add(str);
    }
}

//Fills a vector of hospitals with sets of random cities
void setUpHospitals(Set<string> cities , Vector<Set<string> > & hospitals){
    for(int i = 0; i < totalNumOfHospitalsGenerated; i++){
        Set<string> temp;
        for(char a = STARTINGCHAR ; a < ENDINGCHAR + 1; a++){
            if(randomChance(chanceOfHavingCity)){
                string str = ""; str += a;
                temp.add(str);
            }
        }
        hospitals.add(temp);
    }
}


int main() {
    
    Set<string> cities;
    setUpCities(cities);
    cout << "Total number of cities: " << cities.size() << endl;
    
    //Create vector of random hospitals
    Vector<Set<string> > locations;
    setUpHospitals(cities,locations);

    
    //Bulk of Work
    Vector<Set<string> > result;
    canOfferUniversalCoverage(cities,locations,totalHospitals,result);
    

    
    return 0;
}
