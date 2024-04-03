#include "ParticleSystem.h"

ParticleSystem::ParticleSystem() {}


void ParticleSystem::whichBomb() {
    if (EnemyManager::bombCount > 0 && EnemyManager::newBomb) {
        int randomNum = int(ofRandom(3));

        // Use a conditional structure to determine what to do based on the generated number
        switch (randomNum) {
            case 0:
                // Configuration for the first case
                bomb = 0;
                    particle.setStartColor(0, 255, 255, 255); // baby blue
                    particle.setEndColor(0, 0, 255, 0); // Transparent blue
                
                break;
            case 1:
                // Configuration for the second case
                bomb = 1;
                    particle.setStartColor(255, 51, 51, 255); // red
                    particle.setEndColor(255, 128, 0, 0); // Transparent orange
                
                break;
            case 2:
                // Configuration for the third case
                bomb = 2;
                    particle.setStartColor(0, 255, 0, 255); // green
                    particle.setEndColor(153, 255, 153, 0); // Transparent green
                
                break;
            default:
                break;
        }
        EnemyManager::newBomb=false;
    }
}
 int ParticleSystem::getBomb() {
    return this->bomb;
}
void ParticleSystem::explode(ofVec2f position) {
    int numberOfParticles = 300; // Customizable
    for (int i = 0; i < numberOfParticles; i++) {
        float angle = ofRandom(TWO_PI);
        float speed = ofRandom(5, 500); // Customize speed
        ofVec2f vel = ofVec2f(cos(angle), sin(angle)) * speed;

        particle.setup(position, vel, ofRandom(1, 3)); // Random lifespan 
        particles.push_back(particle);
    }
}

void ParticleSystem::update(float deltaTime) {
    for (auto& particle : particles) {
        particle.update(deltaTime);
    }
    particles.erase(std::remove_if(particles.begin(), particles.end(), 
        [](const Particle& p) { return !p.isAlive(); }), particles.end());
}

void ParticleSystem::draw() {
    for (auto& particle : particles) {
        particle.draw();
    }
  
}
