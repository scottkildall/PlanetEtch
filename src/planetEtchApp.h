#pragma once

#include "ofxVectorGraphics.h"
#include "ofMain.h"
#include "city.h"

#include "ofxCsv.h"
using namespace wng;

//#define CANVAS_RATIO (5.17)
#define CANVAS_RATIO (1)
#define CANVAS_WIDTH (1280)
#define CANVAS_HEIGHT (CANVAS_WIDTH/CANVAS_RATIO)
#define CANVAS_MARGIN (20)

#define DISPLAY_MODE_POPULATION         (1)
#define DISPLAY_MODE_CARBON_FOOTPRINT   (2)

class planetEtchApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
	/*
        void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		
*/
		ofxVectorGraphics output;
		bool capture;

		
    private:
        int displayMode;       // one the defined values
        float adjustX(float x);
        float adjustY(float y);
        float map(float x, float in_min, float in_max, float out_min, float out_max);
    
        float lngToX(float x);
        float latToY(float y);
    
        unsigned long getNumCities(ofxCsv csv, float popMin);
    
        unsigned long  hash(const char *str);
    
        void initCities();
        void initCarbonEmissions();
        void toggleDisplayMode();
    
        city *cities;
        long numCities;

        void filterCSV();

};


