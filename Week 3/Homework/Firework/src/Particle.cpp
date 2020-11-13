/*
 * Modified from 01_particle_system by Tyler Henry on 10/2/18
 */

#include "Particle.hpp"

Particle::Particle()
{
    
    // default constructor:
    // Particle particle = Particle();
    
    pos = glm::vec2(0,0);
    vel = glm::vec2(0,0);
    acc = glm::vec2(0,0);
    
    bornTime = ofGetElapsedTimef();
}

Particle::Particle(glm::vec2 _pos, glm::vec2 _vel, float _mass)
{
    
	//wrappingImage.load("laugh.png");  // The performance is really bad.
    pos = _pos;
    vel = _vel;
    mass = _mass;
    
    bornTime = ofGetElapsedTimef();
}

void Particle::applyForce(glm::vec2 force)
{
    acc += force / mass;
}

void Particle::update()
{
    vel += acc;
    pos += vel;
    acc *= 0;
    
}

void Particle::draw()
{
	/*int imgWidth = wrappingImage.getWidth();
	int imgHeight = wrappingImage.getHeight();
	wrappingImage.draw(pos, imgWidth / 10, imgHeight / 10);*/

	// I tried to use the images as particles, but the performance is poor.

    ofPushStyle();
    float aliveTime = ofGetElapsedTimef() - bornTime;
    float alpha = ofMap(aliveTime, 0, 2, 255, 0, true);
	float hue = ofMap(aliveTime, 0, 2, 150, 50, true);
	//float hue = ofMap(mass, 0, 5, 0, 255);
	float sat = 255;
	float brt = 255;
    ofColor color = ofColor::fromHsb(hue,sat,brt,alpha);
    ofSetColor(color);
    
    ofDrawCircle(pos, mass * 5.0);
    ofPopStyle();
}

