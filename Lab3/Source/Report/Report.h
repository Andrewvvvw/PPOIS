#ifndef LAB3_REPORT_H
#define LAB3_REPORT_H

#include <string>
#include <ctime>

class Report {
protected:
    std::string title;
    time_t generationTime;
    bool isFinalized;
    std::string generatedBy;

public:
    Report(const std::string& title, const std::string& generatedBy);
    virtual ~Report() = default;

    virtual void generate() = 0;
    virtual bool validate() const;

    std::string getTitle() const;
    time_t getGenerationTime() const;
    bool getIsFinalized() const;
    std::string getGeneratedBy() const;
};

#endif //LAB3_REPORT_H
