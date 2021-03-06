#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "Player.h"
#include "Map.h"
#include "ofxRestartOFApp.h"

class ofApp : public ofBaseApp{

	public:
		int lifeNum;
		ofXml xmlFile;
		float liveTime;
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
		
		ofxBox2d	box2d;
		Map map;
		string		game_state;

		Player current_self;
		vector<Player> previous_selves;

		vector<shared_ptr<ofxBox2dRect>> map_dangers;
		vector<shared_ptr<ofxBox2dRect>> finishBlocks;

	ofxRestartOFApp restartApp;

};
