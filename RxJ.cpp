#include "raylib.h"

struct AnimData
{
    Rectangle Rec;
    Vector2 Pos;
    int Frame;
    float UpdateTime;
    float MoveTime;
};

int main()
{
    // window dimensions
    int WindowDimension[2];
    WindowDimension[0] = 400;
    WindowDimension[1] = 250;

    InitWindow(WindowDimension[0], WindowDimension[1], "Rai x Jin");
    
    // background texture
    Texture2D Background = LoadTexture("textures/RxJBackground.png");

    // rai texture
    Texture2D Rai = LoadTexture("textures/rai.png");
    AnimData RaiIdleData{
        {Rai.width-Rai.width/8 * 7, Rai.height-Rai.height/7*6, Rai.width/8, Rai.height/7},
        {-15, 170},
        1,
        1.0/7.0,
        0.0
    };

    // jin texture
    Texture2D Jin = LoadTexture("textures/jin.png");
    AnimData JinIdleData{
        {Jin.width-Jin.width/7*6, 0, Jin.width/7, Jin.height/5},
        {300, 147},
        1,
        1.0/7.0,
        0.0
    };

    bool RaiIsWalking = false;
    bool JinIsWalking = false;
    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexture(Background, 0, 0, WHITE);

        // deltatime
        const float DeltaTime = GetFrameTime();
        
        // rai idle animation
        if(!RaiIsWalking)
        {
            RaiIdleData.Pos.x = RaiIdleData.Pos.x;
            RaiIdleData.MoveTime = RaiIdleData.MoveTime + DeltaTime;
            if(RaiIdleData.MoveTime >= RaiIdleData.UpdateTime)
            {
                RaiIdleData.MoveTime = 0.0;
                RaiIdleData.Rec.x = RaiIdleData.Frame * RaiIdleData.Rec.width;
                RaiIdleData.Frame = RaiIdleData.Frame + 1;
                if(RaiIdleData.Frame >4)
                {
                    RaiIdleData.Frame = 1;
                }
            }
        }

        // jin idle animation
        if(!JinIsWalking)
        {
            JinIdleData.Pos.x = JinIdleData.Pos.x;
            JinIdleData.MoveTime = JinIdleData.MoveTime + DeltaTime;
            if(JinIdleData.MoveTime >= JinIdleData.UpdateTime)
            {
                JinIdleData.MoveTime = 0.0;
                JinIdleData.Rec.x = JinIdleData.Frame * JinIdleData.Rec.width;
                JinIdleData.Frame = JinIdleData.Frame + 1;
                if(JinIdleData.Frame >3)
                {
                    JinIdleData.Frame = 1;
                }
            }
        }

        if(!RaiIsWalking)
        {
            DrawTextureRec(Rai, RaiIdleData.Rec, RaiIdleData.Pos, WHITE);
        }
        if(!JinIsWalking)
        {
            DrawTextureRec(Jin, JinIdleData.Rec, JinIdleData.Pos, WHITE);
        }
        
        EndDrawing();
    }
    UnloadTexture(Jin);
    UnloadTexture(Rai);
    UnloadTexture(Background);
    CloseWindow();
}