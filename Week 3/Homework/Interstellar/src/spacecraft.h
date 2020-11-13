
class spacecraft {
public: 
	glm::vec2 location;
	float width = 30;
	float height = 10;

	void setup(glm::vec2 loc) {
		location = loc;
	}

	void update() {
	
	}

	void draw() {
		ofSetColor(255, 0, 0);
		ofDrawRectangle(location, width, height);
		ofSetColor(0, 0, 0);
	}

	void easeTo(glm::vec2 mouseLoc) {
		location = 0.90 * location + 0.10 * mouseLoc;
	}

};

