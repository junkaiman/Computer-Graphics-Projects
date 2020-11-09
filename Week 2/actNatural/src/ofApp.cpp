#include "ofApp.h"

/*
 Mover
*/
void Mover::setup(float m, float x, float y, float h, float l, float a) {
	mass = m;
	length = l;
	height = h;
	angle = a;
	pos.set(x, y);
	vel.set(0, 0);
	acc.set(0, 0);
}

void Mover::update(ofPoint target) {
	ofPoint dir = target - pos;
	float rad = atan2(dir.y, dir.x);
	angle = ofRadToDeg(rad);
	vel += acc;
	pos += vel;
	acc *= 0;
	ofRotate(20);
}

void Mover::draw() {
	
	ofSetColor(255);
	ofDrawRectangle(pos.x - length / 2, pos.y - height / 2, length, height);
	ofDrawCircle(pos.x - length / 2, pos.y, height / 2);
	ofDrawCircle(pos.x + length / 2, pos.y, height / 2);
	
}

void Mover::applyForce(ofPoint force) {
	force /= mass;
	acc += force;
}

/*
 Magnet
*/
void Magnet::setup(float x, float y) {
	pos.x = x;
	pos.y = y;
}

void Magnet::update() {
	if (ofGetMousePressed()) {
		pos.x = ofGetMouseX();
		pos.y = ofGetMouseY();
	}
}

void Magnet::draw() {
	ofDrawCircle(pos, 2);
}

/*
 ofApp
*/
void ofApp::setup(){
	ofSetCircleResolution(100);
	ofEnableSmoothing();
	ofSetFrameRate(60);
	ofBackground(0);
	mover.setup(1, 100, 100, 40, 60, 0);
	magnet.setup(500, 500);
	
}

//--------------------------------------------------------------
void ofApp::update(){
	float time = ofGetElapsedTimef();
	// the following code are learned from nature of code 06-attraction
	ofPoint force = magnet.pos - mover.pos;
	float distance = force.length();
	distance = ofClamp(distance, 2.0, 70.0);
	force.normalize();
	float strength = mover.mass / pow(distance, 2); // does not exactly follow the physics law
	force *= 500 * strength; // 500 times
	cout << "the distance" << distance << endl;
	

	// act like there's fraction when is close to the magnet

	if (distance < 20) {
		mover.vel *= 0.8;
		mover.applyForce(-0.7 * force);
	}
	else {
		mover.applyForce(force);
	}

	mover.update(magnet.pos);
	magnet.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofDrawBitmapString("Click the Left Mouse to set the location of magnet", 10, 20);
	magnet.draw();
	mover.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
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
