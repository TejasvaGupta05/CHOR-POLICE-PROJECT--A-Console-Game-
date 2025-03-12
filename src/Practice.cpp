#include<iostream>
#include<raylib.h>
#include<ctime>
#include<cmath>

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

Color OpaqueGray = {240,240,240,250};

void CreateBoard(int TposX,int TposY,int PposX,int PposY,int GposX,int GposY);
bool checkGameWon(int playposX,int playposY,int treposX,int treposY);
bool checkGameOver(int playposX, int playposY, int guardposX, int guardposY);
void guardMove(int &GposX,int &GposY,int TposX,int TposY);
bool EndBox();

int main(){
    srand(time(NULL));
    bool restricted_Spawn[5][5]={0};
    bool playermoved=false;
    bool Restart=false;
    InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"PROJECT");
    SetTargetFPS(60);
   
    start:
        Restart=false;
        //Defining Position
        int playerPosition_X = rand()%5 , playerPosition_Y = rand()%5; 
        int treasurePosition_X = rand()%5 , treasurePosition_Y = rand()%5;
        int guardPosition_X = rand()%5, guardPosition_Y = rand()%5;


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
        
        while (!WindowShouldClose())
        {
            EndDrawing();

            playermoved=0;
            if(Restart) break;
            BeginDrawing();
            ClearBackground(WHITE);
            CreateBoard(treasurePosition_X,treasurePosition_Y,playerPosition_X,playerPosition_Y,guardPosition_X,guardPosition_Y);
            if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && playerPosition_Y>0)
            {
                playerPosition_Y--;
                playermoved=true;
            }
            else if ((IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) && playerPosition_Y<4)
            {
                playerPosition_Y++;
                playermoved=true;
            }
            else if ((IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) && playerPosition_X>0)
            {
                playerPosition_X--;
                playermoved=true;
            }
            else if ((IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) && playerPosition_X<4)
            {
                playerPosition_X++;
                playermoved=true;
            }
            check:
            if(checkGameOver(playerPosition_X,playerPosition_Y,guardPosition_X,guardPosition_Y)){
                Restart=EndBox();
                DrawText("YOU LOSE!!",(SCREEN_WIDTH/2)-80,(SCREEN_HEIGHT/2)-45,30,BLACK); 
                continue;
            }
            else if(checkGameWon(playerPosition_X,playerPosition_Y,treasurePosition_X,treasurePosition_Y)){
                Restart=EndBox();
                DrawText("YOU WIN!!",(SCREEN_WIDTH/2)-70,(SCREEN_HEIGHT/2)-45,30,BLACK);
                continue; 
            }

            if(playermoved){ 
                guardMove(guardPosition_X,guardPosition_Y,treasurePosition_X,treasurePosition_Y);
            }
            if(checkGameOver(playerPosition_X,playerPosition_Y,guardPosition_X,guardPosition_Y) || checkGameWon(playerPosition_X,playerPosition_Y,treasurePosition_X,treasurePosition_Y)){goto check;}
        }   
    if(Restart) goto start;
    CloseWindow();
    
}

void CreateBoard(int TposX,int TposY,int PposX,int PposY,int GposX,int GposY){    
    for (int i = 1; i < 5; i++)
    {
        DrawLine(i*100,0,i*100,SCREEN_HEIGHT,BLACK);
        DrawLine(0,(i*100)+SCREEN_HEIGHT-500,SCREEN_WIDTH,(i*100)+SCREEN_HEIGHT-500,BLACK);
    }
    DrawCircle((TposX*100)+SCREEN_WIDTH-450,(TposY*100)+SCREEN_HEIGHT-450,10,YELLOW);
    DrawCircle((PposX*100)+SCREEN_WIDTH-450,(PposY*100)+SCREEN_HEIGHT-450,10,GREEN);
    DrawCircle((GposX*100)+SCREEN_WIDTH-450,(GposY*100)+SCREEN_HEIGHT-450,10,RED);
}

bool checkGameWon(int playposX,int playposY,int treposX,int treposY){
    if (playposX==treposX && playposY==treposY)
    {
        return true;
    }
    else{
        return false;
    }
    
    return true;
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
    bool clicked;
    DrawRectangle(150,175+SCREEN_HEIGHT-500,200,150,OpaqueGray);
    if(pow(mouseX-250,2)+pow(mouseY-285-SCREEN_HEIGHT+500,2)<pow(25,2) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        DrawCircle(250,285+SCREEN_HEIGHT-500,25,LIGHTGRAY);
        clicked=true;
    }
    else if(pow(mouseX-250,2)+pow(mouseY-285-SCREEN_HEIGHT+500,2)<pow(25,2))
    {
        DrawCircle(250,285+SCREEN_HEIGHT-500,25,{245,245,245,255});
    }
    else DrawCircle(250,285+SCREEN_HEIGHT-500,25,WHITE);
    DrawRing({250,285+SCREEN_HEIGHT-500},12,14,0,270,20,BLACK);
    DrawTriangleLines({248, 276}, {248, 268}, {255, 272}, BLACK);
    return clicked;
}

