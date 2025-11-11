#ifndef LAB3_SOUSCHEF_H
#define LAB3_SOUSCHEF_H

#include "../Employee.h"
#include <vector>
#include <string>

class SousChef : public Employee {
private:
    std::vector<std::string> assignedStations;
    int shiftHours;
    bool isCertified;
    int dishesPreparedToday;

public:
    SousChef(const std::string& name, double hourlyRate, int yearsOfExperience);

    void assignStation(const std::string& station);
    bool isStationAssigned(const std::string& station) const;
    void completeDish();
    void certify();

    std::string getRole() const override;
    bool getIsCertified() const;
};

#endif //LAB3_SOUSCHEF_H
