#include "NewEnemy.h"


NewEnemy::NewEnemy(int xpos, int ypos) : EnemyShip(xpos, ypos, 0.5, 20, 100) {
    amIBoss = false;
    enemyShipSprite.load("ShipModels/newEnemy.png");
    enemyShipSprite.rotate90(2);
    enemyHitBox = new HitBox(pos, enemyShipSprite.getWidth() * 0.1, enemyShipSprite.getHeight() * 0.1);
}

void NewEnemy::update(const ofPoint& playerPos) {
    // Calculate the angle to the player
        ofVec2f toPlayer = playerPos - pos;
        float angleToPlayer = ofRadToDeg(-atan2(toPlayer.x, toPlayer.y));

    // Update ship's orientation
        shipOrientation = angleToPlayer;

    // Move towards the player
        pos += toPlayer.getNormalized() * speed;
        enemyHitBox->box.setPosition(pos.x - 15, pos.y - 10);

    this->shotTimer++;
    // Check if the ship should shoot
        if (shotTimer % 50 == 0) {
            shoot();
            shotTimer = 0; //resets the timer
        }
}

void NewEnemy::draw() {
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    ofRotateDeg(shipOrientation);
    enemyShipSprite.draw(-32, -32, 60, 60);
    ofPopMatrix();
    
    if(showHitboxes){
        enemyHitBox->draw();
    }
}

void NewEnemy::shoot() {
    // Create a new projectile and add it to the list of bullets
    Projectiles p = Projectiles(pos-7, shipOrientation + 90);
    p.setColors(ofColor::green, ofColor::purple);
    enemyBullets.push_back(p);

     Projectiles p2 = Projectiles(pos+7, shipOrientation + 90); 
    p2.setColors(ofColor::green, ofColor::purple);
    enemyBullets.push_back(p2);
    
    SoundManager::playSong("bulletSound", false);
}
