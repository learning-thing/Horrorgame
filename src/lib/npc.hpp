#pragma once
#include "vec3.hpp"
#include <iostream>

class NPC {//Class for all NPCs
    protected:
        vec3 position = vec3(0);
        vec3 speed = {0, 0, 0};
        Color myColor = WHITE;

        
    void draw() {
        DrawCapsule(position.toRayVec(), (position+vec3(0, 1,0)).toRayVec(), 1, 6, 6, myColor);
    }
};


class Enemy : NPC {//This one is bad
    private:
        vec3 dirvec;
        vec3 lookdirVec;
        vec3 Oheight = {1, 0, 1};
        bool disappeared = false;
    public:
    Enemy() : NPC() {
        myColor = RED;
        position+= vec3(GetRandomValue(-10, 10), 0, 0);
    }
    void update(vec3 PlayerPos, vec3 playerLook) {
        draw();
        //Chech viewdirection stuff
        dirvec = PlayerPos*Oheight-position;         //Vector to the player
        lookdirVec = PlayerPos-(PlayerPos+playerLook);   //ViewDirection
        lookdirVec /= lookdirVec.length();//normalised Direction to the player
        dirvec /= dirvec.length();//normalised Viewdirection
        float viewperc = (lookdirVec-dirvec).length();
        //std::clog << viewperc << "\n";
        if (viewperc >= 1) {
            if (!disappeared) {
                disappeared = true;
                position = PlayerPos+lookdirVec*Oheight*4;
                std::clog << "Teleported to " << position.x() << "," << position.z() << "\n";
            }
        } 
        else {
            disappeared = false;
            myColor = RED;
        }
    }
};

class Ally : NPC {//This one is good
    private:
        vec3 dirvec;
        vec3 Oheight = {1, 0, 1};
    public:
    Ally() : NPC() {
        myColor = BLUE;
        position+= vec3(GetRandomValue(-10, 10), 0, 0);
    }
    void update(vec3 PlayerPos) {
        draw();
        dirvec = PlayerPos*Oheight-position;         //Vector to the player

        speed+=dirvec*5;
        dirvec/=dirvec.length();
        speed-=dirvec*15;
        speed-=speed*GetFrameTime()*5;//Slow down
        position+=speed*GetFrameTime()*.05;
    }
};

