#include "Particle.h"

Particle::Particle() : lifespan(0), startTime(ofGetElapsedTimef()) {}

void Particle::setup(ofVec2f position, ofVec2f velocity, float lifetime) {
    pos = position;
    vel = velocity;
    lifespan = lifetime;
    startTime = ofGetElapsedTimef();
}
void Particle::setStartColor(int r, int g, int b, int a) {
    startColor = ofColor(r, g, b, a);
}
void Particle::setEndColor(int r, int g, int b, int a) {
    endColor = ofColor(r, g, b, a);
}
void Particle::update(float deltaTime) {
    pos += vel * deltaTime; // Update position based on velocity
}


bool Particle::isAlive() const {
    return (ofGetElapsedTimef() - startTime) < lifespan;
}


void Particle::draw() {
    
    float lifeRatio = (ofGetElapsedTimef() - startTime) / lifespan;
    ofSetColor(startColor.getLerped(endColor, lifeRatio)); // Lerp color based on lifeRatio
    
    ofDrawCircle(pos, 5); // Draw particle as a simple circle
}
