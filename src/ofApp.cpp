#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    font.load(fontFile, fontSize);
    
    ofBackground(255, 255, 255);
    fbo.allocate(640, 480, GL_RGBA);
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();
    
    color = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
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
    
    ofClear(255,255,255,0);
    
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
                ofSetColor(color, 0, 0, 255);
            } else if (targ % 2 == 0) {
                ofSetColor(0, color, 0, 255);
            } else {
                ofSetColor(0, 0, color, 255);
            }
            
            int deg = (o / 360);
            if (deg < 0) {
                deg *= -1;
            }
            deg = deg * 360;
            
            ofPushMatrix();
            
            ofRotate(deg + x + (y));
            ofDrawCircle(x, y, 0, 1);
            
            ofPopMatrix();
            
            currentLine = (float) y;
        }
    }
    
    fbo.end();
    
    ofPushMatrix();
    fbo.draw(0,0);
    ofPopMatrix();
    
    ofPushStyle();
    ofSetColor(255,0,0);
    string slogan = "give me moiré";
    font.drawString(slogan, (ofGetWidth()/2) - (font.stringWidth(slogan)/2), 255);
    ofPopStyle();
    
}

