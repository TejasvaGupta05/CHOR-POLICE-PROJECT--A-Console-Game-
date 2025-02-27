
//Not Stopping till this project is complete....
#include<iostream>
#include<algorithm>

using std::cout,std::cin,std::endl,std::fill;
typedef std::string str;

void CreateBoard(int rows, int columns, char *Board);
void ClearBoard(int rows, int columns);
bool checkGameWon();
bool checkGameOver();

int main(){
    srand(getpid());
    bool Running=true;
    char Board[25];
    fill(Board,Board+25,' ');
    int playerPosition=rand()%25;
    int TreasurePosition=rand()%25;
    // int Trsize;
    // if (TreasurePosition==12) Trsize=12;
    // else if (TreasurePosition==7 || TreasurePosition==11 || TreasurePosition==13 || TreasurePosition==17) Trsize=11;
    // else if (TreasurePosition==6 || TreasurePosition==8 || TreasurePosition==16 || TreasurePosition==18) Trsize=10;
    // else if (TreasurePosition==0 || TreasurePosition==4 || TreasurePosition==20 || TreasurePosition==24) Trsize=5;
    // else if (TreasurePosition==2 || TreasurePosition==10 || TreasurePosition==14 || TreasurePosition==22) Trsize=8;
    // else Trsize=7;

    // int TrArea[Trsize];

    // switch (TreasurePosition)
    // {
    // case 0:
    //     TrArea={1,2,5,6,10};
    //     break;
    // case 1:
    //     TrArea={0,2,3,5,6,7,11};
    //     break;
    // case 2:
    //     TrArea={0,1,3,4,6,7,8,12};
    //     break;
    // case 3:
    //     TrArea={1,2,4,7,8,9,13};
    //     break;
    // case 4:
    //     TrArea={2,3,8,9,14};
    //     break;
    // case 5:
    //     TrArea={0,1,6,7,10,11,15};
    //     break;
    // case 6:
    //     TrArea={0,1,2,5,7,8,10,11,12,16};
    //     break;
    // case 7:
    //     TrArea={1,2,3,5,6,8,9,11,12,13,17};
    //     break;
    // case 8:
    //     TrArea={2,3,4,6,7,9,12,13,14,18};
    //     break;
    // case 9:
    //     TrArea={3,4,7,8,13,14,19};
    //     break;
    // case 10:
    //     TrArea={0,5,6,11,12,15,16,20};
    //     break;
    // case 11:
    //     TrArea={1,5,6,7,10,12,13,15,16,17,21};
    //     break;
    // case 12:
    //     TrArea={2,6,7,8,10,11,13,14,16,17,18,22};
    //     break;
    // case 13:
    //     TrArea={3,7,8,9,11,12,14,17,18,19,23};
    //     break;
    // case 14:
    //     TrArea={4,8,9,12,13,18,19,24};
    //     break;
    // case 15:
    //     TrArea={5,10,11,16,17,20,21};
    //     break;
    // case 16:
    //     TrArea={6,10,11,12,15,17,18,20,21,22};
    //     break;
    // case 17:
    //     TrArea={7,11,12,13,15,16,18,19,21,22,23};
    //     break;
    // case 18:
    //     TrArea={8,12,13,14,16,17,19,22,23,24};
    //     break;
    // case 19:
    //     TrArea={9,13,14,17,18,23,24};
    //     break;
    // case 20:
    //     TrArea={10,15,16,21,22};
    //     break;
    // case 21:
    //     TrArea={11,15,16,17,20,22,23};
    //     break;
    // case 22:
    //     TrArea={12,16,17,18,20,21,23,24};
    //     break;
    // case 23:
    //     TrArea={13,17,18,19,21,22,24};
    //     break;
    // case 24:
    //     TrArea={14,18,19,22,23};
    //     break;
    // }

    while(playerPosition==TreasurePosition)
        TreasurePosition=rand()%25;
    Board[playerPosition]='O';
    Board[TreasurePosition]='$';
    CreateBoard(5,5,Board);
    return 0;
}

void CreateBoard(int rows, int columns, char *Board){
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
    cout<<' '<<Board[0]<<" | "<<Board[1]<<" | "<<Board[2]<<" | "<<Board[3]<<" | "<<Board[4]<<endl;
    cout<<"---|---|---|---|---\n";
    cout<<' '<<Board[5]<<" | "<<Board[6]<<" | "<<Board[7]<<" | "<<Board[8]<<" | "<<Board[9]<<endl;
    cout<<"---|---|---|---|---\n";
    cout<<' '<<Board[10]<<" | "<<Board[11]<<" | "<<Board[12]<<" | "<<Board[13]<<" | "<<Board[14]<<endl;
    cout<<"---|---|---|---|---\n";
    cout<<' '<<Board[15]<<" | "<<Board[16]<<" | "<<Board[17]<<" | "<<Board[18]<<" | "<<Board[19]<<endl;
    cout<<"---|---|---|---|---\n";
    cout<<' '<<Board[20]<<" | "<<Board[21]<<" | "<<Board[22]<<" | "<<Board[23]<<" | "<<Board[24]<<endl;
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

bool checkGameWon(){
    return true;
}

bool checkGameOver(){
    return true;
}