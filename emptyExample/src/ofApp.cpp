#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofSetCircleResolution(50);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    int circleAddPerFrame = 10;
    
    for(int i=0; i<circleAddPerFrame; i++) {

        float x = ofRandom(ofGetWidth());
        float y = ofRandom(ofGetHeight());
        float radiusMin = 2.0;
        float radiusMax = 200.0;
        float radiusGrowth = (radiusMax - radiusMin) / 100.0;
        float gap = 1.0;
        ofColor colorFill(0);
        ofColor colorStroke(0);
        
        circlePacker.addCircle(x, y, radiusMin, radiusMax, radiusGrowth, gap, colorFill, colorStroke);
    }
    
    circlePacker.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    circlePacker.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if(key == ' ') {
        circlePacker.togglePause();
    }
    
    if(key == 'r' || key == 'R') {
        circlePacker.reset();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}