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
    void whichBomb();
    ofColor startColor;
    ofColor endColor;
    void setStartColor(int r, int g, int b, int a);
    void setEndColor(int r, int g, int b, int a);
private:
    ofVec2f pos;
    ofVec2f vel;
    float lifespan;
    float startTime;
};
