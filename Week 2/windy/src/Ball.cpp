#include "Ball.h"

// constructor
Ball::Ball() {

	// inside the constructor you initialize the object's variables

	// random radius between 10 and 50
	radius = ofRandom(10,50);
	mass = 3 / 4 * 3.14 * radius * radius * radius;
	fraction = 0.5;
	// random color
	float red	= ofRandom(0,255);
	float green	= ofRandom(0,255);		
	float blue	= ofRandom(0,255);
	color = ofColor(red, green, blue);

	// random position in window
	pos.x = ofRandom(radius, ofGetWidth()  - radius);
	pos.y = ofRandom(radius, ofGetHeight() - radius);

	// random x and y speeds/directions between -10 and 10
	/*dir.x = ofRandom(-10,10);
	dir.y = ofRandom(-10,10);*/
	dir.x = 0;
	dir.y = 0;
    
    
}

// update position, etc.
void Ball::update() {
    
	dir += acc;
	pos += dir;
	acc *= 0;

	// check for bounces at edges of window:

	// check left
	if (pos.x <= radius) {
		pos.x = radius;			// set the position back to the edge of window
		dir.x = - 0.7 * dir.x;		// and reverse direction
	}
	// check right
	else if (pos.x >= ofGetWidth() - radius) {
		pos.x = ofGetWidth() - radius;			// similar to above
		dir.x = - 0.7 * dir.x; // slow down
	}

	// check top and bottom
	if (pos.y <= radius) {
		pos.y = radius;
		dir.y = - 0.7* dir.y;
	}
	else if (pos.y >= ofGetHeight() - radius) {
		pos.y = ofGetHeight() - radius;
		dir.y = - 0.7 * dir.y;
	}
}


// draw the ball
void Ball::draw() {

	ofSetColor(color);				// set the GLOBAL color
	ofDrawCircle(pos, radius);		// and draw
}

// apply force (accumulative)
void Ball::applyForce(ofVec2f force) {
	ofVec2f f = force;
	f = force / mass;
	acc += f;

}

// jm687 - collide function from last homework
void Ball::collide() {
	
	dir *= -0.7;
	pos += dir;

}