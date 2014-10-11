//
//  city.cpp
//  vectorGraphicsExample
//
//  Created by Scott Kildall on 6/16/14.
//
//

#include "city.h"
#include "ofMath.h"

city::city() {
    vSquares = NULL;
    pop = 0;
    perCapitaCarbon = 0;
    carbonFootprint = 0;
    
    bHasCarbonData = false;
}
        
city::~city() {
    if( vSquares )
        delete [] vSquares;
}

void city::setVars(float _x, float _y, float _pop, unsigned long _cnum) {
    // init squares
    numSquares = pop/1000 + 1;
    numSquares = (int)ofRandom(1, 20);
    /*
    if( numSquares < 10 )
        numSquares = 1;
    else  if( numSquares < 15 )
        numSquares = 3;
    else
        numSquares = numSquares/2;
    */
    
  //
    x = _x;
    y = _y;
    cnum = _cnum;
    pop = _pop;
    //cout << "cnum = " << cnum;
    
    numSquares = 1;
    vSquares = new vSquare[numSquares];
    for( int i = 0; i < numSquares; i++ )
        (vSquares +i)->setVars(x,y,pop/15000);
        //(vSquares +i)->setVars(x+(int)ofRandom(-5,5),y+(int)ofRandom(-5,5),pop/15000);
}

void city::drawPopulation(ofxVectorGraphics &output, float minPop) {
    if( pop < minPop )
        return;
    
    for( int i = 0; i < numSquares; i++ ) {
        (vSquares+i)->draw(output);
    }
}

void city::drawCarbonFootprint(ofxVectorGraphics &output, float minPop) {
    if( pop < minPop )
        return;
    
    output.fill();
    output.circle(x, y, (sqrt(carbonFootprint))/350 );
}

void city::setPerCapitaCarbonEmission(float _perCapitaCarbon) {
    
    perCapitaCarbon = _perCapitaCarbon;
    carbonFootprint = perCapitaCarbon * pop;
    bHasCarbonData = true;
}