#include "ofApp.h"

ofPolyline line;
ofPolyline face;
ofPolyline nose;
ofPolyline mouth;
ofPolyline hair;

ofPoint startPoint = ofPoint(200, 160);
ofPoint startLowerPoint = ofPoint(270, 660);
int upperLength = 520;
int lowerLength = 380;
int eyeRadius = 70;
float speed = 10;
float time1;
float recordedTime = 0;
ofPoint eye1 = ofPoint(350, 300);
ofPoint eye2 = ofPoint(570, 300);
ofPoint eye1_black = ofPoint(350, 300);
ofPoint eye2_black = ofPoint(570, 300);


//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0,0,0);
}

//--------------------------------------------------------------
void ofApp::update(){
	time1 = ofGetElapsedTimef() - recordedTime;
	float sinT = sin(10*time1) * 50;
	int direction = 1;

	hair.addVertex(startPoint.x + direction * ofMap(time1, 0, speed, 0, upperLength), startPoint.y + sinT);

	if (hair.getVertices().size() > 5000) {
		hair.clear();
	}

	ofPoint mouse = ofPoint(ofGetMouseX(), ofGetMouseY());
	ofPoint eye1_target = ofPoint(eye1_black.x + ofMap(ofGetMouseX() - eye1_black.x, 0, ofGetWidth(), 0, eyeRadius / 3), eye1_black.y + ofMap(ofGetMouseY() - eye1_black.y, 0, ofGetHeight(), 0, eyeRadius / 3));
	ofPoint eye2_target = ofPoint(eye2_black.x + ofMap(ofGetMouseX() - eye2_black.x, 0, ofGetWidth(), 0, eyeRadius / 3), eye2_black.y + ofMap(ofGetMouseY() - eye2_black.y, 0, ofGetHeight(), 0, eyeRadius / 3));

	eye1_black = eye1_black * 0.97 + eye1_target * 0.03;
	eye2_black = eye2_black * 0.97 + eye2_target * 0.03;
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofDrawBitmapString("press -/= to change the amount of hair", 10, 20);
	ofDrawBitmapString("press a/d to stretch the mouth", 10, 30);
	ofDrawBitmapString("press the Left Mouse to add border of face", 10, 40);
	ofDrawBitmapString("haha I kept this spooky eye effect by intention, you may lose one of your eye~!", 10, 60);


	hair.draw();

	face.draw();
	face.addVertex(startPoint);
	face.addVertex(startPoint.x + upperLength, startPoint.y);

	face.addVertex(startLowerPoint.x+lowerLength, startLowerPoint.y);
	face.addVertex(startLowerPoint);
	face.close();
	
	ofSetColor(255);
	ofDrawCircle(eye1, eyeRadius);
	ofDrawCircle(eye2, eyeRadius);
	ofSetColor(0);
	ofDrawCircle(eye1_black, eyeRadius / 3);
	ofDrawCircle(eye2_black, eyeRadius / 3);
	ofSetColor(255);
	ofDrawLine(350 - eyeRadius, 300, startPoint.x, 300); // glasses pt1
	ofDrawLine(350 + eyeRadius, 300, 570 - eyeRadius, 300); // glasses pt2
	ofDrawLine(570 + eyeRadius, 300, startPoint.x + upperLength, 300); // glasses pt3

	ofDrawLine(350 - eyeRadius - 5, 200, 350 + eyeRadius + 5, 200); // eyebow left
	ofDrawLine(570 - eyeRadius - 5, 200, 570 + eyeRadius + 5, 200); // eyebow right

	nose.draw();
	nose.addVertex(startPoint.x + upperLength/2 - 15, 330);
	nose.addVertex(startPoint.x + upperLength/2 - 15, 440);
	nose.addVertex(startPoint.x + upperLength/2 + 15, 440);
	nose.close();

	mouth.draw();
	mouth.addVertex(400, 540);
	mouth.addVertex(600, 540);
	mouth.close();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == '-') {
		hair.clear();
		speed += 10;
		recordedTime = ofGetElapsedTimef();
	}
	if (key == '=' and speed > 10) {
		hair.clear();
		speed -= 10;
		recordedTime = ofGetElapsedTimef();
	}

	if (key == 'a') {
		for (auto &vert: mouth.getVertices()) {
			vert.x -= 3;
		}
	}

	if (key == 'd') {
		for (auto &vert : mouth.getVertices()) {
			vert.x += 3;
		}
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (button == 0) {
		for (auto &vert : face.getVertices()) {
			vert.x += ofRandom(-3, 3);
			vert.y += ofRandom(-3, 3);
		}
	}
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
