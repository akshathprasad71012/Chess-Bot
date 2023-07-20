
#define ull unsigned long long
#define DEPTH 5
#define MOVE int
#include <chrono>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;
#include <cctype>





int ama = 0;
int SQ2BIT(int x, int y);
//pair<pair<int, int>, pair<int, int>> prevMove = makeMove(10,10,10,10);
//WHITE IS SMALL CASE
int makeMove(int a, int b, int x, int y){
    int mm = 0;
    mm += y + (x*10) + (b*100) + (a*1000);
    return mm;
}

int prevMove = makeMove(10,10,10,10);
int prevEval = -99999989;



int nodes = 0;
int pruned = 0;






string printBit(ull attack){
    string s = "";
    for(int i=63;i>=0;i--){
        
        if(attack & (1ULL << i)){
            s.push_back('1');
        }else{
            s.push_back('0');
        }
    }
    cout << endl;
    return s;
}
// void cloud(string fen, pair<pair<int, int>, pair<int, int>>n,int d){
//     ofstream clouds;
//     clouds.open("cloud.txt", ios::app);
//     fen.push_back('=');
//     fen.push_back(char(48+n.first.first));
//     fen.push_back(char(48+n.first.second));
//     fen.push_back(char(48+n.second.first));
//     fen.push_back(char(48+n.second.second));
//     fen.push_back(char(48+d));
//     clouds << fen <<endl;
// }
// pair<int, int> cloud_find(string fen,int d){
//     int r = 0;
//     ifstream f("cloud.txt");
//     string ins;
//     int oo;string line;
//     if(f.is_open()){
//         while(getline(f, line)){
//             ins.clear();
//             for(int o=0; o<line.length();o++){
//                 if(line[o]!='='){
//                     ins.push_back(line[o]);
//                 }else{
//                     oo = o;
//                     break;
//                 }
//             }
//             if(ins == fen){
                
//                 if((int(line[oo+5])-48)>=d){
//                     return make_pair(int(line[oo+5])-48,makeMove(int(line[oo+1])-48, int(line[oo+2])-48, int(line[oo+3])-48, int(line[oo+4])-48));
//                 }
//             }
//         }
//     }
//     return make_pair(0,makeMove(-10,-10,-10,-10));
// }
int SQ2BIT(int x, int y){
    return (x*8)+y;
}
// pair<int, int> opening_db(string fen, string file){
//     int r = 0;
//     ifstream f(file);
//     string ins;
//     int oo;string line;
//     if(f.is_open()){
//         while(getline(f, line)){
//             ins.clear();
//             for(int o=0; o<line.length();o++){
//                 if(line[o]!='='){
//                     ins.push_back(line[o]);
//                 }else{
//                     oo = o;
//                     break;
//                 }
//             }
//             if(ins == fen){
                
                
//                 return make_pair(int(line[oo+5])-48,makeMove(int(line[oo+1])-48, int(line[oo+2])-48, int(line[oo+3])-48, int(line[oo+4])-48));
                
//             }
//         }
//     }
//     return make_pair(0,makeMove(-10,-10,-10,-10));
// }
ull bitSet(string s){
    ull r = 0ULL;
    for(int i=0; i<64; i++){
        if(s[i] == '1'){
            r = r | (1ULL<<i);
        }
    }
    return r;
}


MOVE Move(int a){
    return makeMove(a/1000, (a/100)%10,(a/10)%10 ,a%10);
}


unordered_map<char, int>pieces = {{'k',99999999},{'n',320},{'b',330},{'p',100},{'r',500},{'q',900}};
int pawn[8][8] = {{0,  0,  0,  0,  0,  0,  0,  0 },
                  {50, 50, 50, 50, 50, 50, 50, 50},
                  {10, 10, 20, 30, 30, 20, 10, 10},
                  {5,  5, 10, 25, 25, 10,  5,  5},
                  {0,  0,  0, 20, 20,  0,  0,  0},
                  {5, -5,-10,  0,  0,-10, -5,  5},
                  {5, 10, 10,-20,-20, 10, 10,  5},
                  {0,  0,  0,  0,  0,  0,  0,  0}};
int knight[8][8] = {{-50,-40,-30,-30,-30,-30,-40,-50},
                   {-40,-20,  0,  0,  0,  0,-20,-40},
                   {-30,  0, 10, 15, 15, 10,  0,-30},
                   {-30,  5, 15, 20, 20, 15,  5,-30},
                   {-30,  0, 15, 20, 20, 15,  0,-30},
                   {-30,  5, 10, 15, 15, 10,  5,-30},
                   {-40,-20,  0,  5,  5,  0,-20,-40},
                   {-50,-40,-30,-30,-30,-30,-40,-50}};

int bishop[8][8] = {{-20,-10,-10,-10,-10,-10,-10,-20},
                   {-10,  0,  0,  0,  0,  0,  0,-10},
                   {-10,  0,  5, 10, 10,  5,  0,-10},
                   {-10,  5,  5, 10, 10,  5,  5,-10},
                   {-10,  0, 10, 10, 10, 10,  0,-10},
                   {-10, 10, 10, 10, 10, 10, 10,-10},
                   {-10,  5,  0,  0,  0,  0,  5,-10},
                   {-20,-10,-10,-10,-10,-10,-10,-20}};

int rook[8][8] = {{0,  0,  0,  0,  0,  0,  0,  0},
                  {5, 10, 10, 10, 10, 10, 10,  5},
                  {-5,  0,  0,  0,  0,  0,  0, -5},
                  {-5,  0,  0,  0,  0,  0,  0, -5},
                  {-5,  0,  0,  0,  0,  0,  0, -5},
                  {-5,  0,  0,  0,  0,  0,  0, -5},
                  {-5,  0,  0,  0,  0,  0,  0, -5},
                  {0,  0,  0,  5,  5,  0,  0,  0}};

int queen[8][8] = {{-20,-10,-10, -5, -5,-10,-10,-20},
                  {-10,  0,  0,  0,  0,  0,  0,-10},
                  {-10,  0,  5,  5,  5,  5,  0,-10},
                   {-5,  0,  5,  5,  5,  5,  0, -5},
                    {0,  0,  5,  5,  5,  5,  0, -5},
                   {-10,  5,  5,  5,  5,  5,  0,-10},
                   {-10,  0,  5,  0,  0,  0,  0,-10},
                   {-20,-10,-10, -5, -5,-10,-10,-20}};

int king[8][8] = {{-30,-40,-40,-50,-50,-40,-40,-30},
                  {-30,-40,-40,-50,-50,-40,-40,-30},
                  {-30,-40,-40,-50,-50,-40,-40,-30},
                  {-30,-40,-40,-50,-50,-40,-40,-30},
                  {-20,-30,-30,-40,-40,-30,-30,-20},
                  {-10,-20,-20,-20,-20,-20,-20,-10},
                  { 20, 20,  0,  0,  0,  0, 20, 20},
                  {20, 30, 10,  0,  0, 10, 30, 20}};

int king_end[8][8] = {{-50,-40,-30,-20,-20,-30,-40,-50},
                      {-30,-20,-10,  0,  0,-10,-20,-30},
                      {-30,-10, 20, 30, 30, 20,-10,-30},
                      {-30,-10, 30, 40, 40, 30,-10,-30},
                      {-30,-10, 30, 40, 40, 30,-10,-30},
                      {-30,-10, 20, 30, 30, 20,-10,-30},
                      {-30,-30,  0,  0,  0,  0,-30,-30},
                      {-50,-30,-30,-30,-30,-30,-30,-50}};









class Board{
    public:
    char position[8][8] = {{'R','N','B','Q','K','B','N','R'},
                           {'P','P','P','P','P','P','P','P'},
                           {' ',' ',' ',' ',' ',' ',' ',' '},
                           {' ',' ',' ',' ',' ',' ',' ',' '},
                           {' ',' ',' ',' ',' ',' ',' ',' '},
                           {' ',' ',' ',' ',' ',' ',' ',' '},
                           {'p','p','p','p','p','p','p','p'},
                           {'r','n','b','q','k','b','n','r'}}; //4,0 -> 4,7
    // char position[8][8] = {{'R',' ',' ',' ','K',' ',' ',' '},
    //                        {'P',' ','P','B',' ',' ',' ','P'},
    //                        {'r',' ',' ',' ','P','R',' ',' '},
    //                        {' ',' ',' ','P',' ',' ',' ',' '},
    //                        {' ',' ',' ','p',' ','p','P',' '},
    //                        {' ',' ','p',' ',' ',' ','p',' '},
    //                        {' ',' ','p','n','b',' ','k','p'},
    //                        {' ',' ',' ',' ',' ',' ',' ','r'}}; //4,0 -> 4,7
    unordered_map<char, int> material = {{'k',1},{'q',1},{'n',2},{'b',2},{'r',2},{'p',8},{'K',1},{'Q',1},{'B',2},{'N',2},{'R',2},{'P',8}};;
    int eval;
    int black_check = 0;
    int white_check = 0;
    int white_short_castle = 0;
    int black_long_castle = 0;
    int black_short_castle = 0;
    int white_long_castle = 0;
    int turn = 1;
    ull attack_black = 0ULL;
    ull attack_white = 0ULL;
    pair<int, int> white_king = make_pair(7, 2);
    pair<int, int> black_king = make_pair(0, 4);
    int vulKing(){
        int count = 0;
        // for(int i=-1;i<=1;i++){
        //     for(int j=-1;j<=1;j++){
        //         if(attack_black & (1ULL << SQ2BIT(white_king.first+i, white_king.second+j))){
        //             count++;
        //         }
        //     }
        // }
        // if(count >= 6){
        //     return 1;
        // }else{
        //     count = 0;
        // }
        for(int i=-1;i<=1;i++){
            for(int j=-1;j<=1;j++){
                if(attack_white & (1ULL << SQ2BIT(black_king.first+i, black_king.second+j))){
                    count++;
                }
            }
        }
        if(count >= 6){
            return 1;
        }else{
            return 0;
        }
        return 0;
    }
    void setAttack(){
        int it = turn;
        turn = 1;
        PosMoves();
        turn = -1;
        PosMoves();
        turn = it;
        
    }
    void move_user(pair<pair<int,int>,pair<int,int>>m){
        
        int x1 = (m.second).first;
        int y1 = (m.second).second;
        int a1 = (m.first).first;
        int b1 = (m.first).second;
        if(b1 == -1){
            if(turn == 1){
                position[7][4] = ' ';
                position[7][7] = ' ';
                position[7][5] = 'r';
                position[7][6] = 'k';
                white_king = make_pair(7, 6);
                 white_short_castle = 0;
                 white_long_castle = 0;
            }else{
                position[0][4] = ' ';
                position[0][7] = ' ';
                position[0][5] = 'R';
                position[0][6] = 'K';
                black_king = make_pair(0, 6);
                black_short_castle = 0;
                black_long_castle = 0;
            }
            
        }else if(b1 == -2){
            if(turn == 1){
                position[7][4] = ' ';
                position[7][0] = ' ';
                position[7][3] = 'r';
                position[7][2] = 'k';
                white_king = make_pair(7, 2);
                white_long_castle = 0;
                white_short_castle = 0;
            }else{
                position[0][4] = ' ';
                position[0][0] = ' ';
                position[0][3] = 'R';
                position[0][2] = 'K';
                black_king = make_pair(0, 2);
                black_long_castle = 0;
                black_short_castle = 0;
            }
        }else if(a1 == -5){
            int y = (m.second).first;
            int x = 7 - (m.second).second;
            int b = (m.first).first;
            int a = 7 - (m.first).second;
            if(position[x][y] == 'k'){
                white_long_castle = 0;
                white_short_castle = 0;
            }
            if(position[x][y] == 'K'){
                black_long_castle = 0;
                black_short_castle = 0;
            }
            if(position[x][y] == 'r'){
                if(y == 0)white_long_castle = 0;
                if(y == 7)white_short_castle = 0;
            }
            if(position[x][y] == 'R'){
                if(y == 0)black_long_castle = 0;
                if(y == 7)black_short_castle = 0;
            }
            if (position[x][y] != ' '){
                material[position[x][y]]--;
            }
            char proto;
            if(turn == 1){
                a = x + turn;
                proto = 'q';
            }else{
                a = x + turn;
                proto = 'Q';
            }
            position[x][y] = proto;
            position[a][b] = ' ';

        }else if(a1 == -6){
            int y = (m.second).first;
            int x = 7 - (m.second).second;
            int b = (m.first).first;
                int a = 7 - (m.first).second;
                if(position[x][y] == 'k'){
                white_long_castle = 0;
                white_short_castle = 0;
            }
            if(position[x][y] == 'K'){
                black_long_castle = 0;
                black_short_castle = 0;
            }
            if(position[x][y] == 'r'){
                if(y == 0)white_long_castle = 0;
                if(y == 7)white_short_castle = 0;
            }
            if(position[x][y] == 'R'){
                if(y == 0)black_long_castle = 0;
                if(y == 7)black_short_castle = 0;
            }
            if (position[x][y] != ' '){
                material[position[x][y]]--;
            }
            char proto;
            if(turn == 1){
                a = x + turn;
                proto = 'r';
            }else{
                a = x + turn;
                proto = 'R';
            }
            position[x][y] = proto;
            position[a][b] = ' ';
        }else if(a1 == -7){
            int y = (m.second).first;
            int x = 7 - (m.second).second;
            int b = (m.first).first;
                int a = 7 - (m.first).second;
                if(position[x][y] == 'k'){
                white_long_castle = 0;
                white_short_castle = 0;
            }
            if(position[x][y] == 'K'){
                black_long_castle = 0;
                black_short_castle = 0;
            }
            if(position[x][y] == 'r'){
                if(y == 0)white_long_castle = 0;
                if(y == 7)white_short_castle = 0;
            }
            if(position[x][y] == 'R'){
                if(y == 0)black_long_castle = 0;
                if(y == 7)black_short_castle = 0;
            }
            if (position[x][y] != ' '){
                material[position[x][y]]--;
            }
            char proto;
            if(turn == 1){
                a = x + turn;
                proto = 'n';
            }else{
                a = x + turn;
                proto = 'N';
            }
            position[x][y] = proto;
            position[a][b] = ' ';
        }else if(a1 == -8){
            int y = (m.second).first;
            int x = 7 - (m.second).second;
            int b = (m.first).first;
                int a = 7 - (m.first).second;
            if(position[x][y] == 'k'){
                white_long_castle = 0;
                white_short_castle = 0;
            }
            if(position[x][y] == 'K'){
                black_long_castle = 0;
                black_short_castle = 0;
            }
            if(position[x][y] == 'r'){
                if(y == 0)white_long_castle = 0;
                if(y == 7)white_short_castle = 0;
            }
            if(position[x][y] == 'R'){
                if(y == 0)black_long_castle = 0;
                if(y == 7)black_short_castle = 0;
            }
            if (position[x][y] != ' '){
                material[position[x][y]]--;
            }
            char proto;
            if(turn == 1){
                a = x + turn;
                proto = 'b';
            }else{
                a = x + turn;
                proto = 'B';
            }
            position[x][y] = proto;
            position[a][b] = ' ';
        }else{

                int y = (m.second).first;
                int x = 7 - (m.second).second;
                if(position[x][y] == 'k'){
                white_long_castle = 0;
                white_short_castle = 0;
            }
            if(position[x][y] == 'K'){
                black_long_castle = 0;
                black_short_castle = 0;
            }
            if(position[x][y] == 'r'){
                if(y == 0)white_long_castle = 0;
                if(y == 7)white_short_castle = 0;
            }
            if(position[x][y] == 'R'){
                if(y == 0)black_long_castle = 0;
                if(y == 7)black_short_castle = 0;
            }
                if (position[x][y] != ' '){
                    material[position[x][y]]--;
                }
                int b = (m.first).first;
                int a = 7 - (m.first).second;
                if(position[a][b]=='k') {
                white_long_castle = 0;
                white_short_castle = 0;
            }
            if(position[a][b]=='K'){
                black_long_castle = 0;
                black_short_castle = 0;
            }
            if(position[a][b]=='r') {
                if(b==0){
                    white_long_castle = 0;
                }else if(b==7){
                    white_short_castle = 0;
                }
            }
            if(position[a][b]=='R'){
                if(b==0){
                    black_long_castle = 0;
                }else if(b==7){
                    black_short_castle = 0;
                }
            }
                position[x][y] = position[a][b];
                position[a][b] = ' ';
                if(turn == 1){
                    if(position[x][y]=='k'){
                        white_king = make_pair(x, y);
                    }
                }else{
                    if(position[x][y]=='K'){
                        black_king = make_pair(x, y);
                    }
                }
            }
        
        setAttack();
    //cout << "White Attack : " << printBit(attack_white) << endl;
    //cout << "Black Attack : " << printBit(attack_black) << endl;
    }
    

    void move(int m){
      
        
        int x = (m/10)%10; //(m.second).first;
        int y = m%10; //(m.second).second;
        int a = m/1000;
        int b = (m/100)%10;
        if(b == -1){
            if(turn == 1){
                position[7][4] = ' ';
                position[7][7] = ' ';
                position[7][5] = 'r';
                position[7][6] = 'k';
                white_king = make_pair(7, 6);
                white_short_castle = 0;
                white_long_castle = 0;
            }else{
                position[0][4] = ' ';
                position[0][7] = ' ';
                position[0][5] = 'R';
                position[0][6] = 'K';
                black_king = make_pair(0, 6);
                black_short_castle = 0;
                black_long_castle = 0;
            }
            
        }else if(b == -2){
            //cout<<"in";
            if(turn == 1){
                position[7][4] = ' ';
                position[7][0] = ' ';
                position[7][3] = 'r';
                position[7][2] = 'k';
                white_king = make_pair(7, 2);
                white_long_castle = 0;
                white_short_castle = 0;
            }else{
                position[0][4] = ' ';
                position[0][0] = ' ';
                position[0][3] = 'R';
                position[0][2] = 'K';
                black_king = make_pair(0, 2);
                black_long_castle = 0;
                black_short_castle = 0;
            }
            
        }else if(a == -5){
            if(position[x][y] == 'k'){
                white_long_castle = 0;
                white_short_castle = 0;
            }
            if(position[x][y] == 'K'){
                black_long_castle = 0;
                black_short_castle = 0;
            }
            if(position[x][y] == 'r'){
                if(y == 0)white_long_castle = 0;
                if(y == 7)white_short_castle = 0;
            }
            if(position[x][y] == 'R'){
                if(y == 0)black_long_castle = 0;
                if(y == 7)black_short_castle = 0;
            }
            if (position[x][y] != ' '){
                material[position[x][y]]--;
            }

            char proto;
            if(turn == 1){
                a = x + turn;
                proto = 'q';
            }else{
                a = x + turn;
                proto = 'Q';
            }
            position[x][y] = proto;
            position[a][b] = ' ';

        }else if(a == -6){
            if(position[x][y] == 'k'){
                white_long_castle = 0;
                white_short_castle = 0;
            }
            if(position[x][y] == 'K'){
                black_long_castle = 0;
                black_short_castle = 0;
            }
            if(position[x][y] == 'r'){
                if(y == 0)white_long_castle = 0;
                if(y == 7)white_short_castle = 0;
            }
            if(position[x][y] == 'R'){
                if(y == 0)black_long_castle = 0;
                if(y == 7)black_short_castle = 0;
            }
            if (position[x][y] != ' '){
                material[position[x][y]]--;
            }
            char proto;
            if(turn == 1){
                a = x + turn;
                proto = 'r';
            }else{
                a = x + turn;
                proto = 'R';
            }
            position[x][y] = proto;
            position[a][b] = ' ';
        }else if(a == -7){
            if(position[x][y] == 'k'){
                white_long_castle = 0;
                white_short_castle = 0;
            }
            if(position[x][y] == 'K'){
                black_long_castle = 0;
                black_short_castle = 0;
            }
            if(position[x][y] == 'r'){
                if(y == 0)white_long_castle = 0;
                if(y == 7)white_short_castle = 0;
            }
            if(position[x][y] == 'R'){
                if(y == 0)black_long_castle = 0;
                if(y == 7)black_short_castle = 0;
            }
            if (position[x][y] != ' '){
                material[position[x][y]]--;
            }
            char proto;
            if(turn == 1){
                a = x + turn;
                proto = 'n';
            }else{
                a = x + turn;
                proto = 'N';
            }
            position[x][y] = proto;
            position[a][b] = ' ';
        }else if(a == -8){
            if(position[x][y] == 'k'){
                white_long_castle = 0;
                white_short_castle = 0;
            }
            if(position[x][y] == 'K'){
                black_long_castle = 0;
                black_short_castle = 0;
            }
            if(position[x][y] == 'r'){
                if(y == 0)white_long_castle = 0;
                if(y == 7)white_short_castle = 0;
            }
            if(position[x][y] == 'R'){
                if(y == 0)black_long_castle = 0;
                if(y == 7)black_short_castle = 0;
            }
            if (position[x][y] != ' '){
                material[position[x][y]]--;
            }
            char proto;
            if(turn == 1){
                a = x + turn;
                proto = 'b';
            }else{
                a = x + turn;
                proto = 'B';
            }
            position[x][y] = proto;
            position[a][b] = ' ';
        }else{
            if(position[x][y] == 'k'){
                white_long_castle = 0;
                white_short_castle = 0;
            }
            if(position[x][y] == 'K'){
                black_long_castle = 0;
                black_short_castle = 0;
            }
            if(position[x][y] == 'r'){
                if(y == 0)white_long_castle = 0;
                if(y == 7)white_short_castle = 0;
            }
            if(position[x][y] == 'R'){
                if(y == 0)black_long_castle = 0;
                if(y == 7)black_short_castle = 0;
            }
            if (position[x][y] != ' '){
                material[position[x][y]]--;
            }
            
            
            if(position[a][b]=='k') {
                white_long_castle = 0;
                white_short_castle = 0;
            }
            if(position[a][b]=='K'){
                black_long_castle = 0;
                black_short_castle = 0;
            }
            if(position[a][b]=='r') {
                if(b==0){
                    white_long_castle = 0;
                }else if(b==7){
                    white_short_castle = 0;
                }
            }
            if(position[a][b]=='R'){
                if(b==0){
                    black_long_castle = 0;
                }else if(b==7){
                    black_short_castle = 0;
                }
            }
            
            position[x][y] = position[a][b];
            position[a][b] = ' ';
            if(turn == 1){
                    if(position[x][y]=='k'){
                        white_king = make_pair(x, y);
                    }
                }else{
                    if(position[x][y]=='K'){
                        black_king = make_pair(x, y);
                    }
                }
        }
        
        setAttack();
    }

    void Print(){
        for(int i=0; i<=7; i++){
            cout << " ---------------------------------" << endl;
            for(int j=0; j<8; j++){
                
                cout <<" | " << position[i][j]; 
            }
            cout << " |" <<endl;
        }
        cout << " ---------------------------------" << endl;

    }
    
    vector<int> PosMoves(){
        vector<int> m;
        if(turn == 1){
            attack_white = 0ULL;
        }else{
            attack_black = 0ULL;
        }
        for(int i=0; i<8; i++){
            for(int j=0; j<8; j++){
                if(position[i][j] != ' '){
                    char p = position[i][j];
                    if(turn == 1){
                        
                        if(islower(p)){
                            if(p == 'p'){
                                if(i == 6){
                                    if((position[i-2][j] == ' ')&&(position[i-1][j] == ' ')){
                                        m.push_back(makeMove(i, j, i-2, j));
                                        
                                    }
                                }
                                if(i == 1){
                                    if(position[i-1][j] == ' '){
                                        m.push_back(makeMove(-5, j, i-1, j));
                                        m.push_back(makeMove(-6, j, i-1, j));
                                        m.push_back(makeMove(-7, j, i-1, j));
                                        m.push_back(makeMove(-8, j, i-1, j));
                                    }
                                    if((position[i-1][j-1]!=' ') && (isupper(position[i-1][j-1])) && j>0){
                                        m.push_back(makeMove(-5, j, i-1, j-1));attack_white = attack_white | (1ULL << SQ2BIT(i-1, j-1));
                                        m.push_back(makeMove(-6, j, i-1, j-1));attack_white = attack_white | (1ULL << SQ2BIT(i-1, j-1));
                                        m.push_back(makeMove(-7, j, i-1, j-1));attack_white = attack_white | (1ULL << SQ2BIT(i-1, j-1));
                                        m.push_back(makeMove(-8, j, i-1, j-1));attack_white = attack_white | (1ULL << SQ2BIT(i-1, j-1));
                                    }
                                    if((position[i-1][j+1]!=' ') && (isupper(position[i-1][j+1])) && j<7){
                                        //cout<<"upleft"<<endl;
                                        m.push_back(makeMove(-5, j, i-1, j+1));attack_white = attack_white | (1ULL << SQ2BIT(i-1, j+1));
                                        m.push_back(makeMove(-6, j, i-1, j+1));attack_white = attack_white | (1ULL << SQ2BIT(i-1, j+1));
                                        m.push_back(makeMove(-7, j, i-1, j+1));attack_white = attack_white | (1ULL << SQ2BIT(i-1, j+1));
                                        m.push_back(makeMove(-8, j, i-1, j+1));attack_white = attack_white | (1ULL << SQ2BIT(i-1, j+1));
                                    }
                                }else{
                                    if(position[i-1][j] == ' '){
                                        m.push_back(makeMove(i, j, i-1, j));
                                    }
                                    if((position[i-1][j-1]!=' ') && (isupper(position[i-1][j-1])) && j>0){
                                        m.push_back(makeMove(i, j, i-1, j-1));attack_white = attack_white | (1ULL << SQ2BIT(i-1, j-1));
                                    }
                                    if((position[i-1][j+1]!=' ') && (isupper(position[i-1][j+1])) && j<7){
                                        //cout<<"upleft"<<endl;
                                        m.push_back(makeMove(i, j, i-1, j+1));attack_white = attack_white | (1ULL << SQ2BIT(i-1, j+1));
                                    }
                                }
                                
                            }
                            else if(p == 'k'){
                                
                                for(int k = -1; k<=1; k++){
                                    for(int t = -1; t<=1; t++){
                                        if(((i+k)>=0) && ((i+k)<=7) && ((j+t)>=0) && ((j+t)<=7)){attack_white = attack_white | (1ULL << SQ2BIT(i+k, j+t));}
                                        if(((i+k)>=0) && ((i+k)<=7) && ((j+t)>=0) && ((j+t)<=7) && (!(attack_black & (1ULL << (SQ2BIT(i+k, j+t)))))){
                                            //cout << i+k << j+t <<endl;
                                            
                                            if((position[i+k][j+t]!=' ') && (isupper(position[i+k][j+t]))){
                                                
                                                m.push_back(makeMove(i, j, i+k, j+t));
                                            }
                                            if(position[i+k][j+t] == ' '){
                                                m.push_back(makeMove(i, j, i+k, j+t));
                                            }
                                        }
                                    }
                                }
                            }
                            else if(p == 'r'){
                                for(int k=i-1; k>=0; k--){
                                    if(k < 0){
                                        break;
                                    }
                                    if(position[k][j]==' '){
                                        m.push_back(makeMove(i, j, k, j));attack_white = attack_white | (1ULL << SQ2BIT(k, j));
                                    }else{
                                        if(isupper(position[k][j])){
                                            m.push_back(makeMove(i, j, k, j));attack_white = attack_white | (1ULL << SQ2BIT(k, j));
                                        }
                                        break;
                                    }
                                }
                                for(int k=j-1; k>=0; k--){
                                    if(k < 0){
                                        break;
                                    }
                                    if(position[i][k]==' '){
                                        m.push_back(makeMove(i, j, i, k));attack_white = attack_white | (1ULL << SQ2BIT(i, k));
                                    }else{
                                        if(isupper(position[i][k])){
                                            m.push_back(makeMove(i, j, i, k));attack_white = attack_white | (1ULL << SQ2BIT(i, k));
                                        }
                                        break;
                                    }
                                }
                                for(int k=i+1; k<8; k++){
                                    if(k > 7){
                                        break;
                                    }
                                    if(position[k][j]==' '){
                                        m.push_back(makeMove(i, j, k, j));attack_white = attack_white | (1ULL << SQ2BIT(k, j));
                                    }else{
                                        if(isupper(position[k][j])){
                                            m.push_back(makeMove(i, j, k, j));attack_white = attack_white | (1ULL << SQ2BIT(k, j));
                                        }
                                        break;
                                    }
                                }
                                for(int k=j+1; k<8; k++){
                                    if(k > 7){
                                        break;
                                    }
                                    if(position[i][k]==' '){
                                        m.push_back(makeMove(i, j, i, k));attack_white = attack_white | (1ULL << SQ2BIT(i, k));
                                    }else{
                                        if(isupper(position[i][k])){
                                            m.push_back(makeMove(i, j, i, k));attack_white = attack_white | (1ULL << SQ2BIT(i, k));
                                        }
                                        break;
                                    }
                                }
                            }
                            else if(p == 'b'){
                                int k, mm;
                                k=i;
                                mm=j+1;
                                for(int k=i-1; k>=0; k--){
                                    if(mm > 7){
                                        break;
                                    }
                                    if(position[k][mm]==' '){
                                        m.push_back(makeMove(i, j, k, mm));attack_white = attack_white | (1ULL << SQ2BIT(k, mm));
                                    }else{
                                        if(isupper(position[k][mm]))
                                        {m.push_back(makeMove(i, j, k, mm));attack_white = attack_white | (1ULL << SQ2BIT(k, mm));}
                                        break;
                                    }
                                    mm++;
                                    if(mm > 7){
                                        break;
                                    }
                                }mm=j-1;
                                for(int k=i+1; k<=7; k++){
                                    if(mm < 0){
                                        break;
                                    }
                                    if(position[k][mm]==' '){
                                        m.push_back(makeMove(i, j, k, mm));attack_white = attack_white | (1ULL << SQ2BIT(k, mm));
                                    }else{
                                        if(isupper(position[k][mm]))
                                        {m.push_back(makeMove(i, j, k, mm));attack_white = attack_white | (1ULL << SQ2BIT(k, mm));}
                                        break;
                                    }
                                    mm--;
                                    if(mm < 0){
                                        break;
                                    }
                                }mm=j-1;
                                for(int k=i-1; k>=0; k--){
                                    if(mm < 0){
                                        break;
                                    }
                                    if(position[k][mm]==' '){
                                        m.push_back(makeMove(i, j, k, mm));attack_white = attack_white | (1ULL << SQ2BIT(k, mm));
                                    }else{
                                        if(isupper(position[k][mm]))
                                        {m.push_back(makeMove(i, j, k, mm));attack_white = attack_white | (1ULL << SQ2BIT(k, mm));}
                                        break;
                                    }
                                    mm--;
                                    if(mm < 0){
                                        break;
                                    }
                                }mm=j+1;
                                for(int k=i+1; k<=7; k++){
                                    if(mm > 7){
                                        break;
                                    }
                                    if(position[k][mm]==' '){
                                        m.push_back(makeMove(i, j, k, mm));attack_white = attack_white | (1ULL << SQ2BIT(k, mm));
                                    }else{
                                        if(isupper(position[k][mm]))
                                        {m.push_back(makeMove(i, j, k, mm));attack_white = attack_white | (1ULL << SQ2BIT(k, mm));}

                                        break;
                                    }
                                    mm++;
                                    if(mm > 7){
                                        break;
                                    }
                                }
                            }
                            else if(p == 'q'){
                                for(int k=i-1; k>=0; k--){
                                    if(k < 0){
                                        break;
                                    }
                                    if(position[k][j]==' '){
                                        m.push_back(makeMove(i, j, k, j));attack_white = attack_white | (1ULL << SQ2BIT(k, j));
                                    }else{
                                        if(isupper(position[k][j])){
                                            m.push_back(makeMove(i, j, k, j));attack_white = attack_white | (1ULL << SQ2BIT(k, j));
                                        }
                                        break;
                                    }
                                }
                                for(int k=j-1; k>=0; k--){
                                    if(k < 0){
                                        break;
                                    }
                                    if(position[i][k]==' '){
                                        m.push_back(makeMove(i, j, i, k));attack_white = attack_white | (1ULL << SQ2BIT(i, k));
                                    }else{
                                        if(isupper(position[i][k])){
                                            m.push_back(makeMove(i, j, i, k));attack_white = attack_white | (1ULL << SQ2BIT(i, k));
                                        }
                                        break;
                                    }
                                }
                                for(int k=i+1; k<8; k++){
                                    if(k > 7){
                                        break;
                                    }
                                    if(position[k][j]==' '){
                                        m.push_back(makeMove(i, j, k, j));attack_white = attack_white | (1ULL << SQ2BIT(k, j));
                                    }else{
                                        if(isupper(position[k][j])){
                                            m.push_back(makeMove(i, j, k, j));attack_white = attack_white | (1ULL << SQ2BIT(k, j));
                                        }
                                        break;
                                    }
                                }
                                for(int k=j+1; k<8; k++){
                                    if(k > 7){
                                        break;
                                    }
                                    if(position[i][k]==' '){
                                        m.push_back(makeMove(i, j, i, k));attack_white = attack_white | (1ULL << SQ2BIT(i, k));
                                    }else{
                                        if(isupper(position[i][k])){
                                            m.push_back(makeMove(i, j, i, k));attack_white = attack_white | (1ULL << SQ2BIT(i, k));
                                        }
                                        break;
                                    }
                                }
                                int k, mm;
                                k=i;
                                mm=j+1;
                                for(int k=i-1; k>=0; k--){
                                    if(mm > 7){
                                        break;
                                    }
                                    if(position[k][mm]==' '){
                                        m.push_back(makeMove(i, j, k, mm));attack_white = attack_white | (1ULL << SQ2BIT(k, mm));
                                    }else{
                                        if(isupper(position[k][mm]))
                                        {m.push_back(makeMove(i, j, k, mm));attack_white = attack_white | (1ULL << SQ2BIT(k, mm));}
                                        break;
                                    }
                                    mm++;
                                    if(mm > 7){
                                        break;
                                    }
                                }mm=j-1;
                                for(int k=i+1; k<=7; k++){
                                    if(mm < 0){
                                        break;
                                    }
                                    if(position[k][mm]==' '){
                                        m.push_back(makeMove(i, j, k, mm));attack_white = attack_white | (1ULL << SQ2BIT(k, mm));
                                    }else{
                                        if(isupper(position[k][mm]))
                                        {m.push_back(makeMove(i, j, k, mm));attack_white = attack_white | (1ULL << SQ2BIT(k, mm));}
                                        break;
                                    }
                                    mm--;
                                    if(mm < 0){
                                        break;
                                    }
                                }mm=j-1;
                                for(int k=i-1; k>=0; k--){
                                    if(mm < 0){
                                        break;
                                    }
                                    if(position[k][mm]==' '){
                                        m.push_back(makeMove(i, j, k, mm));attack_white = attack_white | (1ULL << SQ2BIT(k, mm));
                                    }else{
                                        if(isupper(position[k][mm]))
                                        {m.push_back(makeMove(i, j, k, mm));attack_white= attack_white | (1ULL << SQ2BIT(k, mm));}
                                        break;
                                    }
                                    mm--;
                                    if(mm < 0){
                                        break;
                                    }
                                }mm=j+1;
                                for(int k=i+1; k<=7; k++){
                                    if(mm > 7){
                                        break;
                                    }
                                    if(position[k][mm]==' '){
                                        m.push_back(makeMove(i, j, k, mm));attack_white = attack_white | (1ULL << SQ2BIT(k, mm));
                                    }else{
                                        if(isupper(position[k][mm]))
                                        {m.push_back(makeMove(i, j, k, mm));attack_white = attack_white | (1ULL << SQ2BIT(k, mm));}
                                        break;
                                    }
                                    mm++;
                                    if(mm > 7){
                                        break;
                                    }
                                }
                            }
                            else if(p == 'n'){
                                if(i>=2 && j>=1 && position[i-2][j-1] == ' '){
                                    m.push_back(makeMove(i, j, i-2, j-1));attack_white = attack_white | (1ULL << SQ2BIT(i-2, j-1));
                                }else{
                                    if(i>=2 && j>=1 && isupper(position[i-2][j-1])){
                                        m.push_back(makeMove(i, j, i-2, j-1));attack_white = attack_white | (1ULL << SQ2BIT(i-2, j-1));
                                    }
                                }
                                if(i>=2 && j<=6 && position[i-2][j+1] == ' '){
                                    m.push_back(makeMove(i, j, i-2, j+1));attack_white = attack_white | (1ULL << SQ2BIT(i-2, j+1));
                                }else{
                                    if(i>=2 && j<=6 && isupper(position[i-2][j+1])){
                                        m.push_back(makeMove(i, j, i-2, j+1));attack_white = attack_white | (1ULL << SQ2BIT(i-2, j+1));
                                    }
                                }
                                if(i<=5 && j>=1 && position[i+2][j-1] == ' '){
                                    m.push_back(makeMove(i, j, i+2, j-1));attack_white = attack_white | (1ULL << SQ2BIT(i+2, j-1));
                                }else{
                                    if(i<=5 && j>=1 && isupper(position[i+2][j-1])){
                                        m.push_back(makeMove(i, j, i+2, j-1));attack_white = attack_white | (1ULL << SQ2BIT(i+2, j-1));
                                    }
                                }
                                if(i<=5 && j<=6 && position[i+2][j+1] == ' '){
                                    m.push_back(makeMove(i, j, i+2, j+1));attack_white = attack_white | (1ULL << SQ2BIT(i+2, j+1));
                                }else{
                                    if(i<=5 && j<=6 && isupper(position[i+2][j+1])){
                                        m.push_back(makeMove(i, j, i+2, j+1));attack_white = attack_white | (1ULL << SQ2BIT(i+2, j+1));
                                    }
                                }
                                if(i>=1 && j>=2 && position[i-1][j-2] == ' '){
                                    m.push_back(makeMove(i, j, i-1, j-2));attack_white = attack_white | (1ULL << SQ2BIT(i-1, j-2));
                                }else{
                                    if(i>=1 && j>=2 && isupper(position[i-1][j-2])){
                                        m.push_back(makeMove(i, j, i-1, j-2));attack_white = attack_white | (1ULL << SQ2BIT(i-1, j-2));
                                    }
                                }
                                if(i>=1 && j<=5 && position[i-1][j+2] == ' '){
                                    m.push_back(makeMove(i, j, i-1, j+2));attack_white = attack_white | (1ULL << SQ2BIT(i-1, j+2));
                                }else{
                                    if(i>=1 && j<=5 && isupper(position[i-1][j+2])){
                                        m.push_back(makeMove(i, j, i-1, j+2));attack_white = attack_white | (1ULL << SQ2BIT(i-1, j+2));
                                    }
                                }
                                if(i<=6 && j>=2 && position[i+1][j-2] == ' '){
                                    m.push_back(makeMove(i, j, i+1, j-2));attack_white = attack_white | (1ULL << SQ2BIT(i+1, j-2));
                                }else{
                                    if(i<=6 && j>=2 && isupper(position[i+1][j-2])){
                                        m.push_back(makeMove(i, j, i+1, j-2));attack_white = attack_white | (1ULL << SQ2BIT(i+1, j-2));
                                    }
                                }
                                if(i<=6 && j<=5 && position[i+1][j+2] == ' '){
                                    m.push_back(makeMove(i, j, i+1, j+2));attack_white = attack_white | (1ULL << SQ2BIT(i+1, j+2));
                                }else{
                                    if(i<=6 && j<=5 && isupper(position[i+1][j+2])){
                                        m.push_back(makeMove(i, j, i+1, j+2));attack_white = attack_white | (1ULL << SQ2BIT(i+1, j+2));
                                    }
                                }
                            }
                        }
                    }else{
                        //cout << "jada nasha" <<endl;
                        
                        if(isupper(p)){
                            if(p == 'P'){
                                if(i == 1){
                                    if((position[i+2][j] == ' ')&&(position[i+1][j] == ' ')){
                                        m.push_back(makeMove(i, j, i+2, j));
                                        
                                    }
                                }
                                if(i == 6){
                                    if(position[i+1][j] == ' '){
                                        m.push_back(makeMove(-5, j, i+1, j));
                                        m.push_back(makeMove(-6, j, i+1, j));
                                        m.push_back(makeMove(-7, j, i+1, j));
                                        m.push_back(makeMove(-8, j, i+1, j));
                                    }
                                    if((position[i+1][j-1]!=' ') && (islower(position[i+1][j-1])) && j>0){
                                        m.push_back(makeMove(-5, j, i+1, j-1));attack_black = attack_black | (1ULL << SQ2BIT(i+1, j-1));
                                        m.push_back(makeMove(-6, j, i+1, j-1));attack_black = attack_black | (1ULL << SQ2BIT(i+1, j-1));
                                        m.push_back(makeMove(-7, j, i+1, j-1));attack_black = attack_black | (1ULL << SQ2BIT(i+1, j-1));
                                        m.push_back(makeMove(-8, j, i+1, j-1));attack_black = attack_black | (1ULL << SQ2BIT(i+1, j-1));
                                    }
                                    if((position[i+1][j+1]!=' ') && (islower(position[i+1][j+1])) && j<7){
                                        m.push_back(makeMove(-5, j, i+1, j+1));attack_black = attack_black | (1ULL << SQ2BIT(i+1, j+1));
                                        m.push_back(makeMove(-6, j, i+1, j+1));attack_black = attack_black | (1ULL << SQ2BIT(i+1, j+1));
                                        m.push_back(makeMove(-7, j, i+1, j+1));attack_black = attack_black | (1ULL << SQ2BIT(i+1, j+1));
                                        m.push_back(makeMove(-8, j, i+1, j+1));attack_black = attack_black | (1ULL << SQ2BIT(i+1, j+1));
                                    }
                                }else{
                                    if(position[i+1][j] == ' '){
                                        m.push_back(makeMove(i, j, i+1, j));
                                    }
                                    if((position[i+1][j-1]!=' ') && (islower(position[i+1][j-1])) && j>0){
                                        m.push_back(makeMove(i, j, i+1, j-1));attack_black = attack_black | (1ULL << SQ2BIT(i+1, j-1));
                                    }
                                    if((position[i+1][j+1]!=' ') && (islower(position[i+1][j+1])) && j<7){
                                        m.push_back(makeMove(i, j, i+1, j+1));attack_black = attack_black | (1ULL << SQ2BIT(i+1, j+1));
                                    }
                                }
                                
                            }
                            else if(p == 'K'){
                                
                                for(int k = -1; k<=1; k++){
                                    for(int t = -1; t<=1; t++){ attack_black = attack_black | (1ULL << SQ2BIT(i+k, j+t));
                                        //cout << i+k << j+t <<endl;
                                        if(((i+k)>=0) && ((i+k)<=7) && ((j+t)>=0) && ((j+t)<=7) && (!(attack_white & (1ULL << (SQ2BIT(i+k, j+t)))))){
                                           
                                            if((position[i+k][j+t]!=' ') && (islower(position[i+k][j+t]))){
                                                
                                                m.push_back(makeMove(i, j, i+k, j+t));
                                            }
                                            if(position[i+k][j+t] == ' '){
                                                m.push_back(makeMove(i, j, i+k, j+t));
                                            }
                                        }
                                    }
                                }
                            }
                            else if(p == 'R'){
                                for(int k=i-1; k>=0; k--){
                                    if(k < 0){
                                        break;
                                    }
                                    if(position[k][j]==' '){
                                        m.push_back(makeMove(i, j, k, j));attack_black = attack_black | (1ULL << SQ2BIT(k, j));
                                    }else{
                                        if(islower(position[k][j])){
                                            m.push_back(makeMove(i, j, k, j));attack_black = attack_black | (1ULL << SQ2BIT(k, j));
                                        }
                                        break;
                                    }
                                }
                                for(int k=j-1; k>=0; k--){
                                    if(k < 0){
                                        break;
                                    }
                                    if(position[i][k]==' '){
                                        m.push_back(makeMove(i, j, i, k));attack_black = attack_black | (1ULL << SQ2BIT(i, k));
                                    }else{
                                        if(islower(position[i][k])){
                                            m.push_back(makeMove(i, j, i, k));attack_black = attack_black | (1ULL << SQ2BIT(i, k));
                                        }
                                        break;
                                    }
                                }
                                for(int k=i+1; k<8; k++){
                                    if(k > 7){
                                        break;
                                    }
                                    if(position[k][j]==' '){
                                        m.push_back(makeMove(i, j, k, j));attack_black = attack_black | (1ULL << SQ2BIT(k, j));
                                    }else{
                                        if(islower(position[k][j])){
                                            m.push_back(makeMove(i, j, k, j));attack_black = attack_black | (1ULL << SQ2BIT(k, j));
                                        }
                                        break;
                                    }
                                }
                                for(int k=j+1; k<8; k++){
                                    if(k > 7){
                                        break;
                                    }
                                    if(position[i][k]==' '){
                                        m.push_back(makeMove(i, j, i, k));attack_black = attack_black | (1ULL << SQ2BIT(i, k));
                                    }else{
                                        if(islower(position[i][k])){
                                            m.push_back(makeMove(i, j, i, k));attack_black = attack_black | (1ULL << SQ2BIT(i, k));
                                        }
                                        break;
                                    }
                                }
                            }
                            else if(p == 'B'){
                                int k, mm;
                                k=i;
                                mm=j+1;
                                for(int k=i-1; k>=0; k--){
                                    if(mm > 7){
                                        break;
                                    }
                                    if(position[k][mm]==' '){
                                        m.push_back(makeMove(i, j, k, mm));attack_black = attack_black | (1ULL << SQ2BIT(k, mm));
                                    }else{
                                        if(islower(position[k][mm]))
                                        {m.push_back(makeMove(i, j, k, mm));attack_black = attack_black | (1ULL << SQ2BIT(k, mm));}
                                        break;
                                    }
                                    mm++;
                                    if(mm > 7){
                                        break;
                                    }
                                }mm=j-1;
                                for(int k=i+1; k<=7; k++){
                                    if(mm < 0){
                                        break;
                                    }
                                    if(position[k][mm]==' '){
                                        m.push_back(makeMove(i, j, k, mm));attack_black = attack_black | (1ULL << SQ2BIT(k, mm));
                                    }else{
                                        if(islower(position[k][mm]))
                                        {m.push_back(makeMove(i, j, k, mm));attack_black = attack_black | (1ULL << SQ2BIT(k, mm));}
                                        break;
                                    }
                                    mm--;
                                    if(mm < 0){
                                        break;
                                    }
                                }mm=j-1;
                                for(int k=i-1; k>=0; k--){
                                    if(mm < 0){
                                        break;
                                    }
                                    if(position[k][mm]==' '){
                                        m.push_back(makeMove(i, j, k, mm));attack_black = attack_black | (1ULL << SQ2BIT(k, mm));
                                    }else{
                                        if(islower(position[k][mm]))
                                        {m.push_back(makeMove(i, j, k, mm));attack_black = attack_black | (1ULL << SQ2BIT(k, mm));}
                                        break;
                                    }
                                    mm--;
                                    if(mm < 0){
                                        break;
                                    }
                                }mm=j+1;
                                for(int k=i+1; k<=7; k++){
                                    if(mm > 7){
                                        break;
                                    }
                                    if(position[k][mm]==' '){
                                        m.push_back(makeMove(i, j, k, mm));attack_black = attack_black | (1ULL << SQ2BIT(k, mm));
                                    }else{
                                        if(islower(position[k][mm]))
                                        {m.push_back(makeMove(i, j, k, mm));attack_black = attack_black | (1ULL << SQ2BIT(k, mm));}
                                        break;
                                    }
                                    mm++;
                                    if(mm > 7){
                                        break;
                                    }
                                }
                            }
                            else if(p == 'Q'){
                                for(int k=i-1; k>=0; k--){
                                    if(k < 0){
                                        break;
                                    }
                                    if(position[k][j]==' '){
                                        m.push_back(makeMove(i, j, k, j));attack_black = attack_black | (1ULL << SQ2BIT(k, j));
                                    }else{
                                        if(islower(position[k][j])){
                                            m.push_back(makeMove(i, j, k, j));attack_black = attack_black | (1ULL << SQ2BIT(k, j));
                                        }
                                        break;
                                    }
                                }
                                for(int k=j-1; k>=0; k--){
                                    if(k < 0){
                                        break;
                                    }
                                    if(position[i][k]==' '){
                                        m.push_back(makeMove(i, j, i, k));attack_black = attack_black | (1ULL << SQ2BIT(i, k));
                                    }else{
                                        if(islower(position[i][k])){
                                            m.push_back(makeMove(i, j, i, k));attack_black = attack_black | (1ULL << SQ2BIT(i, k));
                                        }
                                        break;
                                    }
                                }
                                for(int k=i+1; k<8; k++){
                                    if(k > 7){
                                        break;
                                    }
                                    if(position[k][j]==' '){
                                        m.push_back(makeMove(i, j, k, j));attack_black = attack_black | (1ULL << SQ2BIT(k, j));
                                    }else{
                                        if(islower(position[k][j])){
                                            m.push_back(makeMove(i, j, k, j));attack_black = attack_black | (1ULL << SQ2BIT(k, j));
                                        }
                                        break;
                                    }
                                }
                                for(int k=j+1; k<8; k++){
                                    if(k > 7){
                                        break;
                                    }
                                    if(position[i][k]==' '){
                                        m.push_back(makeMove(i, j, i, k));attack_black = attack_black | (1ULL << SQ2BIT(i, k));
                                    }else{
                                        if(islower(position[i][k])){
                                            m.push_back(makeMove(i, j, i, k));attack_black = attack_black | (1ULL << SQ2BIT(i, k));
                                        }
                                        break;
                                    }
                                }
                                int k, mm;
                                k=i;
                                mm=j+1;
                                for(int k=i-1; k>=0; k--){
                                    if(mm > 7){
                                        break;
                                    }
                                    if(position[k][mm]==' '){
                                        m.push_back(makeMove(i, j, k, mm));attack_black = attack_black | (1ULL << SQ2BIT(k, mm));
                                    }else{
                                        if(islower(position[k][mm]))
                                        {m.push_back(makeMove(i, j, k, mm));attack_black = attack_black | (1ULL << SQ2BIT(k, mm));}
                                        break;
                                    }
                                    mm++;
                                    if(mm > 7){
                                        break;
                                    }
                                }mm=j-1;
                                for(int k=i+1; k<=7; k++){
                                    if(mm < 0){
                                        break;
                                    }
                                    if(position[k][mm]==' '){
                                        m.push_back(makeMove(i, j, k, mm));attack_black = attack_black | (1ULL << SQ2BIT(k, mm));
                                    }else{
                                        if(islower(position[k][mm]))
                                        {m.push_back(makeMove(i, j, k, mm));attack_black = attack_black | (1ULL << SQ2BIT(k, mm));}
                                        break;
                                    }
                                    mm--;
                                    if(mm < 0){
                                        break;
                                    }
                                }mm=j-1;
                                for(int k=i-1; k>=0; k--){
                                    if(mm < 0){
                                        break;
                                    }
                                    if(position[k][mm]==' '){
                                        m.push_back(makeMove(i, j, k, mm));attack_black = attack_black | (1ULL << SQ2BIT(k, mm));
                                    }else{
                                        if(islower(position[k][mm]))
                                        {m.push_back(makeMove(i, j, k, mm));attack_black = attack_black | (1ULL << SQ2BIT(k, mm));}
                                        break;
                                    }
                                    mm--;
                                    if(mm < 0){
                                        break;
                                    }
                                }mm=j+1;
                                for(int k=i+1; k<=7; k++){
                                    if(mm > 7){
                                        break;
                                    }
                                    if(position[k][mm]==' '){
                                        m.push_back(makeMove(i, j, k, mm));attack_black = attack_black | (1ULL << SQ2BIT(k, mm));
                                    }else{
                                        if(islower(position[k][mm]))
                                        {m.push_back(makeMove(i, j, k, mm));attack_black = attack_black | (1ULL << SQ2BIT(k, mm));}
                                        break;
                                    }
                                    mm++;
                                    if(mm > 7){
                                        break;
                                    }
                                }
                            }
                            else if(p == 'N'){
                                if(i>=2 && j>=1 && position[i-2][j-1] == ' '){
                                    m.push_back(makeMove(i, j, i-2, j-1));attack_black = attack_black | (1ULL << SQ2BIT(i-2, j-1));
                                }else{
                                    if(i>=2 && j>=1 && islower(position[i-2][j-1])){
                                        m.push_back(makeMove(i, j, i-2, j-1));attack_black = attack_black | (1ULL << SQ2BIT(i-2, j-1));
                                    }
                                }
                                if(i>=2 && j<=6 && position[i-2][j+1] == ' '){
                                    m.push_back(makeMove(i, j, i-2, j+1));attack_black = attack_black | (1ULL << SQ2BIT(i-2, j+1));
                                }else{
                                    if(i>=2 && j<=6 && islower(position[i-2][j+1])){
                                        m.push_back(makeMove(i, j, i-2, j+1));attack_black = attack_black | (1ULL << SQ2BIT(i-2, j+1));
                                    }
                                }
                                if(i<=5 && j>=1 && position[i+2][j-1] == ' '){
                                    m.push_back(makeMove(i, j, i+2, j-1));attack_black = attack_black | (1ULL << SQ2BIT(i+2, j-1));
                                }else{
                                    if(i<=5 && j>=1 && islower(position[i+2][j-1])){
                                        m.push_back(makeMove(i, j, i+2, j-1));attack_black = attack_black | (1ULL << SQ2BIT(i+2, j-1));
                                    }
                                }
                                if(i<=5 && j<=6 && position[i+2][j+1] == ' '){
                                    m.push_back(makeMove(i, j, i+2, j+1));attack_black = attack_black | (1ULL << SQ2BIT(i+2, j+1));
                                }else{
                                    if(i<=5 && j<=6 && islower(position[i+2][j+1])){
                                        m.push_back(makeMove(i, j, i+2, j+1));attack_black = attack_black | (1ULL << SQ2BIT(i+2, j+1));
                                    }
                                }
                                if(i>=1 && j>=2 && position[i-1][j-2] == ' '){
                                    m.push_back(makeMove(i, j, i-1, j-2));attack_black = attack_black | (1ULL << SQ2BIT(i-1, j-2));
                                }else{
                                    if(i>=1 && j>=2 && islower(position[i-1][j-2])){
                                        m.push_back(makeMove(i, j, i-1, j-2));attack_black = attack_black | (1ULL << SQ2BIT(i-1, j-2));
                                    }
                                }
                                if(i>=1 && j<=5 && position[i-1][j+2] == ' '){
                                    m.push_back(makeMove(i, j, i-1, j+2));attack_black = attack_black | (1ULL << SQ2BIT(i-1, j+2));
                                }else{
                                    if(i>=1 && j<=5 && islower(position[i-1][j+2])){
                                        m.push_back(makeMove(i, j, i-1, j+2));attack_black = attack_black | (1ULL << SQ2BIT(i-1, j+2));
                                    }
                                }
                                if(i<=6 && j>=2 && position[i+1][j-2] == ' '){
                                    m.push_back(makeMove(i, j, i+1, j-2));attack_black = attack_black | (1ULL << SQ2BIT(i+1, j-2));
                                }else{
                                    if(i<=6 && j>=2 && islower(position[i+1][j-2])){
                                        m.push_back(makeMove(i, j, i+1, j-2));attack_black = attack_black | (1ULL << SQ2BIT(i+1, j-2));
                                    }
                                }
                                if(i<=6 && j<=5 && position[i+1][j+2] == ' '){
                                    m.push_back(makeMove(i, j, i+1, j+2));attack_black = attack_black | (1ULL << SQ2BIT(i+1, j+2));
                                }else{
                                    if(i<=6 && j<=5 && islower(position[i+1][j+2])){
                                        m.push_back(makeMove(i, j, i+1, j+2));attack_black = attack_black | (1ULL << SQ2BIT(i+1, j+2));
                                    }
                                }
                            }
                        }
                            
                    }
                }
            }
        }
        return m;
    }
    vector<int> PosMoves(MOVE prem){
        unordered_map<char, vector<int>> m;
        m.insert(make_pair('k', vector<int>()));
        m.insert(make_pair('q', vector<int>()));
        m.insert(make_pair('r', vector<int>()));
        m.insert(make_pair('b', vector<int>()));
        m.insert(make_pair('n', vector<int>()));
        m.insert(make_pair('p',vector<int>()));
        vector<char> order = {'k', 'q', 'r', 'n', 'b', 'p'};
        
        if(turn == 1){
            attack_white = 0ULL;
        }else{
            attack_black = 0ULL;
        }
        for(int i=0; i<8; i++){
            for(int j=0; j<8; j++){
                if(position[i][j] != ' '){
                    char p = position[i][j];
                    if(turn == 1){
                        
                        if(islower(p)){
                            if(p == 'p'){
                                if(i == 6){
                                    if((position[i-2][j] == ' ')&&(position[i-1][j] == ' ')){
                                        m[tolower(p)].push_back(makeMove(i, j, i-2, j));
                                        
                                    }
                                }
                                if(i == 1){
                                    if(position[i-1][j] == ' '){
                                        m[tolower(p)].push_back(makeMove(-5, j, i-1, j));
                                        m[tolower(p)].push_back(makeMove(-6, j, i-1, j));
                                        m[tolower(p)].push_back(makeMove(-7, j, i-1, j));
                                        m[tolower(p)].push_back(makeMove(-8, j, i-1, j));
                                    }
                                    if((position[i-1][j-1]!=' ') && (isupper(position[i-1][j-1])) && j>0){
                                        m[tolower(p)].push_back(makeMove(-5, j, i-1, j-1));attack_white = attack_white | (1ULL << SQ2BIT(i-1, j-1));
                                        m[tolower(p)].push_back(makeMove(-6, j, i-1, j-1));attack_white = attack_white | (1ULL << SQ2BIT(i-1, j-1));
                                        m[tolower(p)].push_back(makeMove(-7, j, i-1, j-1));attack_white = attack_white | (1ULL << SQ2BIT(i-1, j-1));
                                        m[tolower(p)].push_back(makeMove(-8, j, i-1, j-1));attack_white = attack_white | (1ULL << SQ2BIT(i-1, j-1));
                                    }
                                    if((position[i-1][j+1]!=' ') && (isupper(position[i-1][j+1])) && j<7){
                                        //cout<<"upleft"<<endl;
                                        m[tolower(p)].push_back(makeMove(-5, j, i-1, j+1));attack_white = attack_white | (1ULL << SQ2BIT(i-1, j+1));
                                        m[tolower(p)].push_back(makeMove(-6, j, i-1, j+1));attack_white = attack_white | (1ULL << SQ2BIT(i-1, j+1));
                                        m[tolower(p)].push_back(makeMove(-7, j, i-1, j+1));attack_white = attack_white | (1ULL << SQ2BIT(i-1, j+1));
                                        m[tolower(p)].push_back(makeMove(-8, j, i-1, j+1));attack_white = attack_white | (1ULL << SQ2BIT(i-1, j+1));
                                    }
                                }else{
                                    if(position[i-1][j] == ' '){
                                        m[tolower(p)].push_back(makeMove(i, j, i-1, j));
                                    }
                                    if((position[i-1][j-1]!=' ') && (isupper(position[i-1][j-1])) && j>0){
                                        m[tolower(p)].push_back(makeMove(i, j, i-1, j-1));attack_white = attack_white | (1ULL << SQ2BIT(i-1, j-1));
                                    }
                                    if((position[i-1][j+1]!=' ') && (isupper(position[i-1][j+1])) && j<7){
                                        //cout<<"upleft"<<endl;
                                        m[tolower(p)].push_back(makeMove(i, j, i-1, j+1));attack_white = attack_white | (1ULL << SQ2BIT(i-1, j+1));
                                    }
                                }
                                
                            }
                            else if(p == 'k'){
                                
                                for(int k = -1; k<=1; k++){
                                    for(int t = -1; t<=1; t++){
                                        if(((i+k)>=0) && ((i+k)<=7) && ((j+t)>=0) && ((j+t)<=7)){attack_white = attack_white | (1ULL << SQ2BIT(i+k, j+t));}
                                        if(((i+k)>=0) && ((i+k)<=7) && ((j+t)>=0) && ((j+t)<=7) && (!(attack_black & (1ULL << (SQ2BIT(i+k, j+t)))))){
                                            //cout << i+k << j+t <<endl;
                                            
                                            if((position[i+k][j+t]!=' ') && (isupper(position[i+k][j+t]))){
                                                
                                                m[tolower(p)].push_back(makeMove(i, j, i+k, j+t));
                                            }
                                            if(position[i+k][j+t] == ' '){
                                                m[tolower(p)].push_back(makeMove(i, j, i+k, j+t));
                                            }
                                        }
                                    }
                                }
                            }
                            else if(p == 'r'){
                                for(int k=i-1; k>=0; k--){
                                    if(k < 0){
                                        break;
                                    }
                                    if(position[k][j]==' '){
                                        m[tolower(p)].push_back(makeMove(i, j, k, j));attack_white = attack_white | (1ULL << SQ2BIT(k, j));
                                    }else{
                                        if(isupper(position[k][j])){
                                            m[tolower(p)].push_back(makeMove(i, j, k, j));attack_white = attack_white | (1ULL << SQ2BIT(k, j));
                                        }
                                        break;
                                    }
                                }
                                for(int k=j-1; k>=0; k--){
                                    if(k < 0){
                                        break;
                                    }
                                    if(position[i][k]==' '){
                                        m[tolower(p)].push_back(makeMove(i, j, i, k));attack_white = attack_white | (1ULL << SQ2BIT(i, k));
                                    }else{
                                        if(isupper(position[i][k])){
                                            m[tolower(p)].push_back(makeMove(i, j, i, k));attack_white = attack_white | (1ULL << SQ2BIT(i, k));
                                        }
                                        break;
                                    }
                                }
                                for(int k=i+1; k<8; k++){
                                    if(k > 7){
                                        break;
                                    }
                                    if(position[k][j]==' '){
                                        m[tolower(p)].push_back(makeMove(i, j, k, j));attack_white = attack_white | (1ULL << SQ2BIT(k, j));
                                    }else{
                                        if(isupper(position[k][j])){
                                            m[tolower(p)].push_back(makeMove(i, j, k, j));attack_white = attack_white | (1ULL << SQ2BIT(k, j));
                                        }
                                        break;
                                    }
                                }
                                for(int k=j+1; k<8; k++){
                                    if(k > 7){
                                        break;
                                    }
                                    if(position[i][k]==' '){
                                        m[tolower(p)].push_back(makeMove(i, j, i, k));attack_white = attack_white | (1ULL << SQ2BIT(i, k));
                                    }else{
                                        if(isupper(position[i][k])){
                                            m[tolower(p)].push_back(makeMove(i, j, i, k));attack_white = attack_white | (1ULL << SQ2BIT(i, k));
                                        }
                                        break;
                                    }
                                }
                            }
                            else if(p == 'b'){
                                int k, mm;
                                k=i;
                                mm=j+1;
                                for(int k=i-1; k>=0; k--){
                                    if(mm > 7){
                                        break;
                                    }
                                    if(position[k][mm]==' '){
                                        m[tolower(p)].push_back(makeMove(i, j, k, mm));attack_white = attack_white | (1ULL << SQ2BIT(k, mm));
                                    }else{
                                        if(isupper(position[k][mm]))
                                        {m[tolower(p)].push_back(makeMove(i, j, k, mm));attack_white = attack_white | (1ULL << SQ2BIT(k, mm));}
                                        break;
                                    }
                                    mm++;
                                    if(mm > 7){
                                        break;
                                    }
                                }mm=j-1;
                                for(int k=i+1; k<=7; k++){
                                    if(mm < 0){
                                        break;
                                    }
                                    if(position[k][mm]==' '){
                                        m[tolower(p)].push_back(makeMove(i, j, k, mm));attack_white = attack_white | (1ULL << SQ2BIT(k, mm));
                                    }else{
                                        if(isupper(position[k][mm]))
                                        {m[tolower(p)].push_back(makeMove(i, j, k, mm));attack_white = attack_white | (1ULL << SQ2BIT(k, mm));}
                                        break;
                                    }
                                    mm--;
                                    if(mm < 0){
                                        break;
                                    }
                                }mm=j-1;
                                for(int k=i-1; k>=0; k--){
                                    if(mm < 0){
                                        break;
                                    }
                                    if(position[k][mm]==' '){
                                        m[tolower(p)].push_back(makeMove(i, j, k, mm));attack_white = attack_white | (1ULL << SQ2BIT(k, mm));
                                    }else{
                                        if(isupper(position[k][mm]))
                                        {m[tolower(p)].push_back(makeMove(i, j, k, mm));attack_white = attack_white | (1ULL << SQ2BIT(k, mm));}
                                        break;
                                    }
                                    mm--;
                                    if(mm < 0){
                                        break;
                                    }
                                }mm=j+1;
                                for(int k=i+1; k<=7; k++){
                                    if(mm > 7){
                                        break;
                                    }
                                    if(position[k][mm]==' '){
                                        m[tolower(p)].push_back(makeMove(i, j, k, mm));attack_white = attack_white | (1ULL << SQ2BIT(k, mm));
                                    }else{
                                        if(isupper(position[k][mm]))
                                        {m[tolower(p)].push_back(makeMove(i, j, k, mm));attack_white = attack_white | (1ULL << SQ2BIT(k, mm));}

                                        break;
                                    }
                                    mm++;
                                    if(mm > 7){
                                        break;
                                    }
                                }
                            }
                            else if(p == 'q'){
                                for(int k=i-1; k>=0; k--){
                                    if(k < 0){
                                        break;
                                    }
                                    if(position[k][j]==' '){
                                        m[tolower(p)].push_back(makeMove(i, j, k, j));attack_white = attack_white | (1ULL << SQ2BIT(k, j));
                                    }else{
                                        if(isupper(position[k][j])){
                                            m[tolower(p)].push_back(makeMove(i, j, k, j));attack_white = attack_white | (1ULL << SQ2BIT(k, j));
                                        }
                                        break;
                                    }
                                }
                                for(int k=j-1; k>=0; k--){
                                    if(k < 0){
                                        break;
                                    }
                                    if(position[i][k]==' '){
                                        m[tolower(p)].push_back(makeMove(i, j, i, k));attack_white = attack_white | (1ULL << SQ2BIT(i, k));
                                    }else{
                                        if(isupper(position[i][k])){
                                            m[tolower(p)].push_back(makeMove(i, j, i, k));attack_white = attack_white | (1ULL << SQ2BIT(i, k));
                                        }
                                        break;
                                    }
                                }
                                for(int k=i+1; k<8; k++){
                                    if(k > 7){
                                        break;
                                    }
                                    if(position[k][j]==' '){
                                        m[tolower(p)].push_back(makeMove(i, j, k, j));attack_white = attack_white | (1ULL << SQ2BIT(k, j));
                                    }else{
                                        if(isupper(position[k][j])){
                                            m[tolower(p)].push_back(makeMove(i, j, k, j));attack_white = attack_white | (1ULL << SQ2BIT(k, j));
                                        }
                                        break;
                                    }
                                }
                                for(int k=j+1; k<8; k++){
                                    if(k > 7){
                                        break;
                                    }
                                    if(position[i][k]==' '){
                                        m[tolower(p)].push_back(makeMove(i, j, i, k));attack_white = attack_white | (1ULL << SQ2BIT(i, k));
                                    }else{
                                        if(isupper(position[i][k])){
                                            m[tolower(p)].push_back(makeMove(i, j, i, k));attack_white = attack_white | (1ULL << SQ2BIT(i, k));
                                        }
                                        break;
                                    }
                                }
                                int k, mm;
                                k=i;
                                mm=j+1;
                                for(int k=i-1; k>=0; k--){
                                    if(mm > 7){
                                        break;
                                    }
                                    if(position[k][mm]==' '){
                                        m[tolower(p)].push_back(makeMove(i, j, k, mm));attack_white = attack_white | (1ULL << SQ2BIT(k, mm));
                                    }else{
                                        if(isupper(position[k][mm]))
                                        {m[tolower(p)].push_back(makeMove(i, j, k, mm));attack_white = attack_white | (1ULL << SQ2BIT(k, mm));}
                                        break;
                                    }
                                    mm++;
                                    if(mm > 7){
                                        break;
                                    }
                                }mm=j-1;
                                for(int k=i+1; k<=7; k++){
                                    if(mm < 0){
                                        break;
                                    }
                                    if(position[k][mm]==' '){
                                        m[tolower(p)].push_back(makeMove(i, j, k, mm));attack_white = attack_white | (1ULL << SQ2BIT(k, mm));
                                    }else{
                                        if(isupper(position[k][mm]))
                                        {m[tolower(p)].push_back(makeMove(i, j, k, mm));attack_white = attack_white | (1ULL << SQ2BIT(k, mm));}
                                        break;
                                    }
                                    mm--;
                                    if(mm < 0){
                                        break;
                                    }
                                }mm=j-1;
                                for(int k=i-1; k>=0; k--){
                                    if(mm < 0){
                                        break;
                                    }
                                    if(position[k][mm]==' '){
                                        m[tolower(p)].push_back(makeMove(i, j, k, mm));attack_white = attack_white | (1ULL << SQ2BIT(k, mm));
                                    }else{
                                        if(isupper(position[k][mm]))
                                        {m[tolower(p)].push_back(makeMove(i, j, k, mm));attack_white= attack_white | (1ULL << SQ2BIT(k, mm));}
                                        break;
                                    }
                                    mm--;
                                    if(mm < 0){
                                        break;
                                    }
                                }mm=j+1;
                                for(int k=i+1; k<=7; k++){
                                    if(mm > 7){
                                        break;
                                    }
                                    if(position[k][mm]==' '){
                                        m[tolower(p)].push_back(makeMove(i, j, k, mm));attack_white = attack_white | (1ULL << SQ2BIT(k, mm));
                                    }else{
                                        if(isupper(position[k][mm]))
                                        {m[tolower(p)].push_back(makeMove(i, j, k, mm));attack_white = attack_white | (1ULL << SQ2BIT(k, mm));}
                                        break;
                                    }
                                    mm++;
                                    if(mm > 7){
                                        break;
                                    }
                                }
                            }
                            else if(p == 'n'){
                                if(i>=2 && j>=1 && position[i-2][j-1] == ' '){
                                    m[tolower(p)].push_back(makeMove(i, j, i-2, j-1));attack_white = attack_white | (1ULL << SQ2BIT(i-2, j-1));
                                }else{
                                    if(i>=2 && j>=1 && isupper(position[i-2][j-1])){
                                        m[tolower(p)].push_back(makeMove(i, j, i-2, j-1));attack_white = attack_white | (1ULL << SQ2BIT(i-2, j-1));
                                    }
                                }
                                if(i>=2 && j<=6 && position[i-2][j+1] == ' '){
                                    m[tolower(p)].push_back(makeMove(i, j, i-2, j+1));attack_white = attack_white | (1ULL << SQ2BIT(i-2, j+1));
                                }else{
                                    if(i>=2 && j<=6 && isupper(position[i-2][j+1])){
                                        m[tolower(p)].push_back(makeMove(i, j, i-2, j+1));attack_white = attack_white | (1ULL << SQ2BIT(i-2, j+1));
                                    }
                                }
                                if(i<=5 && j>=1 && position[i+2][j-1] == ' '){
                                    m[tolower(p)].push_back(makeMove(i, j, i+2, j-1));attack_white = attack_white | (1ULL << SQ2BIT(i+2, j-1));
                                }else{
                                    if(i<=5 && j>=1 && isupper(position[i+2][j-1])){
                                        m[tolower(p)].push_back(makeMove(i, j, i+2, j-1));attack_white = attack_white | (1ULL << SQ2BIT(i+2, j-1));
                                    }
                                }
                                if(i<=5 && j<=6 && position[i+2][j+1] == ' '){
                                    m[tolower(p)].push_back(makeMove(i, j, i+2, j+1));attack_white = attack_white | (1ULL << SQ2BIT(i+2, j+1));
                                }else{
                                    if(i<=5 && j<=6 && isupper(position[i+2][j+1])){
                                        m[tolower(p)].push_back(makeMove(i, j, i+2, j+1));attack_white = attack_white | (1ULL << SQ2BIT(i+2, j+1));
                                    }
                                }
                                if(i>=1 && j>=2 && position[i-1][j-2] == ' '){
                                    m[tolower(p)].push_back(makeMove(i, j, i-1, j-2));attack_white = attack_white | (1ULL << SQ2BIT(i-1, j-2));
                                }else{
                                    if(i>=1 && j>=2 && isupper(position[i-1][j-2])){
                                        m[tolower(p)].push_back(makeMove(i, j, i-1, j-2));attack_white = attack_white | (1ULL << SQ2BIT(i-1, j-2));
                                    }
                                }
                                if(i>=1 && j<=5 && position[i-1][j+2] == ' '){
                                    m[tolower(p)].push_back(makeMove(i, j, i-1, j+2));attack_white = attack_white | (1ULL << SQ2BIT(i-1, j+2));
                                }else{
                                    if(i>=1 && j<=5 && isupper(position[i-1][j+2])){
                                        m[tolower(p)].push_back(makeMove(i, j, i-1, j+2));attack_white = attack_white | (1ULL << SQ2BIT(i-1, j+2));
                                    }
                                }
                                if(i<=6 && j>=2 && position[i+1][j-2] == ' '){
                                    m[tolower(p)].push_back(makeMove(i, j, i+1, j-2));attack_white = attack_white | (1ULL << SQ2BIT(i+1, j-2));
                                }else{
                                    if(i<=6 && j>=2 && isupper(position[i+1][j-2])){
                                        m[tolower(p)].push_back(makeMove(i, j, i+1, j-2));attack_white = attack_white | (1ULL << SQ2BIT(i+1, j-2));
                                    }
                                }
                                if(i<=6 && j<=5 && position[i+1][j+2] == ' '){
                                    m[tolower(p)].push_back(makeMove(i, j, i+1, j+2));attack_white = attack_white | (1ULL << SQ2BIT(i+1, j+2));
                                }else{
                                    if(i<=6 && j<=5 && isupper(position[i+1][j+2])){
                                        m[tolower(p)].push_back(makeMove(i, j, i+1, j+2));attack_white = attack_white | (1ULL << SQ2BIT(i+1, j+2));
                                    }
                                }
                            }
                        }
                    }else{
                        //cout << "jada nasha" <<endl;
                        
                        if(isupper(p)){
                            if(p == 'P'){
                                if(i == 1){
                                    if((position[i+2][j] == ' ')&&(position[i+1][j] == ' ')){
                                        m[tolower(p)].push_back(makeMove(i, j, i+2, j));
                                        
                                    }
                                }
                                if(i == 6){
                                    if(position[i+1][j] == ' '){
                                        m[tolower(p)].push_back(makeMove(-5, j, i+1, j));
                                        m[tolower(p)].push_back(makeMove(-6, j, i+1, j));
                                        m[tolower(p)].push_back(makeMove(-7, j, i+1, j));
                                        m[tolower(p)].push_back(makeMove(-8, j, i+1, j));
                                    }
                                    if((position[i+1][j-1]!=' ') && (islower(position[i+1][j-1])) && j>0){
                                        m[tolower(p)].push_back(makeMove(-5, j, i+1, j-1));attack_black = attack_black | (1ULL << SQ2BIT(i+1, j-1));
                                        m[tolower(p)].push_back(makeMove(-6, j, i+1, j-1));attack_black = attack_black | (1ULL << SQ2BIT(i+1, j-1));
                                        m[tolower(p)].push_back(makeMove(-7, j, i+1, j-1));attack_black = attack_black | (1ULL << SQ2BIT(i+1, j-1));
                                        m[tolower(p)].push_back(makeMove(-8, j, i+1, j-1));attack_black = attack_black | (1ULL << SQ2BIT(i+1, j-1));
                                    }
                                    if((position[i+1][j+1]!=' ') && (islower(position[i+1][j+1])) && j<7){
                                        m[tolower(p)].push_back(makeMove(-5, j, i+1, j+1));attack_black = attack_black | (1ULL << SQ2BIT(i+1, j+1));
                                        m[tolower(p)].push_back(makeMove(-6, j, i+1, j+1));attack_black = attack_black | (1ULL << SQ2BIT(i+1, j+1));
                                        m[tolower(p)].push_back(makeMove(-7, j, i+1, j+1));attack_black = attack_black | (1ULL << SQ2BIT(i+1, j+1));
                                        m[tolower(p)].push_back(makeMove(-8, j, i+1, j+1));attack_black = attack_black | (1ULL << SQ2BIT(i+1, j+1));
                                    }
                                }else{
                                    if(position[i+1][j] == ' '){
                                        m[tolower(p)].push_back(makeMove(i, j, i+1, j));
                                    }
                                    if((position[i+1][j-1]!=' ') && (islower(position[i+1][j-1])) && j>0){
                                        m[tolower(p)].push_back(makeMove(i, j, i+1, j-1));attack_black = attack_black | (1ULL << SQ2BIT(i+1, j-1));
                                    }
                                    if((position[i+1][j+1]!=' ') && (islower(position[i+1][j+1])) && j<7){
                                        m[tolower(p)].push_back(makeMove(i, j, i+1, j+1));attack_black = attack_black | (1ULL << SQ2BIT(i+1, j+1));
                                    }
                                }
                                
                            }
                            else if(p == 'K'){
                                
                                for(int k = -1; k<=1; k++){
                                    for(int t = -1; t<=1; t++){ attack_black = attack_black | (1ULL << SQ2BIT(i+k, j+t));
                                        //cout << i+k << j+t <<endl;
                                        if(((i+k)>=0) && ((i+k)<=7) && ((j+t)>=0) && ((j+t)<=7) && (!(attack_white & (1ULL << (SQ2BIT(i+k, j+t)))))){
                                           
                                            if((position[i+k][j+t]!=' ') && (islower(position[i+k][j+t]))){
                                                
                                                m[tolower(p)].push_back(makeMove(i, j, i+k, j+t));
                                            }
                                            if(position[i+k][j+t] == ' '){
                                                m[tolower(p)].push_back(makeMove(i, j, i+k, j+t));
                                            }
                                        }
                                    }
                                }
                            }
                            else if(p == 'R'){
                                for(int k=i-1; k>=0; k--){
                                    if(k < 0){
                                        break;
                                    }
                                    if(position[k][j]==' '){
                                        m[tolower(p)].push_back(makeMove(i, j, k, j));attack_black = attack_black | (1ULL << SQ2BIT(k, j));
                                    }else{
                                        if(islower(position[k][j])){
                                            m[tolower(p)].push_back(makeMove(i, j, k, j));attack_black = attack_black | (1ULL << SQ2BIT(k, j));
                                        }
                                        break;
                                    }
                                }
                                for(int k=j-1; k>=0; k--){
                                    if(k < 0){
                                        break;
                                    }
                                    if(position[i][k]==' '){
                                        m[tolower(p)].push_back(makeMove(i, j, i, k));attack_black = attack_black | (1ULL << SQ2BIT(i, k));
                                    }else{
                                        if(islower(position[i][k])){
                                            m[tolower(p)].push_back(makeMove(i, j, i, k));attack_black = attack_black | (1ULL << SQ2BIT(i, k));
                                        }
                                        break;
                                    }
                                }
                                for(int k=i+1; k<8; k++){
                                    if(k > 7){
                                        break;
                                    }
                                    if(position[k][j]==' '){
                                        m[tolower(p)].push_back(makeMove(i, j, k, j));attack_black = attack_black | (1ULL << SQ2BIT(k, j));
                                    }else{
                                        if(islower(position[k][j])){
                                            m[tolower(p)].push_back(makeMove(i, j, k, j));attack_black = attack_black | (1ULL << SQ2BIT(k, j));
                                        }
                                        break;
                                    }
                                }
                                for(int k=j+1; k<8; k++){
                                    if(k > 7){
                                        break;
                                    }
                                    if(position[i][k]==' '){
                                        m[tolower(p)].push_back(makeMove(i, j, i, k));attack_black = attack_black | (1ULL << SQ2BIT(i, k));
                                    }else{
                                        if(islower(position[i][k])){
                                            m[tolower(p)].push_back(makeMove(i, j, i, k));attack_black = attack_black | (1ULL << SQ2BIT(i, k));
                                        }
                                        break;
                                    }
                                }
                            }
                            else if(p == 'B'){
                                int k, mm;
                                k=i;
                                mm=j+1;
                                for(int k=i-1; k>=0; k--){
                                    if(mm > 7){
                                        break;
                                    }
                                    if(position[k][mm]==' '){
                                        m[tolower(p)].push_back(makeMove(i, j, k, mm));attack_black = attack_black | (1ULL << SQ2BIT(k, mm));
                                    }else{
                                        if(islower(position[k][mm]))
                                        {m[tolower(p)].push_back(makeMove(i, j, k, mm));attack_black = attack_black | (1ULL << SQ2BIT(k, mm));}
                                        break;
                                    }
                                    mm++;
                                    if(mm > 7){
                                        break;
                                    }
                                }mm=j-1;
                                for(int k=i+1; k<=7; k++){
                                    if(mm < 0){
                                        break;
                                    }
                                    if(position[k][mm]==' '){
                                        m[tolower(p)].push_back(makeMove(i, j, k, mm));attack_black = attack_black | (1ULL << SQ2BIT(k, mm));
                                    }else{
                                        if(islower(position[k][mm]))
                                        {m[tolower(p)].push_back(makeMove(i, j, k, mm));attack_black = attack_black | (1ULL << SQ2BIT(k, mm));}
                                        break;
                                    }
                                    mm--;
                                    if(mm < 0){
                                        break;
                                    }
                                }mm=j-1;
                                for(int k=i-1; k>=0; k--){
                                    if(mm < 0){
                                        break;
                                    }
                                    if(position[k][mm]==' '){
                                        m[tolower(p)].push_back(makeMove(i, j, k, mm));attack_black = attack_black | (1ULL << SQ2BIT(k, mm));
                                    }else{
                                        if(islower(position[k][mm]))
                                        {m[tolower(p)].push_back(makeMove(i, j, k, mm));attack_black = attack_black | (1ULL << SQ2BIT(k, mm));}
                                        break;
                                    }
                                    mm--;
                                    if(mm < 0){
                                        break;
                                    }
                                }mm=j+1;
                                for(int k=i+1; k<=7; k++){
                                    if(mm > 7){
                                        break;
                                    }
                                    if(position[k][mm]==' '){
                                        m[tolower(p)].push_back(makeMove(i, j, k, mm));attack_black = attack_black | (1ULL << SQ2BIT(k, mm));
                                    }else{
                                        if(islower(position[k][mm]))
                                        {m[tolower(p)].push_back(makeMove(i, j, k, mm));attack_black = attack_black | (1ULL << SQ2BIT(k, mm));}
                                        break;
                                    }
                                    mm++;
                                    if(mm > 7){
                                        break;
                                    }
                                }
                            }
                            else if(p == 'Q'){
                                for(int k=i-1; k>=0; k--){
                                    if(k < 0){
                                        break;
                                    }
                                    if(position[k][j]==' '){
                                        m[tolower(p)].push_back(makeMove(i, j, k, j));attack_black = attack_black | (1ULL << SQ2BIT(k, j));
                                    }else{
                                        if(islower(position[k][j])){
                                            m[tolower(p)].push_back(makeMove(i, j, k, j));attack_black = attack_black | (1ULL << SQ2BIT(k, j));
                                        }
                                        break;
                                    }
                                }
                                for(int k=j-1; k>=0; k--){
                                    if(k < 0){
                                        break;
                                    }
                                    if(position[i][k]==' '){
                                        m[tolower(p)].push_back(makeMove(i, j, i, k));attack_black = attack_black | (1ULL << SQ2BIT(i, k));
                                    }else{
                                        if(islower(position[i][k])){
                                            m[tolower(p)].push_back(makeMove(i, j, i, k));attack_black = attack_black | (1ULL << SQ2BIT(i, k));
                                        }
                                        break;
                                    }
                                }
                                for(int k=i+1; k<8; k++){
                                    if(k > 7){
                                        break;
                                    }
                                    if(position[k][j]==' '){
                                        m[tolower(p)].push_back(makeMove(i, j, k, j));attack_black = attack_black | (1ULL << SQ2BIT(k, j));
                                    }else{
                                        if(islower(position[k][j])){
                                            m[tolower(p)].push_back(makeMove(i, j, k, j));attack_black = attack_black | (1ULL << SQ2BIT(k, j));
                                        }
                                        break;
                                    }
                                }
                                for(int k=j+1; k<8; k++){
                                    if(k > 7){
                                        break;
                                    }
                                    if(position[i][k]==' '){
                                        m[tolower(p)].push_back(makeMove(i, j, i, k));attack_black = attack_black | (1ULL << SQ2BIT(i, k));
                                    }else{
                                        if(islower(position[i][k])){
                                            m[tolower(p)].push_back(makeMove(i, j, i, k));attack_black = attack_black | (1ULL << SQ2BIT(i, k));
                                        }
                                        break;
                                    }
                                }
                                int k, mm;
                                k=i;
                                mm=j+1;
                                for(int k=i-1; k>=0; k--){
                                    if(mm > 7){
                                        break;
                                    }
                                    if(position[k][mm]==' '){
                                        m[tolower(p)].push_back(makeMove(i, j, k, mm));attack_black = attack_black | (1ULL << SQ2BIT(k, mm));
                                    }else{
                                        if(islower(position[k][mm]))
                                        {m[tolower(p)].push_back(makeMove(i, j, k, mm));attack_black = attack_black | (1ULL << SQ2BIT(k, mm));}
                                        break;
                                    }
                                    mm++;
                                    if(mm > 7){
                                        break;
                                    }
                                }mm=j-1;
                                for(int k=i+1; k<=7; k++){
                                    if(mm < 0){
                                        break;
                                    }
                                    if(position[k][mm]==' '){
                                        m[tolower(p)].push_back(makeMove(i, j, k, mm));attack_black = attack_black | (1ULL << SQ2BIT(k, mm));
                                    }else{
                                        if(islower(position[k][mm]))
                                        {m[tolower(p)].push_back(makeMove(i, j, k, mm));attack_black = attack_black | (1ULL << SQ2BIT(k, mm));}
                                        break;
                                    }
                                    mm--;
                                    if(mm < 0){
                                        break;
                                    }
                                }mm=j-1;
                                for(int k=i-1; k>=0; k--){
                                    if(mm < 0){
                                        break;
                                    }
                                    if(position[k][mm]==' '){
                                        m[tolower(p)].push_back(makeMove(i, j, k, mm));attack_black = attack_black | (1ULL << SQ2BIT(k, mm));
                                    }else{
                                        if(islower(position[k][mm]))
                                        {m[tolower(p)].push_back(makeMove(i, j, k, mm));attack_black = attack_black | (1ULL << SQ2BIT(k, mm));}
                                        break;
                                    }
                                    mm--;
                                    if(mm < 0){
                                        break;
                                    }
                                }mm=j+1;
                                for(int k=i+1; k<=7; k++){
                                    if(mm > 7){
                                        break;
                                    }
                                    if(position[k][mm]==' '){
                                        m[tolower(p)].push_back(makeMove(i, j, k, mm));attack_black = attack_black | (1ULL << SQ2BIT(k, mm));
                                    }else{
                                        if(islower(position[k][mm]))
                                        {m[tolower(p)].push_back(makeMove(i, j, k, mm));attack_black = attack_black | (1ULL << SQ2BIT(k, mm));}
                                        break;
                                    }
                                    mm++;
                                    if(mm > 7){
                                        break;
                                    }
                                }
                            }
                            else if(p == 'N'){
                                if(i>=2 && j>=1 && position[i-2][j-1] == ' '){
                                    m[tolower(p)].push_back(makeMove(i, j, i-2, j-1));attack_black = attack_black | (1ULL << SQ2BIT(i-2, j-1));
                                }else{
                                    if(i>=2 && j>=1 && islower(position[i-2][j-1])){
                                        m[tolower(p)].push_back(makeMove(i, j, i-2, j-1));attack_black = attack_black | (1ULL << SQ2BIT(i-2, j-1));
                                    }
                                }
                                if(i>=2 && j<=6 && position[i-2][j+1] == ' '){
                                    m[tolower(p)].push_back(makeMove(i, j, i-2, j+1));attack_black = attack_black | (1ULL << SQ2BIT(i-2, j+1));
                                }else{
                                    if(i>=2 && j<=6 && islower(position[i-2][j+1])){
                                        m[tolower(p)].push_back(makeMove(i, j, i-2, j+1));attack_black = attack_black | (1ULL << SQ2BIT(i-2, j+1));
                                    }
                                }
                                if(i<=5 && j>=1 && position[i+2][j-1] == ' '){
                                    m[tolower(p)].push_back(makeMove(i, j, i+2, j-1));attack_black = attack_black | (1ULL << SQ2BIT(i+2, j-1));
                                }else{
                                    if(i<=5 && j>=1 && islower(position[i+2][j-1])){
                                        m[tolower(p)].push_back(makeMove(i, j, i+2, j-1));attack_black = attack_black | (1ULL << SQ2BIT(i+2, j-1));
                                    }
                                }
                                if(i<=5 && j<=6 && position[i+2][j+1] == ' '){
                                    m[tolower(p)].push_back(makeMove(i, j, i+2, j+1));attack_black = attack_black | (1ULL << SQ2BIT(i+2, j+1));
                                }else{
                                    if(i<=5 && j<=6 && islower(position[i+2][j+1])){
                                        m[tolower(p)].push_back(makeMove(i, j, i+2, j+1));attack_black = attack_black | (1ULL << SQ2BIT(i+2, j+1));
                                    }
                                }
                                if(i>=1 && j>=2 && position[i-1][j-2] == ' '){
                                    m[tolower(p)].push_back(makeMove(i, j, i-1, j-2));attack_black = attack_black | (1ULL << SQ2BIT(i-1, j-2));
                                }else{
                                    if(i>=1 && j>=2 && islower(position[i-1][j-2])){
                                        m[tolower(p)].push_back(makeMove(i, j, i-1, j-2));attack_black = attack_black | (1ULL << SQ2BIT(i-1, j-2));
                                    }
                                }
                                if(i>=1 && j<=5 && position[i-1][j+2] == ' '){
                                    m[tolower(p)].push_back(makeMove(i, j, i-1, j+2));attack_black = attack_black | (1ULL << SQ2BIT(i-1, j+2));
                                }else{
                                    if(i>=1 && j<=5 && islower(position[i-1][j+2])){
                                        m[tolower(p)].push_back(makeMove(i, j, i-1, j+2));attack_black = attack_black | (1ULL << SQ2BIT(i-1, j+2));
                                    }
                                }
                                if(i<=6 && j>=2 && position[i+1][j-2] == ' '){
                                    m[tolower(p)].push_back(makeMove(i, j, i+1, j-2));attack_black = attack_black | (1ULL << SQ2BIT(i+1, j-2));
                                }else{
                                    if(i<=6 && j>=2 && islower(position[i+1][j-2])){
                                        m[tolower(p)].push_back(makeMove(i, j, i+1, j-2));attack_black = attack_black | (1ULL << SQ2BIT(i+1, j-2));
                                    }
                                }
                                if(i<=6 && j<=5 && position[i+1][j+2] == ' '){
                                    m[tolower(p)].push_back(makeMove(i, j, i+1, j+2));attack_black = attack_black | (1ULL << SQ2BIT(i+1, j+2));
                                }else{
                                    if(i<=6 && j<=5 && islower(position[i+1][j+2])){
                                        m[tolower(p)].push_back(makeMove(i, j, i+1, j+2));attack_black = attack_black | (1ULL << SQ2BIT(i+1, j+2));
                                    }
                                }
                            }
                        }
                            
                    }
                }
            }
        }
        int u = prem/100;//cout << position[u/10][u%10]<< endl;
        for(int i=0;i<6;i++){
            if(order[i] == tolower(position[u/10][u%10])){
                
                swap(order[0], order[i]);
                break;
            }
        }

        vector<int>ms;
        for(int i=0;i<6;i++){
            ms.insert(ms.end(), m[order[i]].begin(), m[order[i]].end());
        }
        
        return ms;
    }
    int evaluate(){
        int e = 0;int it = turn;
        turn = 1;
        int mw = PosMoves().size();
        turn = -1;
        int mb = PosMoves().size();
        turn = it;
        e = 3*(mw-mb);
        for(int i=0; i<8; i++){
            for(int j=0; j<8; j++){
                if(position[i][j] != ' '){
                    if(isupper(position[i][j])){
                        //black pieces
                        char p = (char)tolower(position[i][j]);
                        e -= pieces[p];
                        if(p=='p'){
                            e -= pawn[7-i][j];
                        }else if(p=='r'){
                            e -= rook[7-i][j];
                        }else if(p=='n'){
                            e -= knight[7-i][j];
                        }else if(p=='b'){
                            e -= bishop[7-i][j];
                        }else if(p=='q'){
                            e -= queen[7-i][j];
                        }else if(p=='k'){
                            if(material['q']+material['Q']==0){
                                e -= king_end[7-i][7-j];
                            }else{
                                e -= king[7-i][7-j];
                            }
                        }
                    }else{ //WHITE
                        char p = position[i][j];
                        e += pieces[p];
                        if(p=='p'){
                            e += pawn[i][j];
                        }else if(p=='r'){
                            e += rook[i][j];
                        }else if(p=='n'){
                            e += knight[i][j];
                        }else if(p=='b'){
                            e += bishop[i][j];
                        }else if(p=='q'){
                            e += queen[i][j];
                        }else if(p=='k'){
                            if(material['q']+material['Q']==0){
                                e += king_end[i][j];
                            }else{
                                e += king[i][j];
                            }
                        }
                    }
                }
            }
        }
        
        return e * it;
    }
};

string fen(Board B){
    string s;
    int spaces = 0;
    for(int i = 0;i<8;i++){
        
        
        spaces = 0;
        for(int j=0;j<8;j++){
            if(B.position[i][j]!=' '){
                if(spaces != 0){
                    s.push_back(char(spaces+48));
                    
                }
                s.push_back(B.position[i][j]);
                spaces = 0;
            }else{
                spaces++;
            }
            
        }
        if(spaces != 0){
            s.push_back(char(spaces+48));
                    
        }
        s.push_back('/');
    }
    return s;
}




vector<vector<MOVE>> posmov2d = {};
unordered_map<int, int> pos2dans;

int posmovD5 = 0;
void printMov(MOVE prevMove){
    //cout <<prevMove<<endl;
}



pair<int, int> negamax_eval(Board B, int turn, int depth, int alpha, int beta){
    //alpha = alpha * turn;
    B.turn = turn;
    vector<int> movesRes = {};
    vector<int> movesQues = {};
    if(depth == -1){
        //cout << "Vulnerable King"<< endl;
        if(depth == (DEPTH - 1)){
                posmov2d.push_back(movesQues);
                //pos2dans.push_back(movesRes);
                //cout << "movres" << movesRes.size()<<" = "<<movesQues.size()<<endl;
            }
        return make_pair(makeMove(1000,1000,1000,1000), B.evaluate());
    }
    if(depth == 1){
        if(!(B.vulKing())){
            
            return make_pair(makeMove(2000,1000,1000,1000), B.evaluate());
        }else{
            
            
        }
    }else{
        
        
        vector<int> moves = B.PosMoves();
        // vector<pair<pair<int, int>, pair<int, int>>> movesRes = {};
        // vector<pair<pair<int, int>, pair<int, int>>> movesQues = {};
        
        int short_castle, long_castle;
        int a=100;char cr, ck;
        ull attacks;
        if(turn == -1){
                short_castle = B.black_short_castle;
                long_castle = B.black_long_castle;
                a = 0;cr='R';ck = 'K';attacks = B.attack_white;
        }else{
            short_castle = B.white_short_castle;
            long_castle = B.white_long_castle;
            a = 7;cr='r';ck = 'k';attacks = B.attack_black;
        }
        if(short_castle){
            if(a!=100){
                if((B.position[a][5]==' ')&&(B.position[a][6]==' ')&&(B.position[a][4]==ck)&&(B.position[a][7]==cr)){
                    if(((attacks & (1ULL << SQ2BIT(a, 5))) + (attacks & (1ULL << SQ2BIT(a, 6))))){
                        moves.push_back(makeMove(-1,-1,-1,-1));
                    }
                    
                }
            }
            
        }
        if(long_castle){
            if(a!=100){
                if((B.position[a][1]==' ')&&(B.position[a][2]==' ')&&(B.position[a][3]==' ')&&(B.position[a][4]==ck)&&(B.position[a][0]==cr)){
                    if(((attacks & (1ULL << SQ2BIT(a, 1))) + (attacks & (1ULL << SQ2BIT(a, 2))) + (attacks & (1ULL << SQ2BIT(a, 3))))){
                        moves.push_back(makeMove(-2,-2,-2,-2));
                    }
                    
                }
            }
        }
        int maxeval = -99999989;
        int mxr = 0;
        int maxmove = 0;//cout <<"akjfieufhuerihg"<<moves.size()+B.long_castle+B.short_castle<<endl;
        // if(depth == (DEPTH - 1)){
        //     cout << "ooooooo : " <<moves.size() << endl;
        // }
        
        if(moves.size() == 0){
            if(turn == 1){
                if(!((B.attack_black & (1ULL << SQ2BIT(B.white_king.first, B.white_king.second))))){
                    return make_pair(makeMove(3000,1000,1000,1000), 0);
                }else{
                    
                    return make_pair(makeMove(4000,1000,1000,1000), (-999999-(5*abs(depth))));
                }

            }else{
                if(!((B.attack_white & (1ULL << SQ2BIT(B.black_king.first, B.black_king.second))))){
                    
                    return make_pair(makeMove(5000,1000,1000,1000), 0);
                }else{
                    
                    return make_pair(makeMove(6000,1000,1000,1000), (-999999-(5*abs(depth))));
                }
            }
        }
        
        int r;
        for(r=0; r<moves.size(); r++){
            int ceval;
            Board sample = B;//cout<<r<<endl;
            sample.move(moves[r]);
            if(turn == 1){
                if(sample.material['k'] == 0){
                    if(depth == (DEPTH - 1)){
                        posmov2d.push_back(movesQues);
                        //pos2dans.push_back(movesRes);
                        //cout << "movres" << movesRes.size()<<" = "<<movesQues.size()<<endl;
                    }
                    return make_pair(makeMove(7000,1000,1000,1000), (-9999999-(5*abs(depth))));
                }
                if(sample.material['K'] == 0){
                    if(depth == (DEPTH - 1)){
                        posmov2d.push_back(movesQues);
                        //pos2dans.push_back(movesRes);
                        //cout << "movres" << movesRes.size()<<" = "<<movesQues.size()<<endl;
                    }
                    return make_pair(makeMove(8000,1000,1000,1000), -(-9999999-(5*abs(depth))));
                }
            }else{
                if(sample.material['K'] == 0){
                    if(depth == (DEPTH - 1)){
                        posmov2d.push_back(movesQues);
                        //pos2dans.push_back(movesRes);
                        //cout << "movres" << movesRes.size()<<" = "<<movesQues.size()<<endl;
                    }
                    return make_pair(makeMove(9000,1000,1000,1000), (-9999999-(5*abs(depth))));
                }if(sample.material['k'] == 0){
                    if(depth == (DEPTH - 1)){
                        posmov2d.push_back(movesQues);
                        //pos2dans.push_back(movesRes);
                        //cout << "movres" << movesRes.size()<<" = "<<movesQues.size()<<endl;
                    }
                    return make_pair(moves[r], -(-9999999-(5*abs(depth))));
                }
            }
            if(depth == (DEPTH - 1)){
            
            //cout<<"jjjjjjjjj"<<endl;
            
        }
            pair<MOVE, int> Ceval = negamax_eval(sample, turn*(-1), depth-1, -beta, -alpha);
            nodes++;
            ceval = -1 * Ceval.second;
            movesQues.push_back(moves[r]);
            //movesRes.push_back(Ceval.first);
            //pos2dans[moves[r]] = Ceval.first;
            pos2dans.insert(make_pair(moves[r], Ceval.first));
            // printMov(moves[r]);
            // cout << Int(moves[r]) <<endl;
            // printMov(Ceval.first);
            // cout << Int(Ceval.first) << endl;
            // cout << "---------------------------" << endl;
            //if(depth == 4 && ama == 1){
                //sample.Print();
                //cout<<ceval<<endl;
        
            if(ceval > maxeval){
                maxeval = ceval;
                maxmove = r;
                
            }
            if(maxeval > alpha){
                alpha = maxeval;
            }
            if(alpha >= beta){
                if(depth == (DEPTH - 1)){
                    posmov2d.push_back(movesQues);
                    //pos2dans.push_back(movesRes);
                    //cout << "movres" << movesRes.size()<<" = "<<movesQues.size()<<endl;
                }
                pruned++;
                return make_pair(moves[r], alpha);
            }
            
        }
        if(depth == (DEPTH - 1)){
            posmov2d.push_back(movesQues);
            //pos2dans.push_back(movesRes);
            //cout << "movres" << movesRes.size()<<" = "<<movesQues.size()<<endl;
        }
        return make_pair(moves[maxmove], maxeval);

        
    }
}

int negamax_Mov(Board B, int turn, int depth){
    


    B.turn = turn;
    pair<int, pair<pair<int, int>, pair<int, int>>>cloud_result;
    //cloud_result = cloud_find(fen(B),depth);
    //if(cloud_result.first){
    //    cout << "Cloud Move (depth = " <<cloud_result.first <<")" <<endl;
    //    return cloud_result.second;
    //}
    vector<int> moves = B.PosMoves();
    //random_shuffle(moves.begin(), moves.end());
    int short_castle, long_castle;
    int a=100;char cr, ck;
    ull attacks;
    if(turn == -1){
            short_castle = B.black_short_castle;
            long_castle = B.black_long_castle;
            a = 0;cr='R';ck = 'K';attacks = B.attack_white;
    }else{
        short_castle = B.white_short_castle;
        long_castle = B.white_long_castle;
        a = 7;cr='r';ck = 'k';attacks = B.attack_black;
    }
    if(short_castle){
        if(a!=100){
            if((B.position[a][5]==' ')&&(B.position[a][6]==' ')&&(B.position[a][4]==ck)&&(B.position[a][7]==cr)){
                if(((attacks & (1ULL << SQ2BIT(a, 5))) + (attacks & (1ULL << SQ2BIT(a, 6))))){
                    moves.push_back(makeMove(-1,-1,-1,-1));
                }
                
            }
        }
        
    }
    if(long_castle){
        if(a!=100){
            if((B.position[a][1]==' ')&&(B.position[a][2]==' ')&&(B.position[a][3]==' ')&&(B.position[a][4]==ck)&&(B.position[a][0]==cr)){
                if(((attacks & (1ULL << SQ2BIT(a, 1))) + (attacks & (1ULL << SQ2BIT(a, 2))) + (attacks & (1ULL << SQ2BIT(a, 3))))){
                    moves.push_back(makeMove(-2,-2,-2,-2));
                }
                
            }
        }
        
    }
    int maxeval = -999999978;
    int alpha = -99999999;
    int beta =  99999999;
    int maxmove = 0;
    
    for(int r=0; r<moves.size(); r++){
        int ceval;
        Board sample = B;
        
        sample.move(moves[r]);
        pair<MOVE, int> Ceval = negamax_eval(sample, turn*(-1), depth-1, -beta, -alpha);
        nodes++;
        ceval = -1 * Ceval.second;
        if(((moves[r]/10)%10 == 1) && (moves[r]%10 ==0)){
            ama = 1;
        }else{
            ama = 0;
        }
        //cout << r << " - "<<"ceval "<<ceval<<" | "<<(moves[r])<<endl;
        if(ceval > maxeval){
            maxeval = ceval;
            maxmove = r;
        }
        if(maxeval > alpha){
                alpha = maxeval;
        }
        if(alpha >= beta){
            pruned++;
            //cout << "MAXSPTH PRUNED" <<endl;
            return moves[r];
        }
        // if(ceval == 99999999){
        //     cout << "jfeur"<<(B.attack_black & (1ULL << SQ2BIT(2, 0)))<<endl;
        // }
        

    }
    
    //cout << "jjj"<< maxeval <<endl;
    posmovD5 = maxmove;
    return moves[maxmove];

}

int negamax_Mov(Board B, int turn, int depth, int prem){
    


    B.turn = turn;
    pair<int, pair<pair<int, int>, pair<int, int>>>cloud_result;
    //cloud_result = cloud_find(fen(B),depth);
    //if(cloud_result.first){
    //    cout << "Cloud Move (depth = " <<cloud_result.first <<")" <<endl;
    //    return cloud_result.second;
    //}
    vector<int> moves = B.PosMoves(prem);
    //random_shuffle(moves.begin(), moves.end());
    int short_castle, long_castle;
    int a=100;char cr, ck;
    ull attacks;
    if(turn == -1){
            short_castle = B.black_short_castle;
            long_castle = B.black_long_castle;
            a = 0;cr='R';ck = 'K';attacks = B.attack_white;
    }else{
        short_castle = B.white_short_castle;
        long_castle = B.white_long_castle;
        a = 7;cr='r';ck = 'k';attacks = B.attack_black;
    }
    if(short_castle){
        if(a!=100){
            if((B.position[a][5]==' ')&&(B.position[a][6]==' ')&&(B.position[a][4]==ck)&&(B.position[a][7]==cr)){
                if(((attacks & (1ULL << SQ2BIT(a, 5))) + (attacks & (1ULL << SQ2BIT(a, 6))))){
                    moves.push_back(makeMove(-1,-1,-1,-1));
                }
                
            }
        }
        
    }
    if(long_castle){
        if(a!=100){
            if((B.position[a][1]==' ')&&(B.position[a][2]==' ')&&(B.position[a][3]==' ')&&(B.position[a][4]==ck)&&(B.position[a][0]==cr)){
                if(((attacks & (1ULL << SQ2BIT(a, 1))) + (attacks & (1ULL << SQ2BIT(a, 2))) + (attacks & (1ULL << SQ2BIT(a, 3))))){
                    moves.push_back(makeMove(-2,-2,-2,-2));
                }
                
            }
        }
        
    }
    int maxeval = -999999978;
    int alpha = -99999999;
    int beta =  99999999;
    int maxmove = 0;
    int isthere = 0;
    // cout << "Hi thsere"<<endl;
    // for(int r=0; r<moves.size(); r++){
    //     if(moves[r] == prem){
    //         isthere = 1;
    //         moves.insert(moves.begin(), prem);
    //         break;
    //     }
    // }
    
    for(int r=0; r<moves.size(); r++){
        if((r>0)&&(isthere)&&((moves[r] == moves[0]))){
            //cout << "skipped" << endl;
            continue;
        }
        int ceval;
        Board sample = B;
        sample.move(moves[r]);
        pair<MOVE, int> Ceval = negamax_eval(sample, turn*(-1), depth-1, -beta, -alpha);
        nodes++;
        ceval = -1 * Ceval.second;
        if((moves[r]%100 == 10)){
            ama = 1;
        }else{
            ama = 0;
        }
        //cout << r << " - "<<"ceval "<<ceval<<" | "<<(moves[r])<<endl;
        if(ceval > maxeval){
            maxeval = ceval;
            maxmove = r;
        }
        if(maxeval > alpha){
            alpha = maxeval;
        }
         if(alpha >= beta){
            pruned++;
            //cout << "MAXSPTH PRUNED" <<endl;
            return moves[r];
        }
    }
    //cout << "jjj"<< maxeval <<endl;
    posmovD5 = maxmove;
    return moves[maxmove];

}



int main(){
    Board g1;
    g1.turn = 1;
    int play = 1;
    g1.Print();
    //vector<string>e4;
    //e4.push_back("pirc.txt");
    //unordered_map<string, vector<string>>openings = {{"e4", e4}};
    int opening_lock = 0;string o;
    while(play){
        string mov;
        cout << "Enter move (Example e2,e4 to move from e2 to e4 square) \n >>";
        cin >> mov;
        int a, b, x, y;
        if(mov == "o-o"){
            a = -1;
            b = -1;
            x = -1;
            y = -1;
        }else if(mov == "o-o-o"){
            a = -2;
            b = -2;
            x = -2;
            y = -2;
        }else{
        
            a = int(mov[0]) - 97;
            b = int(mov[1]) - 49;
            x = int(mov[3]) - 97;
            y = int(mov[4]) - 49;
        }
        // //cout << endl<<a<<", "<<b<<", "<<x<<", "<<y;
        g1.move_user(make_pair(make_pair(a,b), make_pair(x, y)));
        MOVE preMov = makeMove(786,0,0,0);
        //cout << 7-b << a << 7-y << x << endl;
        int umov = (7-b)*1000 + a*100 + (7-y)*10 + x;
        if(play == -1){
            //cout << "PPPPP : " << posmovD5 << endl;
            for(int i=0; i<posmov2d[posmovD5].size(); i++){
                //cout << i <<" | ";
                MOVE aa = posmov2d[posmovD5][i];
                printMov(aa);
                //cout << i <<" | ";
                printMov(Move(pos2dans[aa]));
                // // cout << i <<" | ";
                // printMov(pos2dans[posmovD5][i]);
                if((aa == umov)){
                    //cout << "______________________________________________"<<endl<<endl;
                    //cout << "Prediction"<< endl;
                    preMov = pos2dans[(posmov2d[posmovD5][i])];
                    //preMov = posmov2d[posmovD5][i];
                    pos2dans.clear();
            posmov2d = {};

                    printMov(preMov);
                    //cout << "______________________________________________"<< endl<<endl;
                }

            }
        }
        // g1.Print();
        //cout<<fen(g1)<<endl;
        int Maxdepth = DEPTH;
        int d = DEPTH;
        g1.turn = -1;
        int bestMove;
        auto start = high_resolution_clock::now();
        int cloud_result;
        int openingdb_result;
        //cout << g1.evaluate() <<endl;
        
        
        while(d<=Maxdepth){
            //cloud_result = cloud_find(fen(g1),d);
           // openingdb_result = opening_db(fen(g1), openings[o][0]);
            //cout<<openingdb_result.first<<endl;
            //if(openingdb_result.first){
            //    cout << "Opening Move"<<endl;
            //    bestMove = openingdb_result.second;
            //    break;
            //}else if(cloud_result.first){
            //    cout << "Cloud Move (depth = " <<cloud_result.first <<")" <<endl;
            //    bestMove = cloud_result.second;
            //    break;
            //}else{
                // cout << "Searching Move (depth = " <<d <<")" <<endl;
                if((play == -1)&&(preMov != 786000)){
                    bestMove = negamax_Mov(g1, -1, DEPTH, preMov);
                }else{
                    //cout << "Yo" << endl;
                    bestMove = negamax_Mov(g1, -1, DEPTH);
                }
                //
            //d1}
            
            auto stop = high_resolution_clock::now();
            auto dd = duration_cast<microseconds>(stop-start);
            cout <<"Move Time :"<<dd.count()/1000000.0<<" sec"<<endl;
            auto start = high_resolution_clock::now();
            //cout <<prevMove.first.first<<", "<<prevMove.first.second<<" -> "<<prevMove.second.first<<", "<<prevMove.second.second <<" | "<<prevEval<<endl;
            d++;
        }
        auto stop = high_resolution_clock::now();
        auto dd = duration_cast<microseconds>(stop-start);
        //cout <<"Move Time : "<<dd.count()/1000000.0<<" sec"<<endl;
        // if(cloud_result.first == 0){
        //     cloud(fen(g1),bestMove,Maxdepth);
        // }
        
        
        g1.move(bestMove);
        
        //cout << "Pruning : " << pruned <<" / "<<nodes<< endl;
        nodes = 0;
        pruned = 0;
        g1.Print();

        cout <<  "EVAL = " <<g1.evaluate()/100.0<<endl; 
        cout <<"Move Time :"<<dd.count()/1000000.0<<" sec"<<endl;
        unordered_map<char, int>::iterator it = g1.material.begin();
        int sum = 0;
        for(it = g1.material.begin();it != g1.material.end(); it++){
            sum += it->second;
        }
        // if(sum < 6){
        //     Maxdepth = 7;
        // }
        play = -1;
        g1.setAttack();
        g1.turn = 1;
    }
    
}
    // int ff;
    // cin >> ff;
    // return 0;
