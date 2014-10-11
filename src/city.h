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
    
    void setVars(float _x, float _y, float _pop, unsigned long _cnum );
    unsigned long getCountryNum() { return cnum; }
    
    void setPerCapitaCarbonEmission(float _perCapitaCarbon);
    void drawPopulation(ofxVectorGraphics &output, float minPop);
    void drawCarbonFootprint(ofxVectorGraphics &output, float minPop);
    
    
    
private:
    float x;
    float y;
    float pop;
    float perCapitaCarbon;
    float carbonFootprint;      // gets caluclated after setPerCapitaCarbonEmission()
    unsigned long cnum;
    bool bHasCarbonData;              // true if we have a matching carbon footprint
    
    int numSquares;
    
    vSquare *vSquares;
};


#endif /* defined(__vectorGraphicsExample__city__) */
