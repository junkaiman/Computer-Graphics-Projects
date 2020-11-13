#include "ofApp.h"

int init_PlanetNum = 40;

int generatePlanetInterval = 4;			// data used to trigger event every 4 seconds
int nextTriggerGeneratingPlanets = 0;   // data used to trigger event every 4 seconds
//--------------------------------------------------------------
void ofApp::setup(){
	// Basic Set up
    ofSetFrameRate(60);
    ofBackground(200);
    ofEnableSmoothing();
    ofEnableAlphaBlending();

	// Set up planets
    float g = 0.01;
    for (int i = 0; i < init_PlanetNum; i++) {
        planet m = planet(ofRandom(0.5,1),ofRandom(ofGetWidth()),ofRandom(ofGetHeight()-100),g);
        planets.push_back(m);
    }
	planet M = planet(3, ofGetWidth() / 2, ofGetHeight() / 2, 2 * g);
	planets.push_back(M);

	// Set up spacecraft
	spacecraft.setup(glm::vec2(50, 50));
	
}

//--------------------------------------------------------------
void ofApp::update(){
	bool planetToRemove = false;
	int planetToRemoveIndex;
	bool outOfBox = false;
	int outOfBoxIndex;

	/*
	 * Planet
	 */

    for (int i = 0; i < planets.size(); i++) {
		if (planets[i].location.x > ofGetWidth() or planets[i].location.y > ofGetHeight()) {
			outOfBox = true;
			outOfBoxIndex = i;
		}
        for (int j = 0; j < planets.size(); j++) {
            if (i != j) {
				// detect collision
				float distance = sqrt(pow(planets[i].location.x - planets[j].location.x, 2) - pow(planets[i].location.y - planets[j].location.y, 2));
				// if it's inside
				if (distance + min(planets[i].radius, planets[j].radius) < max(planets[i].radius, planets[j].radius)) {
					if (planets[i].radius > planets[j].radius) {
						planets[i].radius += planets[j].radius * 0.03;
						planets[i].mass += planets[j].mass * 0.1;
						planetToRemove = true;
						planetToRemoveIndex = j;
					}
					else {
						planets[j].radius += planets[i].radius * 0.03;
						planets[j].mass += planets[i].mass * 0.1;
						planetToRemove = true;
						planetToRemoveIndex = i;
					}
				}
                glm::vec2 force = planets[j].attract(planets[i]);
                planets[i].applyForce(force);
            }
        }
        planets[i].update();
    }
	if (planetToRemove && planets.size() > 1) {
		planets.erase(planets.begin() + planetToRemoveIndex);
	}
	
	if (outOfBox) {
		planets.erase(planets.begin() + outOfBoxIndex);
	}
	
	/*
	 * Spacecraft
	 */

	spacecraft.easeTo(glm::vec2(ofGetMouseX()-spacecraft.width/2, ofGetMouseY()-spacecraft.height/2));
	spacecraft.update();
	
	/*
	 * Bullet
	 */

	bool bulletToRemove = false;
	int bulletToRemoveIndex;
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i].location.y < 0) {
			bulletToRemove = true;
			bulletToRemoveIndex = i;
		}
		for (int j = 0; j < planets.size(); j++) {
			float distance = sqrt(
				pow(bullets[i].location.x - planets[j].location.x, 2)
				- pow(bullets[i].location.y - planets[j].location.y, 2));
			if (distance + min(bullets[i].radius, planets[j].radius) < max(bullets[i].radius, planets[j].radius)) {
				bulletToRemove = true;
				bulletToRemoveIndex = i;
				planets[j].mass -= 0.9;
				planets[j].radius -= 0.9;
			}
		}
		bullets[i].update();
	}

	// Remove bullet that is out of window or be absorbed by planet
	if (bulletToRemove) {
		bullets.erase(bullets.begin() + bulletToRemoveIndex);
	}

	// Randomly generate planets for every 4 seconds
	int currentTime = ofGetElapsedTimef();
	if (currentTime > nextTriggerGeneratingPlanets) {
		float g = 0.01;
		for (int i = 0; i < init_PlanetNum; i++) {
			planet m = planet(ofRandom(0.5, 1), ofRandom(ofGetWidth()), ofRandom(ofGetHeight() - 100), g);
			planets.push_back(m);
		}
		nextTriggerGeneratingPlanets = currentTime + generatePlanetInterval;
	}



}

//--------------------------------------------------------------
void ofApp::draw(){
	ofDrawBitmapString("Planets: " + ofToString(planets.size()), 10, 20);
	ofDrawBitmapString("Bullets: " + ofToString(bullets.size()), 10, 30);
	ofDrawBitmapString("Press 'N' to generate planets. ", 10, 40);
	ofDrawBitmapString("Press 'R' to clear all objects. ", 10, 50);
	ofDrawBitmapString("Left Click to shoot bullet.", 10, 60);
	ofDrawBitmapString("Shoot to erode planets, ", 10, 70);
	ofDrawBitmapString("Don't make planets accumulate together, otherwise it will become abosulute black and explode.", 10, 80);
	ofSetColor(255, 0, 0);
	ofDrawBitmapString("Planets will have repulsion ability when the color turns white.", 10, 90);
	ofSetColor(0);

	for (auto&m: planets){
        m.display();
    }

	spacecraft.draw();

	for (auto&b: bullets) {
		b.display();
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){ }
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	float g = 0.01;
	if (key == 'n') {
		for (int i = 0; i < init_PlanetNum; i++) {
			planet m = planet(ofRandom(0.5, 1), ofRandom(ofGetWidth()), ofRandom(ofGetHeight()-100), g);
			planets.push_back(m);
		}
	}

	if (key == 'r') {
		bullets.clear();
		planets.clear();
	}
	

}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){ }
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (button == 0) {
		bullet tempBullet;
		tempBullet.location.x = spacecraft.location.x + spacecraft.width / 2;
		tempBullet.location.y = spacecraft.location.y;
		bullets.push_back(tempBullet);
	}

}
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){ }
//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){ }
//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){ }
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ }