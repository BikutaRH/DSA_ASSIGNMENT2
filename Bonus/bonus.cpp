// Sinh viên hiện thực fucntion

// vector<Position> ganh(int** board, Move m, int player)

// vector<Position> vay(int** board, Move m, int player)

// Các thư viện ĐÃ có trong bài, các bạn KHÔNG được phép thêm bất kì thư viện nào khác:

#include <iostream>

#include <vector>

#include <cmath>

#include <algorithm>

#include <ctime>


struct Position

{

    int x; int y;

    Position(){x = y = 0;}

    Position(int a, int b)

    {

        x = a; y = b;

    }

};



struct Move

{

    Position pos_start, pos_end;

    Move(Position s, Position e)

    {

        pos_start = s; pos_end = e;

    }

};

//Helping functions goes here
vector<Position> ganh(int** board, Move m, int player){
    //TODO
}

vector<Position> vay(int** board, Move m, int player){
    //TODO
}