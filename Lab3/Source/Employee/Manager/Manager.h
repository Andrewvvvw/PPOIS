#ifndef LAB3_MANAGER_H
#define LAB3_MANAGER_H

#include "../Employee.h"

class Manager : public Employee {
private:
    std::string department;
    int teamSize;
    double bonus;
    int accessLevel;
    bool isCertified;

public:
    Manager(const std::string& name, const std::string& position, double hourlyRate,
           const std::string& dept, int accessLvl);

    std::string getDepartment() const;
    int getTeamSize() const;
    double getBonus() const;
    int getAccessLevel() const;
    bool getIsCertified() const;

    void setDepartment(const std::string& dept);
    void setTeamSize(int size);
    void setBonus(double amount);
    void setAccessLevel(int level);
    void setIsCertified(bool certified);

    std::string getRole() const override;

    void assignTask(const std::string& task, const std::string& employeeName);
    bool approveExpense(double amount);
    double evaluateTeam() const;
    bool getBonusEligibility() const;
};

#endif //LAB3_MANAGER_H
