#pragma once

#include "ofMain.h"
#include "math.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
    ofFbo fbo;
    ofMesh mesh;
    
    int totalX = ofGetWidth();
    int totalY = ofGetHeight();
    
    int color;
    float speed = 0.1;
    
    float midPointX = 1.0;
    float midPointY = 1.0;
    
    ofTrueTypeFont font;
    string fontFile = "Montserrat-ExtraBold.ttf";
    int fontSize = 30;
		
};
