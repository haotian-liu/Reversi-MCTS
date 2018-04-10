#include "common.h"
#include <iostream>

#include <ctime>
#include <sys/time.h>
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
    return {p2, p1, 2};
}

MCTSPlayer mp;

char * httpd_callback(char * str){


    struct timeval t1,t2;
    double timeuse;
    printf("start search\n");
    gettimeofday(&t1,NULL);

    auto action_str = new char[64];
    Board board = str2board(str);
    int action = mp.move(board);


    gettimeofday(&t2,NULL);
    timeuse = t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec)/1000000.0;
    printf("prediction time=%0.3fs\n", timeuse);

    sprintf(action_str, "%d", action);
    return action_str;
}

int main() {
    httpd_main();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}