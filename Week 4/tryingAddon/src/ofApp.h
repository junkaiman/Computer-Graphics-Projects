#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
class ofApp : public ofBaseApp{
	public:
		bool leftIsPressed;
		bool rightIsPressed;
		bool jumpIsPressed;
		bool shootIsReleased;
		int collisionTimes;
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		
		ofxBox2d									 box2d;
		vector		<ofPolyline>					 lines;
		vector		<shared_ptr<ofxBox2dCircle>>	 circles;
		vector		<shared_ptr<ofxBox2dRect>>		 boxes;
		vector      <shared_ptr<ofxBox2dBaseShape>>  shapes;
		vector		<shared_ptr<ofxBox2dEdge>>		 edges;

		void contactStart(ofxBox2dContactArgs &e);
		void contactEnd(ofxBox2dContactArgs &e);
};
