#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

class ofApp : public ofBaseApp{
	ofxOscReceiver oscReceiver;
	public:
		void drawFacePoints();
		void drawFacePolygons();

		vector<ofPolyline> ribbons;

		bool bMakingRibbon;
		float zSpeed;


		bool found = false;
		float programRunningTime;
		float lastFaceFoundTime;
		float lastFaceLostTime;
		float faceFoundElaspedTime;

		float poseScale;
		float posePositionX;
		float posePositionY;
		float poseOrientationX;
		float poseOrientationY;
		float poseOrientationZ;
		float gestureMouthWidth;
		float gestureMouthHeight;
		float gestureEyeLeft;
		float gestureEyeRight;
		float gestureEyebrowLeft;
		float gestureEyebrowRight;
		float gestureJaw;
		float gestureNostrills;
		vector<glm::vec2> points;



		void setup();
		void update();
		void draw();
		
};
