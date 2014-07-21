#include "planetEtchApp.h"
#include "ofUtils.h"

#include <stdlib.h>

//--------------------------------------------------------------
// INPUT CSV: millions of records
// Country,City,AccentCity,Region,Population,Latitude,Longitude
#define INPUT_COL_COUNTRY         (0)
#define INPUT_COL_CITY            (2)
#define INPUT_COL_POP             (4)
#define INPUT_COL_LAT             (5)
#define INPUT_COL_LNG             (6)
//--------------------------------------------------------------
// OUTPUT CSV: ~50000 records
// 1,Dubai,25.258171,55.304718,0.0,1137.376
#define OUTPUT_COL_COUNTRY          (0)
#define OUTPUT_COL_CITY             (1)
#define OUTPUT_COL_POP              (2)
#define OUTPUT_COL_LAT              (3)
#define OUTPUT_COL_LNG              (4)

// uncommenting will make it so that we go through the worlds CSV file
//     and extract only cities that have a non-zero population
// #define FILTER_CSV

//--------------------------------------------------------------
void planetEtchApp::setup(){
	capture = false;
    numCities = 0;
    cities = NULL;
    
#ifdef FILTER_CSV
    filterCSV();
#endif
    
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
		output.beginEPS("citypop.ps");
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

                //output.line((cities+i)->x, (cities+i)->y, (cities+j)->x, (cities+j)->y );
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
    csv.loadFile(ofToDataPath("allcities.csv"));
    
    numCities = csv.numRows;
    cities = new city[numCities];
    unsigned long cityIndex = 0;
    
    float x;
    float y;
    
    for(int i=0; i<numCities; i++) {
        
        
        /*cout << endl << csv.data[i][0] << endl;
        cout << "pop = " << csv.data[i][COL_POP] << endl;
        cout << "x = " << csv.data[i][COL_X] << endl;
        cout << "y = " << csv.data[i][COL_Y] << endl;
        */
        
        //x = adjustX(ofToFloat(csv.data[i][COL_X]));
        //y = adjustY(ofToFloat(csv.data[i][COL_Y]));
        
        x = ofToFloat(csv.data[i][OUTPUT_COL_LNG]);
        y = ofToFloat(csv.data[i][OUTPUT_COL_LAT]);
        x = lngToX(x);
        y = latToY(y);
        
        
        x = adjustX(x);
        y = adjustY(y);
        
        /*
        cout << "x = ";
        cout << x;
        cout << endl;
        cout << "y = ";
        cout << y;
        cout << endl;
        */
        
        string countryString = csv.getString(i, OUTPUT_COL_COUNTRY);
        unsigned long hashID = hash(countryString.c_str());
        
        
        float pop =  ofToFloat(csv.data[i][OUTPUT_COL_POP]);
        
        (cities+i)->setVars( /*CANVAS_WIDTH/4 + x/2*/x, y, pop, hashID);  // pop not used right now

        
        
        
        //(cities+i)->setVars( /*CANVAS_WIDTH/4 + x/2*/x, y, ofToFloat(csv.data[i][COL_POP]), ofToInt(csv.data[i][COL_COUNTRY]));  // pop not used right now
    }
}


void planetEtchApp::filterCSV() {
    ofxCsv inputCSV;
    inputCSV.loadFile(ofToDataPath("cities_master.csv"));
    
    ofxCsv outputCSV;
    //outputCSV.createFile(ofToDataPath("allcities.csv"));
    
    unsigned long badRecords = 0;
    unsigned long goodRecords = 0;
    unsigned long totalRecords = inputCSV.numRows;
    
    for(unsigned long i=0; i<inputCSV.numRows; i++) {
        float pop = ofToFloat(inputCSV.data[i][INPUT_COL_POP]);
        
        if( pop == 0) {
            badRecords++;
        }
        else {
            // save this line in a CSV
           // OUTPUT_COL_COUNTRY          (0)
/*#define OUTPUT_COL_CITY             (1)
#define OUTPUT_COL_POP              (2)
#define OUTPUT_COL_LAT              (3)
#define OUTPUT_COL_LNG
*/
            
            outputCSV.setString(goodRecords, OUTPUT_COL_COUNTRY, inputCSV.data[i][INPUT_COL_COUNTRY]);
            outputCSV.setString(goodRecords, OUTPUT_COL_CITY, inputCSV.data[i][INPUT_COL_CITY]);
            
            outputCSV.setFloat(goodRecords, OUTPUT_COL_POP, pop);
            
            float lat = ofToFloat(inputCSV.data[i][INPUT_COL_LAT]);
            float lng = ofToFloat(inputCSV.data[i][INPUT_COL_LNG]);
            
            outputCSV.setFloat(goodRecords, OUTPUT_COL_LAT, lat);
            outputCSV.setFloat(goodRecords, OUTPUT_COL_LNG, lng);
            
            
            cout << "Pop: ";
            cout << pop;
            cout << endl;
            goodRecords++;
        }
        
    }
    
    outputCSV.saveFile(ofToDataPath("allcities.csv"), ",");
    
    cout << "Total records: ";
    cout << totalRecords;
    cout << endl;
    
    cout << "Good records: ";
    cout << goodRecords;
    cout << endl;
    
    cout << "Bad records: ";
    cout << badRecords;
    cout << endl;
}



float planetEtchApp::adjustX(float x) {
    float HIGHEST_X = 160;
    float LOWEST_X = -160;   //-37;
    
    return map(x, LOWEST_X, HIGHEST_X, CANVAS_MARGIN, CANVAS_WIDTH-CANVAS_MARGIN );
}

float planetEtchApp::adjustY(float y) {
    // original
    //float LOWEST_Y = -123;
    //float HIGHEST_Y = 153;
    
    // flipped
    float LOWEST_Y = -160;  //-153;
    float HIGHEST_Y = 160;
    y = -y;
    
    //cout << "y = " << y << endl;
    
    return map(y, LOWEST_Y, HIGHEST_Y, CANVAS_MARGIN, CANVAS_HEIGHT-CANVAS_MARGIN );
}

float planetEtchApp::lngToX(float x) {
    return x;
}

float planetEtchApp::latToY(float y) {
    return y;
}

float planetEtchApp::map(float m, float in_min, float in_max, float out_min, float out_max)
{
    //cout << "m = " << m << endl;
    return (m - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

unsigned long  planetEtchApp::hash(const char *str) {
    unsigned long hash = 5381;
    int c;
    
    // go to end of line
    while ((c = *str++) != 0) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    
    return hash;
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
