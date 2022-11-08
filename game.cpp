#include "raylib.h" // import raylib library

struct Anim
{
    Rectangle rec;     // rectangle around character
    Vector2 pos;       // position of character
    int frame;         // position on sprite, frame 0 is first pic of character
    float updateTime;  // movement varaible
    float runningTime; // movement varaible
};

// program main entry point
int main()
{
    const int windowWidth{1800};  // variable to set window width
    const int windowHeight{1200}; // variable to set window height
    const int gravity{1000};      // gravity varaible (pixels per second)

    InitWindow(windowWidth, windowHeight, "Eco Warrior");                  // Show the game window with title
    InitAudioDevice();                                                     // Initialize audio device
    Music music = LoadMusicStream("resources/rhythm_garden.mp3");          // load music
    PlayMusicStream(music);                                                // play music
    float timePlayed{0.0f};                                                // variable to loop music
    Texture2D background = LoadTexture("resources/forest-background.png"); // background variable

    // character variables
    Texture2D warrior = LoadTexture("resources/viking.png");         // load character sprite
    Anim warriorAnim;                                                // create character object from struct
    warriorAnim.rec.width = warrior.width / 6;                       // set rectangle width
    warriorAnim.rec.height = warrior.height;                         // set rectangle height
    warriorAnim.rec.x = 0;                                           // set rectangle x axis positon
    warriorAnim.rec.y = 0;                                           // set rectangle y axis positon
    warriorAnim.pos.x = windowWidth / 2 - warriorAnim.rec.width / 2; // set character x axis positon
    warriorAnim.pos.y = windowHeight - warriorAnim.rec.height;       // set character y axis positon
    warriorAnim.frame = 0;                                           // frame on sprite sheet
    warriorAnim.updateTime = 1.0 / 12.0;                             // initialise movement varaible
    warriorAnim.runningTime = 0.0;                                   // initialise movement varaible

    // object variables
    Texture2D obstacle = LoadTexture("resources/log.png"); // load object sprite
    Rectangle obRec;                                       // create rectangle for object
    obRec.width = obstacle.width;                          // set object width
    obRec.height = obstacle.height;                        // set object height
    obRec.x = 0;                                           // set rectangle x axis positon
    obRec.y = 0;                                           // set rectangle y axis positon
    Vector2 obPos;                                         // vector represents geometrical properties of object
    obPos.x = windowWidth - obRec.width;                   // set vector x axis positon
    obPos.y = windowHeight - obRec.height;                 // set vector y axis positon

    // movement and collison varables
    int obVel{-200};
    int velocity{0};
    int speed{200};
    const int jumpHeight{1000}; // characters jump height in pixels
    bool jumped{false};         // if character has jumped or not
    bool collision{};           // if character has hit another object

    SetTargetFPS(60);            // Set target FPS (maximum)
    while (!WindowShouldClose()) // loop while window open
    {
        UpdateMusicStream(music);
        timePlayed = GetMusicTimePlayed(music) / GetMusicTimeLength(music);
        if (timePlayed >= 1.0f) // Loop the music
            SeekMusicStream(music, 0);
        const float deltaTime{GetFrameTime()}; // time since last frame
        // create rectangle for character
        Rectangle warriorRec{
            warriorAnim.pos.x,
            warriorAnim.pos.y,
            warriorAnim.rec.height,
            warriorAnim.rec.width};
        // create rectangle for object
        Rectangle obstacleRec{
            obPos.x,
            obPos.y,
            obRec.height,
            obRec.width,
        };

        if (CheckCollisionRecs(warriorRec, obstacleRec)) // Check collision between two rectangles
        {
            collision = true;
        }

        if (IsKeyDown(KEY_D) && !jumped) // move if D pressed and not jumping
        {
            warriorAnim.pos.x += speed * deltaTime;    // change position on X axis
            warriorAnim.rec.width = warrior.width / 6; // change sprite frame
            warriorAnim.runningTime += deltaTime;
            if (warriorAnim.runningTime >= warriorAnim.updateTime)
            {
                warriorAnim.runningTime = 0.0;
                warriorAnim.rec.x = warriorAnim.frame * warriorAnim.rec.width;
                warriorAnim.frame++;       // increments frame by one
                if (warriorAnim.frame > 6) // if character is on his last frame go back to frame 0
                {
                    warriorAnim.frame = 0;
                }
            }
        }
        if (IsKeyReleased(KEY_D) && !jumped) // if D released and not jumping
        {
            warriorAnim.frame = 0; // character is on his first frame (still)
            warriorAnim.rec.x = warriorAnim.frame * warriorAnim.rec.width;
        }

        if (IsKeyDown(KEY_A) && !jumped)
        {
            warriorAnim.pos.x -= speed * deltaTime;
            warriorAnim.rec.width = -warrior.width / 6;

            warriorAnim.runningTime += deltaTime;
            if (warriorAnim.runningTime >= warriorAnim.updateTime)
            {
                warriorAnim.runningTime = 0.0;
                warriorAnim.rec.x = warriorAnim.frame * warriorAnim.rec.width;
                warriorAnim.frame++;       // increments frame by one
                if (warriorAnim.frame > 6) // if character is on his last frame go back to frame 0
                {
                    warriorAnim.frame = 0;
                }
            }
        }
        if (IsKeyReleased(KEY_A) && !jumped)
        {
            warriorAnim.frame = 0; // character is on his first frame (still)
            warriorAnim.rec.x = warriorAnim.frame * warriorAnim.rec.width;
        }

        BeginDrawing(); // Setup canvas to start drawing

        if (warriorAnim.pos.y >= windowHeight - warrior.height)
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

        warriorAnim.pos.y += velocity * deltaTime; // acount for delta time frames
        obPos.x += obVel * deltaTime;
        DrawTexture(background, 0, 0, WHITE); // add background image

        if (collision)
        {
            DrawText("GAME OVER", windowWidth / 4, windowHeight / 2, 150, RED); // say Game Over on screen
        }
        else
        {
            DrawTextureRec(warrior, warriorAnim.rec, warriorAnim.pos, WHITE); // add character
            DrawTextureRec(obstacle, obRec, obPos, WHITE);                    // add obstacle
        }
        EndDrawing();
    }
    UnloadMusicStream(music);  // Unload music stream buffers from RAM
    UnloadTexture(background); // unload texture from memory
    UnloadTexture(warrior);    // unload texture from memory
    UnloadTexture(obstacle);   // unload texture from memory
    CloseAudioDevice();        // Close audio device (music streaming is automatically stopped)
    CloseWindow();             // close game window
}