//Not Stopping till this project is complete....
#include<iostream>
#include<algorithm>
#include<vector>

using std::cout,std::cin,std::endl,std::fill;
typedef std::string str;

void CreateBoard(int rows, int columns, char *Board);
void ClearBoard(int rows, int columns);
bool checkGameWon();
bool checkGameOver();

int main(){
    srand(getpid());
    bool Running=true;
    char Board[5][5];
    fill(Board[0],Board[4]+5,'$');
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout<<Board[i][j];
        }
        cout<<endl;
    }
    

    // cout<<&Board[0];
    // CreateBoard(5,5,Board);
    
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
    // cout<<Board[0][0];
    // cout<<endl;
    // cout<<' '<<Board[0]<<" | "<<Board[1]<<" | "<<Board[2]<<" | "<<Board[3]<<" | "<<Board[4]<<endl;
    // cout<<"---|---|---|---|---\n";
    // cout<<' '<<Board[5]<<" | "<<Board[6]<<" | "<<Board[7]<<" | "<<Board[8]<<" | "<<Board[9]<<endl;
    // cout<<"---|---|---|---|---\n";
    // cout<<' '<<Board[10]<<" | "<<Board[11]<<" | "<<Board[12]<<" | "<<Board[13]<<" | "<<Board[14]<<endl;
    // cout<<"---|---|---|---|---\n";
    // cout<<' '<<Board[15]<<" | "<<Board[16]<<" | "<<Board[17]<<" | "<<Board[18]<<" | "<<Board[19]<<endl;
    // cout<<"---|---|---|---|---\n";
    // cout<<' '<<Board[20]<<" | "<<Board[21]<<" | "<<Board[22]<<" | "<<Board[23]<<" | "<<Board[24]<<endl;
    // cout<<endl;
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