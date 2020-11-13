#pragma once
#include "ofMain.h"
#include "Particle.hpp"

class ParticleSystem {
public:
  
    ParticleSystem();                   
    ParticleSystem(glm::vec2 _pos, glm::vec2 _vel); 
    void applyForce(glm::vec2 force);   // applies force to particles   
    void update(int numNewParticles = 10, int maxParticles = 1000);
    void draw();
    glm::vec2 pos;                      // origin of the particle system
	glm::vec2 vel;
    vector<Particle> particles;
};
