#pragma once
#include <raylib.h>

namespace AudioDemo {

class Ui {
public:
    Ui() {
        InitWindow(800, 450, "init Lab audio demo");
    }

    ~Ui() {
        CloseWindow();
    }

    void mainLoop() {
        while (!WindowShouldClose())
        {
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
            EndDrawing();
        }
    }
};

}