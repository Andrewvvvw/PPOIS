#include "EmployeePerformanceReport.h"

EmployeePerformanceReport::EmployeePerformanceReport(const std::string& generatedBy, int empId)
    : Report("Employee Performance Report", generatedBy), employeeId(empId), overallRating(0.0), totalTasksCompleted(0) {}

void EmployeePerformanceReport::addMetric(const std::string& metricName, double value) {
    performanceMetrics[metricName] = value;
    updateRating();
}

void EmployeePerformanceReport::updateRating() {
    if (performanceMetrics.empty()) {
        overallRating = 0.0;
        return;
    }

    double sum = 0.0;
    for (const auto& metric : performanceMetrics) {
        sum += metric.second;
    }

    overallRating = sum / performanceMetrics.size();
}

void EmployeePerformanceReport::incrementTasksCompleted() {
    totalTasksCompleted++;
}

void EmployeePerformanceReport::generate() {
    isFinalized = true;
}

bool EmployeePerformanceReport::validate() const {
    return Report::validate() && employeeId > 0;
}

double EmployeePerformanceReport::getOverallRating() const {
    return overallRating;
}

int EmployeePerformanceReport::getTotalTasksCompleted() const {
    return totalTasksCompleted;
}

const std::map<std::string, double>& EmployeePerformanceReport::getPerformanceMetrics() const {
    return performanceMetrics;
}
