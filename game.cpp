#include "raylib.h"

int main(){
    const int windowWidth{500};
    const int windowHeight{500};
    InitWindow(windowWidth,windowHeight,"Eoin");
    SetTargetFPS(60);
    while(WindowShouldClose() == false){
        BeginDrawing();
        DrawCircle(250,250,10,RED);
        ClearBackground(BLUE);
        EndDrawing();
    }
    CloseWindow();
}