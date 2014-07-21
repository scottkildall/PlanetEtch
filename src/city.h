//
//  city.h
//  vectorGraphicsExample
//
//  Created by Scott Kildall on 6/16/14.
//
//

#ifndef __vectorGraphicsExample__city__
#define __vectorGraphicsExample__city__

#include <iostream>

#include <string.h>
#include "vSquare.h"
#include "ofxVectorGraphics.h"

class city {
    
public:
    
    city();
    ~city();
    
    void setVars(float _x, float _y, float _pop, unsigned long );
    void draw(ofxVectorGraphics &output);
    
    float x;
    float y;
    float pop;
    unsigned long cnum;
    
private:
    char country[256];
    int numSquares;
    vSquare *vSquares;
};


#endif /* defined(__vectorGraphicsExample__city__) */
