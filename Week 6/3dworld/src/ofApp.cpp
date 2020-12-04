#include "ofApp.h"
float sphereRadius = 2000;

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
	ofSetSmoothLighting(true);
	ofSetVerticalSync(true);

	earthImg.load("earth_texture.jpg");
	sphere.mapTexCoordsFromTexture(earthImg.getTexture());

	cam.setDistance(0);
	cam.setPosition(sphereRadius +10, 800, 800);

	sphere.rotateAround(glm::vec3(0, 200, 100), glm::vec3(0, 0, 0));

	sphere.setPosition(0, 0, 0);
	sphere.setRadius(sphereRadius);
	light.setSpotlight();
	light.setPosition(sphereRadius + 50, sphereRadius +50, sphereRadius + 50);
	light.lookAt(glm::vec3(0, 0, 0));

	light.setDiffuseColor(ofColor::white);
	light.setAttenuation(2);

	for (int i = 0; i < 1000; i++) {
		ofSpherePrimitive satellite;
		satellites.push_back(satellite);
	}

	for (auto &satellite: satellites){
		satellite.setRadius(ofRandom(10, 60));
		glm::vec3 randomPos = glm::vec3(ofRandom(-sphereRadius - 300, sphereRadius+ 800), ofRandom(-sphereRadius - 300, sphereRadius + 300), ofRandom(-sphereRadius - 300, sphereRadius + 300));
		satellite.setPosition(randomPos);
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	float time = ofGetElapsedTimef();
	sphere.rotateDeg(0.1, 0, 1, 0);
	sphere.setResolution(100);

	for (auto &satellite : satellites) {
		satellite.rotateAround(1, glm::vec3(1, 1, 1), glm::vec3(0, 0, 0));
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();
	ofSetColor(0, 0, 0);
	ofNoFill();

	ofEnableLighting();		// turn on lighting globally
	ofEnableDepthTest();	// render objects in order of depth
	light.enable();
	ofSetColor(255);

	earthImg.bind();
	sphere.draw();
	earthImg.unbind();

	ofNoFill();
	sphere.drawWireframe();
	ofSetColor(0);
	
	ofSetColor(255);
	ofFill();
	light.draw();

	for (auto &satellite : satellites) {
		ofFill();
		ofSetColor(255);
		satellite.draw();
	}
	light.disable();
	ofDisableLighting();		// disable global lighting
	cam.end();
	ofDisableDepthTest();
	
	string info;
	info += "Junkai Man\n";
	info += "Space Junk\n";
	info += "MEDIART 206";
	ofDrawBitmapStringHighlight(info, ofGetWidth() - 100, 20);

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
