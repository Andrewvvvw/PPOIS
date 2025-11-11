#ifndef LAB3_ALLERGENINFO_H
#define LAB3_ALLERGENINFO_H
#include <string>
#include <vector>

enum class AllergenSeverity {
    LOW,
    MEDIUM,
    HIGH
};

class AllergenInfo {
private:
    std::string name;
    std::string description;
    std::vector<std::string> alternativeNames;
    AllergenSeverity severity;
    bool isCommon;

public:
    AllergenInfo(const std::string& name, const std::string& description,
                 AllergenSeverity severity, bool isCommon);

    void addAlternativeName(const std::string& alternative);
    bool isSevere() const;
    bool hasAlternative(const std::string& alternative) const;
    bool isMoreSevereThan(AllergenSeverity otherSeverity) const;
    std::string getSeverityString() const;

    std::string getName() const;
    std::string getDescription() const;
    AllergenSeverity getSeverity() const;
    bool getIsCommon() const;
    const std::vector <std::string>& getAlternativeNames() const;

    void setSeverity(AllergenSeverity newSeverity);
    void setDescription(const std::string& newDesc);
};
#endif //LAB3_ALLERGENINFO_H
