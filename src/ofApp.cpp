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
//    mesh.clear();
    
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
            
            int deg = (o / 360) * ofRandomf();
            if (deg < 0) {
                deg *= -1;
            }
            deg = deg * 360;
            
            ofPushMatrix();
            
            ofRotate(deg + x + (y));
            
            mesh.addVertex(ofPoint(x,y,deg*0.3)); // make a new vertex
            
            if (targ % 3 == 0) {
                mesh.addColor(ofFloatColor(color,0,0));
            } else if (targ % 2 == 0) {
                mesh.addColor(ofFloatColor(0,color,0));
            } else {
                mesh.addColor(ofFloatColor(0,0,color));
            }
            
            ofPopMatrix();
            
            currentLine = (float) y;
        }
    }
    
    for (int y = 0; y<totalY-1; y++){
        for (int x=0; x<totalX-1; x++){
            mesh.addIndex(x+y*totalX);               // 0
            mesh.addIndex((x+1)+y*totalX);           // 1
            mesh.addIndex(x+(y+1)*totalX);           // 10
            
            mesh.addIndex((x+1)+y*totalX);           // 1
            mesh.addIndex((x+1)+(y+1)*totalX);       // 11
            mesh.addIndex(x+(y+1)*totalX);           // 10
        }
    }
    
    mesh.draw();
    fbo.end();
    
    ofPushMatrix();
    fbo.draw(0,0);
    ofPopMatrix();
    
    string slogan = "give me moiré";
    int fontX = (ofGetWidth()/2) - (font.stringWidth(slogan)/2);
    int fontY = 255;
    
    // Animate string mesh
    ofPushStyle();
    ofSetColor(0,0,255);
    ofMesh stringMesh = font.getStringMesh(slogan, fontX, fontY);
    for(int i = 0; i < stringMesh.getNumVertices(); i++) {
        stringMesh.setVertex(i, stringMesh.getVertex(i) + ofVec3f(10*(0.5-ofRandomuf()),ofRandom(-30,30)*(0.3 - ofRandomf()), 100*(0.3 - ofRandomf())));
    }
    
    stringMesh.draw();
    ofPopStyle();
    
    ofPushStyle();
    ofSetColor(255,0,0);
    
    font.drawString(slogan, fontX, fontY);
    ofPopStyle();
    
}











