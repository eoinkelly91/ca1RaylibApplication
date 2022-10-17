#include "raylib.h"

int main(){
    const int windowWidth{500};
    const int windowHeight{500};
    
    InitWindow(windowWidth,windowHeight,"Eoin");
    Texture2D scarfy =  LoadTexture("resources/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0; 
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    SetTargetFPS(60);
    while(WindowShouldClose() == false){
        BeginDrawing();
        DrawTextureRec(scarfy,scarfyRec, scarfyPos,WHITE);
        ClearBackground(WHITE);
        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();
}