#include "raylib.h"

class Character
{
public:
    void tick(float DeltaTime);

private:
    Texture2D rTexture = LoadTexture("textures/rai.png");
    Texture2D jTexture = LoadTexture("textures/jin.png");

    const float jumpVel = 0.0f;
    const float gravity = 0.0f;

    struct AnimData{
        Rectangle rec;
        Vector2 pos;
        int frame;
        float updateTime;
        float runningTime;
    };
    
    float rightLeft = 1.0;

};
void Character::tick(float DeltaTime)
{
    // rai idle animation variables
    AnimData raiIdle{
        {rTexture.width-rTexture.width/8 * 7, rTexture.height-rTexture.height/7*6, rTexture.width/8, rTexture.height/7}, // rectangle rec
        {-15, 250 - raiIdle.rec.height}, // vector2 pos
        1, // int frame
        1.0/6.0, // float update time
        0 // float move time
    };

    // rai idle animation

    DrawTextureRec(rTexture, raiIdle.rec, raiIdle.pos, WHITE);

}

int main()
{
    // window dimensions
    const int windowWidth = 400;
    const int windowHeight = 250;
    InitWindow(windowWidth, windowHeight, "Rai vs Jin");

    Texture2D background = LoadTexture("textures/rxjbackground.png");

    Character rai;
    Character jin;

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexture(background, 0, 0, WHITE);
        
        rai.tick(GetFrameTime());
        jin.tick(GetFrameTime());
        
        EndDrawing();
    }
    UnloadTexture(background);
    CloseWindow();
}