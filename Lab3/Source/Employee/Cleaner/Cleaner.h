#ifndef LAB3_CLEANER_H
#define LAB3_CLEANER_H

#include "../Employee.h"
#include <vector>
#include <string>

class Cleaner : public Employee {
private:
    std::vector <std::string> cleaningAreas;
    int cleaningSpeed;
    bool hasCleaningSupplies;
    int yearsOfExperience;

public:
    Cleaner(const std::string& name, double hourlyRate, int yearsOfExperience);

    void cleanArea(const std::string& area);
    void addCleaningArea(const std::string& area);
    bool isAreaInCharge(const std::string& area) const;
    void restockSupplies();

    std::string getRole() const override;
};

#endif //LAB3_CLEANER_H