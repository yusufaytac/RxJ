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
    
    const int Gravity = 2000;

    // textures
    Texture2D Background = LoadTexture("textures/RxJBackground_2.png");
    Texture2D Rai = LoadTexture("textures/rai.png");
    Texture2D Jin = LoadTexture("textures/jin.png");
    Texture2D Healthbar = LoadTexture("textures/rxjhealth-sheet.png");
    Texture2D RaiWin = LoadTexture("textures/raiwin.png");
    Texture2D JinWin = LoadTexture("textures/jinwin.png");


    // rai healthbar data
    AnimData RaiHealthbarData{
        {0, 0, Healthbar.width/7, Healthbar.height},
        {19, 27},
        0,
        1.0,
        0.0
    };

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
    const int RaiVelocity = 200;
    AnimData RaiRunData{
        {Rai.width-Rai.width/8 * 7, Rai.height-Rai.height/7*5, Rai.width/8, Rai.height/7},
        {-15, 170},
        1,
        1.0/12.0,
        0.0
    };

    // rai jump data
    const int RaiJumpPower = -600;
    float RaiVelocityY = 0.0;
    AnimData RaiJumpData{
        {Rai.width-Rai.width/8 * 7, Rai.height-Rai.height/7*4, Rai.width/8, Rai.height/7},
        {-15, 170},
        1,
        1.0/4.0,
        0.0

    };

    // rai hit data
    AnimData RaiHitData{
        {Rai.width-Rai.width/8 * 7, Rai.height-Rai.height/7*3, Rai.width/8, Rai.height/7},
        {-15, 170},
        1,
        1.0/12.0,
        0.0
    };

    // jin healthbar data
    AnimData JinHealthbarData{
        {0, 0, Healthbar.width/7, Healthbar.height},
        {284, 27},
        0,
        1.0,
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

    // jin jump data
    const float JinJumpPower = -600;
    float JinVelocityY = 0.0;
    AnimData JinJumpData{
        {Jin.width-Jin.width/7*6, Jin.height-Jin.height/5*3, Jin.width/7, Jin.height/5},
        {300, 147},
        1,
        1.0/4.0,
        0.0
    };
    // jin hit data
    AnimData JinHitData{
        {Jin.width-Jin.width/7*6, Jin.height-Jin.height/5*2, Jin.width/7, Jin.height/5},
        {300, 147},
        1,
        1.0/12.0,
        0.0
    };
    
    bool JinIsGrounded = true;
    float JinFacing = 1.0;
    bool JinIsHit = false;

    bool RaiIsGrounded = true;
    bool RaiIsHit = false;
    float RaiFacing = 1.0;

    int RaiHealth = 7;
    int JinHealth = 7;

    bool RaiDamageDealt = false;
    bool JinDamageDealt = false;
    
    bool GameOver = false;

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

        // update rain healthbar
        int RaiFrame = 7 - RaiHealth;
        if(RaiFrame > 6)
        {
            RaiFrame = 6;
        }
        RaiHealthbarData.Rec.x = RaiFrame * Healthbar.width/7;


        // update jin healthbar
        int JinFrame = 7 - JinHealth;
        if(JinFrame > 6)
        {
            JinFrame = 6;
        }
        JinHealthbarData.Rec.x = JinFrame * Healthbar.width/7;
        JinHealthbarData.Rec.width = -Healthbar.width/7;

        if(!GameOver)
        {
        //rai collision box
        Rectangle RaiCollisionBox;
        RaiCollisionBox.x = RaiRunData.Pos.x + 40; 
        RaiCollisionBox.y = RaiRunData.Pos.y + 20;
        RaiCollisionBox.width = RaiFrameWidth - 70; 
        RaiCollisionBox.height = (Rai.height/7) - 40;
        //DrawRectangleLines(RaiCollisionBox.x, RaiCollisionBox.y, RaiCollisionBox.width, RaiCollisionBox.height, RED);

        //jin collision box
        Rectangle JinCollisionBox;
        JinCollisionBox.x = JinRunData.Pos.x + 50; 
        JinCollisionBox.y = JinRunData.Pos.y + 43;
        JinCollisionBox.width = JinFrameWidth - 100; 
        JinCollisionBox.height = (Jin.height/5) -72;
        //DrawRectangleLines(JinCollisionBox.x, JinCollisionBox.y, JinCollisionBox.width, JinCollisionBox.height, GREEN);



        // rai idle animation
        if(RaiFacing == -1.0)
        {
            RaiIdleData.Rec.width = -RaiFrameWidth;
        }
        else
        {
            RaiIdleData.Rec.width = RaiFrameWidth;
        }

        if(!RaiIsRunning)
        {
            RaiIdleData.Pos.x = RaiIdleData.Pos.x;
            RaiIdleData.MoveTime = RaiIdleData.MoveTime + DeltaTime;
            if(RaiIdleData.MoveTime >= RaiIdleData.UpdateTime)
            {
                RaiIdleData.MoveTime = 0.0;
                RaiIdleData.Rec.x = RaiIdleData.Frame * RaiFrameWidth;
                RaiIdleData.Frame = RaiIdleData.Frame + 1;
                if(RaiIdleData.Frame >4)
                {
                    RaiIdleData.Frame = 1;
                }
            }
        }
        // rai run animation
        if(IsKeyDown(KEY_D) && RaiCollisionBox.x <= 360)
        {
            RaiIsRunning = true;
            RaiFacing = 1.0f;
            RaiRunData.Rec.width = RaiFrameWidth;
            RaiRunData.Pos.x = RaiRunData.Pos.x + (RaiVelocity * DeltaTime);
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
        if(IsKeyDown(KEY_A) && RaiCollisionBox.x >= 5)
        {
            RaiIsRunning = true;
            RaiFacing = -1.0;
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

        // rai jump animation
        if(RaiFacing == -1.0) 
        {
            RaiJumpData.Rec.width = -RaiFrameWidth;
        }
        else 
        {
            RaiJumpData.Rec.width = RaiFrameWidth;
        }

        RaiJumpData.Pos = RaiRunData.Pos;
        RaiVelocityY = RaiVelocityY + Gravity * DeltaTime;
        if(IsKeyDown(KEY_W) && RaiIsGrounded)
        {
            RaiVelocityY = RaiJumpPower;
            RaiIsGrounded = false;
        }

        RaiRunData.Pos.y = RaiRunData.Pos.y + RaiVelocityY * DeltaTime;
        RaiIdleData.Pos.y = RaiRunData.Pos.y;
        RaiJumpData.Pos.y = RaiRunData.Pos.y;

        if (RaiRunData.Pos.y >= 170) 
        {
            RaiRunData.Pos.y = 170;
            RaiIdleData.Pos.y = 170;
            RaiVelocityY = 0;
            RaiIsGrounded = true;
        }

        if (!RaiIsGrounded)
        {
            RaiJumpData.MoveTime = RaiJumpData.MoveTime + DeltaTime;
            if(RaiJumpData.MoveTime >= RaiJumpData.UpdateTime)
            {
                RaiJumpData.MoveTime = 0;
                RaiJumpData.Rec.x = RaiJumpData.Frame * RaiFrameWidth;
                RaiJumpData.Frame = RaiJumpData.Frame + 1;
                if(RaiJumpData.Frame > 2) 
                {
                    RaiJumpData.Frame = 1; 
                }
            }
        }

        // rai hit animation
        if(IsKeyPressed(KEY_SPACE))
        {   
            RaiIsHit = true;
            RaiDamageDealt = false;
            if(RaiFacing == -1.0)
            {
                RaiHitData.Rec.width = -RaiFrameWidth;
            }
            else
            {
                RaiHitData.Rec.width = RaiFrameWidth;
            }
            RaiHitData.Rec.x = RaiFrameWidth;
            RaiHitData.Frame = 1;
            RaiHitData.MoveTime = 0;
        }
        RaiHitData.Pos = RaiRunData.Pos;
        if(RaiIsHit)
        {
            RaiHitData.MoveTime = RaiHitData.MoveTime + DeltaTime;
            if(RaiHitData.MoveTime >= RaiHitData.UpdateTime)
            {
                RaiHitData.MoveTime = 0.0;
                RaiHitData.Rec.x = RaiHitData.Frame * RaiFrameWidth;
                RaiHitData.Frame = RaiHitData.Frame + 1; 

                if(RaiHitData.Frame > 4)
                {
                    RaiIsHit = false;
                    RaiHitData.Frame = 1;
                }
            }
        }

        // jin idle animation
        if(JinFacing == -1.0)
        {
            JinIdleData.Rec.width = -JinFrameWidth;
        }
        else
        {
            JinIdleData.Rec.width = JinFrameWidth;
        }
        if(!JinIsRunning)
        {
            JinIdleData.Pos.x = JinIdleData.Pos.x;
            JinIdleData.MoveTime = JinIdleData.MoveTime + DeltaTime;
            if(JinIdleData.MoveTime >= JinIdleData.UpdateTime)
            {
                JinIdleData.MoveTime = 0.0;
                JinIdleData.Rec.x = JinIdleData.Frame * JinFrameWidth;
                JinIdleData.Frame = JinIdleData.Frame + 1;
                if(JinIdleData.Frame >3)
                {
                    JinIdleData.Frame = 1;
                }
            }
        }
        
        // jin run animation
        if(IsKeyDown(KEY_RIGHT) && JinCollisionBox.x <= 355)
        {
            JinIsRunning = true;
            JinFacing = 1.0;
            JinRunData.Rec.width = JinFrameWidth;
            JinRunData.Pos.x = JinRunData.Pos.x + (JinVelocity * DeltaTime);
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
        if(IsKeyDown(KEY_LEFT) && JinCollisionBox.x >= 0)
        {
            JinIsRunning = true;
            JinFacing = -1.0;
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

        // jin jump animation
        if(JinFacing == -1.0)
        {
            JinJumpData.Rec.width = -JinFrameWidth;
        }
        else
        {
            JinJumpData.Rec.width = JinFrameWidth;
        }
        JinJumpData.Pos = JinRunData.Pos;
        JinVelocityY = JinVelocityY + Gravity * DeltaTime;
        if(IsKeyDown(KEY_UP) && JinIsGrounded)
        {
            JinVelocityY = JinJumpPower;
            JinIsGrounded = false;
        }

        JinRunData.Pos.y = JinRunData.Pos.y + JinVelocityY * DeltaTime;
        JinIdleData.Pos.y = JinRunData.Pos.y;
        JinJumpData.Pos.y = JinRunData.Pos.y;

        if (JinRunData.Pos.y >= 147) 
        {
            JinRunData.Pos.y = 147;
            JinIdleData.Pos.y = 147;
            JinVelocityY = 0;
            JinIsGrounded = true;
        }

        if (!JinIsGrounded)
        {
            JinJumpData.MoveTime = JinJumpData.MoveTime + DeltaTime;
            if(JinJumpData.MoveTime >= JinJumpData.UpdateTime)
            {
                JinJumpData.MoveTime = 0;
                JinJumpData.Rec.x = JinJumpData.Frame * JinFrameWidth;
                JinJumpData.Frame = JinJumpData.Frame + 1;
                if(JinJumpData.Frame > 2) 
                {
                    JinJumpData.Frame = 1; 
                }
            }
        }

        // jin hit animation
        if(IsKeyPressed(KEY_ENTER))
        {   
            JinIsHit = true;
            JinDamageDealt = false;
            if(JinFacing == -1.0)
            {
                JinHitData.Rec.width = -JinFrameWidth;
            }
            else
            {
                JinHitData.Rec.width = JinFrameWidth;
            }
            
            JinHitData.Rec.x = JinFrameWidth;
            JinHitData.Frame = 1;
            JinHitData.MoveTime = 0;
        }
        
        JinHitData.Pos = JinRunData.Pos;
        
        if(JinIsHit)
        {
            JinHitData.MoveTime = JinHitData.MoveTime + DeltaTime;
            if(JinHitData.MoveTime >= JinHitData.UpdateTime)
            {
                JinHitData.MoveTime = 0.0;
                
                JinHitData.Rec.x = JinHitData.Frame * JinFrameWidth;
                JinHitData.Frame = JinHitData.Frame + 1; 

                if(JinHitData.Frame > 4)
                {
                    JinIsHit = false;
                    JinHitData.Frame = 1;
                }
            }
        }

        // rai attack box
        if(RaiIsHit)
        {
            Rectangle RaiAttackBox;
            RaiAttackBox.y = RaiRunData.Pos.y + 32;
            RaiAttackBox.width = 26;
            RaiAttackBox.height = 25;
        
            if(RaiFacing == 1.0) 
            {
                RaiAttackBox.x = RaiCollisionBox.x + RaiCollisionBox.width - 15;
            }
            else 
            {
                RaiAttackBox.x = RaiCollisionBox.x - RaiAttackBox.width + 15;
            }

            //DrawRectangleLines(RaiAttackBox.x, RaiAttackBox.y, RaiAttackBox.width, RaiAttackBox.height, BLUE);

            if(!RaiDamageDealt && CheckCollisionRecs(RaiAttackBox, JinCollisionBox))
            {
                JinHealth = JinHealth - 1;        
                RaiDamageDealt = true; 
            }
        }

        // Jin attack box
        if(JinIsHit)
        {
            Rectangle JinAttackBox;
            JinAttackBox.y = JinRunData.Pos.y + 40;
            JinAttackBox.width = 30;
            JinAttackBox.height = 40;

            if(JinFacing == 1.0)
            {
                JinAttackBox.x = JinCollisionBox.x + JinCollisionBox.width - 20;
            }
            else
            {
                JinAttackBox.x = JinCollisionBox.x - JinAttackBox.width + 20;
            }
            
            //DrawRectangleLines(JinAttackBox.x, JinAttackBox.y, JinAttackBox.width, JinAttackBox.height, ORANGE);

            if(!JinDamageDealt && CheckCollisionRecs(JinAttackBox, RaiCollisionBox))
            {
                RaiHealth = RaiHealth - 1;
                JinDamageDealt = true;
            }
        }



        // draws

        DrawTextureRec(Healthbar, RaiHealthbarData.Rec, RaiHealthbarData.Pos, WHITE);
        DrawTextureRec(Healthbar, JinHealthbarData.Rec, JinHealthbarData.Pos, WHITE);

        if(RaiIsHit)
        {
            DrawTextureRec(Rai, RaiHitData.Rec, RaiHitData.Pos, WHITE);
        }
        else if(!RaiIsGrounded)
        {
            DrawTextureRec(Rai, RaiJumpData.Rec, RaiJumpData.Pos, WHITE);            
        }
        else if(RaiIsRunning)
        {
            DrawTextureRec(Rai, RaiRunData.Rec, RaiRunData.Pos, WHITE);
        }
        else
        {
            DrawTextureRec(Rai, RaiIdleData.Rec, RaiIdleData.Pos, WHITE);
        }

        

        if(JinIsHit)
        {
            DrawTextureRec(Jin, JinHitData.Rec, JinHitData.Pos, WHITE);
        }
        else if(!JinIsGrounded)
        {
           DrawTextureRec(Jin, JinJumpData.Rec, JinJumpData.Pos, WHITE);
        }
        else if(JinIsRunning)
        {
            DrawTextureRec(Jin, JinRunData.Rec, JinRunData.Pos, WHITE);
        }
        else
        {
             DrawTextureRec(Jin, JinIdleData.Rec, JinIdleData.Pos, WHITE);
        }
        
        if (RaiHealth == 0 || JinHealth == 0)
        {
            GameOver = true;
        }

        }
        else
        {
            if(RaiHealth == 0)
            {
                DrawTexture(JinWin, 0, 0, WHITE);
            }
            else if(JinHealth == 0)
            {
                DrawTexture(RaiWin, 0, 0, WHITE);
            }
        }

        EndDrawing();
    }
    UnloadTexture(RaiWin);
    UnloadTexture(JinWin);
    UnloadTexture(Healthbar);
    UnloadTexture(Jin);
    UnloadTexture(Rai);
    UnloadTexture(Background);
    CloseWindow();
}