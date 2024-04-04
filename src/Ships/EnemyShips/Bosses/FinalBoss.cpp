#include "FinalBoss.h"

FinalBoss::FinalBoss(int xpos, int ypos, string name) : Boss(xpos, ypos,0.5, 1000, name) {
    enemyShipSprite.load("CompressedImages/FinalBoss-min.png");
    enemyHitBox = new HitBox(pos.x, pos.y - 30, enemyShipSprite.getWidth() * 0.15, enemyShipSprite.getHeight() * 0.35);
    
    shootingPoint = ofPoint(pos.x - enemyHitBox->box.getHeight() / 2, pos.y + enemyHitBox->box.getHeight() / 2);
    
    switchPosIndex = 0;
    switchPosTimer = 0;

    possiblePositions = {
        ofPoint(0, 0),
        ofPoint(ofGetWidth() * 1/4, ofGetHeight() * 1/4),
        ofPoint(ofGetWidth() * 1/4, ofGetHeight() * 3/4),
        ofPoint(ofGetWidth() * 3/4, ofGetHeight() * 1/4),
        ofPoint(ofGetWidth() * 3/4, ofGetHeight() * 3/4)
    };

}
    
void FinalBoss::update(const ofPoint& playerPos) {
     enemyHitBox->box.setPosition(pos.x + 10, pos.y - 30);   // Update the hitbox to follow the boss
    shootingPoint = ofPoint(pos.x + enemyHitBox->box.getWidth(), pos.y + enemyHitBox->box.getHeight() / 2);   // Update the shooting point


    // Update the switch position
    switchPosTimer++;
    if (switchPosTimer % 100 == 0) {
        switchPosIndex++;
        pos = possiblePositions[switchPosIndex % possiblePositions.size()];
    }

    // Shoot bullets in a semi-circular motion, 4 bullets with a space of 90 degrees
    if (shotTimer % 10  == 0) { //  frequency of shooting
        shoot();
    }

    if(enemyBullets.size() > 0) {
        // Update bullets
        for (Projectiles& bullet : enemyBullets) {
            bullet.update();
        
        }
         for (Projectiles& bullet2 : enemyBullets) {
            bullet2.update();
        
        }
         for (Projectiles& bullet3 : enemyBullets) {
            bullet3.update();
        
        }
         for (Projectiles& bullet4 : enemyBullets) {
            bullet4.update();
        
        }
    }

    // Increment shot timer
    shotTimer++;

}

void FinalBoss::draw() {
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


void FinalBoss::shoot() {
    

 float angle = shootAngleOffset;
 float angle2 = shootAngleOffset2;
 float angle3 = shootAngleOffset3;
 float angle4 = shootAngleOffset4;
    Projectiles bullet(shootingPoint, angle);
     Projectiles bullet2(shootingPoint, angle2);
      Projectiles bullet3(shootingPoint, angle3);
       Projectiles bullet4(shootingPoint, angle4);
    bullet.setSpeed(3);
     bullet2.setSpeed(3);
      bullet3.setSpeed(3);
       bullet4.setSpeed(3);
    bullet.setColors(ofColor::yellow, ofColor::yellow);
     bullet2.setColors(ofColor::yellow, ofColor::yellow);
      bullet3.setColors(ofColor::yellow, ofColor::yellow);
       bullet4.setColors(ofColor::yellow, ofColor::yellow);
    enemyBullets.push_back(bullet);
     enemyBullets.push_back(bullet2);
      enemyBullets.push_back(bullet3);
       enemyBullets.push_back(bullet4);
    // Increment the shootAngleOffset for the next call to shoot() to continue the spiral
    shootAngleOffset += 10.0; // Adjust this value for the desired spiral rotation speed
    shootAngleOffset2 += 10.0;
    shootAngleOffset3 += 10.0;
    shootAngleOffset4 += 10.0;
    // Optional: Reset shootAngleOffset to keep it within 0-360 degrees to avoid overflow
    if(shootAngleOffset >= 360.0) {
        shootAngleOffset -= 360.0;
    }
    if(shootAngleOffset2 >= 360.0) {
        shootAngleOffset2 -= 360.0;
    }
    if(shootAngleOffset3 >= 360.0) {
        shootAngleOffset3 -= 360.0;
    }
    if(shootAngleOffset4 >= 360.0) {
        shootAngleOffset4 -= 360.0;
    }

    SoundManager::playSong("bulletSound", false);
}

