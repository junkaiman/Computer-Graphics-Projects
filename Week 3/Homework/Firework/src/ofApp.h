#pragma once

#include "ofMain.h"
#include "ParticleSystem.hpp"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

	void mousePressed(int x, int y, int button);
	void keyPressed(int key);
	glm::vec2 startPos;
    void mouseReleased(int x, int y, int button);
	glm::vec2 endPos;
    vector<ParticleSystem> particleSystems;
    glm::vec2 gravity;
    
		
};
