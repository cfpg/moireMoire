#pragma once

#include "ofMain.h"
#include "math.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofFbo fbo;
    
    int color;
    float speed = 0.1;
    int currentZ = 1;
    bool goingFront = true;
    
    float midPointX = 1.0;
    float midPointY = 1.0;
    
    ofTrueTypeFont font;
    string fontFile = "Montserrat-ExtraBold.ttf";
    int fontSize = 30;
		
};