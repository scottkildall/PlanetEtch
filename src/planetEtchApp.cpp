#include "planetEtchApp.h"
#include "ofUtils.h"
#include "ofxCsv.h"
using namespace wng;

#include <stdlib.h>

//--------------------------------------------------------------
void planetEtchApp::setup(){
	capture = false;
    numCities = 0;
    cities = NULL;
    
    initCities();
}

//--------------------------------------------------------------
void planetEtchApp::update(){
	ofBackground(255, 255, 255);

}

//--------------------------------------------------------------
void planetEtchApp::draw(){

	//we don't want to capture every frame
	//so we only capture one frame when capture
	//is set to true
	if(capture){
		output.beginEPS("test.ps");
	}

	//do we want filled shapes or outlines?
	//if(bFill)output.fill();
	


	// Generaal draw parameters
	output.enableCenterRect();
    output.noFill();
    //output.fill();
	output.setColor(0x000000);
    
    for( int i = 0; i < numCities; i++ ) {
        for( int j = 0; j < numCities; j++ ) {
            if( i != j && (cities+i)->cnum == (cities+j)->cnum ) {
                //cout << "lines: " << "i = " << i << " j = " << j << " cnum = " << (cities+i)->cnum;
                //cout << endl;
                ofSetHexColor(0xCCCCCC);

                output.line((cities+i)->x, (cities+i)->y, (cities+j)->x, (cities+j)->y );
            }
        }
        
       
    }
    
    for( int i = 0; i < numCities; i++ ) {
         ofSetHexColor(0x000000);
         (cities+i)->draw(output);
     }
    
//    for( int i = 0; i < numCities; i++ ) {
//        if( i < 100 ) {
//            output.line((cities+i)->x, (cities+i)->y, (cities+i+1)->x, (cities+i+1)->y);
//        }
//    }
	
    
    
	//output.rect(280, 280, 1, 1);
    //output.rect(280.5, 280.5, 1, 1);

	//once we have done all our drawing
	//we end the ouput which saves the file
	//and then we stop capturing
	if(capture){
		output.endEPS();
		capture =false;
	}

	//
	// End capture!
	//-------------------------
	//-------------------------


	//we don't save this to eps - just info for the app
	/*ofFill();
	ofSetRectMode(OF_RECTMODE_CORNER);
	ofSetHexColor(0x000000);
	ofRect(60, 630, 200,60);

	//some text to explain whats what
	ofSetHexColor(0xDDDDDD);
	ofDrawBitmapString("spacebar to capture\n", 75, 650);
*/
}

//--------------------------------------------------------------
void planetEtchApp::keyPressed(int key){
	if(key == ' '){
		capture = true;
	}
}


void planetEtchApp::initCities() {
    
    ofxCsv csv;
    csv.loadFile(ofToDataPath("worldcitiespop.csv"));
    int NUM_CSV_COLUMNS = 6;
    int COL_COUNTRY = 0;
    int COL_X = 2;
    int COL_Y = 3;
    int COL_POP = 5;
    
    numCities = csv.numRows;
    cities = new city[numCities];
    
    float x;
    float y;
    
    for(int i=0; i<csv.numRows; i++) {
        /*cout << endl << csv.data[i][0] << endl;
        cout << "pop = " << csv.data[i][COL_POP] << endl;
        cout << "x = " << csv.data[i][COL_X] << endl;
        cout << "y = " << csv.data[i][COL_Y] << endl;
        */
        
        x = adjustX(ofToFloat(csv.data[i][COL_X]));
        y = adjustY(ofToFloat(csv.data[i][COL_Y]));
        
        
        
        (cities+i)->setVars( /*CANVAS_WIDTH/4 + x/2*/x, y, ofToFloat(csv.data[i][COL_POP]), ofToInt(csv.data[i][COL_COUNTRY]));  // pop not used right now
    }
}

float planetEtchApp::adjustX(float x) {
    float HIGHEST_X = 59;
    float LOWEST_X = -37;

    return map(x, LOWEST_X, HIGHEST_X, CANVAS_MARGIN, CANVAS_WIDTH-CANVAS_MARGIN );
}

float planetEtchApp::adjustY(float y) {
    // original
    //float LOWEST_Y = -123;
    //float HIGHEST_Y = 153;
    
    // flipped
    float LOWEST_Y = -153;
    float HIGHEST_Y = 123;
    y = -y;
    
    cout << "y = " << y << endl;
    
    return map(y, LOWEST_Y, HIGHEST_Y, CANVAS_MARGIN, CANVAS_HEIGHT-CANVAS_MARGIN );
}

float planetEtchApp::map(float m, float in_min, float in_max, float out_min, float out_max)
{
    //cout << "m = " << m << endl;
    return (m - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/*
 (cities+i)->setVars( ofRandom(CANVAS_MARGIN, CANVAS_WIDTH-CANVAS_MARGIN),
 ofRandom(CANVAS_MARGIN, CANVAS_HEIGHT-CANVAS_MARGIN),
 250);  // pop not used right now
 */

// OLD: RANDOM PLACEMENT CODE

    //}

    //OLD
    /*
    numCities = 294;
    cities = new city[numCities];
    
    for( int i = 0; i < numCities; i++ ) {
        (cities+i)->setVars( ofRandom(CANVAS_MARGIN, CANVAS_WIDTH-CANVAS_MARGIN),
                             ofRandom(CANVAS_MARGIN, CANVAS_HEIGHT-CANVAS_MARGIN),
                            250 );  // pop not used right now
        
    }
     */
//}
