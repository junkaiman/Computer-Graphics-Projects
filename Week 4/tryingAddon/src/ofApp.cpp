#include "ofApp.h"
/*
 * In my midterm project, I am using a very convenient Addon ofxBox2D
 * as physics engine, so that I can get rid of the process of hard coding
 * physic system on my own with low efficiency and poor performance.
 *
 * The ofxBox2D contains many useful functions such as event listener,
 * edge detection, physics separation, etc.
 *
 * So my homework this time is basically a lab project playing with powerful
 * functions of ofxBox2D.
 */
//--------------------------------------------------------------
void ofApp::setup(){

	ofSetVerticalSync(true);
	ofBackgroundHex(0xfdefc2);

	box2d.init();
	box2d.enableEvents();
	
	box2d.createGround();
	box2d.createBounds();
	box2d.setGravity(0, 9);
	box2d.setFPS(60.0);
	box2d.registerGrabbing();

	ofAddListener(box2d.contactStartEvents, this, &ofApp::contactStart);
	ofAddListener(box2d.contactEndEvents, this, &ofApp::contactEnd);

	for (int i = 0; i < 10; i++) {
		auto circle = std::make_shared<ofxBox2dCircle>();
		circle->setPhysics(1, 0.5, 0.9);
		circle->setup(box2d.getWorld(), ofRandom(ofGetWidth()), ofRandom(ofGetHeight()), ofRandom(20, 40));
		circles.push_back(circle);
	}

	auto rect = std::make_shared<ofxBox2dRect>();
	rect->setPhysics(1, 0.5, 0.9);
	rect->setup(box2d.getWorld(), ofRandom(ofGetWidth()), ofRandom(ofGetHeight()), 40, 40);
	boxes.push_back(rect);

	collisionTimes = 0;
	leftIsPressed = false;
	rightIsPressed = false;
	jumpIsPressed = false;
	shootIsReleased = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	if ((int)ofRandom(0, 10) == 0) {
		auto c = make_shared<ofxBox2dCircle>();
		c->setPhysics(0.2, 0.2, 0.002);
		c->setup(box2d.getWorld(), ofRandom(40, 80), 20, ofRandom(3, 10));
		c->setVelocity(0, 15);
		circles.push_back(c);
	}

	if (circles.size() > 1000) {
		circles.pop_back();
	}

	box2d.update();

	glm::vec2 box_vel = boxes[0]->getVelocity();


	if (leftIsPressed && box_vel.x > -10) {
		boxes[0]->setVelocity(box_vel + glm::vec2(-3, 0));
	}
	if (box_vel.x < 10 && rightIsPressed) {
		boxes[0]->setVelocity(box_vel + glm::vec2(3, 0));
	}
	if (abs(box_vel.y) < 0.1 && jumpIsPressed) {
		boxes[0]->setVelocity(box_vel + glm::vec2(0, -5));
	}
	if (shootIsReleased) {
		
	}

}
void ofApp::draw(){
	for (auto &circle : circles) {
		ofSetColor(230, 111, 120);
		ofFill();
		circle->draw();
	}

	for (auto &box: boxes) {
		ofSetColor(230, 111, 120);
		ofFill();
		box->draw();
	}

	ofSetHexColor(0x444342);
	ofNoFill();
	for (auto &line : lines) {
		line.draw();
	}
	for (auto & edge : edges) {
		edge->draw();
	}

	string info;
	info += "Information Board:\n";
	info += "Balls amount count: " + ofToString(circles.size()) + "\n";
	info += "Collision times count: " + ofToString(collisionTimes) + "\n";
	info += "\n";
	info += "Drag the mouse to draw lines.\n";
	info += "Press C to clear the lines.\n";
	ofDrawBitmapString(info, 20, 30);

}


void ofApp::keyPressed(int key){
	if (key == 'c') {
		lines.clear();
		edges.clear();
	}

	if (key == 'a' || key == 'A') {
		leftIsPressed = true;
	}
	if (key == 'd' || key == 'D') {
		rightIsPressed = true;
	}
	if (key == 'w' || key == 'W') {
		jumpIsPressed = true;
	}


}
void ofApp::keyReleased(int key){
	if (key == 'a' || key == 'A') {
		leftIsPressed = false;
	}
	if (key == 'd' || key == 'D') {
		rightIsPressed = false;
	}
	if (key == 'w' || key == 'W') {
		jumpIsPressed = false;
	}
	if (key == ' ') {
		shootIsReleased = true;
	}

}
void ofApp::mouseMoved(int x, int y ){
}
void ofApp::mouseDragged(int x, int y, int button){
	lines.back().addVertex(x, y);
}
void ofApp::mousePressed(int x, int y, int button){
	lines.push_back(ofPolyline());
	lines.back().addVertex(x, y);
}
void ofApp::mouseReleased(int x, int y, int button){
	auto edge = make_shared<ofxBox2dEdge>();
	lines.back().simplify();

	for (int i = 0; i < lines.back().size(); i++) {
		edge->addVertex(lines.back()[i]);
	}

	// edge->setPhysics(1, .2, 1); 
	edge->create(box2d.getWorld());
	edges.push_back(edge);
}

void ofApp::contactStart(ofxBox2dContactArgs &e) {
	if (e.a != NULL && e.b != NULL) {
		collisionTimes++;
	}
}

void ofApp::contactEnd(ofxBox2dContactArgs &e) {
	if (e.a != NULL && e.b != NULL) {

	}
}