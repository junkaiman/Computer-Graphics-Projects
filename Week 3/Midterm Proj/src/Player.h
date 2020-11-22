#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"
#include "ofXml.h"
#include "Map.h"

class Player {
public:
	Player();
	ofXml xmlFile;
	ofXml currentChild;

	bool leftIsPressed;
	bool rightIsPressed;
	bool jumpIsPressed;
	bool shootIsReleased;

	bool isDead;
	bool canJump;
	float width, height, speed;
	float liveTime;
	glm::vec2 pos, vel; 

	void setup(ofxBox2d &box2d);

	void initLive(ofxBox2d &box2d, Map &map);
	void initDead(ofxBox2d &box2d, string xmlFilename);

	void toLeft();
	void toRight();
	void toJump();
	void draw();
	void update();
	
	ofxBox2d world;
	vector<shared_ptr<ofxBox2dRect>> rects;
	shared_ptr<ofxBox2dRect> body;
	

};