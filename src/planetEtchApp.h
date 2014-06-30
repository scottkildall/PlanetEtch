#pragma once

#include "ofxVectorGraphics.h"
#include "ofMain.h"
#include "city.h"

#define CANVAS_RATIO (5.17)
#define CANVAS_WIDTH (1280)
#define CANVAS_HEIGHT (CANVAS_WIDTH/CANVAS_RATIO)
#define CANVAS_MARGIN (20)

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
    
        float adjustX(float x);
        float adjustY(float y);
        float map(float x, float in_min, float in_max, float out_min, float out_max);
    
    
        void initCities();
        city *cities;
        long numCities;


};


