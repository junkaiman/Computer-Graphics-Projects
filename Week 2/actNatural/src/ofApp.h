#pragma once

#include "ofMain.h"
class Mover {
public:
	void setup(float m, float x, float y, float h, float l, float a);
	void update(ofPoint target);
	void draw();
	void applyForce(ofPoint force);

	float mass;
	float length;
	float height;
	float angle;
	ofPoint pos;
	ofPoint vel;
	ofPoint acc;
};

class Magnet {
public:
	void setup(float x, float y);
	void update();
	void draw();

	ofPoint pos;
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		Mover mover;
		Magnet magnet;
};

