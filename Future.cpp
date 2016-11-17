//
// Created by nick on 2016/11/4.
//

#include <iostream>
#include <future>
#include <thread>

int subThreadWork() {
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << std::this_thread::get_id()<<std::endl;
    return 99;
}

int main() {

    int x ;
    std::future<int> future = std::async(std::launch::async, subThreadWork);
    std::cout << std::this_thread::get_id() << std::endl;

    x = future.get();
    std::cout<< x << std::endl;

    int i ;
    int &r = i;

    return 0;
}