#include "ofApp.h"
int init_redHeartNum = 80;
int init_blackHeartNum = 100;
int timeTotal = 300;
int timePassed;
int game_state = 0; // 0 - ready, 1 - game, 2 - gameover
glm::vec2 mousePos;

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(180);

	for (int i = 0; i < init_redHeartNum; i++) {
		float posX = ofRandom(ofGetWidth());
		float posY = ofRandom(ofGetHeight());
		float size = 2;
		ofColor color = ofColor(211, 0, 0);
		Heart tempHeart;
		tempHeart.setup(glm::vec2(posX, posY), size, color);
		red_hearts.push_back(tempHeart);
	}

	for (int i = 0; i < init_blackHeartNum; i++) {
		float posX = ofRandom(ofGetWidth());
		float posY = ofRandom(ofGetHeight());
		float size = 2.5;
		ofColor color = ofColor(0,0,0);
		Heart tempHeart;
		tempHeart.setup(glm::vec2(posX+7, posY+7), size, color);
		black_hearts.push_back(tempHeart);
	}
}

//--------------------------------------------------------------
void ofApp::update() {
	mousePos = glm::vec2(ofGetMouseX(), ofGetMouseY());

	if (game_state == 0) {
		if (ofGetKeyPressed()) {
			game_state = 1;
		}
	}

	else if (game_state == 1) {
		// for each red_heart
		timePassed = ofGetElapsedTimef();
		for (int i = 0; i < red_hearts.size(); i++) {
			bool willRemove = false;
			for (int j = 0; j < black_hearts.size(); j++) {
				// for each black heart
				glm::vec2 target = black_hearts[j].pos - red_hearts[i].pos;
				float distance = glm::length(target);

				if (distance != 0 && distance < 200) {
					glm::vec2 direction = target / distance;
					red_hearts[i].applyForce(0.3* direction);
				}

				if (ofGetMousePressed()) {
					if (glm::length(mousePos - (black_hearts[j].pos + black_hearts[j].size * 16 / 2)) < 10) {
						game_state = 2;
					}
				}

			}

			if (ofGetMousePressed()) {
				if (glm::length(mousePos - (red_hearts[i].pos + red_hearts[i].size * 16 / 2)) < 15) {
					willRemove = true;
				}
			}
			if (willRemove) {
				red_hearts.erase(red_hearts.begin() + i);
			}
			red_hearts[i].update();
		}
	}

	else if (game_state == 2) {
		if (ofGetKeyPressed()) {
			game_state = 0;
			red_hearts.clear();
			black_hearts.clear();
			this->setup();
		}
	}
	
	else {
		game_state = 0;
	}

	


}

//--------------------------------------------------------------
void ofApp::draw(){
	if (game_state == 0) {
		ofDrawBitmapString("ready to start", 10, 20);
		ofDrawBitmapString("FATAL ATTRACTION", 10, 50);
		ofDrawBitmapString("Description:\nLove is hide and seek.\nLove is hit and run.\n\nCollect as much red heart as possible in limited time.\n Don't touch those black hearts!", 10, 70);
		ofDrawBitmapString("Press any key to start.", 10, 500);
	}

	else if (game_state == 1) {
		ofBackground(180);
		ofDrawBitmapString("Red heart remain: " + ofToString(red_hearts.size()), 10, 20);
		ofDrawBitmapString("Time left: " + ofToString(timeTotal - timePassed), 10, 40);


		for (auto &heart : red_hearts) {
			heart.draw();
		}

		for (auto &heart : black_hearts) {
			heart.draw();
		}


		ofSetColor(0, 0, 0, 20);
		ofDrawCircle(mousePos, 15);
		ofSetColor(0, 0, 0);
	}

	else if (game_state == 2) {
		ofBackground(0);
		ofSetColor(255);
		ofDrawBitmapString("GAME OVER!!!", 10, 20);
		ofDrawBitmapString("FATAL ATTRACTION", 10, 50);
		ofDrawBitmapString("Description:\nLove is hide and seek.\nLove is hit and run.\n\nCollect as much red heart as possible in limited time.\nDon't touch those black hearts!\nDon't touch those black hearts!!!", 10, 70);
		ofDrawBitmapString("Press any key to restart.", 10, 400);
	}
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 0) {
	}
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
