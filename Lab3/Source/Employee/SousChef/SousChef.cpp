#include "SousChef.h"

SousChef::SousChef(const std::string& name, double hourlyRate, int yearsOfExperience)
    : Employee(name, "Sous Chef", hourlyRate), shiftHours(8), isCertified(false), dishesPreparedToday(0) {
    setYearsOfExperience(yearsOfExperience);
}

void SousChef::assignStation(const std::string& station) {
    if (!isStationAssigned(station)) {
        assignedStations.push_back(station);
    }
}

bool SousChef::isStationAssigned(const std::string& station) const {
    return std::find(assignedStations.begin(), assignedStations.end(), station) != assignedStations.end();
}

void SousChef::completeDish() {
    if (isCertified) {
        dishesPreparedToday++;
    }
}

void SousChef::certify() {
    isCertified = true;
}

std::string SousChef::getRole() const {
    return "Sous Chef";
}

bool SousChef::getIsCertified() const {
    return isCertified;
}

