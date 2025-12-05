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
    
    // textures
    Texture2D Background = LoadTexture("textures/RxJBackground.png");
    Texture2D Rai = LoadTexture("textures/rai.png");
    Texture2D Jin = LoadTexture("textures/jin.png");

    // rai idle data
    AnimData RaiIdleData{
        {Rai.width-Rai.width/8 * 7, Rai.height-Rai.height/7*6, Rai.width/8, Rai.height/7},
        {-15, 170},
        1,
        1.0/7.0,
        0.0
    };

    // rai run data
    const float RaiFrameWidth = Rai.width/8;
    const int RaiVelocity = 150;
    AnimData RaiRunData{
        {Rai.width-Rai.width/8 * 7, Rai.height-Rai.height/7*5, Rai.width/8, Rai.height/7},
        {-15, 170},
        1,
        1.0/12.0,
        0.0
    };

    // jin idle data
    AnimData JinIdleData{
        {Jin.width-Jin.width/7*6, 0, Jin.width/7, Jin.height/5},
        {300, 147},
        1,
        1.0/7.0,
        0.0
    };

    // jin run data
    const float JinFrameWidth = Jin.width/7;
    const int JinVelocity = 150;
    AnimData JinRunData{
        {Jin.width-Jin.width/7*6, Jin.height-Jin.height/5*4, Jin.width/7, Jin.height/5},
        {300, 147},
        1,
        1.0/12.0,
        0.0
    };

    
    
    
    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexture(Background, 0, 0, WHITE);
        bool RaiIsRunning = false;
        bool JinIsRunning = false;

        // deltatime
        const float DeltaTime = GetFrameTime();
        
        // rai idle animation
        if(!RaiIsRunning)
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
        // rai run animation
        if(IsKeyDown(KEY_D))
        {
            RaiIsRunning = true;
            RaiRunData.Rec.width = RaiFrameWidth;
            RaiRunData.Pos.x = RaiRunData.Pos.x + (RaiVelocity * DeltaTime);
            RaiRunData.MoveTime = RaiRunData.MoveTime + DeltaTime;
            RaiIdleData.Pos = RaiRunData.Pos;
            if(RaiRunData.MoveTime >= RaiRunData.UpdateTime && RaiIsRunning == true)
            {
                RaiRunData.MoveTime = 0;
                RaiRunData.Rec.x = RaiRunData.Frame * RaiRunData.Rec.width;
                RaiRunData.Frame = RaiRunData.Frame + 1;
                if(RaiRunData.Frame > 4)
                {
                    RaiRunData.Frame = 1;
                }

            }
        }
        if(IsKeyDown(KEY_A))
        {
            RaiIsRunning = true;
            RaiRunData.Rec.width = -RaiFrameWidth;
            RaiRunData.Pos.x = RaiRunData.Pos.x + (-RaiVelocity * DeltaTime);
            RaiRunData.MoveTime = RaiRunData.MoveTime + DeltaTime;
            RaiIdleData.Pos = RaiRunData.Pos;
            if(RaiRunData.MoveTime >= RaiRunData.UpdateTime && RaiIsRunning == true)
            {
                RaiRunData.MoveTime = 0;
                RaiRunData.Rec.x = RaiRunData.Frame * RaiFrameWidth;
                RaiRunData.Frame = RaiRunData.Frame + 1;
                if(RaiRunData.Frame > 4)
                {
                    RaiRunData.Frame = 1;
                }

            }
        }

        // jin idle animation
        if(!JinIsRunning)
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
        
        // jin run animation
        if(IsKeyDown(KEY_RIGHT))
        {
            JinIsRunning = true;
            JinRunData.Rec.width = JinFrameWidth;
            JinRunData.Pos.x = JinRunData.Pos.x + (JinVelocity * DeltaTime);
            JinRunData.MoveTime = JinRunData.MoveTime + DeltaTime;
            JinIdleData.Pos = JinRunData.Pos;
            if(JinRunData.MoveTime >= JinRunData.UpdateTime && JinIsRunning == true)
            {
                JinRunData.MoveTime = 0;
                JinRunData.Rec.x = JinRunData.Frame * JinRunData.Rec.width;
                JinRunData.Frame = JinRunData.Frame + 1;
                if(JinRunData.Frame > 4)
                {
                    JinRunData.Frame = 1;
                }

            }
        }
        if(IsKeyDown(KEY_LEFT))
        {
            JinIsRunning = true;
            JinRunData.Rec.width = -JinFrameWidth;
            JinRunData.Pos.x = JinRunData.Pos.x + (-JinVelocity * DeltaTime);
            JinRunData.MoveTime = JinRunData.MoveTime + DeltaTime;
            JinIdleData.Pos = JinRunData.Pos;
            if(JinRunData.MoveTime >= JinRunData.UpdateTime && JinIsRunning == true)
            {
                JinRunData.MoveTime = 0;
                JinRunData.Rec.x = JinRunData.Frame * JinFrameWidth;
                JinRunData.Frame = JinRunData.Frame + 1;
                if(JinRunData.Frame > 4)
                {
                    JinRunData.Frame = 1;
                }

            }
        }


        if(!RaiIsRunning)
        {
            DrawTextureRec(Rai, RaiIdleData.Rec, RaiIdleData.Pos, WHITE);
        }
        else
        {
            DrawTextureRec(Rai, RaiRunData.Rec, RaiRunData.Pos, WHITE);
        }
        if(!JinIsRunning)
        {
            DrawTextureRec(Jin, JinIdleData.Rec, JinIdleData.Pos, WHITE);
        }
        else
        {
            DrawTextureRec(Jin, JinRunData.Rec, JinRunData.Pos, WHITE);
        }
        
        EndDrawing();
    }
    UnloadTexture(Jin);
    UnloadTexture(Rai);
    UnloadTexture(Background);
    CloseWindow();
}