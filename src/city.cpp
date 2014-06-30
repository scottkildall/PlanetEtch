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
}
        
city::~city() {
    if( vSquares )
        delete [] vSquares;
}

void city::setVars(float _x, float _y, float pop, int _cnum) {
    // init squares
    numSquares = pop/1000 + 1;  //(int)ofRandom(1, 20);
    /*if( numSquares < 10 )
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
    
    cout << "cnum = " << cnum;
    
    numSquares = 1;
    vSquares = new vSquare[numSquares];
    
    
    float dx = x;
   float dy = y;
    float randMin = 1;
    float randMax = 5;
    
    for( int i = 0; i < numSquares; i++ ) {
        float s = pop/1000.0;//ofRandom(pop/1000,randMax);
        dx += ofRandom(-s/2,s/2);
        dy += ofRandom(-s/2,s/2);
        (vSquares+i)->setVars(dx,dy,s);
    }

}

void city::draw(ofxVectorGraphics &output) {
    for( int i = 0; i < numSquares; i++ ) {
        (vSquares+i)->draw(output);
    }

}