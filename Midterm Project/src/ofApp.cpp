#include "ofApp.h"
#include "ofxBox2d.h";
#include "ofxRestartOFApp.h"
extern string game_state;
ofTrueTypeFont font;
//--------------------------------------------------------------
void ofApp::setup(){
	// setting up OpenFrameworks
	ofBackgroundHex(0xfdefc2);
	ofSetVerticalSync(true);

	// setting up box2d
	box2d.init();
	box2d.setGravity(0, 40);
	box2d.createGround();
	box2d.createBounds();
	box2d.setFPS(60.0);

	// init variables
	game_state = "ready";  // ready, game, finish, dead
	lifeNum = 1;

	// setting up the Map
	map = Map();
	map.setup(box2d);
	map_dangers = map.dangers;
	finishBlocks = map.finishBlocks;

	// setting up the XmlFile
	ofDirectory dir("./");
	dir.allowExt("xml");
	int fileNums = dir.listDir();
	cout << "file Nums: " << fileNums << endl;
	for (int i = 0; i < fileNums; i++) {
		cout << dir.getName(i) << endl;
	}
	if (fileNums > 0) {
		lifeNum = fileNums + 1;
	}
	xmlFile.appendChild("lifeNum").set(lifeNum);
	
	// setting up previous_selves
	for (int i = 0; i < fileNums; i++) {
		Player previous_self;
		previous_selves.push_back(previous_self);
	}

	for (int i = 0; i < previous_selves.size(); i++) {
		auto &previous_self = previous_selves[i];
		previous_self.setup(box2d);
		previous_self.initDead(box2d, ofToString(i+1) +".xml");
	}

	// setting up current_self
	current_self = Player();
	current_self.setup(box2d);
	current_self.initLive(box2d, map);

	// setting up the font
	font.load("IndieFlower.ttf", 30);

}

//--------------------------------------------------------------
void ofApp::update() {
	if (game_state == "ready") {
		
	}

	else if (game_state == "game") {
		// reset the time
		liveTime = ofGetElapsedTimeMillis();

		map.update();
		current_self.update();
		for (auto &previous_self : previous_selves) {
			previous_self.update();
		}

		box2d.update();

		if (current_self.rects[0]->body->GetContactList() != NULL) {
			if (current_self.rects[0]->body->GetContactList()->contact->GetFixtureA()
				== finishBlocks[0]->body->GetFixtureList()) {
				game_state = "finish";
				//cout << "finish!!!" << endl;
			}

			for (auto map_danger : map_dangers) {
				if (current_self.rects[0]->body->GetContactList()->contact->GetFixtureA()
					== map_danger->body->GetFixtureList()) {
					game_state = "dead";
					//cout << "now touch the danger" << endl;
				}
			}
		}
	}

	else if (game_state == "finish") {

	}

	else { // game_state == "dead"
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	if (game_state == "ready") {
		ofSetColor(0);
		font.drawString("Circle of Life", 30, 50);

		string info = "MEDIART 206 - Computer Graphics \n";
		info += "Junkai Man";
		font.drawString(info, 30, 150);

		font.drawString("Press any key to start", ofGetWidth()/2 -180, ofGetHeight()-40);
		if (ofGetKeyPressed()) {
			ofResetElapsedTimeCounter();
			game_state = "game";
		}
	}
	else if (game_state == "game") {
		map.draw();
		current_self.draw();
		for (auto &previous_self : previous_selves) {
			previous_self.draw();
		}

		ofSetColor(0);
		string info;
		info += "Game State: " + ofToString(game_state) + "\n";
		info += "Life Num: " + ofToString(lifeNum) + "\n";
		info += "Live Time: " + ofToString(int(liveTime) / 1000) + "\n";
		info += "WSAD to move, use 0 to suicide this life\n";
		info += "R to restart the game";
		ofDrawBitmapString(info, 70, 40);
	}
	else if (game_state == "finish") {
		font.drawString("You finished it!\n Congrats!", 570, 400);
	}
	else { // if (game_state == "dead")
		font.drawString("You are dead.\nSee you next life!", 570, 400);
		font.drawString("Press R to restart, press Space to continue.", 360, 600);
	}
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (game_state == "ready") {
		
	}
	else if (game_state == "game") {
		if ((key == 'a' || key == 'A') && !current_self.leftIsPressed) {
			current_self.leftIsPressed = true;
			auto data = xmlFile.appendChild("data");
			data.appendAttribute("liveTime").set(liveTime);
			data.appendAttribute("status").set("leftIsPressed");
		};
		if ((key == 'd' || key == 'D') && !current_self.rightIsPressed) {
			current_self.rightIsPressed = true;
			auto data = xmlFile.appendChild("data");
			data.appendAttribute("liveTime").set(liveTime);
			data.appendAttribute("status").set("rightIsPressed");
		};
		if ((key == 'w' || key == 'W') && !current_self.jumpIsPressed) {
			current_self.jumpIsPressed = true;
			auto data = xmlFile.appendChild("data");
			data.appendAttribute("liveTime").set(liveTime);
			data.appendAttribute("status").set("jumpIsPressed");
		};
		if (key == '0') {
			string filename = ofToString(lifeNum) + ".xml";
			xmlFile.save(filename);
			// push it to previous self
			game_state = "stop";
			restartApp.initRestart(0, false);
		}
		if (key == 'r' || key == 'R') {
			ofDirectory dir("./");
			int fileNum = dir.listDir();
			for (int i = 0; i < fileNum; i++) {
				ofFile file(ofToString(i + 1) + ".xml");
				file.remove();
			}
			restartApp.initRestart(0, false);
		}
	}
		
	else if (game_state == "finish") {
	}

	else {
		if (key == 'r' || key == 'R') {
			ofDirectory dir("./");
			int fileNum = dir.listDir();
			for (int i = 0; i < fileNum; i++) {
				ofFile file(ofToString(i + 1) + ".xml");
				file.remove();
			}
			restartApp.initRestart(0, false);
		}

		if (key == ' ') {
			string filename = ofToString(lifeNum) + ".xml";
			xmlFile.save(filename);
			// push it to previous self
			game_state = "stop";
			restartApp.initRestart(0, false);
		}

	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if ((key == 'a' || key == 'A') && current_self.leftIsPressed) {
		current_self.leftIsPressed = false;
		auto data = xmlFile.appendChild("data");
		data.appendAttribute("liveTime").set(liveTime);
		data.appendAttribute("status").set("leftIsReleased");
	};

	if ((key == 'd' || key == 'D') && current_self.rightIsPressed) {
		current_self.rightIsPressed = false;
		auto data = xmlFile.appendChild("data");
		data.appendAttribute("liveTime").set(liveTime);
		data.appendAttribute("status").set("rightIsReleased");
	};

	if ((key == 'w' || key == 'W') && current_self.jumpIsPressed) {
		current_self.jumpIsPressed = false;
		auto data = xmlFile.appendChild("data");
		data.appendAttribute("liveTime").set(liveTime);
		data.appendAttribute("status").set("jumpIsReleased");
	};

	//if ((key == ' ') && !current_self.shootIsReleased) {
	//	current_self.shootIsReleased = true;
	//	auto data = xmlFile.appendChild("data");
	//	data.appendAttribute("liveTime").set(liveTime);
	//	data.appendAttribute("status").set("shootIsPressed");
	//};

}

void ofApp::mouseMoved(int x, int y ){}
void ofApp::mouseDragged(int x, int y, int button){}
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::mouseEntered(int x, int y){}
void ofApp::mouseExited(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){}
