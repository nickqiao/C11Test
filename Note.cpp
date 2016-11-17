//
// Created by nick on 2016/11/7.
//
#include <iostream>
using namespace std;
/**
 * C++ 05 Disallow Function
 *
 * 如果没有显式声明编译器会自动生成4个function
 * 1 copy constructor
 * 2 copy Assignmengt Operator
 * 3 Destructor
 * 4 Default constructor
 *
 * 在C++11中  使用delete关键字
 * 在C++03中  声明为私有private
 * 如果想把析构函数设为私有,必须单独提供一个自杀函数,
 * 并且在使用类的时候，将类初始化在堆上，
 * 如果初始化在栈上,当超出scope销毁的时候,调用完destroyme后，出scope时候还会再调一次析构
 * 这时由于析构函数是私有,会出现错误
 */

//class OpenFile {
//
//public:
//    OpenFile(std::string filename) { cout << "open a file" << filename << endl; }
//    void destroyme() { delete this; }
//private:
//
//    ~OpenFile() {
//        cout << "OpenFile destructed" << endl;
//    }
//
//};
//
//int main() {
//    OpenFile *file = new OpenFile("ddd");
//    file->destroyme();
//    return 0;
//}


/**
 * C++ 06
 * 1 当使用多态时，在析构函数前加上virtual ,这样才能正确调用子类析构
 *   如果不想用virtual，可以考虑在声明指针的时候用 shared_ptr,在对象销毁时会自动调用析构
 *   但是unique_ptr不具有这个功能
 *
 * 2 所有的STL中的类都没有 virtual析构,所以在继承自这些类的时候最好使用 shared_ptr
 *
*/

/**
 * C++08 构造函数和析构函数中的virtul function
 *
 * 1 如果在 基类的 构造函数或者析构函数中调用成员函数，并不会自动绑定到子类实现的函数
 */


/** C++09 自赋值
 * Handle self-assignment in operator=
 * What is self-assignment
 * Dog dd;
 * dd = dd; looks silly
 * dogs[i] = dogs[j];  looks less silly
 */

//class collar;
//
//class Dog {
//
//    collar* pCollar;
//
//    // 第一种解决方案
////    Dog& operator=(const Dog& rhs) {
////        if (this == &rhs)
////            return *this;
////        // 此处为了避免在 pCollar = new collar(*rhs.pCollar)出现异常，pCollar已经被删除,
////        // 最后会是个空值
//////        delete pCollar;
//////        pCollar = new collar(*rhs.pCollar);
//////        return *this;
////        // 此种写法避免了上面提到的异常
////        collar *pOrigCollar = pCollar;
////        pCollar = new collar(*rhs.pCollar);
////        delete(pOrigCollar);
////        return *this;
////    }
//
//    // member by member copying of collar or call collar's operator=
//    Dog& operator=(const Dog& rhs) {
//        *pCollar = *rhs.pCollar;
//        return *this;
//    }
//
//};

/**
 * C++ lesson10 RAII
 * RAII(Resource Acquisition Is Initialization) 要求资源的有效期与持有资源的对象的生命周期严格绑定
 * 即由对象的构造函数完成资源的分配(获取),同时由析构函数完成资源的释放
 * 在这种要求下,只要对象能正确析构,就不会出现资源泄漏问题
 * 不要在shared_ptr中存储对象连带其他状态
 * train(tr1::shared_ptr<Dog> pd(new Dog()),getTrick());
 * 在这个参数传递中发生了三件事:
 * 1 new Dog()
 * 2 getTrick()
 * 3 construct tr1::shared_ptr<Dog>
 * 这三件事的顺序由编译器决定,加入按上面的顺序,getTrick发生异常,New Dog()会产生溢出
 * 应该改为
 * tr1::shared_ptr<Dog> pd(new Dog())
 * train(pd,getTrick())
 *
 * 注意点3:
 *
 *
 */

/**
 * C++ lesson11 static initialization Fiasco(惨败)
 *
 * 假如有两个类,Cat 和Dog，并且声明了两个全局变量pc和pd，
 * 在Cat的成员函数中调用pd,在Dog的成员函数中调用pc，会发生错误，因为并不知道编译器
 * 会先编译哪个文件,所以碰到这种全局变量的情况最好使用singleton
 * singleton
 * 使用单例时候最好声明一个实例变量,由于是临时变量，在scope结束的时候,会调用析构函数销毁
 */

//class Dog {
//public:
//    void bark() {
//        cout << "bark" << endl;
//    }
//    ~Dog() {
//        cout << "Dog is destroyed" << endl;
//    }
//};
//
//class Cat {
//public:
//    void meow() {
//        cout << "meow" << endl;
//    }
//    ~Cat() {
//        cout << "Cat is destroyed" <<endl;
//    }
//};
//
//
//class Singleton {
//    static Dog* pd;
//    static Cat* pc;
//public:
//    ~Singleton();
//    static Dog* getDog() ;
//    static Cat* getCat();
//};
//
//Dog* Singleton::pd = 0;
//Cat* Singleton::pc = 0;
//
//Cat* Singleton::getCat() {
//    if (!pc)
//        pc = new Cat();
//    return pc;
//}
//
//Dog* Singleton::getDog() {
//    if (!pd)
//        pd = new Dog();
//    return pd;
//}
//
//Singleton::~Singleton() {
//    if (pd) delete pd;
//    if (pc) delete pc;
//    pd = 0;
//    pc = 0;
//}
//
//int main() {
//    // 使用单例时候最好声明一个实例变量,由于是临时变量，在scope结束的时候,会调用析构函数销毁
//    Singleton singleton;
//    Singleton::getCat()->meow();
//    return 0;
//}

/**
 * C++ lesson12 struct and class
 * 不同点:
 * 1 data member struct默认是public class默认是private
 * 2 struct is used for data container
 * 3 class is used for complex data structure
 *
 * age_(成员变量) 右下划线
 * 在很早的时候用m_age,
 * _age(左下划线)(python的私有变量) (全局变量，内部实现相关变量)
*/

/**
 * C++ lesson13 Resource Managing Class
 * 资源管理类(Resource Managing Class)
 * pitfall(陷阱)
 *
 * persons.push_back(Person("James"));这句话发生了以下三个过程:
 * // 1 "George is constructed"
 * // 2 A copy of "George" is saved in vector persons(shallow copy)
 * // 3 "George" is destroyed
 */
//#include <vector>
//#include <deque>
//class Person {
//private:
//    string* pName_;
//
//public:
//
//    Person(const Person& rhs) = delete;
//    Person& operator=(const Person& rhs) = delete;
//
//    Person(string name) {
//        pName_ = new string(name);
//    }
//
//    ~Person() {
//        delete pName_;
//    }
//
//    void printName() {
//        cout << *pName_ << endl;
//    }
//};
//
//int main() {
//    // 这里如果是vector会有错误,因为vector要求加入的元素要么copyalbe 要么moveable,所以改成deque就可以
//    deque<Person> persons;
//    persons.emplace_back("James");
//    persons.back().printName();
//    return 0;
//}

/**
 * C++ lesson14
 * virtual constructor Clone()
 * 显式的clone函数,在多态时候的用处,能够直接调用到本省类
 *
 */
//class Dog {
//    virtual Dog* clone() {
//        return new Dog(*this);
//    }
//};
//class YellowDog :public Dog{
//    virtual Dog *clone() override {
//        return new YellowDog(*this);
//    }
//};
//void foo(Dog *dog) {
//
//}
//
//int main () {
//    YellowDog yellowDog;
//    foo(&yellowDog);
//    return 0;
//}


/**
 * C++ Lesson15
 * Implicit Type Conversion(隐式类型转换)
 * 有两种方式定义隐式类型转换
 * 1 使用构造函数接受一个单独的参数,把其他类型转换城你定义的类型
 * 2 使用类型定义函数,把你的类的实例转换为其他类型
 * 例：
 * class dog {
 * private:
 *      string name_;
 *  public:
 *      dog(string name) { name_ = name; }
 *      // 类型定义函数
 *      operator string() const { return name_ }
 * }
 */
//class dog {
// private:
//     string name_;
// public:
//    dog(string name) { name_ = name; }
//     // 类型定义函数
//     operator string() const { return name_; }
//};
//
//int main() {
//    string dogname = "yyyouio";
//    dog dog1 = dogname;
//    return 0;
//}

/**
 * C++11 Lesson16
 *
 * 1.static_cast
 */

/**
 * C++ Lesson21 static polymorphism
 * dynamic polymorphism
 * static polymorphism 提升性能  模版元编程，在编译阶段确定类型
 */

/**
 * C++ Lesson22 Multiple Inheritance
 * Pure Abstract Classes(抽象类)
 * A class
 */

/**
 * Oerator new/delete
 */







