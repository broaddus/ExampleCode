/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: Payton Broaddus
 * Section: Rahul Pandey
 * 
 */

#include <iostream>
#include "gwindow.h"
#include "simpio.h"
#include "gmath.h"
#include <cmath> //Seen in 106L
using namespace std;

void drawSierpenski(double edgeLength, int srpnsk,GPoint upperLeft,GWindow & gw){
    if(srpnsk == 0){
        return;
    }
    else{
        //Draws the Main Traingle
        GPoint upperRight = gw.drawPolarLine(upperLeft, edgeLength/2, 0);
        GPoint bottomTip = gw.drawPolarLine(upperRight, edgeLength/2, -120);
        gw.drawPolarLine(bottomTip, edgeLength/2, 120);
        
        //Draws the surrounding Traingles recursively
        GPoint topTriangle = GPoint(upperLeft.getX()+edgeLength/8,upperLeft.getY()-sqrt(3)*edgeLength/8);
        drawSierpenski(edgeLength/2, srpnsk - 1, topTriangle, gw);
        GPoint bottomLeftTriangle = GPoint(upperLeft.getX()-edgeLength/8,upperLeft.getY()+sqrt(3)*edgeLength/8);
        drawSierpenski(edgeLength/2, srpnsk - 1, bottomLeftTriangle, gw);
        GPoint bottomRightTriangle = GPoint(upperLeft.getX()+3*edgeLength/8,upperLeft.getY()+sqrt(3)*edgeLength/8);
        drawSierpenski(edgeLength/2, srpnsk - 1, bottomRightTriangle, gw);
    }
    
  
}

int main() {
    //Get edgeLength and sierpinski number from the user
    double edgeLength = getReal("Enter Edge length: ");
    int sierpinski = getInteger("Enter Sierpinski number: ");
    
    //Make sure sierpinski >= 0
    if(sierpinski < 0){
        sierpinski = 0;
    }
    
    //Set up GWindow
    GWindow gw = GWindow(1000,1000);
    gw.setColor("BLACK");
    double height = gw.getHeight();
    double width = gw.getWidth();
    GPoint center = GPoint(width/2-edgeLength/2,height/2+sqrt(3)*edgeLength/4);
    //GPoint center = GPoint(width/2,height/2);
    
    
    //Draw Starting Traingle
    GPoint g1 = gw.drawPolarLine(center, edgeLength, 0);
    GPoint g2 = gw.drawPolarLine(g1, edgeLength, 120);
    gw.drawPolarLine(g2, edgeLength, -120);
    
    //Starting point
    GPoint startingPoint = GPoint(width/2-edgeLength/4,height/2);

    
    //Bulk of Drawing code
    drawSierpenski(edgeLength,sierpinski,startingPoint,gw);

    return 0;
}
