#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    posX.reset((ofGetWidth()/2) * -1);
    posX.setRepeatType(LOOP_BACK_AND_FORTH);
    posX.setCurve(SWIFT_GOOGLE);
    posX.animateTo((float)ofGetWidth()/2);
    
    posY.reset((ofGetHeight()/2) * -1);
    posY.setRepeatType(LOOP_BACK_AND_FORTH);
    posY.setCurve(SWIFT_GOOGLE);
    posY.animateTo((float)ofGetHeight()/2);
    
    degAnim.reset(1);
    degAnim.setRepeatType(LOOP_BACK_AND_FORTH);
    degAnim.setCurve(SWIFT_GOOGLE);
    degAnim.animateTo(360.0f);
    
    font.load(fontFile, fontSize);
    
    ofBackground(255);
    fbo.allocate(640, 480, GL_RGB);
    fbo.begin();
    ofClear(255,255,255);
    fbo.end();
    
    color = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    posX.update(1.0f/60.0f);
    posY.update(1.0f/60.0f);
    degAnim.update(1.0f/120.0f);
    
    if (color > 255) {
        color = 0;
    }
    
    midPointX += midPointX * speed;
    midPointY += midPointY * speed;
    
    if (midPointX > ofGetWidth()) {
        midPointX = 1.0;
    }
    if (midPointY > ofGetHeight()) {
        midPointY = 1.0;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.begin();
    
    ofClear(255,255,255);
    
    int halfWidth = ofGetWidth() / 2;
    int halfHeight = ofGetHeight() / 2;
    
    halfWidth = midPointX;
    halfHeight = midPointY;
    
    color = speed * color + ( 255 - color ) * 0.5;
    if (color > 255) {
        color = 0;
    }
    
    int totalX = ofGetWidth();
    int totalY = ofGetHeight();
    totalX = 300;
    totalY = 300;
    
    for (int x = 0; x < totalX; x++) {
        float currentLine = 0.0;
        
        float farAway = (halfWidth - x);
        if (farAway < 0.0) {
            farAway = farAway * -1;
        }
        
        for (int y = 0; y < totalY; y++) {
            
            float farY = (halfHeight - y);
            if (farY < 0) {
                farY = farY * -1;
            }
            
            float total = farAway + farY;
            if (total < 0) {
                total = total * -1;
            }
            total = total / 2;
            
            int o = (total / halfWidth) * 255;
            
            o = o - 255;
            if (o < 0) {
                o = o * -1;
            }
            
            int targ = y;//(x + y);
            
            if (targ % 3 == 0) {
                ofSetColor(color, 0, 0);
            } else if (targ % 2 == 0) {
                ofSetColor(0, color, 0);
            } else {
                ofSetColor(0, 0, color);
            }
            ofSetColor(0);
            
            int deg = (o / 360) * ofRandomuf();
            if (deg < 0) {
                deg *= -1;
            }
            deg = deg * 360;
            
            ofPushMatrix();
            
            ofRotate(x+ (y*degAnim.getCurrentValue()));
            ofTranslate(-100, x+y);
            ofDrawCircle(posX.getCurrentValue(), (float)y - posY.getCurrentValue(), 0, 1);
            
            ofPopMatrix();
            
            currentLine = (float) y;
        }
    }
    
    fbo.end();
    
    ofPushMatrix();
    fbo.draw(0,0);
    ofPopMatrix();
    
    string slogan = "give me moiré";
    int fontX = (ofGetWidth()/2) - (font.stringWidth(slogan)/2);
    int fontY = 250;
    
    // Animate string mesh
    ofPushStyle();
    ofSetColor(0,100,255);
    ofMesh stringMesh = font.getStringMesh(slogan, fontX, fontY);
    for(int i = 0; i < stringMesh.getNumVertices(); i++) {
        stringMesh.setVertex(i, stringMesh.getVertex(i) + ofVec3f(10*(0.5-ofRandomuf()),ofRandom(-30,30)*(0.3 - ofRandomf()), 100*(0.8 - ofRandomuf())));
    }

    stringMesh.draw();
    ofPopStyle();
    
    ofPushStyle();
    ofSetColor(0);
    
    font.drawString(slogan, fontX, fontY);
    ofPopStyle();
    
}











