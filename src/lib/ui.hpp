#pragma once
#include <vector>
#include "vec2.hpp"
#include <raylib.h>

class TUI {
    private:
        std::vector<menu> menus;
    public:
        void draw() {
            for (auto men : menus) {
                men.draw();
            }
        }
};


class menu {
    public:
        void draw() {

        }
};