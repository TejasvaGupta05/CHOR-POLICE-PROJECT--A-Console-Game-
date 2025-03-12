#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main() {
    InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT, "Smooth Circle Movement");
    int posX=SCREEN_WIDTH/2,posY=SCREEN_HEIGHT/2;
    double velX=0,velY=0;
    double accX=0,accY=0;
    double friction=0.9;
    SetTargetFPS(60);
    
    while (!WindowShouldClose() && GetKeyPressed()!=KEY_ESCAPE) {
        accX=0;
        accY=0;
        
        if(IsKeyDown(KEY_D)) accX=40;
        if(IsKeyDown(KEY_S)) accY=40;
        if(IsKeyDown(KEY_A)) accX=-40;
        if(IsKeyDown(KEY_W)) accY=-40;
        velX=velX+(accX*GetFrameTime()*6);
        posX=posX+(velX*GetFrameTime()*6);
        velX=velX*friction;
        velY=velY+(accY*GetFrameTime()*6);
        posY=posY+(velY*GetFrameTime()*6);
        velY=velY*friction;

        
        ClearBackground(RAYWHITE);
        DrawCircle(posX,posY,20,BLUE);
        DrawText("Use WASD to move the circle!", 10, 10, 1, DARKGRAY);
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
