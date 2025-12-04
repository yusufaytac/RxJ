#include "raylib.h"

struct AnimData{
    Rectangle Rec;
    Vector2 Pos;
    int Frame;
    float UpdateTime;
    float MoveTime;
};

int main()
{
    // window dimension
    int WindowDimension[2];
    WindowDimension[0] = 400;
    WindowDimension[1] = 250;

    InitWindow(WindowDimension[0], WindowDimension[1], "Rai x Jin");
    Texture2D Background = LoadTexture("textures/RxJBackground.png");
    

    // rai idle texture
    Texture2D RaiIdle = LoadTexture("textures/rai.png");
    AnimData RaiIdleData{
        {RaiIdle.width/8, RaiIdle.height/7, RaiIdle.width/8, RaiIdle.height/7}, // rectangle rec
        {-15, WindowDimension[1] - RaiIdleData.Rec.height}, // vector2 pos
        1, // int frame
        1.0/6.0, // float update time
        0 // float move time
    };

    while(!WindowShouldClose())
    {   
        // open window
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexture(Background, 0, 0, WHITE);
        

        // delta time 
        const float DeltaTime = GetFrameTime();
        
        // rai idle animation
        RaiIdleData.Pos.x = RaiIdleData.Pos.x; 
        RaiIdleData.MoveTime = RaiIdleData.MoveTime + DeltaTime;
        if(RaiIdleData.MoveTime >= RaiIdleData.UpdateTime)
        {
            RaiIdleData.MoveTime = 0.0;
            RaiIdleData.Rec.x = RaiIdleData.Frame * RaiIdleData.Rec.width;
            RaiIdleData.Frame = RaiIdleData.Frame + 1;
            if(RaiIdleData.Frame > 4)
            {
                RaiIdleData.Frame = 1;
            }
        }
        DrawTextureRec(RaiIdle, RaiIdleData.Rec, RaiIdleData.Pos, WHITE);

        EndDrawing();
    }
    
    UnloadTexture(RaiIdle);
    UnloadTexture(Background);

    CloseWindow();
}