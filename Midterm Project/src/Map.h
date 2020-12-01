#pragma once
#include "ofxBox2d.h"
#include "ofMain.h"
#include "ofXml.h"

class Map {
public:
	Map();
	ofXml mapFile;
	void setup(ofxBox2d &box2d);
	void update();
	void draw();
	
	vector<shared_ptr<ofxBox2dRect>> rects;
	vector<shared_ptr<ofxBox2dRect>> dangers;
	vector<shared_ptr<ofxBox2dRect>> finishBlocks;

	vector<shared_ptr<ofxBox2dCircle>> circles;
	vector<shared_ptr<ofxBox2dEdge>> edges;



};