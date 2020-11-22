#include "Player.h"

Player::Player(){}

void Player::setup(ofxBox2d &box2d) {
	world = box2d;
	leftIsPressed = false;
	rightIsPressed = false;
	jumpIsPressed = false;

};

void Player::initLive(ofxBox2d &box2d, Map &map) {
	isDead = false;
	auto rect = std::make_shared<ofxBox2dRect>();
	rect->setPhysics(0.3, 0.1, 1.5);
	rect->setup(box2d.getWorld(), ofGetWidth() / 2 + 600, ofGetHeight() / 2 - 200, 30, 30);
	rects.push_back(rect);
};

void Player::initDead(ofxBox2d &box2d, string xmlFilename) {
	isDead = true;
	// setting up xml
	xmlFile.load(xmlFilename);
	currentChild = xmlFile.getFirstChild();
	auto rect = std::make_shared<ofxBox2dRect>();
	rect->setPhysics(0.3, 0.1, 1.5);
	cout << "initDead complete" << endl;
	rect->setup(box2d.getWorld(), ofGetWidth() / 2 + 600, ofGetHeight() / 2 - 200, 30, 30);
	rects.push_back(rect);
};

void Player::draw() {
	if (!isDead) {
		ofSetColor(196, 34, 70);
		ofFill();
		rects[0]->draw();
	}
	else {
		ofSetColor(180);
		ofFill();
		rects[0]->draw();
	}
};

void Player::update() {
	pos = rects[0]->getPosition();
	vel = rects[0]->getVelocity();

	liveTime = ofGetElapsedTimeMillis();
	if (!isDead) {
	}
	else {
		if (currentChild != NULL) {
			// check time
			auto nextChild = currentChild.getNextSibling();
			if (liveTime > nextChild.getAttribute("liveTime").getFloatValue()) {
				currentChild = nextChild;
			}
			string status = currentChild.getAttribute("status").getValue();
			if (status == "leftIsPressed")			leftIsPressed = true;
			if (status == "leftIsReleased")			leftIsPressed = false;
			if (status == "rightIsPressed")			rightIsPressed = true;
			if (status == "rightIsReleased")		rightIsPressed = false;
			if (status == "jumpIsPressed")			jumpIsPressed = true;
			if (status == "jumpIsReleased")			jumpIsPressed = false;
			//if (status == "shootIsPressed")			shootIsReleased = false;
			//if (status == "shootIsReleased")		shootIsReleased = true;
			
		}
	}
	if (leftIsPressed)		toLeft();
	if (rightIsPressed)		toRight();
	if (jumpIsPressed)		toJump();
	//if (shootIsReleased)	toShoot();
};

void Player::toLeft() {
	if (vel.x > -10 && leftIsPressed) {
		rects[0]->setVelocity(vel + glm::vec2(-0.7, 0));
	}
};

void Player::toRight() {
	if (vel.x < 10 && rightIsPressed) {
		rects[0]->setVelocity(vel + glm::vec2(+0.7, 0));
	}
};

void Player::toJump() {
	if (abs(vel.y) < 0.1) {
		rects[0]->setVelocity(vel + glm::vec2(0, -15));
	}
};
