#include "ofApp.h"
int snowNum = 200;
/*
 * Junkai Man (jm687)
 * Mediart 206 | Week5 Homework
 *  *  *   *   ** ** *   **     *   *  *
 *    * *  Winter is Coming *    * *  *
 *  *  *   **    *   *   ** **    *  * * 
 * 3D Models are downloaded from below:
 * White Walker: https://cults3d.com/en/3d-model/art/white-walker
 * Snowflake: https://cults3d.com/en/3d-model/home/flocon-de-neige-robinwood87cnc-3
 */


//--------------------------------------------------------------
void ofApp::setup(){
	/*
	 * I was thinking about replacing the face of white walker to Camera Video. However,
	 * I haven't figured it out how to wrap the video texture on only part of the 3D model.
	 */

	//vid.listDevices();    // print your webcams to the console
	//vid.setup(640, 480);    // or choose cam #0 using: vid.setup(0, 640, 480)
	
	/*
	 * I have the idea of playing music in the background, but it runs really slow.
	 * And I don't know if it is caused by the low performance of my laptop.
	 * The following lines can be uncommented if the hardware is good enough.
	 */

	//soundPlayer.load("clip.mp3");
	//soundPlayer.setLoop(true);
	//soundPlayer.play();

	ofSetVerticalSync(false);
	cam.setDistance(160);
	whiteWalker.loadModel("White_walker.obj");
	ofSetSmoothLighting(true);

	for (int i = 0; i < snowNum; i++) {
		ofxAssimpModelLoader snow;
		snows.push_back(snow);
	}

	for (int i = 0; i < snowNum; i++) {
		snows[i].loadModel("snow.stl");
		snows[i].setScale(0.03, 0.03, 0.03);
		snows[i].setPosition(ofRandom(-200, 200), ofRandom(-200, 200), ofRandom(-200, 200));
	}

	whiteWalker.setScale(0.3, 0.3, 0.3);
	
	staticLight.setSpotlight();
	staticLight.setPosition(80, 80, 80);
	staticLight.lookAt(glm::vec3(0, 0, 0));
	staticLight.setDiffuseColor(ofColor::white);
	staticLight.setAttenuation(.5);

	// setup spot light

	spotlight1.setSpotlight();
	spotlight2.setSpotlight();
	spotlight1.setAttenuation(0.5);
	spotlight2.setAttenuation(0.5);
	spotlight1.setPosition(100, 0, 0);
	spotlight2.setPosition(0, 0, 100);
	
	spotlight1.setDiffuseColor(ofColor::blue);
	spotlight2.setDiffuseColor(ofColor::red);

	// GUI
	gui.setup();
	gui.add(posX.set("positionX", -57.6, -360.0, 360.0));
	gui.add(posY.set("positionY", -75.6, -360.0, 360.0));
	gui.add(posZ.set("positionZ", -43.2, -360.0, 360.0));
	gui.add(rotX.set("rotationX", 178.2, 0.0, 360.0));
	gui.add(rotY.set("rotationY", 198, 0.0, 360.0));
	gui.add(rotZ.set("rotationZ", 0, 0.0, 360.0));

}

//--------------------------------------------------------------
void ofApp::update(){
	float time = ofGetElapsedTimef();

	//vid.update();
	cam.lookAt(glm::vec3(0, 0, 0));
	cam.rotateAroundDeg(1, glm::vec3(1, 0.8, 0.7), glm::vec3(10, 10, 10));

	ofVec3f spot1Pos = spotlight1.getPosition();
	spot1Pos.x = cos(-time) * 350;
	spot1Pos.y = sin(time) * 250;
	spot1Pos.z = sin(-time) * 450;
	spotlight1.setPosition(spot1Pos);

	ofVec3f spot2Pos = spotlight2.getPosition();
	spot2Pos.x = cos(time) * 50;
	spot2Pos.y = sin(time) * 250;
	spot2Pos.z = cos(time) * 550;
	spotlight2.setPosition(spot2Pos);

	for (int i = 0; i < snowNum; i++) {
		ofVec3f snowPos = snows[i].getPosition();
		snowPos.x += cos(1 * time) * ofRandom(-0.3, 3);
		snowPos.y += sin(0.8 * time) * ofRandom(-0.3, 3);
		snowPos.z += sin(1.4 * time) * ofRandom(-0.3, 3);
		snows[i].setPosition(snowPos.x, snowPos.y, snowPos.z);
		snows[i].setRotation(0, snowPos.x, snowPos.x, 0, 0);
		snows[i].setRotation(1, snowPos.y, 0, snowPos.y, 0);
		snows[i].setRotation(2, snowPos.z, 0, 0, snowPos.z);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofEnableDepthTest();

	cam.begin();
	ofNoFill();
	ofDrawSphere(300);
	ofFill();

	ofEnableLighting();		// turn on lighting globally
	ofEnableDepthTest();	// render objects in order of depth

	staticLight.enable();
	spotlight1.enable();
	spotlight2.enable();

	spotlight1.lookAt(glm::vec3(0, 0, 0));
	spotlight2.lookAt(glm::vec3(0, 0, 0));
	
	whiteWalker.setPosition(posX, posY, posZ);
	whiteWalker.setRotation(0, rotX, rotX, 0, 0);
	whiteWalker.setRotation(1, rotY, 0, rotY, 0);
	whiteWalker.setRotation(2, rotZ, 0, 0, rotZ);

	//vid.bind();
	
	for (auto& snow : snows) {
		snow.drawFaces();
	}

	whiteWalker.drawFaces();

	//vid.unbind();
	//whiteWalker.drawWireframe();
	//whiteWalker.drawVertices();

	staticLight.disable();
	spotlight1.disable();
	spotlight2.disable();

	ofDisableLighting();		// disable global lighting

	ofDrawAxis(30);			// draws our scene origin axes

	staticLight.draw();
	spotlight1.draw();			// visualize our lights
	spotlight2.draw();			// visualize our lights

	// visualize the 3d wireframes
	//ofSetColor(255, 100);		// add some alpha
	//whiteWalker.drawWireframe();		// visualize the sphere mesh
	//ofSetColor(255);
	
	cam.end();
	ofDisableDepthTest();
	gui.draw();

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
