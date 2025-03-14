#include<iostream>
#include<raylib.h>
#include<ctime>
#include<cmath>


#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

Color OpaqueGray = {240,240,240,250};
Color OpaqueRed = {255,161,0,161};

void CreateBoard(int TposX,int TposY,int PposX,int PposY,int GposX,int GposY, int KposX, int KposY, bool keyActive, bool hasKey);
bool checkGameWon(int playposX,int playposY,int treposX,int treposY, bool hasKey);
bool checkGameOver(int playposX, int playposY, int guardposX, int guardposY);
void guardMove(int &GposX,int &GposY,int TposX,int TposY);
bool EndBox();

int main(){
    srand(time(NULL));
    bool playermoved=false;
    bool Restart=false;
    InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"PROJECT");
    InitAudioDevice();
    Sound clickSound = LoadSound("resources/click.wav");
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
                        
            check:
            if(checkGameOver(playerPosition_X,playerPosition_Y,guardPosition_X,guardPosition_Y)){
                Restart=EndBox();
                DrawText("YOU LOSE!!",(SCREEN_WIDTH/2)-80,(SCREEN_HEIGHT/2)-45,30,BLACK); 
                continue;
            }
            else if(checkGameWon(playerPosition_X,playerPosition_Y,treasurePosition_X,treasurePosition_Y, hasKey)){
                Restart=EndBox();
                DrawText("YOU WIN!!",(SCREEN_WIDTH/2)-70,(SCREEN_HEIGHT/2)-45,30,BLACK);
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
    
    if (keyActive) {
        Vector2 keyPos = {(KposX*100) + SCREEN_WIDTH-450, (KposY*100) + SCREEN_HEIGHT-450};
        DrawCircleV({keyPos.x+10,keyPos.y},5,GOLD);
        DrawRectangleV({keyPos.x-10,keyPos.y-2},{20,3},GOLD);
        DrawRectangleV({keyPos.x-9,keyPos.y+1},{6,4},GOLD);
    }

    // Collected key indicator
    if (hasKey) {
        Vector2 playerPos = {(PposX*100) + SCREEN_WIDTH-450, (PposY*100) + SCREEN_HEIGHT-450};
        
        // Simple key icon
        DrawCircleV({playerPos.x + 20, playerPos.y - 20}, 5, GOLD);
        DrawRectangleV({playerPos.x + 15, playerPos.y - 18}, {10, 4}, GOLD);
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
            default:
                break;
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

bool EndBox(){
    int mouseX=GetMouseX(),mouseY=GetMouseY();
    bool clicked = false;
    DrawRectangle(150,175+SCREEN_HEIGHT-500,200,150,OpaqueGray);
    if((pow(mouseX-250,2)+pow(mouseY-285-SCREEN_HEIGHT+500,2)<pow(25,2) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) || IsKeyPressed(KEY_ENTER))
    {
        clicked=true;
    }
    if(pow(mouseX-250,2)+pow(mouseY-285-SCREEN_HEIGHT+500,2)<pow(25,2))
    {
        DrawCircle(250,285+SCREEN_HEIGHT-500,25,{245,245,245,255});
    }
    else DrawCircle(250,285+SCREEN_HEIGHT-500,25,WHITE);
    DrawRing({250,285+SCREEN_HEIGHT-500},12,14,0,270,20,BLACK);
    DrawTriangleLines({248, 276}, {248, 268}, {255, 272}, BLACK);
    return clicked;
}