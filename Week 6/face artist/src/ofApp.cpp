#include "ofApp.h"
/*
 * Junkai Man
 * - Face Artist
 *
 * The data is transmitted via OSC. Please be sure to open FaceOSC when running the app.
 * The inspiration comes from the exmaple of 3d-drawing in Week 4. Credit to part of the code.
 * 
 */

int PORT = 8338;
//--------------------------------------------------------------
void ofApp::setup(){
	ofSetBackgroundColor(0);
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	oscReceiver.setup(PORT);
	zSpeed = 5.f;  // normal "drift" speed

	for (int i = 0; i < 66; ++i) {
		points.push_back(glm::vec2());
	}

	ofSetLineWidth(5.);
	for (int i = 0; i < points.size(); ++i) {
		ribbons.push_back(ofPolyline());
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	programRunningTime = ofGetElapsedTimef();

	while (oscReceiver.hasWaitingMessages()) {
		ofxOscMessage m;
		oscReceiver.getNextMessage(&m);

		if (m.getAddress() == "/found") {
			if (!found && m.getArgAsInt32(0) == 1) {
				lastFaceFoundTime = programRunningTime;
			}
			if (found && m.getArgAsInt32(0) == 0) {
				lastFaceLostTime = programRunningTime;

				zSpeed = 5.0; // change zSpeed
			}

			found = (bool)m.getArgAsInt32(0);
		}

		if (m.getAddress() == "/raw" && m.getNumArgs() == 132) {
			int p = 0;
			for (int i = 0; i < 132; i = i + 2) {
				points[p].x = ofMap(m.getArgAsFloat(i), 0, 640, 0, ofGetWidth());
				points[p].y = ofMap(m.getArgAsFloat(i + 1), 0, 480, 0, ofGetHeight());
				p++;
			}

		}
	}

	if (found) {
		for (int i = 0; i < points.size(); i++) {

			glm::vec3 drawPoint = glm::vec3(points[i].x, points[i].y, 0);
			glm::vec3 prevDrawPoint;
			if (i == 0) {
				prevDrawPoint = glm::vec3(ofGetWidth() / 2, ofGetHeight() / 2, 0);
			}
			else {
				prevDrawPoint = glm::vec3(points[i - 1].x, points[i - 1].y, 0);
			}
			ribbons[i].addVertex(drawPoint);
			zSpeed = glm::distance(drawPoint, prevDrawPoint) * 2;
		}
	}
	


	for (int i = 0; i < ribbons.size(); i++)
	{
		for (int j = 0; j < ribbons[i].size(); j++)
		{
			ribbons[i][j].z -= zSpeed; // push z back
		}
	}

	// delete old ribbons
	for (auto &ribbon : ribbons) {
		if (ribbon.size() > 80) {
			ribbon.removeVertex(0);
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw(){

	// draw the ribbons
	for (int i = 0; i < ribbons.size(); i++)
	{
		ofColor color = ofColor::fromHsb(0, 255, 200); 
		for (int j = 1; j < ribbons[i].size(); j++)
		{
			// draw ribbon segments in rainbow hues
			// color.setHue(ofRandom(0, 255));
			color.setHue(ofMap(j, 0, ribbons[i].size(), 0, 255));
			ofSetColor(color);

			glm::vec3 pt1 = ribbons[i][j - 1];
			glm::vec3 pt2 = ribbons[i][j];

			ofDrawLine(pt1, pt2); // draw line from prev pt to current pt
		}
	}

	ofSetColor(255);
	string info;
	info += "Listening on: " + ofToString(PORT) + "\n";
	info += "Ribbons.size(): " + ofToString(ribbons.size()) + "\n";
	info += "Ribbons[0].size(): " + ofToString(ribbons[0].size()) + "\n";
	info += "Program Running Time" + ofToString(programRunningTime) + "\n";
	info += "Last Face Found Time" + ofToString(lastFaceFoundTime) + "\n";
	info += "Last Face Lost Time" + ofToString(lastFaceLostTime) + "\n";
	info += "Face is found: " + ofToString(found) + "\n\n\n";
	info += "[NOTICE] Be sure to open the \"raw\" in FaceOSC\n";
	ofDrawBitmapString(info, 20, 20);

	string author;
	author += "Junkai Man\n";
	author += "Face Artist\n";
	author += "MEDIART 206\n";
	ofDrawBitmapStringHighlight(author, ofGetWidth() / 2 -50, ofGetHeight() / 2 + 300);


	if (found) {
		drawFacePoints();
		drawFacePolygons();
	}
}


//--------------------------------------------------------------
void ofApp::drawFacePoints() {
	ofFill();
	for (int i = 0; i < points.size(); i++) {
		ofSetColor(100);
		ofDrawCircle(points[i], 8);
	}
}

//--------------------------------------------------------------
void ofApp::drawFacePolygons() {
	ofNoFill();
	ofSetColor(255);

	// Face outline
	ofBeginShape();
	for (int i = 0; i < 17; i++) {
		ofVertex(points[i].x, points[i].y);
	}
	for (int i = 26; i > 16; i--) {
		ofVertex(points[i].x, points[i].y);
	}
	ofEndShape(OF_CLOSE);

	// Eyes
	ofBeginShape();
	for (int i = 36; i < 42; i++) {
		ofVertex(points[i].x, points[i].y);
	}
	ofEndShape(OF_CLOSE);
	ofBeginShape();
	for (int i = 42; i < 48; i++) {
		ofVertex(points[i].x, points[i].y);
	}
	ofEndShape(OF_CLOSE);

	// Upper lip
	ofBeginShape();
	for (int i = 48; i < 55; i++) {
		ofVertex(points[i].x, points[i].y);
	}
	for (int i = 62; i > 59; i--) {
		ofVertex(points[i].x, points[i].y);
	}
	ofEndShape(OF_CLOSE);

	// Lower lip
	ofBeginShape();
	for (int i = 54; i < 60; i += 2) {
		ofVertex(points[i].x, points[i].y);
	}
	ofVertex(points[48].x, points[48].y);
	for (int i = 65; i > 62; i--) {
		ofVertex(points[i].x, points[i].y);
	}
	ofEndShape(OF_CLOSE);

	// Nose bridge
	ofBeginShape();
	for (int i = 27; i < 31; i++) {
		ofVertex(points[i].x, points[i].y);
	}
	ofEndShape();

	// Nose bottom
	ofBeginShape();
	for (int i = 31; i < 36; i++) {
		ofVertex(points[i].x, points[i].y);
	}
	ofEndShape();
}