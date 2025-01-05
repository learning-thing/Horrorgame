#pragma once
#include "vec3.hpp"

class NPC {
    private:
        vec3 position = {0, 0, 0};
        vec3 speed = {0, 0, 0};
    void update(vec3 PlayerPos) {
        float r;
        DrawCapsule((Vector3){0, 0, 0}, (Vector3){0, 0, 0}, 4, 2, 2, WHITE);
    }

    void draw() {
        
    }

    
};


class Enemy : NPC {
    
};

class Ally : NPC {

};

