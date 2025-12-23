#include "raylib.h"

class Character
{
public:

    void tick(float DeltaTime);
    float DeltaTime = GetFrameTime();
    
    // char variables
    Vector2 raiPos{-15, 170};
    int raiVel = 250;
    float raiJumpVel = 0.0f;
    float raiGravity = 0.0f;

    bool isRaiWalking = false;
    bool isRaiOnGround = true;
    bool isRaiInAir = false;
    bool raiHasHit = false;

    float raiRightLeft = 1.0;
    
private:
    Texture2D rTexture = LoadTexture("textures/rai.png");
    Texture2D jTexture = LoadTexture("textures/jin.png");

    struct AnimData{
        Rectangle rec;
        Vector2 pos;
        int frame;
        float updateTime;
        float runningTime;
    };

    float rFrameWidth = rTexture.width/8;
    float rFrameHeight = rTexture.height/7;

    // rai idle data
    AnimData raiIdle{{rTexture.width-rFrameWidth * 7, rTexture.height-rFrameHeight*6, rFrameWidth, rFrameHeight}, raiPos, 1, 1.0/7.0, 0.0};
    // rai walk data
    AnimData raiWalk{{rTexture.width-rFrameWidth * 7, rTexture.height-rFrameHeight*5, rFrameWidth, rFrameHeight}, raiPos, 1, 1.0/12.0, 0.0};
    // rai jump data
    AnimData raiJump{{rTexture.width-rFrameWidth * 7, rTexture.height-rFrameHeight*4, rFrameWidth, rFrameHeight}, raiPos, 1, 1.0/4.0, 0.0};
    // rai hit data
    AnimData raiHit{{rTexture.width-rFrameWidth * 7, rTexture.height-rFrameHeight*3,  rFrameWidth, rFrameHeight}, raiPos, 1,1.0/12.0, 0.0};

};

void Character::tick(float DeltaTime)
{
    isRaiWalking = false;


    if(IsKeyDown(KEY_D)){raiRightLeft = 1.0; isRaiWalking = true;}
    if(IsKeyDown(KEY_A)){raiRightLeft = -1.0; isRaiWalking = true;}
    if(IsKeyPressed(KEY_W) && !isRaiInAir)
    {
        isRaiWalking = false;
        isRaiOnGround = false;
        isRaiInAir = true;
        raiJumpVel = -700.0f;
        raiGravity = 2000.0;
    }
    if(IsKeyPressed(KEY_SPACE))
    {
        raiHasHit = true;
        raiHit.frame = 1;
        raiHit.runningTime = 0;
    }

    raiJumpVel += raiGravity * DeltaTime;
    raiPos.y = raiPos.y + (raiJumpVel * DeltaTime);
    
    if(isRaiWalking)
    {
        raiPos.x += raiRightLeft * raiVel * DeltaTime;
    }
    if(raiPos.y >= 170)
    {
        raiPos.y = 170;
        raiJumpVel = 0.0f;
        raiGravity = 0.0f;
        isRaiOnGround = true;
        isRaiInAir = false;
    }
    
    // update rai animations
    if(raiHasHit)
    {   
        // rai hit
        raiHit.rec.width = rFrameWidth * raiRightLeft;
        raiHit.runningTime += DeltaTime;
        
        if(raiHit.runningTime >= raiHit.updateTime)
        {
            raiHit.runningTime = 0.0;
            raiHit.rec.x = raiHit.frame * rFrameWidth; 
            raiHit.frame++;
            if(raiHit.frame > 4) 
            {
                raiHit.frame = 1;
                raiHasHit = false;
            }
        }
        DrawTextureRec(rTexture, raiHit.rec, raiPos, WHITE);
    }
    else if (isRaiInAir)
    {   
        // rai jump
        raiJump.rec.width = rFrameWidth * raiRightLeft;
        raiJump.runningTime = raiJump.runningTime + DeltaTime;
        if(raiJump.runningTime >= raiJump.updateTime)
        {
            raiJump.runningTime = 0;
            raiJump.rec.x = raiJump.frame * rFrameWidth;
            raiJump.frame ++;
            if(raiJump.frame > 2){raiJump.frame = 1;}
        }
        DrawTextureRec(rTexture, raiJump.rec, raiPos, WHITE);
    }

    else if (isRaiWalking)
    {
        // rai walk
        raiWalk.rec.width = rFrameWidth * raiRightLeft;
        raiWalk.runningTime = raiWalk.runningTime + DeltaTime;
        raiIdle.pos = raiWalk.pos;
        if(raiWalk.runningTime >= raiWalk.updateTime && isRaiWalking == true)
        {
            raiWalk.runningTime = 0;
            raiWalk.rec.x = raiWalk.frame * rFrameWidth;
            raiWalk.frame ++;
            if(raiWalk.frame > 4){raiWalk.frame = 1;}
        }
        DrawTextureRec(rTexture, raiWalk.rec, raiPos, WHITE);
    }
    
    else
    {
        // rai idle
        raiIdle.rec.width = rFrameWidth * raiRightLeft;
        raiIdle.runningTime += DeltaTime;
        if(raiIdle.runningTime >= raiIdle.updateTime)
        {
            raiIdle.runningTime = 0.0f;
            raiIdle.rec.x = rFrameWidth * raiIdle.frame;
            raiIdle.frame ++;
            if(raiIdle.frame > 4){raiIdle.frame = 1;}
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