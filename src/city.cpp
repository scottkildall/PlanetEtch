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
    
    carbonFootprint = 1000000;
    bHasCarbonData = false;
}
        
city::~city() {
    if( vSquares )
        delete [] vSquares;
}

void city::setVars(float _x, float _y, float _pop, unsigned long _cnum) {
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
    pop = _pop;
    //cout << "cnum = " << cnum;
    
    numSquares = 1;
    vSquares = new vSquare[numSquares];
    vSquares->setVars(x,y,pop/50000);
    
    
    /*
    
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
     */
     
     

}

void city::drawPopulation(ofxVectorGraphics &output) {
    //if( pop < 50000)
     //   return;
    
    for( int i = 0; i < numSquares; i++ ) {
        (vSquares+i)->draw(output);
    }
}

void city::drawCarbonFootprint(ofxVectorGraphics &output) {
    output.fill();
    output.circle(x, y, (sqrt(carbonFootprint))/750 );
}

void city::setPerCapitaCarbonEmission(float _perCapitaCarbon) {
    perCapitaCarbon = _perCapitaCarbon;
    carbonFootprint = perCapitaCarbon * pop;
    bHasCarbonData = true;
}