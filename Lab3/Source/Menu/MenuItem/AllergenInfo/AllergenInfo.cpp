#include "AllergenInfo.h"

AllergenInfo::AllergenInfo(const std::string& name, const std::string& description,
                           AllergenSeverity severity, bool isCommon)
        : name(name), description(description), severity(severity), isCommon(isCommon) {}

void AllergenInfo::addAlternativeName(const std::string& alternative) {
    alternativeNames.push_back(alternative);
}

bool AllergenInfo::isSevere() const {
    return severity == AllergenSeverity::HIGH;
}

bool AllergenInfo::hasAlternative(const std::string& alternative) const {
    return std::find(alternativeNames.begin(), alternativeNames.end(), alternative) != alternativeNames.end();
}

bool AllergenInfo::isMoreSevereThan(AllergenSeverity otherSeverity) const {
    return static_cast<int>(severity) > static_cast<int>(otherSeverity);
}

std::string AllergenInfo::getSeverityString() const {
    switch (severity) {
        case AllergenSeverity::LOW: return "Low";
        case AllergenSeverity::MEDIUM: return "Medium";
        case AllergenSeverity::HIGH: return "High";
        default: return "Unknown";
    }
}

std::string AllergenInfo::getName() const {
    return name;
}

std::string AllergenInfo::getDescription() const {
    return description;
}

AllergenSeverity AllergenInfo::getSeverity() const {
    return severity;
}

bool AllergenInfo::getIsCommon() const {
    return isCommon;
}

const std::vector<std::string>& AllergenInfo::getAlternativeNames() const {
    return alternativeNames;
}

void AllergenInfo::setSeverity(AllergenSeverity newSeverity) {
    severity = newSeverity;
}

void AllergenInfo::setDescription(const std::string& newDesc) {
    description = newDesc;
}
