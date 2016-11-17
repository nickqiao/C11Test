//
// Created by nick on 2016/11/4.
//
#include <stdio.h>
#include <thread>
#include <iostream>
#include <fstream>
using namespace std;
std::mutex _mu;

int main() {
    std::unique_lock<std::mutex> lock2(_mu);
    return 0;
}

class LogFile {

    std::mutex _mutex1;
    std::mutex _mutex2;
    once_flag once_flag1;
    fstream _f;

public:

    LogFile() {
    }

    void shared_print(string id, int value) {
        call_once(once_flag1,[&](){ _f.open(""); });
    }
};