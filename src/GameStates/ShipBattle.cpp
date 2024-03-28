#include "ShipBattle.h"

// ====================================
// Constructor & Destructor Section
// ====================================

ShipBattle::ShipBattle() {
    this->player = new Player(ofGetWidth() / 2, ofGetHeight() / 2);
    this->playerScore = 0;
    this->killspreeTimer = 0;

    font.load("Fonts/Orbitron.ttf", 20, true);
    indicatorFont.load("Fonts/Orbitron.ttf", 10, true);
    backgroundImage.load("Menu_Images/BattleArea.jpg");
     heart.load("ShipModels/heart.png");

}

// ====================================
// Core Functionality Section
// ====================================


// Update Method
void ShipBattle::update() {
    // Boss spawn logic
    if (EnemyManager::isBossSpawning()) {
        displayBossWarning = true;
        SoundManager::stopSong("battle");
    } 
    else {
        displayBossWarning = false;
    }

    // Update enemies and player
    EnemyManager::updateEnemies(player);
    this->player->processPressedKeys();
    this->player->update();
    wrapCoords(this->player->pos);

    // Update scoring and kill spree timer
    playerScore += EnemyManager::getPointsScored() * scoreMultiplier() * killSpreeMode();
    this->player->setScore(playerScore);
    killspreeTimer = EnemyManager::getKillSpreeTimer();

    // Update player projectiles
    if (!this->player->bullets.empty()) {
        updateBullets();
    }

    // State switching logic for when the player dies
    if(this->player->lives!=0 && this->player->health <= 0 ){
        this->player->health = 100;
        this->player->lives= this->player->lives-1;
    }
    if(this->player->lives==0){
        
        this->player = new Player(ofGetWidth() / 2, ofGetHeight() / 2);
        this->player->lives = 3;
        this->setNextState("GameOverState");
        SoundManager::stopSong("battle");
        SoundManager::stopSong("ORT Xibalba");
        SoundManager::stopSong("Galactica Supercell ORT"); //Esto lo hice yo para parar la msuica de los bosses
        if(EnemyManager::getSpawningBossType() != ""){
            SoundManager::stopSong(EnemyManager::getSpawningBossType());  //<---- maybe hay un bug con esto se supone que
                                                                          //pare la musica de los boss y no lo hace, por eso hice lo de arriba
        }
            // Write the current score to a file
            ofstream scoreFile("currentScore.txt");
            if (scoreFile.is_open()) {
                scoreFile << playerScore;
                scoreFile.close();
            }
            this->setFinished(true);
            this->playerScore = 0;  // despues que enseña en la pantalla el score vuelve a ser 0
            this->killspreeTimer = 0; //tambien esto
    }
    if (player->shieldon && player->shield > 0) {
        long currentTime = ofGetElapsedTimeMillis();
        float elapsedTimeInSeconds = (currentTime -player->shieldActivationTime) / 1000.0f; // Convierte a segundos
        
        // Si han pasado más de 10 segundos, el escudo se desactiva
        if (elapsedTimeInSeconds >= 10.0) {
            player->shield = 0;
            player->shieldon = false;
        } else {
            // Ajusta el valor de shield basado en cuánto tiempo ha pasado
            // Por ejemplo, si shield se agota linealmente
            player->shield = 100 - (elapsedTimeInSeconds * (100.0 / 10.0));
        }
    }
    
}

//====== Draw Method ====== 
void ShipBattle::draw() {
    ofSetBackgroundColor(ofColor::black);
    backgroundImage.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    // Draw the score
    ofSetColor(ofColor::white);
    font.drawString("SCORE " + to_string(playerScore), ofGetWidth() / 2 - 50, 50);

    // Draw enemies and player
    EnemyManager::drawEnemies();
    player->draw();
    draw_bullets();
    
    // Draw boss warning if needed
    if (displayBossWarning) {
        // Semi-transparent red screen tint
        ofSetColor(255, 0, 0, 128);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

        // Warning text
        ofSetColor(255);
        font.drawString("BOSS APPROACHING!", ofGetWidth() / 2 - 100, ofGetHeight() / 2);
    }

    // Draw UI elements
    healthBar(player->health, 100);
    killSpreeTimer(this->killspreeTimer, 150);
    shieldBar(player->shield,100);
    
    //Draw a mini box for the bomb. Make sure to draw the bomb inside this box.
        ofNoFill();
        ofDrawRectangle(ofGetWidth() - 150, 30, 50, 50);
        ofFill();

    if(this->player->lives>=1){
        heart.draw(ofGetWindowWidth()/2-590, ofGetWindowHeight()/2-275, 25, 25);
    }
     if(this->player->lives>=2){
        heart.draw(ofGetWindowWidth()/2-560, ofGetWindowHeight()/2-275, 25, 25);
    }
     if(this->player->lives==3){
        heart.draw(ofGetWindowWidth()/2-530, ofGetWindowHeight()/2-275, 25, 25);
    }
    
}

// ====================================
// Input Handling Section
// ====================================

void ShipBattle::keyPressed(int key) {
    player->addPressedKey(key);
    
    //DEBUG KEYS - Press these keys to ease the debugging with the game
    if(key == 'k') {
        EnemyManager::toggleHitBoxes = !EnemyManager::toggleHitBoxes; 
        player->showHitbox = !player->showHitbox;
    }
    if(key == 'o')  player->health = 100;
    if(key == 'p')  playerScore += 10000; 
}

void ShipBattle::keyReleased(int key) {
    key = tolower(key);
    this->player->removePressedKey(key);
}

void ShipBattle::mousePressed(int x, int y, int button) {
    // Implementation for mousePressed event in case you want to do something with this
}

// ====================================
// Helper Methods Section
// ====================================

void ShipBattle::wrapCoords(ofPoint &currentPos) {
    // Screen wrapping logic for player ship
    if (currentPos.x < 0.0) currentPos.x = ofGetWidth() - 10;
    if (currentPos.x >= ofGetWidth()) currentPos.x = 10;
    if (currentPos.y < 0.0) currentPos.y = ofGetHeight() - 10;
    if (currentPos.y >= ofGetHeight()) currentPos.y = 10;
}

void ShipBattle::draw_bullets() {
    // Draw all player bullets
    for (auto &bullet : this->player->bullets) {
        bullet.draw();
    }
}

void ShipBattle::updateBullets() {
    // Update logic for player bullets
    for (auto &bullet : this->player->bullets) {
        bullet.update();
    }
}

// ====================================
// UI and Feedback Methods Section
// ====================================
void ShipBattle::healthBar(int currHealth, int maxHealth) {
    indicatorFont.drawString("HEALTH", 10, 30);
    ofNoFill();
    ofDrawRectangle(10, 40, maxHealth *2, 20);
    ofFill();
    ofSetColor(ofColor::green);
    ofDrawRectangle(10, 40, currHealth *2, 20);
    ofSetColor(ofColor::white);
}

void ShipBattle::killSpreeTimer(int currTimer, int maxTimer) {
    indicatorFont.drawString("KILL SPREE", 10, 80);
    ofNoFill();
    ofDrawRectangle(10, 90, maxTimer, 10);
    ofFill();
    ofSetColor(ofColor::red);
    ofDrawRectangle(10, 90, currTimer, 10);
    ofSetColor(ofColor::white);
}

void ShipBattle::shieldBar(int currShield, int maxShield){//este es la barra para el escudo
    indicatorFont.drawString("SHIELD", 10, 155);
    ofNoFill();
    ofDrawRectangle(10, 165, maxShield *2, 20);//crea el barra donde va a estar el escudo
    ofFill();
    ofSetColor(ofColor::blue);
    ofDrawRectangle(10, 165, currShield *2, 20);//cambiar max shield por currShield 
    ofSetColor(ofColor::white);
}


// ====================================
// Game Mechanics Methods Section
// ====================================

double ShipBattle::killSpreeMode() {
    // Logic for kill spree mode bonus
    return this->killspreeTimer > 0 ? 1.5 : 1.0;
}

double ShipBattle::scoreMultiplier() {
    // Logic for score multiplier based on current score
    if (playerScore >= 350) return 3.5;
    else if (playerScore >= 200) return 2.5;
    else if (playerScore >= 100) return 1.5;
    else return 1.0; // Default multiplier
}

void ShipBattle::reset(){
    setFinished(false);
    setNextState("");
}


                                        
