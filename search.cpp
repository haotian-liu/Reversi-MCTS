//
// Created by 张程易 on 27/03/2018.
//
#include <cstdio>
#include <ctime>
#include <sys/time.h>
#include "common.h"
#include "stdlib.h"

int random_range(int l, int r){
    return (rand() % (r - l)) + l;
}

int dx[] = {-1,  0,  1, -1,  1, -1,  0,  1};
int dy[] = {-1, -1, -1,  0,  0,  1,  1,  1};

bool checkEqual(Board & board, int i, int j, int role){
    if( i < 0 || j < 0 || i >= 8 || j >= 8) return false;
    return board.data[i][j] == role;
}

int mark_legal(Board & board, int * actions, int role){
    int cnt = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if( board.data[i][j] == 0){
                for(int k = 0; k < 8; k ++){
                    int ddx = dx[k], ddy = dy[k];
                    int h = 1;
                    while( checkEqual(board, i+ddx*h, j+ddy*h, -role))
                        h++;
                    if (h != 1 && checkEqual(board, i+ddx*h, j+ddy*h, role)){
                        actions[cnt++] = i * 8 + j;
                        break;
                    }
                }
            }
        }
    }
    return cnt;
}

int eval_classical(Board & board){
    int score = 0;
    for(int i = 0; i < 8; i ++){
        for(int j = 0 ; j < 8; j++){
            int weight = (i == 0 || i == 7) + (j == 0 || j == 7);
            if(weight == 1) weight = 4;
            else if( weight == 2) weight = 10;
            else weight = 1;
            score += weight * board.data[i][j];
        }
    }
    return score;
}

void print_actions(int * actions, int action_cnt){
    printf("[");
    for(int i = 0; i < action_cnt; i++){
        printf("(%d,%d)", actions[i]/8, actions[i]%8);
    }
    printf("]\n");
}

void print_board(Board & board){
    for(int i = 0; i < 8; i ++){
        for(int j = 0; j < 8; j++){
            if(board.data[i][j] == -1)printf("2");
            if(board.data[i][j] == 0)printf("0");
            if(board.data[i][j] == 1)printf("1");
        }
        printf("\n");
    }
}

int max_min_search(Board & board, int & action, int deep, int max_deep){
    bool is_max = deep % 2 == 1;
    int actions[64], new_action, score;
    int action_cnt = mark_legal(board, actions, is_max ? 1 : -1);
    if( action_cnt == 0){
        if( deep == max_deep){
            return eval_classical(board);
        }
        else{
            return max_min_search(board, action, deep + 1, max_deep);
        }
    }
    int max_or_min = is_max ? -100000 : 100000, max_or_min_ord = 0;
    for(int i = 0; i < action_cnt; i ++){
        int x = actions[i] / 8, y = actions[i] % 8;
        board.data[x][y] = 1;
        if( deep == max_deep) score = eval_classical(board);
        else score = max_min_search(board, new_action, deep + 1, max_deep);
        if( (is_max && score > max_or_min) || (!is_max && score < max_or_min)){
            max_or_min = score;
            max_or_min_ord = actions[i];
        }
        board.data[x][y] = 0;
    }
    action = max_or_min_ord;
//    printf("mmsearch[%d], score=%d, (%d, %d)\n", deep, max_or_min,
//           max_or_min_ord / 8, max_or_min_ord % 8);
    return max_or_min;
}

int resolve(Board & board){
    print_board(board);
    int action;
    struct timeval t1,t2;
    double timeuse;
    printf("start search\n");
    gettimeofday(&t1,NULL);
    int score = max_min_search(board, action, 1, 8);
    gettimeofday(&t2,NULL);
    timeuse = t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec)/1000000.0;
    printf("prediction action=%d, score=%d, time=%0.3fs\n", action, score, timeuse);
    return action;
}
