#include "raylib.h"

class Character
{
public:
    void tick(float DeltaTime);
    float DeltaTime = GetFrameTime();
private:
    Texture2D rTexture = LoadTexture("textures/rai.png");
    Texture2D jTexture = LoadTexture("textures/jin.png");

   

    Vector2 raiPos{-15, 170};
    int raiVel = 250;
    float raiJumpVel = 0.0f;
    float gravity = 0.0f;

    bool isRaiWalking = false;
    bool isRaiOnGround = true;
    bool isRaiInAir = false;


    struct AnimData{
        Rectangle rec;
        Vector2 pos;
        int frame;
        float updateTime;
        float runningTime;
    };
    
    // rai idle data
    AnimData raiIdle{
        {rTexture.width-rTexture.width/8 * 7, rTexture.height-rTexture.height/7*6, rTexture.width/8, rTexture.height/7}, // rectangle rec
        raiPos, // vector2 pos
        1, // int frame
        1.0/7.0, // float update time
        0 // float running time
    };

    // rai walk data
    AnimData raiWalk{
        {rTexture.width-rTexture.width/8 * 7, rTexture.height-rTexture.height/7*5, rTexture.width/8, rTexture.height/7},
        raiPos,
        1,
        1.0/12.0,
        0.0
    };

    // rai jump data
    AnimData raiJump{
        {rTexture.width-rTexture.width/8 * 7, rTexture.height-rTexture.height/7*4, rTexture.width/8,rTexture.height/7},
        {raiPos},
        1,
        1.0/4.0,
        0.0
    };

    float rightLeft = 1.0;

};
void Character::tick(float DeltaTime)
{
    isRaiWalking = false;

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
    if(IsKeyPressed(KEY_W) && !isRaiInAir)
    {
        isRaiWalking = false;
        isRaiOnGround = false;
        isRaiInAir = true;

        raiJumpVel = -1000.0f;
        gravity = 70.0;
    }
        
    raiJumpVel += gravity;
    raiPos.y = raiPos.y + (raiJumpVel * DeltaTime);
    if(isRaiWalking)
    {
        raiPos.x = raiPos.x + (rightLeft * raiVel * DeltaTime);
    }
    if(raiPos.y >= 170)
    {
        raiPos.y = 170;
        raiJumpVel = 0.0f;
        gravity = 0.0f;
        isRaiOnGround = true;
        isRaiInAir = false;
    }

    if (isRaiInAir)
    {   
        raiJump.rec.width = rTexture.width/8 * rightLeft;

        raiJump.runningTime = raiJump.runningTime + DeltaTime;
        if(raiJump.runningTime >= raiJump.updateTime)
        {
            raiJump.runningTime = 0;
            raiJump.rec.x = raiJump.frame * raiJump.rec.width * rightLeft;
            raiJump.frame = raiJump.frame + 1;
            if(raiJump.frame > 2) 
                {
                    raiJump.frame = 1; 
                }
        }
        DrawTextureRec(rTexture, raiJump.rec, raiPos, WHITE);
    }
    else if (isRaiWalking)
    {
        // rai walk animation
        raiWalk.rec.width = rTexture.width/8 * rightLeft;
        
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
        DrawTextureRec(rTexture, raiWalk.rec, raiPos, WHITE);
    }
    
    else
    {
        // rai idle animation
        raiIdle.rec.width = rTexture.width/8 * rightLeft;

        raiIdle.runningTime += DeltaTime;
        if(raiIdle.runningTime >= raiIdle.updateTime)
        {
            raiIdle.runningTime = 0.0f;
            raiIdle.rec.x = raiIdle.rec.width * raiIdle.frame * rightLeft;
            raiIdle.frame ++;
            if(raiIdle.frame > 4)
            {
                raiIdle.frame = 1;
                
            }
        }
        DrawTextureRec(rTexture, raiIdle.rec, raiPos, WHITE);
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