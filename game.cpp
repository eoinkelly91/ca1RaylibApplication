#include "raylib.h" // import raylib library

struct Anim
{
    Rectangle rec; // rectangle around character
    Vector2 pos;   // position of character
    int frame;     // position on scarfy pic, frame 0 is first pic of character
    float updateTime;
    float runningTime;
};

// program main entry point
int main()
{
    const int windowWidth{1800};  // variable to set window width
    const int windowHeight{1200}; // variable to set window height
    const int gravity{1000};      // gravity varaible (pixels per second)

    InitWindow(windowWidth, windowHeight, "Eoin");                         // Show the game window with title
    Texture2D background = LoadTexture("resources/forest-background.png"); // background variable

    // character variables
    Texture2D scarfy = LoadTexture("resources/scarfy.png");
    Anim scarfyAnim;
    scarfyAnim.rec.width = scarfy.width / 6;
    scarfyAnim.rec.height = scarfy.height;
    scarfyAnim.rec.x = 0;
    scarfyAnim.rec.y = 0;
    scarfyAnim.pos.x = windowWidth / 2 - scarfyAnim.rec.width / 2;
    scarfyAnim.pos.y = windowHeight - scarfyAnim.rec.height;
    scarfyAnim.frame = 0;
    scarfyAnim.updateTime = 1.0 / 12.0;
    scarfyAnim.runningTime = 0.0;

    // object variables
    Texture2D obstacle = LoadTexture("resources/Raylib_logo.png");
    Rectangle obRec;
    obRec.width = obstacle.width;
    obRec.height = obstacle.height;
    obRec.x = 0;
    obRec.y = 0;
    Vector2 obPos;
    obPos.x = windowWidth - obRec.width;
    obPos.y = windowHeight - obRec.height;

    // movement and collison varables
    int obVel{-100};
    int velocity{0};
    const int jumpHeight{500}; // characters jump height in pixels
    bool jumped{false};        // if characte has jumped or not
    int speed{200};
    bool collision{}; // if character has hit another object

    SetTargetFPS(60); // Set target FPS (maximum)
    while (!WindowShouldClose())
    {
        const float deltaTime{GetFrameTime()}; // time since last frame
        Rectangle obstacleRec{
            obPos.x,
            obPos.y,
            obRec.height,
            obRec.width,
        };
        Rectangle scarfyRec{
            scarfyAnim.pos.x,
            scarfyAnim.pos.y,
            scarfyAnim.rec.height,
            scarfyAnim.rec.width};

        if (CheckCollisionRecs(scarfyRec, obstacleRec))
        {
            collision = true;
        }

        if (IsKeyDown(KEY_D) && !jumped)
        {
            scarfyAnim.pos.x += speed * deltaTime;
            scarfyAnim.rec.width = scarfy.width / 6;

            scarfyAnim.runningTime += deltaTime;
            if (scarfyAnim.runningTime >= scarfyAnim.updateTime)
            {
                scarfyAnim.runningTime = 0.0;
                scarfyAnim.rec.x = scarfyAnim.frame * scarfyAnim.rec.width;
                scarfyAnim.frame++;       // increments frame by one
                if (scarfyAnim.frame > 5) // if character is on his last frame go back to frame 0
                {
                    scarfyAnim.frame = 0;
                }
            }
        }
        if (IsKeyReleased(KEY_D) && !jumped)
        {
            scarfyAnim.frame = 0; // character is on his first frame (still)
            scarfyAnim.rec.x = scarfyAnim.frame * scarfyAnim.rec.width;
        }

        if (IsKeyDown(KEY_A) && !jumped)
        {
            scarfyAnim.pos.x -= speed * deltaTime;
            scarfyAnim.rec.width = -scarfy.width / 6;

            scarfyAnim.runningTime += deltaTime;
            if (scarfyAnim.runningTime >= scarfyAnim.updateTime)
            {
                scarfyAnim.runningTime = 0.0;
                scarfyAnim.rec.x = scarfyAnim.frame * scarfyAnim.rec.width;
                scarfyAnim.frame++;       // increments frame by one
                if (scarfyAnim.frame > 5) // if character is on his last frame go back to frame 0
                {
                    scarfyAnim.frame = 0;
                }
            }
        }
        if (IsKeyReleased(KEY_A) && !jumped)
        {
            scarfyAnim.frame = 0; // character is on his first frame (still)
            scarfyAnim.rec.x = scarfyAnim.frame * scarfyAnim.rec.width;
        }

        BeginDrawing(); // Setup canvas to start drawing

        if (scarfyAnim.pos.y >= windowHeight - scarfy.height)
        {
            velocity = 0;
            jumped = false;
        }
        else
        {
            velocity += gravity * deltaTime;
            jumped = true;
        }
        if (IsKeyPressed(KEY_SPACE) && !jumped) // make character jump
        {
            velocity -= jumpHeight;
        }

        scarfyAnim.pos.y += velocity * deltaTime; // acount for delta time frames
        obPos.x += obVel * deltaTime;
        DrawTexture(background, 0, 0, WHITE); // add background image

        if (collision)
        {
            DrawText("GAME OVER", windowWidth / 4, windowHeight / 2, 150, RED); // say Game Over on screen
        }
        else
        {
            DrawTextureRec(scarfy, scarfyAnim.rec, scarfyAnim.pos, WHITE); // add character
            DrawTextureRec(obstacle, obRec, obPos, WHITE);                 // add obstacle
        }
        EndDrawing();
    }
    UnloadTexture(background); // unload texture from memory
    UnloadTexture(scarfy);
    UnloadTexture(obstacle);
    CloseWindow();
}