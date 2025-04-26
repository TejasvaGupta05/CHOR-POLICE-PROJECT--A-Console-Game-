#include<iostream>
#include<raylib.h>
#include<ctime>
#include<cmath>

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 550

Color OpaqueGray = {240,240,240,250};
Color OpaqueRed = {255,161,0,161};

void CreateBoard(int TposX,int TposY,int PposX,int PposY,int GposX,int GposY, int KposX, int KposY, bool keyActive, bool hasKey);
bool checkGameWon(int playposX,int playposY,int treposX,int treposY, bool hasKey);
bool checkGameOver(int playposX, int playposY, int guardposX, int guardposY);
void guardMove(int &GposX,int &GposY,int TposX,int TposY);
bool EndBox(Image ArrowHead);

int main(){
    srand(time(NULL));
    bool playermoved=false;
    bool Restart=false;
    InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"PROJECT");
    InitAudioDevice();
    Sound clickSound = LoadSound("resources/click.wav");
    Image ArrowHead = LoadImage("resources/ArrowHead.png");
    SetTargetFPS(60);
    start:
        Restart=false;
        bool restricted_Spawn[5][5]={0};
        //Defining Position
        int playerPosition_X = rand()%5 , playerPosition_Y = rand()%5; 
        int treasurePosition_X = rand()%5 , treasurePosition_Y = rand()%5;
        int guardPosition_X = rand()%5, guardPosition_Y = rand()%5;
        int keyPosition_X, keyPosition_Y;
        bool keyActive, hasKey;

        //Assigning restricted spawn true for Treasure POV
        for (int i = treasurePosition_X-1; i < treasurePosition_X+2; i++){
            for (int j = treasurePosition_Y-1; j < treasurePosition_Y+2; j++){
                if (i<5 && i>=0 && j<5 && j>=0){
                    restricted_Spawn[i][j]=true;
                }            
            }        
        }

        //Changing Guard Position until it spawns near Treasure
        while (!restricted_Spawn[guardPosition_X][guardPosition_Y] || (guardPosition_X==treasurePosition_X && guardPosition_Y==treasurePosition_Y)){
            guardPosition_X = rand()%5 , guardPosition_Y = rand()%5;
        }

        //Assigning restricted spawn true for guard POV
        if(guardPosition_X+1<5) restricted_Spawn[guardPosition_X+1][guardPosition_Y]=true;
        if(guardPosition_X-1>=0) restricted_Spawn[guardPosition_X-1][guardPosition_Y]=true;
        if(guardPosition_Y+1<5) restricted_Spawn[guardPosition_X][guardPosition_Y+1]=true;
        if(guardPosition_Y-1>=0) restricted_Spawn[guardPosition_X][guardPosition_Y-1]=true;

        //Changing Player Position until spawned away from the treasure and guard
        while (restricted_Spawn[playerPosition_X][playerPosition_Y]){
            playerPosition_X = rand()%5 , playerPosition_Y = rand()%5;
        }

        // Generate key position
        do {
            keyPosition_X = rand()%5;
            keyPosition_Y = rand()%5;
        } while ((keyPosition_X == playerPosition_X && keyPosition_Y == playerPosition_Y) ||
                (keyPosition_X == guardPosition_X && keyPosition_Y == guardPosition_Y) ||
                (keyPosition_X == treasurePosition_X && keyPosition_Y == treasurePosition_Y));
        keyActive = true;
        hasKey = false;
        
        while (!WindowShouldClose())
        {
            EndDrawing();
            playermoved=false;
            if(Restart) break;
            BeginDrawing();
            ClearBackground(WHITE);
            CreateBoard(treasurePosition_X,treasurePosition_Y,playerPosition_X,playerPosition_Y,guardPosition_X,guardPosition_Y, keyPosition_X, keyPosition_Y, keyActive, hasKey);
            
            // Handle keyboard input
            if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && playerPosition_Y>0)
            {
                playerPosition_Y--; PlaySound(clickSound);
                playermoved=true;
            }
            else if ((IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) && playerPosition_Y<4)
            {
                playerPosition_Y++; PlaySound(clickSound);
                playermoved=true;
            }
            else if ((IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) && playerPosition_X>0)
            {
                playerPosition_X--; PlaySound(clickSound);
                playermoved=true;
            }
            else if ((IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) && playerPosition_X<4)
            {
                playerPosition_X++; PlaySound(clickSound);
                playermoved=true;
            }
            else if (IsKeyPressed(KEY_F)) {playermoved=true; PlaySound(clickSound);}
            
            // Check key collection
            if (playermoved && keyActive && playerPosition_X == keyPosition_X && playerPosition_Y == keyPosition_Y) {
                hasKey = true;
                keyActive = false;
            }
            
            // Handle mouse click on restart button
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                Vector2 mousePos = GetMousePosition();
                if (CheckCollisionPointCircle(mousePos, (Vector2){460, 25}, 15)) {
                    Restart = true;
                    PlaySound(clickSound);
                }
            }
                        
            check:
            if(checkGameOver(playerPosition_X,playerPosition_Y,guardPosition_X,guardPosition_Y)){
                Restart=EndBox(ArrowHead);
                DrawText("YOU LOSE!!",(SCREEN_WIDTH/2)-80,(SCREEN_HEIGHT-500+500/2)-45,30,BLACK); 
                continue;
            }
            else if(checkGameWon(playerPosition_X,playerPosition_Y,treasurePosition_X,treasurePosition_Y, hasKey)){
                Restart=EndBox(ArrowHead);
                DrawText("YOU WIN!!",(SCREEN_WIDTH/2)-70,(SCREEN_HEIGHT-500+500/2)-45,30,BLACK);
                continue; 
            }

            if(playermoved){ 
                guardMove(guardPosition_X,guardPosition_Y,treasurePosition_X,treasurePosition_Y);
            }
            if(checkGameOver(playerPosition_X,playerPosition_Y,guardPosition_X,guardPosition_Y) || checkGameWon(playerPosition_X,playerPosition_Y,treasurePosition_X,treasurePosition_Y, hasKey)){goto check;}
        }   
    if(Restart) goto start;
    UnloadSound(clickSound);
    CloseAudioDevice();
    CloseWindow();
    
}

void CreateBoard(int TposX,int TposY,int PposX,int PposY,int GposX,int GposY, int KposX, int KposY, bool keyActive, bool hasKey){    
    for (int i = 1; i < 5; i++)
    {
        DrawLine(i*100,0,i*100,SCREEN_HEIGHT,BLACK);
        DrawLine(0,(i*100)+SCREEN_HEIGHT-500,SCREEN_WIDTH,(i*100)+SCREEN_HEIGHT-500,BLACK);
    }
    DrawCircle(((GposX+1)*100)+SCREEN_WIDTH-450,(GposY*100)+SCREEN_HEIGHT-450,3,OpaqueRed);
    DrawCircle(((GposX-1)*100)+SCREEN_WIDTH-450,(GposY*100)+SCREEN_HEIGHT-450,3,OpaqueRed);
    DrawCircle((GposX*100)+SCREEN_WIDTH-450,((GposY-1)*100)+SCREEN_HEIGHT-450,3,OpaqueRed);
    DrawCircle((GposX)*100+SCREEN_WIDTH-450,((GposY+1)*100)+SCREEN_HEIGHT-450,3,OpaqueRed);
    DrawCircle((TposX*100)+SCREEN_WIDTH-450,(TposY*100)+SCREEN_HEIGHT-450,12,YELLOW);
    DrawCircle((PposX*100)+SCREEN_WIDTH-450,(PposY*100)+SCREEN_HEIGHT-450,12,GREEN);
    DrawCircle((GposX*100)+SCREEN_WIDTH-450,(GposY*100)+SCREEN_HEIGHT-450,12,RED);
    DrawRectangle(0,0,500,50,SKYBLUE);    
       
        // Draw menu button (hamburger icon)
        DrawRectangle(15, 15, 25, 2, WHITE);
        DrawRectangle(15, 25, 25, 2, WHITE);
        DrawRectangle(15, 35, 25, 2, WHITE);
    
        bool hoverInfo = CheckCollisionPointCircle(GetMousePosition(), (Vector2){400, 25}, 15);
        Color infoColor = hoverInfo ? LIGHTGRAY : WHITE;
        DrawText("?", 395, 13, 24, WHITE);
    
        // New minimalist restart button
        bool hoverRestart = CheckCollisionPointCircle(GetMousePosition(), (Vector2){460,25}, 15);
        Color arrowColor = hoverRestart ? SKYBLUE : DARKGRAY;  // Change color on hover
        float rotation = hoverRestart ? GetTime()*100 : 0;      // Rotate only on hover
    
        // Draw circular arrow
        DrawRing((Vector2){460,25}, 10, 12, rotation, rotation+270, 20, infoColor);
        DrawTriangle(
            (Vector2){460 + sin(DEG2RAD*(rotation+270))*18, 25 + cos(DEG2RAD*(rotation+270))*18},
            (Vector2){460 + sin(DEG2RAD*(rotation+240))*18, 25 + cos(DEG2RAD*(rotation+240))*18},
            (Vector2){460 + sin(DEG2RAD*(rotation+300))*18, 25 + cos(DEG2RAD*(rotation+300))*18},
            infoColor
        );
    
    if (keyActive) {
        Vector2 keyPos = {(KposX*100) + SCREEN_WIDTH-450, (KposY*100) + SCREEN_HEIGHT-450};
        DrawCircleV({keyPos.x+10,keyPos.y},5,GOLD);
        DrawRectangleV({keyPos.x-10,keyPos.y-2},{20,3},GOLD);
        DrawRectangleV({keyPos.x-9,keyPos.y+1},{6,4},GOLD);
    }

    // Collected key indicator
    if (hasKey) {
        Vector2 playerPos = {(PposX*100) + SCREEN_WIDTH-450, (PposY*100) + SCREEN_HEIGHT-450};
        DrawCircleV({playerPos.x + 20, playerPos.y - 20}, 5, GOLD);
        DrawRectangleV({playerPos.x + 15, playerPos.y - 18}, {10, 4}, GOLD);
    }

    if(hoverInfo) {
        DrawRectangle(340, 45, 150, 90, WHITE);
        DrawRectangleLines(340, 45, 150, 90, DARKGRAY);
        DrawText("Color Legend:", 345, 50, 12, BLACK);
        DrawText("Green  - Player", 345, 70, 12, BLACK);
        DrawText("Red    - Guard", 345, 85, 12, BLACK);
        DrawText("Yellow - Treasure", 345, 100, 12, BLACK);
        DrawText("Gold   - Key", 345, 115, 12, BLACK);
    }
}

bool checkGameWon(int playposX,int playposY,int treposX,int treposY, bool hasKey){
    return (playposX == treposX && playposY == treposY && hasKey);
}

bool checkGameOver(int playposX, int playposY, int guardposX, int guardposY){
    if((guardposX==playposX && guardposY==playposY) || (guardposX-1==playposX && guardposY==playposY) || (guardposX+1==playposX && guardposY==playposY) || (guardposX==playposX && guardposY-1==playposY) || (guardposX==playposX && guardposY+1==playposY)){
        return true;
    }
    return false;
}

void guardMove(int &GposX,int &GposY,int TposX,int TposY){
    int tempX,tempY,gMove;    
    while (true)
        {
            tempX=GposX;
            tempY=GposY;
            gMove=rand()%4;
            switch (gMove)
            {
            case 0:
                GposX--;
                break;
            case 1:
                GposX++;
                break;
            case 2:
                GposY++;
                break;
            case 3:
                GposY--;
                break;
            default: break;
            }
            if (GposX<5 && GposX>=0 && GposY<5 && GposY>=0 && (GposX!=TposX || GposY!=TposY)) 
            {
                break;
            }
            else{
                GposX=tempX;
                GposY=tempY;
            }
        }
}

bool EndBox(Image ArrowHead){
    int mouseX=GetMouseX(),mouseY=GetMouseY();
    bool clicked = false;
    float UpBarheight=SCREEN_HEIGHT-500;
    DrawRectangle(150,175+UpBarheight,200,150,OpaqueGray);
    if((pow(mouseX-250,2)+pow(mouseY-285-SCREEN_HEIGHT+500,2)<pow(25,2) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) || IsKeyPressed(KEY_ENTER))
    {
        clicked=true;
    }
    if(pow(mouseX-250,2)+pow(mouseY-285-SCREEN_HEIGHT+500,2)<pow(25,2))
    {
        DrawCircle(250,285+UpBarheight,25,{245,245,245,255});
    }
    else DrawCircle(250,285+UpBarheight,25,WHITE);
    DrawRing({250,285+UpBarheight},12,14,0,270,20,BLACK);
    DrawTriangle((Vector2){248, 276+UpBarheight},(Vector2){248, 268+UpBarheight},(Vector2){255, 272+UpBarheight}, BLACK);
    return clicked;
}