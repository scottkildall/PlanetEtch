//
//  vSquare.h
//  vectorGraphicsExample
//
//  Created by Scott Kildall on 6/16/14.
//
//

#ifndef __vectorGraphicsExample__vSquare__
#define __vectorGraphicsExample__vSquare__

#include "ofxVectorGraphics.h"
#include <iostream>

class vSquare {
    
public:
    vSquare();
    void setVars(float _x, float _y, float _s);
    void draw(ofxVectorGraphics &output);
    
private:
    float x;
    float y;
    float s;
};


#endif /* defined(__vectorGraphicsExample__vSquare__) */
