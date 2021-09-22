/*
GraphUtils - basic utils
Author: Yuzheng Cai
2021-09-21
------------------------------
C++ 11 
*/ 


#ifndef UTILS_H
#define UTILS_H

#include "Config.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>

#include <algorithm>
#include <sys/time.h>
#include <math.h>
#include <random>
#include<string.h>

using namespace std;


#if (defined _WIN32) || (defined _WIN64)
    #define WINDOWS 1
#else
    #define INT_MAX 2147483648
#endif


#define min(a, b) ((a)<(b)?(a):(b))
#define max(a, b) ((a)>(b)?(a):(b))


// get current time in millisecond
inline double getCurrentTimeInMs() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec*1000 + tv.tv_usec * 1e-3;
}


// get current time for writing logs
string getCurrentLogTime( )
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return  to_string(1900 + ltm->tm_year) + "-" + to_string(1 + ltm->tm_mon) + "-" + to_string(ltm->tm_mday) + " " +
            to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min) + ":" + to_string(ltm->tm_sec);
}


#endif
