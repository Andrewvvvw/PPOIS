#ifndef LAB4_USER_H
#define LAB4_USER_H

#include <string>

class User {
private:
    std::string name;
    int age;
    unsigned long long id;
public:
    User() : name(""), age(0), id(0) {}
    User(std::string name, int age, unsigned long long id) : name(name), age(age), id(id) {}

    std::string getName() const {
        return name;
    }
    int getAge() const {
        return age;
    }
    unsigned long long getId() const {
        return id;
    }

    bool operator>(const User &other) const {
        return id > other.id;
    }
    bool operator<(const User &other) const {
        return id < other.id;
    }
    bool operator==(const User &other) const {
        return id == other.id;
    }
    bool operator!=(const User &other) const {
        return id != other.id;
    }
    bool operator>=(const User &other) const {
        return id >= other.id;
    }
    bool operator<=(const User &other) const {
        return id <= other.id;
    }
};

#endif //LAB4_USER_H
