#include "Map.h"

Map::Map(){}

void Map::setup(ofxBox2d &box2d) {
	
	// borders
	auto borderLeft = std::make_shared<ofxBox2dRect>();
	auto borderRight = std::make_shared<ofxBox2dRect>();
	auto borderUp = std::make_shared<ofxBox2dRect>();
	auto borderDown = std::make_shared<ofxBox2dRect>();

	borderLeft->setup(box2d.getWorld(), ofGetWidth()/2 - 640, ofGetHeight()/2, 10, ofGetHeight());
	borderRight->setup(box2d.getWorld(), ofGetWidth()/2 + 640, ofGetHeight()/2, 10, ofGetHeight());
	borderUp->setup(box2d.getWorld(), ofGetWidth()/2, ofGetHeight()/2 - 430, ofGetWidth(), 10);
	borderDown->setup(box2d.getWorld(), ofGetWidth()/2, ofGetHeight()/2 + 430, ofGetWidth(), 10);
	
	borderLeft->setPhysics(0, 0, 0.1);
	borderRight->setPhysics(0, 0, 0.1);
	borderUp->setPhysics(0, 0, 0.1);
	borderDown->setPhysics(0, 0, 0.1);

	rects.push_back(borderLeft);
	rects.push_back(borderRight);
	rects.push_back(borderUp);
	rects.push_back(borderDown);

	auto wall0 = std::make_shared<ofxBox2dRect>();
	wall0->setup(box2d.getWorld(), ofGetWidth() / 2 - 90, ofGetHeight() / 2 - 300, ofGetWidth() - 300, 60);
	wall0->setPhysics(0, 0, 0.1);
	rects.push_back(wall0);

	auto wall1 = std::make_shared<ofxBox2dRect>();
	wall1->setup(box2d.getWorld(), ofGetWidth() / 2 + 560, ofGetHeight() / 2 - 195, 20, 470);
	wall1->setPhysics(0, 0, 0.1);
	rects.push_back(wall1);

	auto wall2 = std::make_shared<ofxBox2dRect>();
	wall2->setup(box2d.getWorld(), ofGetWidth() / 2 + 400, ofGetHeight() / 2 - 60, 300, 200);
	wall2->setPhysics(0, 0, 0.1);
	rects.push_back(wall2);

	auto wall3 = std::make_shared<ofxBox2dRect>();
	wall3->setup(box2d.getWorld(), ofGetWidth() / 2 + 130, ofGetHeight() / 2 - 60, 100, 200);
	wall3->setPhysics(0, 0, 0.1);
	rects.push_back(wall3);

	auto wall4 = std::make_shared<ofxBox2dRect>();
	wall4->setup(box2d.getWorld(), ofGetWidth() / 2 + 230, ofGetHeight() / 2 - 20, 100, 120);
	wall4->setPhysics(0, 0, 0.1);
	rects.push_back(wall4);

	auto wall5 = std::make_shared<ofxBox2dRect>();
	wall5->setup(box2d.getWorld(), ofGetWidth() / 2 - 50, ofGetHeight() / 2 + 5, 330, 70);
	wall5->setPhysics(0, 0, 0.1);
	rects.push_back(wall5);

	auto wall6 = std::make_shared<ofxBox2dRect>();
	wall6->setup(box2d.getWorld(), ofGetWidth() / 2 - 350, ofGetHeight() / 2 - 60, 300, 200);
	wall6->setPhysics(0, 0, 0.1);
	rects.push_back(wall6);

	auto wall7 = std::make_shared<ofxBox2dRect>();
	wall7->setup(box2d.getWorld(), ofGetWidth() / 2 - 340, ofGetHeight() / 2 + 400, 590, 70);
	wall7->setPhysics(0, 0, 0.1);
	rects.push_back(wall7);

	auto wall8 = std::make_shared<ofxBox2dRect>();
	wall8->setup(box2d.getWorld(), ofGetWidth() / 2, ofGetHeight() / 2 + 360, 100, 140);
	wall8->setPhysics(0, 0, 0.1);
	rects.push_back(wall8);

	auto wall9 = std::make_shared<ofxBox2dRect>();
	wall9->setup(box2d.getWorld(), ofGetWidth() / 2 + 160, ofGetHeight() / 2 + 330, 220, 200);
	wall9->setPhysics(0, 0, 0.1);
	rects.push_back(wall9);

	auto wall10 = std::make_shared<ofxBox2dRect>();
	wall10->setup(box2d.getWorld(), ofGetWidth() / 2 + 490, ofGetHeight() / 2 + 330, 300, 200);
	wall10->setPhysics(0, 0, 0.1);
	rects.push_back(wall10);

	auto wall11 = std::make_shared<ofxBox2dRect>();
	wall11->setup(box2d.getWorld(), ofGetWidth() / 2 - 470, ofGetHeight() / 2 +140, 60, 200);
	wall11->setPhysics(0, 0, 0.1);
	rects.push_back(wall11);

	auto wall12 = std::make_shared<ofxBox2dRect>();
	wall12->setup(box2d.getWorld(), ofGetWidth() / 2 - 610, ofGetHeight() / 2 + 300, 50, 20);
	wall12->setPhysics(0, 0, 0.1);
	rects.push_back(wall12);

	auto wall13 = std::make_shared<ofxBox2dRect>();
	wall13->setup(box2d.getWorld(), ofGetWidth() / 2 - 525, ofGetHeight() / 2 + 210, 50, 20);
	wall13->setPhysics(0, 0, 0.1);
	rects.push_back(wall13);

	auto wall14 = std::make_shared<ofxBox2dRect>();
	wall14->setup(box2d.getWorld(), ofGetWidth() / 2 - 610, ofGetHeight() / 2 + 120, 50, 20);
	wall14->setPhysics(0, 0, 0.1);
	rects.push_back(wall14);

	auto wall15 = std::make_shared<ofxBox2dRect>();
	wall15->setup(box2d.getWorld(), ofGetWidth() / 2 - 525, ofGetHeight() / 2 + 30, 50, 20);
	wall15->setPhysics(0, 0, 0.1);
	rects.push_back(wall15);

	auto wall16 = std::make_shared<ofxBox2dRect>();
	wall16->setup(box2d.getWorld(), ofGetWidth() / 2 - 610, ofGetHeight() / 2 - 60, 50, 20);
	wall16->setPhysics(0, 0, 0.1);
	rects.push_back(wall16);

	auto finishBlock = std::make_shared<ofxBox2dRect>();
	finishBlock->setPhysics(0, 0, 0.1);
	finishBlock->setup(box2d.getWorld(), ofGetWidth() / 2 - 610, ofGetHeight() / 2 - 378, 50, 95);
	finishBlocks.push_back(finishBlock);

	auto danger0 = std::make_shared<ofxBox2dRect>();
	danger0->setPhysics(0, 0, 0.1);
	danger0->setup(box2d.getWorld(), 0,0, 40, 40);
	dangers.push_back(danger0);

	auto danger1 = std::make_shared<ofxBox2dRect>();
	danger1->setPhysics(0, 0, 0.1);
	danger1->setup(box2d.getWorld(), ofGetWidth()/2 + 305, ofGetHeight()/2 + 130, 40, 40);
	dangers.push_back(danger1);

	auto danger2 = std::make_shared<ofxBox2dRect>();
	danger2->setPhysics(0, 0, 0.1);
	danger2->setup(box2d.getWorld(), 130, ofGetHeight() / 2 + 180, 20, 20);
	dangers.push_back(danger2);

	auto danger3 = std::make_shared<ofxBox2dRect>();
	danger3->setPhysics(0, 0, 0.1);
	danger3->setup(box2d.getWorld(), ofGetWidth() - 195, 35, 50, 20);
	dangers.push_back(danger3);

	auto danger4 = std::make_shared<ofxBox2dRect>();
	danger4->setPhysics(0, 0, 0.1);
	danger4->setup(box2d.getWorld(), ofGetWidth()/2 - 50, ofGetHeight() / 2 - 50, 50, 20);
	dangers.push_back(danger4);

	auto danger5 = std::make_shared<ofxBox2dRect>();
	danger5->setPhysics(0, 0, 0.1);
	danger5->setup(box2d.getWorld(), 600, 50, 40, 40);
	dangers.push_back(danger5);
};

void Map::update() {
	float timeLoop = ofGetElapsedTimeMillis(); 
	float offset = 200 * sin(0.004 * timeLoop);
	float offset2 = 200 * sin(0.002 * timeLoop);

	ofVec2f pos = dangers[0]->getPosition();
	dangers[0]->setPosition(glm::vec2(ofGetWidth() / 2 - 100, ofGetHeight() / 2 + 200) + glm::vec2(offset, 0));
	dangers[2]->setPosition(glm::vec2(130, ofGetHeight() / 2 + 100) + glm::vec2(0, offset2));
	dangers[5]->setPosition(glm::vec2(600, 50) + glm::vec2(0, 0.1 * offset2));

};

void Map::draw() {
	for (auto &rect : rects) {
		ofSetColor(10);
		ofFill();
		rect->draw();
	}

	for (auto &danger : dangers) {
		ofSetColor(255, 100, 100);
		ofFill();
		danger->draw();
	}

	for (auto &finishBlock : finishBlocks) {
		ofSetColor(100, 255, 100);
		ofFill();
		finishBlock->draw();
	}

	

};