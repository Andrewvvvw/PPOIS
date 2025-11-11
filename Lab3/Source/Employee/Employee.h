#ifndef LAB3_EMPLOYEE_H
#define LAB3_EMPLOYEE_H

#include <string>
#include <vector>

class Employee {
protected:
    std::string name;
    std::string position;
    double hourlyRate;
    int yearsOfExperience;
    bool isActive;

public:
    Employee(const std::string& name, const std::string& position, double hourlyRate);
    virtual ~Employee() = default;

    std::string getName() const;
    double getHourlyRate() const;
    int getYearsOfExperience() const;
    bool getIsActive() const;

    void setName(const std::string& name);
    void setHourlyRate(double rate);
    void setYearsOfExperience(int years);
    void setIsActive(bool active);

    virtual std::string getRole() const = 0;
    void addExperience(int years = 1);
};


#endif //LAB3_EMPLOYEE_H
