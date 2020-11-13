#pragma once
class bullet {
public:
	bullet() {}

	glm::vec2 location;
	float speed = 3;
	float radius = 5;

	void setup(glm::vec2 loc) {
		location = loc;
	}

	void update() {
		location.y -= speed;
	}

	void display() {
		ofSetColor(255);
		ofDrawCircle(location, radius);
		ofSetColor(0, 0, 0);
	}
	
};