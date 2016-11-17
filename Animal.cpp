//
// Created by nick on 2016/11/11.
//

#include <iostream>
#include <vector>

using namespace std;

class Animal {

protected:
    string name_ = "Fido";
    int weight_;

public:
    Animal(const string &name_, int weight_) : name_(name_), weight_(weight_) {}
    virtual string who() { return name_ + to_string(weight_) ; };
    virtual string sound() = 0;

};

class Sheep: public Animal {
public:
    string sound() override {
        return "sheep sound";
    }
};

class Dog: public Animal {
public:
    string sound() override {
        return "Dog sound";
    }
};

class Cow: public Animal {
public:
    string sound() override {
        return "Cow sound";
    }
};

class Zoo {

private:
    vector<shared_ptr<string>> actions_;

public:
    void add(string& action) {
        if (actions_.size() > 50) {

        } else {
            actions_.push_back(make_shared(action));
        }
    }

};

int main() {

    return 0;
}
