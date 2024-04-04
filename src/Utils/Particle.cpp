#include "Particle.h"

//This class creates a particle

Particle::Particle() : lifespan(0), startTime(ofGetElapsedTimef()) {}


void Particle::setup(ofVec2f position, ofVec2f velocity, float lifetime) {
    pos = position;
    vel = velocity;
    lifespan = lifetime;
    startTime = ofGetElapsedTimef();
}
//Setters for the particle color, we chose RGB because this way the end color can be a "transparent" color to simulate is fading away
void Particle::setStartColor(int r, int g, int b, int a) {
    startColor = ofColor(r, g, b, a);
}
void Particle::setEndColor(int r, int g, int b, int a) {
    endColor = ofColor(r, g, b, a);
}
void Particle::update(float deltaTime) {
    pos += vel * deltaTime; // Update position based on velocity
}

//The particle is yet alive, meaning its lifetime it not equal to the time that has passed since it spawned
bool Particle::isAlive() const {
    return (ofGetElapsedTimef() - startTime) < lifespan;
}


void Particle::draw() {
    
    //Draw the particle with its start color and its end color as it dies

    float lifeRatio = (ofGetElapsedTimef() - startTime) / lifespan;
    ofSetColor(startColor.getLerped(endColor, lifeRatio)); // Lerp color based on lifeRatio
    
    ofDrawCircle(pos, 5); // Draw particle as a simple circle
}
