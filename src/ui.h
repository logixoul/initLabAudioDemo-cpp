#pragma once
#include <raylib.h>
#include <raygui.h>
#include <map>
#include "NoteManager.h"

namespace AudioDemo
{
    extern std::map<int, int> mapping;

    class Ui
    {
        NoteManager *mNoteManager;

    public:
        Ui(NoteManager *noteManager)
        {
            mNoteManager = noteManager;
            InitWindow(800, 450, "init Lab audio demo");
        }

        ~Ui()
        {
            CloseWindow();
        }

        void mainLoop()
        {
            while (!WindowShouldClose())
            {
                handleInput();
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
                produceUiElements();
                EndDrawing();

                mNoteManager->postMessage(NoteManager::UpdateMessage{});
            }
        }
    private:

        void produceUiElements()
        {
            int oscTypeIndex = GuiDropdownBox((RECTANGLE){10, 10, 200, 20}, "Sine;Square", 0, false);
        }

        void handleInput()
        {
            for (auto &pair : mapping)
            {
                if (IsKeyPressed(pair.first))
                {
                    handleKeyPressed(pair.first);
                }
                if (IsKeyReleased(pair.first))
                {
                    handleKeyReleased(pair.first);
                }
            }
        }

        void handleKeyPressed(int key)
        {
            const int noteIndex = keyCodeToNoteIndex(key);
            if (noteIndex != -1)
            {
                mNoteManager->postMessage(NoteManager::NotePressedMessage{noteIndex});
            }
        }
        void handleKeyReleased(int key)
        {
            const int noteIndex = keyCodeToNoteIndex(key);
            if (noteIndex != -1)
            {
                mNoteManager->postMessage(NoteManager::NoteReleasedMessage{noteIndex});
            }
        }
        int keyCodeToNoteIndex(int keyCode)
        {
            if (mapping.find(keyCode) != mapping.end())
            {
                return mapping[keyCode] + 60;
            }
            return -1;
        }
    };
}
