//Not Stopping till this project is complete....
#include<iostream>
#include<algorithm>
#include<vector>
#include<ctime>

using std::cout,std::cin,std::endl,std::fill;
typedef std::string str;

void CreateBoard(int rows, int columns, auto (&Board)[5][5]);
void ClearBoard(int rows, int columns);
bool checkGameWon(int playposX,int playposY,int treposX,int treposY);
bool checkGameOver(int playposX, int playposY, int guardposX, int guardposY);

int main(){
    srand(getpid());
    bool Running=true;
    char playerMove;
    int guardMove;
    int tempX,tempY;
    char Board[5][5];
    bool restricted_Spawn[5][5]={0};
    fill(Board[0],Board[4]+5,' ');

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

    Board[treasurePosition_X][treasurePosition_Y]='$';
    Board[guardPosition_X][guardPosition_Y]='X';
    
    cout<<"------------------------------------------------\n";
    cout<<"         Welcome to Project CHOR POLICE         \n\n";
    cout<<"Rules for playing the Game ::\n";
    cout<<"1. The Task of the game is to reach the Treasure($) without being caught by the Guard.\n";
    cout<<"2. The Gaurd(X) can caught the player(O), if the player is at the adjacent side of Guard.\n\n";

    start:
    // CreateBoard(5,5,restricted_Spawn);
    do
    {
        Board[playerPosition_X][playerPosition_Y]='O';
        Board[guardPosition_X][guardPosition_Y]='X';
        CreateBoard(5,5,Board);
        Board[playerPosition_X][playerPosition_Y]=' ';
        Board[guardPosition_X][guardPosition_Y]=' ';
        cout<<"\nWhich direction you want to go U:UP D:Down L:Left R:Right Q:Quit !\nEnter Your Choice :: ";
        cin>>playerMove;
        switch (playerMove)
        {
        case 'U':
        case 'u':
            if(playerPosition_X>0){playerPosition_X--; cout<<"You Moved Up!!\n";}
            else{cout<<"You can't move Up\n"; goto start;}
            break;
        case 'D':
        case 'd':
            if(playerPosition_X<4){playerPosition_X++; cout<<"You Moved Down!!\n";}
            else{cout<<"You can't move Down\n"; goto start;}
            break;
        case 'L':
        case 'l':
            if(playerPosition_Y>0){playerPosition_Y--; cout<<"You Moved Left!!\n";}
            else{cout<<"You can't move Left\n"; goto start;}
            break;
        case 'R':
        case 'r':
            if(playerPosition_Y<4){playerPosition_Y++; cout<<"You Moved Right!!\n";}
            else{cout<<"You can't move Right\n"; goto start;}
            break;
        case 'Q':
        case 'q':
            cout<<"Thanks For Playing!!\n";
            Running=false;
            break;
        default:
            cout<<"Wrong Choice!! Try Again....\n";
            goto start;
            break;
        }

        if(checkGameWon(playerPosition_X,playerPosition_Y,treasurePosition_X,treasurePosition_Y) || checkGameOver(playerPosition_X,playerPosition_Y,guardPosition_X,guardPosition_Y)) break;
        
        while (true)
        {
            tempX=guardPosition_X;
            tempY=guardPosition_Y;
            guardMove=rand()%4;
            switch (guardMove)
            {
            case 0:
                guardPosition_X--;
                break;
            case 1:
                guardPosition_X++;
                break;
            case 2:
                guardPosition_Y++;
                break;
            case 3:
                guardPosition_Y--;
                break;
            default:
                break;
            }
            if (guardPosition_X<5 && guardPosition_X>=0 && guardPosition_Y<5 && guardPosition_Y>=0 && (guardPosition_X!=treasurePosition_X || guardPosition_Y!=treasurePosition_Y)) 
            {
                break;
            }
            else{
                guardPosition_X=tempX;
                guardPosition_Y=tempY;
            }
            
        }
        

    } while(Running && (!checkGameWon(playerPosition_X,playerPosition_Y,treasurePosition_X,treasurePosition_Y) && !checkGameOver(playerPosition_X,playerPosition_Y,guardPosition_X,guardPosition_Y)));
    
    cout<<"------------------------------------------------\n";
    
    return 0;
}

void CreateBoard(int rows, int columns, auto (&Board)[5][5]){
    // cout<<'\n';
    // for (int i = 0; i < rows-1; i++)
    // {
    //     for (int j = 0; j < columns-1; j++)
    //     {
    //         cout<<" "<<Board[i+j]<<" "<<"|";
    //     }
    //     cout<<'\b'<<endl;
    //     for (int j = 0; j < columns-1; j++)
    //     {
    //         cout<<"---|";
    //     }
    //     cout<<"---";
    //     cout<<'\b'<<endl;        
    // }
    // for (int  i = 0; i < columns; i++)
    // {
    //     cout<<" "<<Board[rows-1+i]<<" "<<"|";
    // }
    // cout<<'\b'<<' ';
    // cout<<endl<<endl;
    
    cout<<endl;
    cout<<' '<<Board[0][0]<<" | "<<Board[0][1]<<" | "<<Board[0][2]<<" | "<<Board[0][3]<<" | "<<Board[0][4]<<endl;
    cout<<"---|---|---|---|---\n";
    cout<<' '<<Board[1][0]<<" | "<<Board[1][1]<<" | "<<Board[1][2]<<" | "<<Board[1][3]<<" | "<<Board[1][4]<<endl;
    cout<<"---|---|---|---|---\n";
    cout<<' '<<Board[2][0]<<" | "<<Board[2][1]<<" | "<<Board[2][2]<<" | "<<Board[2][3]<<" | "<<Board[2][4]<<endl;
    cout<<"---|---|---|---|---\n";
    cout<<' '<<Board[3][0]<<" | "<<Board[3][1]<<" | "<<Board[3][2]<<" | "<<Board[3][3]<<" | "<<Board[3][4]<<endl;
    cout<<"---|---|---|---|---\n";
    cout<<' '<<Board[4][0]<<" | "<<Board[4][1]<<" | "<<Board[4][2]<<" | "<<Board[4][3]<<" | "<<Board[4][4]<<endl;
    cout<<endl;
}

void ClearBoard(int rows, int columns){
    for(int i=0;i<rows;i++){
        for (int j = 0; j < columns; j++)
        {
            cout<<"\b ";
        }
        cout<<endl;
    }
}

bool checkGameWon(int playposX,int playposY,int treposX,int treposY){
    if (playposX==treposX && playposY==treposY)
    {
        cout<<"Congratulations !! YOU WIN\n";
        return true;
    }
    else{
        return false;
    }
    
    return true;
}

bool checkGameOver(int playposX, int playposY, int guardposX, int guardposY){
    if((guardposX==playposX && guardposY==playposY) || (guardposX-1==playposX && guardposY==playposY) || (guardposX+1==playposX && guardposY==playposY) || (guardposX==playposX && guardposY-1==playposY) || (guardposX==playposX && guardposY+1==playposY)){
        cout<<"YOU LOST!! Better Luck Next Time\n";
        return true;
    }
    return false;
}