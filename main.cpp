#include "raylib.h"

class Character
{
public:
    void tick(float DeltaTime);
    float DeltaTime = GetFrameTime();
    
    // rai variables
    Vector2 raiPos{-15, 170};
    int raiVel = 250;
    float raiJumpVel = 0.0f, raiGravity = 0.0f;
    bool raiWalking = false, raiOnGround = true, raiInAir = false, raiHasHit = false;
    float raiRightLeft = 1.0;
    int raiHealth = 7;
    bool raiDamageDealt = false;
    
    // jin variables
    Vector2 jinPos{300, 147};
    int jinVel = 250;
    float jinJumpVel = 0.0f, jinGravity = 0.0f;
    bool jinWalking = false, jinOnGround = true, jinInAir = false, jinHasHit = false;
    float jinRightLeft = 1.0;
    int jinHealth = 7;
    bool jinDamageDealt = false;

private:
    
    Texture2D rTexture = LoadTexture("textures/rai.png");
    Texture2D jTexture = LoadTexture("textures/jin.png");
    Texture2D healthbar = LoadTexture("textures/rxjhealth-sheet.png");

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
    // jin healthbar data
    AnimData raiHealthbar{{0, 0, healthbar.width/7, healthbar.height}, {19, 27}, 0, 1.0, 0.0};

    float jFrameWidth = jTexture.width/7;
    float jFrameHeight = jTexture.height/5;
    // jin idle data
    AnimData jinIdle{{jTexture.width-jFrameWidth*6, 0, jFrameWidth, jFrameHeight}, jinPos, 1, 1.0/7.0, 0.0};
    // jin walk data
    AnimData jinWalk{{jTexture.width-jFrameWidth*6, jTexture.height-jFrameHeight*4, jFrameWidth, jFrameHeight}, jinPos, 1, 1.0/12.0, 0.0};
    // jin jump data
    AnimData jinJump{{jTexture.width-jFrameWidth*6, jTexture.height-jFrameHeight*3, jFrameWidth, jFrameHeight}, jinPos, 1, 1.0/4.0, 0.0};
    // jin hit data
    AnimData jinHit{{jTexture.width-jFrameWidth*6, jTexture.height-jFrameHeight*2, jFrameWidth, jFrameHeight}, jinPos, 1, 1.0/12.0, 0.0};
    // jin healthbar data
    AnimData jinHealthbar{{0, 0, healthbar.width/7, healthbar.height}, {284, 27}, 0, 1.0, 0.0};
    
};

void Character::tick(float DeltaTime)
{
    raiWalking = false;
    jinWalking = false;
   
    // collisions
    Rectangle raiCollisionBox;
        raiCollisionBox.x = raiPos.x + 35; 
        raiCollisionBox.y = raiPos.y + 25;
        raiCollisionBox.width = 25; 
        raiCollisionBox.height = 40;
        DrawRectangleLines(raiCollisionBox.x, raiCollisionBox.y, raiCollisionBox.width, raiCollisionBox.height, GREEN);
   
    Rectangle jinCollisionBox;
        jinCollisionBox.x = jinPos.x + 52; 
        jinCollisionBox.y = jinPos.y + 48;
        jinCollisionBox.width = 25; 
        jinCollisionBox.height = 40;
        DrawRectangleLines(jinCollisionBox.x, jinCollisionBox.y, jinCollisionBox.width, jinCollisionBox.height, BLUE);
        

    // rai controller
    if(IsKeyDown(KEY_D)){raiRightLeft = 1.0; raiWalking = true;}
    if(IsKeyDown(KEY_A)){raiRightLeft = -1.0; raiWalking = true;}
    if(IsKeyPressed(KEY_W) && !raiInAir)
    {
        raiWalking = false;
        raiOnGround = false;
        raiInAir = true;
        raiJumpVel = -700.0f;
        raiGravity = 2000.0;
    }
    if(IsKeyPressed(KEY_SPACE))
    {
        raiHasHit = true;
        raiHit.frame = 1;
        raiHit.runningTime = 0;
        raiDamageDealt = false;
    }

    raiJumpVel += raiGravity * DeltaTime;
    raiPos.y = raiPos.y + (raiJumpVel * DeltaTime);
    
    if(raiWalking)
    {
        raiPos.x += raiRightLeft * raiVel * DeltaTime;
    }
    if(raiPos.y >= 170)
    {
        raiPos.y = 170;
        raiJumpVel = 0.0f;
        raiGravity = 0.0f;
        raiOnGround = true;
        raiInAir = false;
    }
    
    // jin controller
    if(IsKeyDown(KEY_RIGHT)){jinRightLeft = 1.0; jinWalking = true;}
    if(IsKeyDown(KEY_LEFT)){jinRightLeft = -1.0; jinWalking = true;}
    if(IsKeyPressed(KEY_UP) && !jinInAir)
    {
        jinWalking = false;
        jinOnGround = false;
        jinInAir = true;
        jinJumpVel = -700.0f;
        jinGravity = 2000.0;
    }
    if(IsKeyPressed(KEY_ENTER))
    {
        jinHasHit = true;
        jinHit.frame = 1;
        jinHit.runningTime = 0;
        jinDamageDealt = false;
    }

    jinJumpVel += jinGravity * DeltaTime;
    jinPos.y = jinPos.y + (jinJumpVel * DeltaTime);
    
    if(jinWalking)
    {
        jinPos.x += jinRightLeft * jinVel * DeltaTime;
    }
    if(jinPos.y >= 147)
    {
        jinPos.y = 147;
        jinJumpVel = 0.0f;
        jinGravity = 0.0f;
        jinOnGround = true;
        jinInAir = false;
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

        // rai attack box
        Rectangle raiAttackBox;
        raiAttackBox.y = raiPos.y + 32;
        raiAttackBox.width = 25;
        raiAttackBox.height = 25;
        
        if(raiRightLeft == 1.0) {raiAttackBox.x = raiCollisionBox.x + raiCollisionBox.width - 5;}
        else {raiAttackBox.x = raiCollisionBox.x - raiAttackBox.width + 5;}

        DrawRectangleLines(raiAttackBox.x, raiAttackBox.y, raiAttackBox.width, raiAttackBox.height, BLUE);

        if(!raiDamageDealt && CheckCollisionRecs(raiAttackBox, jinCollisionBox))
        {
            jinHealth = jinHealth - 1;        
            raiDamageDealt = true; 
        }
    }
    else if (raiInAir)
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
    else if (raiWalking)
    {
        // rai walk
        raiWalk.rec.width = rFrameWidth * raiRightLeft;
        raiWalk.runningTime = raiWalk.runningTime + DeltaTime;
        raiIdle.pos = raiWalk.pos;
        if(raiWalk.runningTime >= raiWalk.updateTime && raiWalking)
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
    // update rai healthbar
    int raiFrame = 7 - raiHealth;
    if(raiFrame > 6) {raiFrame = 6;}
    raiHealthbar.rec.x = raiFrame * healthbar.width/7;

    DrawTextureRec(healthbar, raiHealthbar.rec, raiHealthbar.pos, WHITE);

    // update jin animations
    if(jinHasHit)
    {   
        // jin hit
        jinHit.rec.width = jFrameWidth * jinRightLeft;
        jinHit.runningTime += DeltaTime; 
        if(jinHit.runningTime >= jinHit.updateTime)
        {
            jinHit.runningTime = 0.0;
            jinHit.rec.x = jinHit.frame * jFrameWidth; 
            jinHit.frame++;
            if(jinHit.frame > 4) 
            {
                jinHit.frame = 1;
                jinHasHit = false;
            }
        }
        DrawTextureRec(jTexture, jinHit.rec, jinPos, WHITE);
        
        Rectangle jinAttackBox;
        jinAttackBox.y = jinPos.y + 50;
        jinAttackBox.width = 25;
        jinAttackBox.height = 25;

        if(jinRightLeft == 1.0) {jinAttackBox.x = jinCollisionBox.x + jinCollisionBox.width - 10;}
        else{jinAttackBox.x = jinCollisionBox.x - jinAttackBox.width + 10;}
            
        DrawRectangleLines(jinAttackBox.x, jinAttackBox.y, jinAttackBox.width, jinAttackBox.height, ORANGE);

        if(!jinDamageDealt && CheckCollisionRecs(jinAttackBox, raiCollisionBox))
        {
            raiHealth = raiHealth - 1;
            jinDamageDealt = true;
        }

    }
    else if (jinInAir)
    {   
        // jin jump
        jinJump.rec.width = jFrameWidth * jinRightLeft;
        jinJump.runningTime = jinJump.runningTime + DeltaTime;
        if(jinJump.runningTime >= jinJump.updateTime)
        {
            jinJump.runningTime = 0;
            jinJump.rec.x = jinJump.frame * jFrameWidth;
            jinJump.frame ++;
            if(jinJump.frame > 2){jinJump.frame = 1;}
        }
        DrawTextureRec(jTexture, jinJump.rec, jinPos, WHITE);
    }

    else if (jinWalking)
    {
        // jin walk
        jinWalk.rec.width = jFrameWidth * jinRightLeft;
        jinWalk.runningTime = jinWalk.runningTime + DeltaTime;
        jinIdle.pos = jinWalk.pos;
        if(jinWalk.runningTime >= jinWalk.updateTime && jinWalking)
        {
            jinWalk.runningTime = 0;
            jinWalk.rec.x = jinWalk.frame * jFrameWidth;
            jinWalk.frame ++;
            if(jinWalk.frame > 4){jinWalk.frame = 1;}
        }
        DrawTextureRec(jTexture, jinWalk.rec, jinPos, WHITE);
    }
    
    else
    {
        // jin idle
        jinIdle.rec.width = jFrameWidth * jinRightLeft;
        jinIdle.runningTime += DeltaTime;
        if(jinIdle.runningTime >= jinIdle.updateTime)
        {
            jinIdle.runningTime = 0.0f;
            jinIdle.rec.x = jFrameWidth * jinIdle.frame;
            jinIdle.frame ++;
            if(jinIdle.frame > 3){jinIdle.frame = 1;}
        }
        DrawTextureRec(jTexture, jinIdle.rec, jinPos, WHITE);
    }
    // update jin healthbar
    int jinFrame = 7 - jinHealth;
    if(jinFrame > 6) {jinFrame = 6;}
    jinHealthbar.rec.x = jinFrame * healthbar.width/7;
    jinHealthbar.rec.width = -healthbar.width/7;

    DrawTextureRec(healthbar, jinHealthbar.rec, jinHealthbar.pos, WHITE);
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