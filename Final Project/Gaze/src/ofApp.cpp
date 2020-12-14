#include "ofApp.h"
#include "ofMath.h"

// NOTICE: RUN THIS PROGRAM BEFORE RUNNING THE FACEOSC

/*************************************************
 *            G A Z E - Junkai Man               *
 *  ________  ________  ________  _______        *
 * |\   ____\|\   __  \|\_____  \|\  ___ \       *
 * \ \  \___|\ \  \|\  \\|___/  /\ \   __/|      *
 *  \ \  \  __\ \   __  \   /  / /\ \  \_|/__    *
 *   \ \  \|\  \ \  \ \  \ /  /_/__\ \  \_|\ \   *
 *    \ \_______\ \__\ \__\\________\ \_______\  *
 *     \|_______|\|__|\|__|\|_______|\|_______|  *
 *												 *
 *     Media Art 206 - Computer Graphics         *                        
 *          Duke Kunshan University				 *
 *												 *
 *************************************************/

int PORT = 8338;
float ballRadius = 300;
float noiseFreq = 1.0;

 /*
  * OSC Data Example:
  * found: 1
  * pose
  *	  scale: 3.67838
  *	  position: 310.947, 235.929
  *	  orientation: 0.438422, -0.0821559, 0.141841
  * gesture
  * 	  mouth: 13.9134 1.72285
  *	  eye: 3.68059 3.70651
  *	  eyebrow: 8.19522 8.18737
  *	  jaw: 11.7356
  *	  nostrils: 9.68478
  */

//--------------------------------------------------------------
void ofApp::setup(){
	oscReceiver.setup(PORT);
	bgm.load("bgm.mp3");

	// Set up box, ball, camera, texture
	box.set(2000);
	box.setPosition(0, 0, 0);
	ball.set(ballRadius, 80);
	ball.setPosition(0, 0, 0);
	cam.setPosition(glm::vec3(0,0,890));
	textureImg.load("glitch1.jpg");
	box.mapTexCoordsFromTexture(textureImg.getTexture());

	// Set up lights
	light1.setPointLight();
	light1.setAttenuation(0.5);
	light1.setPosition(1500, 0, 0);
	light1.lookAt(glm::vec3(0, 0, 0));

	light2.setPointLight();
	light2.setAttenuation(0.5);
	light2.setPosition(-1500, 0, 0);
	light2.lookAt(glm::vec3(0, 0, 0));

	areaLight1.setAreaLight(10, 10);
	areaLight1.setPosition(glm::vec3(0, 0 , 0));
	areaLight1.setAmbientColor(ofColor::white);

	// Calculate initial camDistance
	float camX = cam.getPosition().x;
	float camY = cam.getPosition().y;
	float camZ = cam.getPosition().z;
	camDistance = pow(camX, 2) + pow(camY, 2) + pow(camZ, 2);
}

//--------------------------------------------------------------
void ofApp::update(){
	programRunningTime =  ofGetElapsedTimef();

	// Geting OSC data
	while (oscReceiver.hasWaitingMessages()) {
		
		ofxOscMessage m;
		oscReceiver.getNextMessage(&m);

		if (m.getAddress() == "/found") {
			if (!found && m.getArgAsInt32(0) == 1) {
				lastFaceFoundTime = programRunningTime;
			}
			if (found && m.getArgAsInt32(0) == 0) {
				lastFaceLostTime = programRunningTime;
			}
			found = (bool)m.getArgAsInt32(0);
		}

		if (m.getAddress() == "/pose/position") {
			posePositionX = m.getArgAsFloat(0);
			posePositionY = m.getArgAsFloat(1);
		}

		if (m.getAddress() == "/pose/scale") {
			poseScale = m.getArgAsFloat(0);
		}

		if (m.getAddress() == "/pose/orientation") {
			poseOrientationX = m.getArgAsFloat(0);
			poseOrientationY = m.getArgAsFloat(1);
			poseOrientationZ = m.getArgAsFloat(2);
		}
		
		if (m.getAddress() == "/gesture/mouth/width") {
			gestureMouthWidth = m.getArgAsFloat(0);
		}

		if (m.getAddress() == "/gesture/mouth/height") {
			gestureMouthHeight = m.getArgAsFloat(0);
		}

		if (m.getAddress() == "/gesture/eyebrow/left") {
			gestureEyebrowLeft = m.getArgAsFloat(0);
		}

		if (m.getAddress() == "/gesture/eyebrow/right") {
			gestureEyebrowRight = m.getArgAsFloat(0);
		}

		if (m.getAddress() == "/gesture/eye/left") {
			gestureEyeLeft = m.getArgAsFloat(0);
		}

		if (m.getAddress() == "/gesture/eye/right") {
			gestureEyeRight = m.getArgAsFloat(0);
		}

		if (m.getAddress() == "/gesture/jaw") {
			gestureJaw = m.getArgAsFloat(0);
		}
		
		if (m.getAddress() == "/gesture/nostrils") {
			gestureNostrills = m.getArgAsFloat(0);
		}

		if (m.getAddress() == "/raw") {

		}
	}

	// Update camera
	float camX, camY, camZ;
	camX = ofMap(posePositionX, 100, 560, 600, -600, true);
	camY = ofMap(posePositionY, 100, 380, 600, -600, true);
	camZ = sqrt(camDistance - pow(camX, 2) - pow(camY, 2));
	cam.setPosition(camX, camY, camZ);
	cam.lookAt(glm::vec3(0, 0, 0));

	// Set transition animation
	float disappearTime = 2;
	float showupTime = 8;
	
	if (lastFaceFoundTime <= lastFaceLostTime && programRunningTime - lastFaceLostTime > disappearTime) {
		faceOnScreen = false;
		faceOnScreenTime = 0;

		// Randomize the Background Graphic and Light Color
		string filename = "glitch" + ofToString(int(ofRandom(1, 6))) + ".jpg";
		textureImg.load(filename);
		light1.setDiffuseColor(ofColor(ofRandom(0,255), ofRandom(0,255), ofRandom(0,255)));
		light2.setDiffuseColor(ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)));
	}
	else {
		faceOnScreen = true;
		faceOnScreenTime += 1 / ofGetFrameRate();
	}

	// Update the transition animation
	if (lastFaceFoundTime <= lastFaceLostTime) {
		coverAlpha = ofMap((programRunningTime - lastFaceLostTime) * 0.1, 0, disappearTime, coverAlpha, 255, true);
	}
	else {
		coverAlpha = ofMap(faceOnScreenTime * 0.1, 0, showupTime, coverAlpha, 0, true);
	}
	

	// Change the shape of ball
	float eyeCloseSize = 2.8;
	if (faceOnScreenTime < 0.1) {
		noiseFreq = 1.0;
	}

	// This segement is referred to the noisy_sphere example in Week4
	if (gestureEyeLeft < eyeCloseSize || gestureEyeRight < eyeCloseSize) {
		noiseFreq += 0.001;
		for (int v = 0; v < ball.getMesh().getNumVertices(); v++)
		{
			glm::vec3 vertex = ball.getMesh().getVertex(v);

			float length = glm::length(vertex);
			if (length > 0) {

				glm::vec3 norm = vertex / length;
				float noise = ofSignedNoise(glm::vec3(programRunningTime* .5) + norm * noiseFreq);
				vertex = norm * (ballRadius + noise * 50);
				ball.getMesh().setVertex(v, vertex);
			}
		}
	}

	// Change the shape of box
	for (int v = 0; v < box.getMesh().getNumVertices(); v++) {
		glm::vec3 vertex = box.getMesh().getVertex(v);
		float length = glm::length(vertex);
		if (length > 0) {
			glm::vec3 norm = vertex / length;
			float noise = ofSignedNoise(glm::vec3(programRunningTime* .5) + norm * noiseFreq);
			// 0 - 1
			vertex = norm * (2000 + noise * 300);

			box.getMesh().setVertex(v, vertex);
		}
	}

	// Rotate the ball
	ofVec3f rot;
	rot.x = sin(programRunningTime * .1);             // rotate around X axis
	rot.y = 1.;										  // rotate around Y axis
	rot.z = sin(programRunningTime * .1 + 1000);      // rotate around Z axis
	ball.rotateDeg(.1, rot);

	// Play background Music
	if (!faceOnScreen) {
		bgm.play();
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	// Debug info
	string info;
	info += "Program Running Time" + ofToString(programRunningTime) + "\n";
	info += "Last Face Found Time" + ofToString(lastFaceFoundTime) + "\n";
	info += "Last Face Lost Time" + ofToString(lastFaceLostTime) + "\n";
	info += "Face is found: " + ofToString(found) + "\n";
	info += "poseScale: " + ofToString(poseScale) + "\n";
	info += "posePositionX: " + ofToString(posePositionX) + "\n";
	info += "posePositionY: " + ofToString(posePositionY) + "\n";
	info += "poseOrientationX: " + ofToString(poseOrientationX) + "\n";
	info += "poseOrientationY: " + ofToString(poseOrientationY) + "\n";
	info += "poseOrientationZ: " + ofToString(poseOrientationZ) + "\n";
	info += "gestureMouthWidth: " + ofToString(gestureMouthWidth) + "\n";
	info += "gestureMouthHeight: " + ofToString(gestureMouthHeight) + "\n";
	info += "gestureEyeLeft: " + ofToString(gestureEyeLeft) + "\n";
	info += "gestureEyeRight: " + ofToString(gestureEyeRight) + "\n";
	info += "gestureEyebrowLeft: " + ofToString(gestureEyebrowLeft) + "\n";
	info += "gestureEyebrowRight: " + ofToString(gestureEyebrowRight) + "\n";
	info += "gestureJaw: " + ofToString(gestureJaw) + "\n";
	info += "gestureNostrills: " + ofToString(gestureNostrills) + "\n";
	info += "\n";
	info += "camPositionX: " + ofToString(cam.getPosition().x) + "\n";
	info += "camPositionY: " + ofToString(cam.getPosition().y) + "\n";
	info += "camPositionZ: " + ofToString(cam.getPosition().z) + "\n";
	info += "\n";

	cam.begin();
	
	// Enable light
	ofEnableDepthTest();
	light1.enable();
	light2.enable();

	areaLight1.enable();
	ofFill();
	//ofNoFill();
	ofSetColor(255);
	textureImg.bind();
	box.draw();
	textureImg.unbind();
	areaLight1.disable();

	ball.draw();

	ofSetColor(255);
	//box.drawWireframe();
	ball.drawWireframe();
	ofSetColor(255);

	// Disable light
	light1.disable();
	light2.disable();
	ofDisableDepthTest();
	cam.end();

	ofSetColor(0, coverAlpha);
	ofDrawRectangle(0, 0, 0, ofGetWidth(), ofGetHeight());
	
	if (faceOnScreen) {
		ofSetColor(255);
		ofDrawBitmapString(info, 20, 20);

		ofDrawBitmapStringHighlight("BGM: No Save Point - Yankee and the Brave (from Cyberpunk 2077)", 10, ofGetHeight() - 10, ofColor::black, ofColor::white);
	}
	else {
	}

}
