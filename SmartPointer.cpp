//
// Created by nick on 2016/11/2.
//
#include <iostream>

using namespace std;

/**
 * C++11 Lesson7 Lesson8 shared_ptr
 *
 * 应该尽快将object赋值给智能指针,避免使用原始指针raw pointer
 * shared_ptr<Dog> p = make_shared<Dog>("Tank");   // faster and safer
 *
 * shared_ptr可以自定义析构函数
 * shared_ptr<Dog> p2 = shared_ptr<Dog>(new Dog("Tom"),[](Dog *d){ delete d; });
 *
 * 如果初始化一个指向数组的指针,这种自定义析构会更有作用
 * shared_ptr<Dog> ptr3(new Dog[3],[](Dog *d){ delete[] d; });
 */

/**
 * C++11  Lesson9 weak_ptr  避免循环引用
 * 更安全的weak_ptr访问方式:
 *
 * lock()作用: 返回一个shared_ptr
 * 1 检查weak_ptr是否还在指向一个有效的object
 * 2 确保在访问的时候，这个object没有被deleted
 *
 * 为了确保weak_ptr不是空值 !m_friend.expired()
 *  void showFriend() {
        if (!m_friend.expired())
            cout << m_friend.lock()->name_ << endl;
    }
 */

/**
 * C++11 Lesson10 unique_ptr exclusive ownership  ( light weight )
 *
 *  unique_ptr<Dog> pd( new Dog("Gunner") );
 *  pd->bark();
 *  Dog *p = pd.release();这样会有内存泄漏 pd是去所有权
 *  release函数返回raw poiter
 *  pd.reset(); destroy original object
 *  pd.reset( new Dog(""));放弃原来所有权，换做新的对象所有权
 *
 *  shared_ptr<Dog> ptr3(new Dog[3],[](Dog *d){ delete[] d; });
 *  unique_ptr<Dog[]> dogs(new Dog[3]) 不用自定义析构,因为unique_ptr做过优化
 */
class Dog {

    string name_;
    weak_ptr<Dog> m_friend;

public:

    Dog(string name) {
        name_ = name;
        cout << "Dog is created,its name is " << name << endl;
    }

    Dog() { cout << "Dog is created" << endl; }

    void bark() {
        cout << "Dog is barking" << endl;
    }

    ~Dog() {
        cout << "Dog is Dead" <<endl;
    }

    void makeFriend(shared_ptr<Dog> f) {
        m_friend = f;
    }

    /**
     *
     */
    void showFriend() {
        if (!m_friend.expired())
            cout << m_friend.lock()->name_ << endl;
    }

};

int main() {

    shared_ptr<Dog> ptr1 = make_shared<Dog>("Dog1");
    shared_ptr<Dog> ptr2 = make_shared<Dog>("Dog2");
    ptr1->makeFriend(ptr2);
    ptr2->makeFriend(ptr1);
    ptr1->showFriend();
    shared_ptr<Dog> ptr3(new Dog[3],[](Dog *d){ delete[] d; });
    return 0;
};