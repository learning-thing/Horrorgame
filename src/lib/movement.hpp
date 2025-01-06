#pragma once
#include "vec3.hpp"
#include <raylib.h>
#define TDEBUG true


void logVec3(vec3 vecToLog, std::string label) {
    if (TDEBUG)
    std::clog << label << ": X:"<< vecToLog.x() <<  " Y:" << vecToLog.y() << " Z:" << vecToLog.z() << "\n";
}


class TMovement {
    private:
        vec3 position = vec3(0, .52, -5);
        vec3 speed = vec3(0);
        vec3 acceleration = vec3(0);
        vec3 gravity = vec3(0, 3, 0);
        vec3 strafevec = vec3(0);
        float floorheight = .5;
        float frameTime = 0;
        bool debug = false;

        void DBGLOG(std::string msg) {
            if (debug) {
                std::clog << msg << "\n";
            }
        }
        void DBGLOG(float msg) {
            if (debug) {
                std::clog << msg << "\n";
            }
        }

        bool IsonGround() {
            return (abs(position.y()-floorheight)<.01f);
        }
        void input() {
            if (IsonGround()) {
                if (IsKeyDown(forwardKey))   MoveForward();
                if (IsKeyDown(backwadsKey))  MoveBackward();
                //if (IsKeyDown(turnRightKey)) turnRight();
                //if (IsKeyDown(turnLeftKey)) turnLeft();
                if (IsKeyDown(MoveLeftKey))  MoveLeft();
                if (IsKeyDown(MoveRightKey)) MoveRight();
                //if (IsKeyPressed(JumpKey))   Jump();
            }
        }
        void MoveForward() {
            acceleration+=dirvec*accelSpeed*vec3(1,0,1);
        }

        void MoveBackward() {
            acceleration-=dirvec*accelSpeed*vec3(1,0,1);
        }

        void MoveRight() {
            acceleration-=strafevec*accelSpeed;
        }

        void MoveLeft() {
            acceleration+=strafevec*accelSpeed;
        }

        void Jump() {
            if (IsonGround()) {
                acceleration+=vec3(0, 200, 0);
            }
        }
    public:
        vec3 dirvec = vec3(0);
        float upAngle = 0;
        float rotation = 0;
        int forwardKey = KEY_W;
        int backwadsKey = KEY_S;
        int turnRightKey = KEY_RIGHT;
        int turnLeftKey = KEY_LEFT;
        int MoveLeftKey = KEY_A;
        int MoveRightKey = KEY_D;
        int JumpKey = KEY_SPACE;
        float accelSpeed = 10;
        float deceleration = 1;
        float height = 0;
        float fov = 60;

        Vector3 update(float frametime) {
            frameTime = frametime;
            input();
            dirvec = vec3(sin(rotation), sin(upAngle), cos(rotation));
            strafevec = vec3(cos(-rotation), 0, sin(-rotation));
            
            gravity = vec3(0, position.y()-floorheight, 0);
            acceleration-=gravity;
            if (position.y()<floorheight || abs(floorheight-position.y())<.02f) {
                DBGLOG("Resetting to groundHeight");
                position.e[1]=floorheight;
            }
            DBGLOG( position.y() );
            //if (IsKeyDown(KEY_SPACE))

            speed+=acceleration*frametime;
            position+=speed*frametime;
            speed+=acceleration*frametime;
            
            if (IsonGround())//If on ground
                speed-=5*speed*frameTime;//decelerate

            fov = 60+speed.length()*.2f;

            acceleration = 0;
            //logVec3(position, "Actual movement position: ");
            
            //std::clog << position.x() << " : " << position.z() << "\n";
            return position.toRayVec();
        }

        vec3 CamTargPos() {
            return position+dirvec*2;
        }

        vec3 CamTargOffset(float scale) {
            return dirvec*scale;
        }

        vec3 CamThirdPersonTargPos() {
            return position+dirvec*5;
        }

        vec3 getPos() {
            return position+vec3(0, height, 0);
        }
};

