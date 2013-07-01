/*
 * File: Boggle.cpp
 * ----------------
 * Name: Payton Broaddus
 * Section: Rahul Pandey
 * This file is the main starter file for Assignment #4, Boggle. For some reason my computer recursive functio takes forever. I can't figure out why.
 */
 
#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include <cmath>
#include <algorithm> // CS 106L!!!
#include "random.h"
#include "filelib.h"
#include "point.h"
#include "strlib.h"

using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;
const int NUM_OF_CUBES = 25;
const string FILE_NAME = "txt.txt";

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

//Displays path for a player.
void displayPath(Vector<Point> path){
    for(int x = 0 ; x < sqrt(NUM_OF_CUBES); x++){
        for(int y = 0 ; y < sqrt(NUM_OF_CUBES); y++){
            highlightCube(x, y, false);
        }
    }
    for(int i = 0; i < path.size() ; i++){
        highlightCube(path.get(i).getX(), path.get(i).getY(), true);
    }
}

//Checks to see if the point is contained in the vector. This assures that the user isn't using a tail twice.
bool containsPoint(Point p1, Vector<Point> points){
    for(int i = 0; i < points.size() ; i++){
        if(points.get(i) == p1){
            return true;
        }
    }
    return false;
}

//Finds out if a Recursive Path exists for the player.
bool recursivePath(string str, string & compare, Vector<Point> & path, Grid<char> board){
    if(str[str.size() - 1] != compare[str.size() - 1]) return false;
    //Returns True if the string and path we put in results in the compare string we want.
    if (str == compare)   return true;
    if(str.size() == compare.size())  return false;
    for(int xdel = -1; xdel < 2; xdel++){
        for(int ydel = -1; ydel < 2; ydel++){
            //Check if you are at center
            if(!(xdel == 0 && ydel == 0)){
                //New Point Coordinates
                int x = path.get(path.size() - 1).getX() + xdel; int y = path.get(path.size() - 1).getY() + ydel;
                Point p1 = Point(x,y);
                if(board.inBounds(x, y) && !containsPoint(p1,path)){
                    Vector<Point> newpath = path;
                    newpath.add(p1);
                    if(recursivePath(str + board.get(x,y),compare, newpath, board)){
                        path = newpath;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

//Checks if the Users guess is correct
bool canBeFormed(string str,Grid<char> & grid){
    for(int x = 0; x < sqrt(NUM_OF_CUBES); x ++){
        for (int y = 0; y < sqrt(NUM_OF_CUBES); y++){
            Vector<Point> path;
            Point startpoint = Point(x,y);
            path.add(startpoint);
            string temp = "";
            temp += grid.get(x,y);
            if(recursivePath(temp, str, path, grid)){
                displayPath(path);
                return true;
            }
        }
    }
    return false;
}

//Computer Recursive Part. Super slow. Don't know why.
bool recursivePathComputers(Player & c, Point & p1, string str, Set<string> & contains, Vector<Point> & path, Grid<char> & grid,Lexicon & lex){
    if(!lex.containsPrefix(str)) return false;
    if(str.size() >= 4 && !contains.contains(str) && lex.contains(str)){
        contains.add(str);
        recordWordForPlayer(str, c);
    }
    //Iterates over all the points around it
    for(int xdel = -1; xdel < 2; xdel++){
        for (int ydel = -1 ; ydel < 2; ydel++){
            if(!(xdel == 0 && ydel == 0)){
                Point newPoint = Point(p1.getX() + xdel,p1.getY() + ydel);
                if(grid.inBounds(newPoint.getX(), newPoint.getY()) && !containsPoint(newPoint,path)){
                    Vector<Point> newPath = path; newPath.add(newPoint);
                    recursivePathComputers(c,newPoint, str + grid.get(newPoint.getX(),newPoint.getY()), contains, newPath, grid, lex);
                }
                
            }
        }
    }
    return true;
}

//Computer Recursive Part. Super slow. Still can't figure out why.
void newrecursivePathComputers(Player & c, int x, int y, string str, Set<string> & contains, Grid<bool> path, Grid<char> & grid,Lexicon & lex){
    
    if(!lex.containsPrefix(str)) return ;
    if(str.size() >= 4 && !contains.contains(str) && lex.contains(str)){
        contains.add(str);
        recordWordForPlayer(str, c);
    }
    //Iterates over all the points around it. 
    for(int xdel = -1; xdel < 2; xdel++){
        for (int ydel = -1 ; ydel < 2; ydel++){
            if(!(xdel == 0 && ydel == 0)){ //At center point
                int newx = x + xdel; int newy = y + ydel; //new position
                if(grid.inBounds(newx, newy) && !path[newx][newy]){
                    path[newx][newy] =  true;
                    newrecursivePathComputers(c,newx,newy, str + grid[newx][newy], contains, path, grid, lex);
                    path[newx][newy] =  false;
                }
            }
        }
    }
}



void playComputerTurn(int & score, Player c, Lexicon & lex,Grid<char> & grid){
    Set<string> contains;
    Grid<bool> path; path.resize(sqrt(NUM_OF_CUBES), sqrt(NUM_OF_CUBES));
    for(int i =0; i < sqrt(NUM_OF_CUBES);i++){
        for(int j = 0; j < sqrt(NUM_OF_CUBES); j++){
            path.set(i,j,false);
        }
    }
    for(int x = 0; x < grid.numCols(); x++){
        for(int y = 0; y < grid.numRows(); y++){
            string str = ""; str += grid.get(x,y);
            cout << x << " : " << y << str << endl;
            //Vector<Point> path; Point startpoint = Point(x,y); path.add(startpoint);
            //recursivePathComputers(c,startpoint, str, contains, path, grid,lex)
            Grid<bool> newpath = path;
            newrecursivePathComputers(c, x, y, str, contains, path, grid, lex);
        }
    }
    foreach(string str in contains){
        cout << str << endl;
    }
}
//Plays the Human Turn. 
void playHumanTurn(int & score, Player h, Lexicon & lex,Grid<char> & grid){
    //Set of guesses the person has already made.
    Set<string> guesses;
    //Lets user guess words till they input "".
    while(true){
        string str = toUpperCase(getLine("Input: "));
        if(str == "") break;
        
        if(!lex.contains(str)){
            cout << "NOT IN DICTIONARY" << endl;
        }
        //Checks if the word is longer than 4 characters, is contained in the lex and isn't contained in the users guesses, as well as makes sure that the word can be formed.
        else if(str.size() >= 4  && lex.contains(str) && !guesses.contains(str) && canBeFormed(str,grid)){
            guesses.add(str);
            score += str.size();
            recordWordForPlayer(str, h);
            cout << "CORRECT" << endl;
        }
        else{
            cout << "INVALID INPUT" << endl;
        }
    }
}

//Plays the Game.
void playGame(Lexicon & lex,Grid<char> & grid){
    Player human = HUMAN; int humanScore = 0;
    Player computer = COMPUTER; int computerScore = 0;
    playHumanTurn(humanScore, human,lex,grid);
    playComputerTurn(computerScore,computer,lex,grid);
    
}



//Draws the board with the letters on it. Cubes are randomized and the side of cube is randomized;
void drawBoardWithLetters(Grid<char> & grid){
    //Construct vector of Dice
    Vector<string> dice;
    for(int i = 0; i < NUM_OF_CUBES; i++){
        string input;
        if(NUM_OF_CUBES == 16) input = STANDARD_CUBES[i];
        else if(NUM_OF_CUBES == 25)  input = BIG_BOGGLE_CUBES[i];
        dice.push_back(input);
    }
    
    //CS 106L. RANDOMIZES dice
    //random_shuffle(dice.begin(), dice.end());
    
    //Randomize Dice the hard way.
    for(int i =0; i < dice.size(); i++){
        int rand = randomInteger(i, dice.size()-1);
        string temp = dice[i];
        dice[i] = dice[rand];
        dice[rand] = temp;
    }

    
    //Construct Board by randomizing side of dice that is facing up and placeing letter into grid.
    for(int i = 0; i < sqrt(NUM_OF_CUBES); ++i){
        for(int j = 0; j < sqrt(NUM_OF_CUBES); j++){
            int num = randomInteger(0, 5); 
            string str = dice.get(i); char ch = str[num];
            labelCube(i,j , ch);
            grid.set(i, j, ch);
        }
    }
}

//Constructs a Lexicon by reading a text file containing all english words.
void constructLex(Lexicon & lex){
    ifstream input;
    openFileDialog(input);
    //openFile(input,FILE_NAME);
    string str;
    while(input >> str){
        lex.add(str);
    }
}


/* Function prototypes */

void welcome();
void giveInstructions();



/* Main program */

int main() {
    Lexicon lex;
    Grid<char> board; board.resize(sqrt(NUM_OF_CUBES), sqrt(NUM_OF_CUBES));
    constructLex(lex);
    while(true){
        GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
        initGBoggle(gw);
        welcome();
        giveInstructions();
        drawBoard(sqrt(NUM_OF_CUBES),sqrt(NUM_OF_CUBES));
        drawBoardWithLetters(board);
        playGame(lex,board);
    }
    return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

// [TODO: Fill in the rest of the code]
