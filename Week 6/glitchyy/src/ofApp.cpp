#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofBackground(0);

	camW = 640;
	camH = 480;

	webcam.setup(camW, camH);
	
	// Split to three chanels
	redImg.allocate(camW, camH, OF_IMAGE_COLOR);
	greenImg.allocate(camW, camH, OF_IMAGE_COLOR);
	blueImg.allocate(camW, camH, OF_IMAGE_COLOR);

	gui.setup();
	gui.add(invert.setup("Invert", false));
	gui.add(noiseScale.setup("NoiseScale", 2, 0, 20));
	gui.add(amplitude.setup("Amplitude", 2, 0, 20));
	gui.add(distortion.setup("Distortion", 2, 0, 20));

}

//--------------------------------------------------------------
void ofApp::update(){
	time = ofGetElapsedTimef();
	webcam.update();

	if (webcam.isFrameNew()) {
		for (int y = 0; y < webcam.getHeight(); y++) {
			for (int x = 0; x < webcam.getWidth(); x++) {
				ofColor color = webcam.getPixels().getColor(x, y);

				// Reference: Wave Distortion Effect
				// https://clab.concordia.ca/openframeworks-tutorial-part-i-wave-distortion-effect-2/

				float noise = ofNoise(time + y * 0.01) * noiseScale;
				float noiseAmp = noise * amplitude;
				float waveform = sin((y * 20) + time * 200);
				float wave = (waveform + distortion) * noiseAmp;

				int xWave = x + wave;

				// in case out of boundary
				if (xWave < 0) {
					xWave = 0;
				}
				if (xWave > webcam.getWidth()) {
					xWave = webcam.getWidth();
				}
				ofColor waveColor = webcam.getPixels().getColor(xWave, y);

				if (invert) {
					waveColor.r = 255 - waveColor.r;
					waveColor.g = 255 - waveColor.g;
					waveColor.b = 255 - waveColor.b;
				}

				redImg.setColor(x, y, ofColor(waveColor.r, 0, 0));
				greenImg.setColor(x, y, ofColor(0, waveColor.g, 0));
				blueImg.setColor(x, y, ofColor(0, 0, waveColor.b));
			
			}
		}
	}
	redImg.update();
	greenImg.update();
	blueImg.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

	// draw images and rectangles with center as origin
	ofSetRectMode(OF_RECTMODE_CENTER);
	// draw using "add" overlay blending effect
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	glm::vec2 center = ofGetWindowSize() * 0.5;
	glm::vec2 offset;
	float amplitude_mappedToPi = ofMap(amplitude, 0, 50, 0, 4*PI);
	offset.x = cos(amplitude_mappedToPi * time + ofRandom(-1, 1)) * 5;
	offset.y = sin(amplitude_mappedToPi * time + ofRandom(-1, 1)) * 5;

	redImg.draw(center + offset);
	greenImg.draw(center);
	blueImg.draw(center - offset);

	// return to default alpha blending and rectangle draw mode
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofSetRectMode(OF_RECTMODE_CORNER);

	gui.draw();

	string info;
	info += "Glitchyy\n";
	info += "Junkai Man\n";
	info += "MEDIART 206";
	ofDrawBitmapStringHighlight(info, center.x - 50, center.y + 200);
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
