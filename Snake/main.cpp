#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <vector>
#include <queue>
#include <deque>
#include <windows.h>

using namespace std;
int bGameOver;
int score = 0;
const int width = 20;
const int height = 20;
int x, y;
int fruitX, fruitY;
int prevX, prevY;
vector< pair<int, int> > bd;
deque< pair<int, int> > dq;
enum enum_direction {
    STOP,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

enum_direction dir;
void SetUp()
{
    srand(time(NULL));
    bGameOver = false;
    fruitX = rand()%width + 1;
    fruitY = rand()%height + 1;
    x = width/2;
    y = height/2;
    bd.push_back(make_pair(x, y));
    dir = STOP;
}
void Draw()
{
    system("cls");
    //wall
    for(int i=0; i<=width; ++i) 
    {
        cout << "#";
    }
    cout << endl;

    for(int i=1; i<=height ; ++i) 
    {
        for(int j=0; j<=width; ++j) 
        {
            if(i == height || j == 0 || j==width) 
            {
                cout << "#";
            }
            else 
            {
                if(i==fruitY && j==fruitX)
                {  
                    cout << "F";                   
                    /*if(i==y && j==x) 
                    {
                        cout << "O";
                        fruitY = rand()%height + 1;
                        fruitX = rand()%width + 1;
                    }
                    else 
                    {
                        cout << "F";
                    }*/
                }
                else if(i==y && j==x)
                {
                    cout << "O";
                }
                else
                {
                    bool bPrint = false;
                    for(auto nd : bd) 
                    {
                        if(i==nd.second && j==nd.first)
                        {
                            cout << "o";
                            bPrint = true;
                        }
                        
                    }
                    if(!bPrint) cout << " ";
                }
            }
        }
        cout << endl;
    }
}

void Input()
{
    if(_kbhit())
    {
        switch(_getch())
        {
            case 'a':
                dir = enum_direction::LEFT;
                //--x;
                break;
            case 'd':
                dir = enum_direction::RIGHT;
                //++x;
                break;
            case 'w':
                dir = enum_direction::UP;
                //++y;
                break;
            case 's':
                dir = enum_direction::DOWN;
                //--y;
                break;
            case 'x':
                bGameOver = true;
                break;
        }
    }
    
}

void Logic()
{
    switch(dir)
    {
        case enum_direction::LEFT:
            --x;
            break;
        case enum_direction::RIGHT:
            ++x;
            break;
        case enum_direction::UP:
            --y;
            break;
        case enum_direction::DOWN:
            ++y;
            break;
    }
    bd.insert(bd.begin(), make_pair(x, y));
    if(y==fruitY && x==fruitX)
    {        
        do 
        {
            fruitY = rand()%height + 1;
            fruitX = rand()%width + 1;
        }while(y==fruitY && x==fruitX);        
    }
    else 
    {
        bd.pop_back();
    }

    if(x<=0 || x>=width || y<=0 || y>=height) bGameOver = true;
}

int main(int argc, char* argv[])
{
    cout << "SNAKE GAME" << endl;
    SetUp();
    int i = 0;
    while(!bGameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(200);
        //cout << endl;
        //cout << i++;
    }

    return 0;
}