#pragma once
#include "Boss.h"


class FinalBoss : public Boss {
    private:
        float shootAngleOffset = 0.0; // Keep track of the shooting angle offset for the spiral pattern
        ofPoint shootingPoint;
         float shootAngleOffset2 = 180.0;
         float shootAngleOffset3 = 90.0;
         float shootAngleOffset4 = 270.0;

      vector<ofPoint> possiblePositions;
        int switchPosIndex;
            int switchPosTimer;
     

    public:
        FinalBoss(int xpos, int ypos, string name);
        void update(const ofPoint& playerPos) override;
        void draw() override;
        void shoot() override;

};
