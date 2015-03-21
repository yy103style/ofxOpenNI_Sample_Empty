#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    //  window
    ofBackground(0, 0, 0);
    ofSetWindowShape(640, 480);
    ofSetFrameRate(30);
    //  setup ofxOpenNI
    kinect.setup();
    kinect.setRegister(true);
    kinect.setMirror(true);
    kinect.addImageGenerator();     //  required for RGB image
    kinect.addDepthGenerator();     //  required for depth image
    kinect.addUserGenerator();      //  required for skeleton tracking
    kinect.setMaxNumUsers(1);       //  max num of skeleton to track
    //  start kinect
    kinect.start();
}

//--------------------------------------------------------------
void testApp::update(){
    kinect.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    //  draw RGB image (weak)
    ofSetColor(100, 100, 100);
    kinect.drawImage(0, 0, 640, 480);
    //  draw skeleton (strong)
    ofSetColor(255, 255, 255);
    kinect.drawSkeletons(0, 0, 640, 480);
}
//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}