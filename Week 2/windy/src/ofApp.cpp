#include "ofApp.h"
bool isOnGravity = false;
//--------------------------------------------------------------
void ofApp::setup(){
	int numBalls = 10;
	for (int i = 0; i < numBalls; i++) {
		Ball tempBall;
		balls.push_back(tempBall);
	}

	ofBackground(0);
    
    gravity = ofVec2f(0,0.2); 
	
}

//--------------------------------------------------------------
void ofApp::update(){
	ofVec2f wind;
	if (ofGetMousePressed()) {
		for (int i = 0; i < balls.size(); i++) {
			if (ofGetMouseX() - balls[i].pos.x > 0) {
				wind.x = ofMap(ofGetMouseX() - balls[i].pos.x, 0, ofGetWidth(), -0.2, 0);
			}
			else {
				wind.x = ofMap(ofGetMouseX() - balls[i].pos.x, -ofGetWidth(), 0, 0, 0.2);
			}

			if (ofGetMouseY() - balls[i].pos.y > 0) {
				wind.y = ofMap(ofGetMouseY() - balls[i].pos.y, 0, ofGetHeight(), -0.2, 0);
			}
			else {
				wind.y = ofMap(ofGetMouseY() - balls[i].pos.y, -ofGetHeight(), 0, 0, 0.2);
			}
			balls[i].applyForce(wind);
		}
	}

	if (isOnGravity) {
		for (int i = 0; i < balls.size(); i++) {
			balls[i].applyForce(gravity);
		}
	}

	// update with ball collision
	for (int i = 0; i < balls.size() - 1; i++) {
		for (int j = i + 1; j < balls.size(); j++) {
			if (pow(balls[i].pos.x - balls[j].pos.x, 2) + pow(balls[i].pos.y - balls[j].pos.y, 2)
				< pow(balls[i].radius + balls[j].radius, 2) + 1) {
				balls[i].collide();
				balls[j].collide();
			}
		}
	}

	for (int i = 0; i < balls.size(); i++) {
		balls[i].update();
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofDrawBitmapString("Hold the Left Mouse to blow the wind.", 10, 20);
	ofDrawBitmapString("*Collision between balls was not simulated.", 10, 30);
	ofDrawBitmapString("-: open gravity (downward wind)", 10, 40);
	ofDrawBitmapString("=: close gravity (downward wind)", 10, 50);
	for (int i = 0; i < balls.size(); i++) {
		balls[i].draw();
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == '-') {
		isOnGravity = true;
	}
	if (key == '=') {
		isOnGravity = false;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
