#pragma once
#include "ofMain.h"
#include "EnemyManager.h"
class Particle {
public:
    Particle();
    void setup(ofVec2f position, ofVec2f velocity, float lifetime);
    void update(float deltaTime);
    void draw();
    bool isAlive() const;
    ofColor startColor;
    ofColor endColor;
    void setStartColor(int r, int g, int b, int a);
    void setEndColor(int r, int g, int b, int a);
private:
    ofVec2f pos; //Particle has a pos from type ofVec2f 
    ofVec2f vel;//Particle has a velocity from type ofVec2f
    float lifespan;//How much the particle is gonna last
    float startTime;//Time since it was spawned
};
