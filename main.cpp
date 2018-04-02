#include "common.h"
#include <iostream>
using namespace std;


/*Board str2board(char * str){
    Board board;
    for(int i = 0; i < 64; i++){
        int val = 0;
        if( str[i] == '0') val = 0;
        else if( str[i] == '1') val = 1;
        else val = -1;
        board.data[i / 8][i % 8] = (char)val;
    }
    return board;
}

char * board2str(Board & board){
    char * result = new char[65];
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j ++){
            char val = 0;
            if( board.data[i][j] == 0) val = '0';
            else if( board.data[i][j] == 1) val = '1';
            else val = '2';
            result[i * 8 + j ] = val;
        }
    }
    result[64] = 0;
    return result;
}*/

Board str2board(const char *str) {
    uint64_t p1 = 0, p2 = 0;
    uint64_t mask = 0x8000000000000000;
    for(int i = 0; i < 64; i++){
        if (str[i] == '1') {
            p1 |= mask;
        } else if (str[i] == '2') {
            p2 |= mask;
        }
        mask >>= 1;
    }
    return {p2, p1};
}

MCTSPlayer mp;

char * httpd_callback(char * str){
    auto action_str = new char[64];
    Board board = str2board(str);
    int action = mp.move(board);
    sprintf(action_str, "%d", action);
    return action_str;
}

int main() {
    httpd_main();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}