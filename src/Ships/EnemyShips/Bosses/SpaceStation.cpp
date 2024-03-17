#include "SpaceStation.h"

SpaceStation::SpaceStation(int xpos, int ypos, string name) : Boss(ofGetWidth()/2 - 60, ofGetHeight()/2 - 60   ,0.5, 250, name) {
    enemyShipSprite.load("ShipModels/Space_Station.png");
    enemyHitBox = new HitBox(ofGetWidth()/2-70, ofGetHeight()/2-65, enemyShipSprite.getWidth() * 0.3, enemyShipSprite.getHeight() * 0.38);
    
    shootingPoint = ofPoint(pos.x + enemyHitBox->box.getWidth()/2 , pos.y + enemyHitBox->box.getHeight() / 2 +1 );
    

}

void SpaceStation::update(const ofPoint& playerPos) {

    // Shoot bullets in a semi-circular motion
    if (shotTimer % 10  == 0) { // Adjust the value for the frequency of shooting
        shoot();
    }

    if(enemyBullets.size() > 0) {
        // Update bullets
        for (Projectiles& bullet : enemyBullets) {
            bullet.update();
        }
    }

    // Increment shot timer
    shotTimer++;

}

void SpaceStation::draw() {
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    // ofRotateDeg(shipOrientation);
    enemyShipSprite.draw(-32, -32, 200, 200);
    ofPopMatrix();
    
    // Uncomment this if you want to see the hitbox for the enemy
    if(showHitboxes){
        enemyHitBox->draw();
    }
    
    showBossHealth();
}


void SpaceStation::shoot() {
    

 float angle = shootAngleOffset;
    Projectiles bullet(shootingPoint, angle);
    bullet.setSpeed(5);
    bullet.setColors(ofColor::cyan, ofColor::blue);
    enemyBullets.push_back(bullet);
    // Increment the shootAngleOffset for the next call to shoot() to continue the spiral
    shootAngleOffset += 10.0; // Adjust this value for the desired spiral rotation speed

    // Optional: Reset shootAngleOffset to keep it within 0-360 degrees to avoid overflow
    if(shootAngleOffset >= 360.0) {
        shootAngleOffset -= 360.0;
    }

    SoundManager::playSong("bulletSound", false);
}

