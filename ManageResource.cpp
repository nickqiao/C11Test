//
// Created by nick on 2016/11/7.
//
#include <iostream>
#include <deque>
#include <vector>
using namespace std;

/** 资源管理的第一种方式
 * C++11 中的第一种方式
 * 删除拷贝构造函数
 * 不用vector,用deque
 * 因为vector要求加入的元素要么copyalbe 要么moveable,所以改成deque就可以)
 *
 * 用emplace_back,不用push_back
 * emplace_back construct the object in place (in the space allocated to vector)
 */
//class Person {
//private:
//    string* pName_;
//
//public:
//    Person(const Person& rhs) = delete;
//    Person& operator=(const Person& rhs) = delete;
//    Person(string name) {
//        pName_ = new string(name);
//    }
//    ~Person() {
//        delete pName_;
//    }
//    void printName() {
//        cout << *pName_ << endl;
//    }
//};
//
//int main() {
//    // 这里如果是vector会有错误,因为vector要求加入的元素要么copyalbe 要么moveable,所以改成deque就可以
//    deque<Person> persons;
//   // persons.push_back(Person("West"));
//    persons.emplace_back("James");
//    persons.back().printName();
//    return 0;
//}

class Person {
private:
    // 如果person会被创建很多次,并且此资源并不会被共享，最好用unique_ptr;
    unique_ptr<string> pName_; // 这里避免了即使构造失败产生的内存泄漏

public:
    Person(string name) : pName_(new string(name)) {}
    //如果定义了析构函数，此处必须加上move constructor
    //Person(Person&& rhs)= default;
    void printName() {
        cout << *pName_ << endl;
    }
};

int main() {
    // 这里如果是vector会有错误,因为vector要求加入的元素要么copyalbe 要么moveable,所以改成deque就可以
    vector<Person> persons;
    Person person("wwwww");
    persons.push_back(std::move(person));
    persons.front().printName();
    return 0;
}

/**
 * C++03 解决资源管理类的方案主要有两个
 * 1 重写拷贝构造和拷贝赋值变为深拷贝(deep copy)
 * 2 将拷贝构造和拷贝赋值设为私有
 */
