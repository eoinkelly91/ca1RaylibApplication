// import raylib library
#include "raylib.h"

// program main entry point
int main()
{
    // window variables
    const int windowWidth{1800};
    const int windowHeight{1200};

    InitWindow(windowWidth, windowHeight, "Eoin"); // Show the game window with title

    Texture2D background = LoadTexture("resources/forest-background.png"); // background variable
    // charachter variables
    Texture2D scarfy = LoadTexture("resources/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width / 6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth / 2 - scarfyRec.width / 2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    SetTargetFPS(60);
    // loop where game logic takes place, only ends on window close
    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexture(background, 0, 0, WHITE);                // add background image
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE); // add charachter image
        EndDrawing();
    }
    UnloadTexture(background); // unload texture from memory
    UnloadTexture(scarfy);
    CloseWindow();
    return 0;
}