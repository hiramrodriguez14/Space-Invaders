#pragma once
#include "ofMain.h"
#include "Particle.h"
#include <vector>

class ParticleSystem {
public:

    ParticleSystem();
    void explode(ofVec2f position);
    void update(float deltaTime);
    void draw();
    int randomNum;
    int bomb;
    int getBomb();
    void whichBomb();
     Particle particle;
private:
    std::vector<Particle> particles;
};
