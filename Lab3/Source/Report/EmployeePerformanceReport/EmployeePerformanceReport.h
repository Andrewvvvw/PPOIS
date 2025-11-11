#ifndef LAB3_EMPLOYEE_PERFORMANCE_REPORT_H
#define LAB3_EMPLOYEE_PERFORMANCE_REPORT_H

#include "../Report.h"
#include <map>

class EmployeePerformanceReport : public Report {
private:
    std::map<std::string, double> performanceMetrics;
    int employeeId;
    double overallRating;
    int totalTasksCompleted;

public:
    EmployeePerformanceReport(const std::string& generatedBy, int empId);

    void addMetric(const std::string& metricName, double value);
    void updateRating();
    void incrementTasksCompleted();

    void generate() override;
    bool validate() const override;

    double getOverallRating() const;
    int getTotalTasksCompleted() const;
    const std::map<std::string, double>& getPerformanceMetrics() const;
};

#endif //LAB3_EMPLOYEE_PERFORMANCE_REPORT_H
