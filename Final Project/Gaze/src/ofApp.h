#pragma once

#include "ofMain.h"
#include "ofxOsc.h"


class ofApp : public ofBaseApp{
	ofxOscReceiver oscReceiver;
	ofImage textureImg;
	ofSoundPlayer bgm;
	ofLight light1;
	ofLight light2;
	ofLight areaLight1;

	public:
		bool found = false;
		bool faceOnScreen = false;
		float faceOnScreenTime = 0;
		float coverAlpha = 255;
		float camDistance;
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
		
		ofBoxPrimitive box;
		ofSpherePrimitive ball;
		ofEasyCam cam;



		void setup();
		void update();
		void draw();
	
};
