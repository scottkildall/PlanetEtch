//
//  vSquare.cpp
//  vectorGraphicsExample
//
//  Created by Scott Kildall on 6/16/14.
//
//

#include "vSquare.h"

vSquare::vSquare() {
    x = 0;
    y = 0;
    s = 1;
}

void vSquare::setVars(float _x, float _y, float _s) {
    x = _x;
    y = _y;
    s = sqrt(_s);
}

void vSquare::draw(ofxVectorGraphics &output) {
    if( s == 0 )
        return;
    
    //output.noFill();
    output.fill();
    
    output.rect(x, y, s, s);
    
       // output.rect(x+1, y+1, s, s);
       // output.rect(x-1, y-1, s, s);
        
        //output.circle(x, y, s/2 + 2);
}


