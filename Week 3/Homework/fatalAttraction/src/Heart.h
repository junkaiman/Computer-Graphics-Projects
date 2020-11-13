#pragma once
#include "ofMain.h"
class Heart {
public:

	glm::vec2 pos, vel, acc;
	ofImage heartImg;
	int imgSize = 16;
	float size, mass;
	ofColor color;
	void setup(glm::vec2 position, float s, ofColor c) {
		pos = position;
		size = s;
		color = c;
		mass = 10 * size;
		heartImg.load("heart.png");
		heartImg.setImageType(OF_IMAGE_COLOR_ALPHA);
	};
	
	void update() {
		if (pos.x > ofGetWidth()) {
			vel.x *= -1;
		}

		if (pos.y > ofGetHeight()) {
			vel.y *= -1;
		}

		vel += acc;
		pos += vel;
		acc *= 0;
	};

	void draw() {
		ofSetColor(color);
		heartImg.draw(pos, imgSize * size, imgSize * size);


		// The following code used function to draw heart,
		// but the performance is poor.

		//ofFill();
		//ofSetColor(color);
		//ofSetPolyMode(OF_POLY_WINDING_NONZERO);
		//ofBeginShape();

		//float i = 0;
		//while (i < TWO_PI) { // make a heart
		//	float r = (2 - 2 * sin(i) + sin(i)*sqrt(abs(cos(i))) / (sin(i) + 1.4)) * - size;
		//	float x = pos.x + cos(i) * r;
		//	float y = pos.y + sin(i) * r;
		//	ofVertex(ofVec3f(x, y, 0));
		//	i += 0.005*HALF_PI*0.5;
		//}
		//ofEndShape();
	};

	void applyForce(glm::vec2 force) {
		acc += force / mass;
	}

	void attract(Heart anotherHeart) {
		
	}
};