//
// Created by nick on 2016/11/4.
//

#include <iostream>
#include <deque>
#include <thread>

std::deque<int> deque;
std::mutex mu;
std::condition_variable cond;

void put() {
    int count = 10;
    while (count > 0) {
        std::unique_lock<std::mutex> lock(mu);
        deque.push_back(count);
        std::cout << "放入" << count << std::endl;
        lock.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        count--;
    }
}

/**
 * 效率太低
 */
void show() {
    int data = 0;
    while (data != 1){
        std::unique_lock<std::mutex> lock(mu);
        if ( !deque.empty()) {
            data = deque.back();
            deque.pop_back();
            lock.unlock();
            std::cout << "取出" << data << std::endl;
        } else{
            lock.unlock();
        }
    }
}

// 高效展示

void highPut() {
    int count = 10;
    while (count > 0) {
        std::unique_lock<std::mutex> lock(mu);
        deque.push_back(count);
        std::cout << "放入" << count << std::endl;
        lock.unlock();
        cond.notify_one();
        count--;
    }
}

void highShow() {
    int data = 0;
    while (1) {
        std::unique_lock<std::mutex> lock(mu);
        // 防止虚假唤醒
        cond.wait(lock, []() { return !deque.empty(); });
        data = deque.back();
        deque.pop_back();
        lock.unlock();
        std::cout << "取出" << data << std::endl;
    }
}
int main() {

    std::thread thread1(highPut);
    std::thread thread2(highShow);

    thread1.join();
    thread2.join();

    return 0;
}