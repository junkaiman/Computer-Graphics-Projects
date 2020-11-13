/*
 * Modified from 01_particle_system by Tyler Henry on 10/2/18
 */

#pragma once
#include "ofMain.h"

class Particle {
    
public:
    
    Particle();
    Particle(glm::vec2 _pos, glm::vec2 _vel, float _mass);
    
    void applyForce(glm::vec2 force);
    void update();
    void draw();
    
    glm::vec2 pos, vel, acc;
    float mass;
    
    float bornTime;

	//ofImage wrappingImage;
	// I tried to use the ofImage as substituion of circles,
	// but the performance is bad. So I abandoned it.
    
};
