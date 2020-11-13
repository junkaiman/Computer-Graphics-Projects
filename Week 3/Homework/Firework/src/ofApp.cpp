#include "ofApp.h"
/*
 * Modified from 01_particle_system by Tyler Henry on 10/2/18
 */

bool okToDrawLine = false;
//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0);
   
    glm::vec2 pos = glm::vec2(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
    ParticleSystem particleSystem = ParticleSystem(pos, glm::vec2(0, -3));
    
    particleSystems.push_back(particleSystem);
    
    // setup general gravity force
    gravity = glm::vec2(0, .5);

}

//--------------------------------------------------------------
void ofApp::update(){
    
    for (int i=0; i<particleSystems.size(); i++){
        particleSystems[i].applyForce(gravity);
        particleSystems[i].update();
    }

}

//--------------------------------------------------------------
void ofApp::draw(){

	// Set a fancy background
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(ofGetWidth(), 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(ofGetWidth(), ofGetHeight(), 0.0f);
	glVertex3f(0.0f, ofGetHeight(), 0.0f);
	glEnd();

	ofDrawBitmapString("Use 'R' to restart the firework launcher.", 10, 20);
	ofDrawBitmapString("Do it like angry birds, drag your mouse to launch the firework!", 10, 40);

    for (int i=0; i<particleSystems.size(); i++){
        particleSystems[i].draw();
    }
	
	if (okToDrawLine) {
		ofSetColor(255);
		ofDrawLine(startPos, glm::vec2(ofGetMouseX(), ofGetMouseY()));
		ofSetColor(0);
		//okToDrawLine = false;
	}
}

//--------------------------------------------------------------

void ofApp::mousePressed(int x, int y, int button) {
	startPos.x = x;
	startPos.y = y;
	okToDrawLine = true;
}

void ofApp::mouseReleased(int x, int y, int button) {
	endPos.x = x;
	endPos.y = y;
	okToDrawLine = false;
	
	glm::vec2 direction;
	direction.x = ofMap(startPos.x - endPos.x, 0, ofGetWidth(), 0, 50);
	direction.y = ofMap(startPos.y - endPos.y, 0, ofGetHeight(), 0, 50);
	particleSystems.push_back(ParticleSystem(glm::vec2(x, y), direction));
}

void ofApp::keyPressed(int key) {
	if (key == 'r') {
		particleSystems.clear();
	}
}