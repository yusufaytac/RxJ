#include "raylib.h"

class Character
{
public:
    void tick(float DeltaTime);
    float DeltaTime = GetFrameTime();
private:
    Texture2D rTexture = LoadTexture("textures/rai.png");
    Texture2D jTexture = LoadTexture("textures/jin.png");

    
    int raiVel = 150;

    const float jumpVel = 0.0f;
    const float gravity = 0.0f;

    struct AnimData{
        Rectangle rec;
        Vector2 pos;
        int frame;
        float updateTime;
        float runningTime;
    };
    
    // rai idle variables
    AnimData raiIdle{
        {rTexture.width-rTexture.width/8 * 7, rTexture.height-rTexture.height/7*6, rTexture.width/8, rTexture.height/7}, // rectangle rec
        {-15, 170}, // vector2 pos
        1, // int frame
        1.0/7.0, // float update time
        0 // float running time
    };

    // rai walk variables
    AnimData raiWalk{
        {rTexture.width-rTexture.width/8 * 7, rTexture.height-rTexture.height/7*5, rTexture.width/8, rTexture.height/7},
        {-15, 170},
        1,
        1.0/12.0,
        0.0
    };

    
    float rightLeft = 1.0;

};
void Character::tick(float DeltaTime)
{
    bool isRaiWalking = false;
    if(IsKeyDown(KEY_D))
    {
        rightLeft = 1.0;
        isRaiWalking = true;
    }
    if(IsKeyDown(KEY_A))
    {
        rightLeft = -1.0;
        isRaiWalking = true;
    }


    // rai idle animation
    if(!isRaiWalking)
    {
        raiIdle.runningTime += DeltaTime;
        if(raiIdle.runningTime >= raiIdle.updateTime)
        {
            raiIdle.runningTime = 0.0f;
            raiIdle.rec.x = raiIdle.rec.width * raiIdle.frame;
            raiIdle.frame ++;
            if(raiIdle.frame > 4)
            {
                raiIdle.frame = 1;
                
            }
        }
    }



    if(!isRaiWalking)
    {
        DrawTextureRec(rTexture, raiIdle.rec, raiIdle.pos, WHITE);
    }
    else
    {
        // rai walk animation
        raiWalk.rec.width = rTexture.width/8 * rightLeft;
        raiWalk.pos.x = raiWalk.pos.x + (rightLeft * raiVel * DeltaTime);
        raiWalk.runningTime = raiWalk.runningTime + DeltaTime;
        raiIdle.pos = raiWalk.pos;
        if(raiWalk.runningTime >= raiWalk.updateTime && isRaiWalking == true)
        {
            raiWalk.runningTime = 0;
            raiWalk.rec.x = raiWalk.frame * raiWalk.rec.width * rightLeft;
            raiWalk.frame = raiWalk.frame + 1;
            if(raiWalk.frame > 4)
            {
                raiWalk.frame = 1;
            }

        }
        DrawTextureRec(rTexture, raiWalk.rec, raiWalk.pos, WHITE);
    }

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