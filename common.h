//
// Created by 张程易 on 27/03/2018.
//

#ifndef OTHELLO_COMMON_H
#define OTHELLO_COMMON_H

struct Board{
    char data[8][8];
};

char * httpd_callback(char * callback);
int httpd_main();

int resolve(Board & board);

#if defined (__i386__)
static __inline__ unsigned long long GetCycleCount(void)
{
        unsigned long long int x;
        __asm__ volatile("rdtsc":"=A"(x));
        return x;
}
#elif defined (__x86_64__)
static __inline__ unsigned long long GetCycleCount(void)
{
    unsigned hi,lo;
    __asm__ volatile("rdtsc":"=a"(lo),"=d"(hi));
    return ((unsigned long long)lo)|(((unsigned long long)hi)<<32);
}
#endif



#endif //OTHELLO_COMMON_H
