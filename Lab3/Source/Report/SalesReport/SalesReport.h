#ifndef LAB3_SALES_REPORT_H
#define LAB3_SALES_REPORT_H

#include "../Report.h"
#include <map>
#include <ctime>

class SalesReport : public Report {
private:
    std::map<int, double> dailySales;
    time_t startDate;
    time_t endDate;
    double totalSales;
    int itemsSold;

public:
    SalesReport(const std::string& generatedBy, time_t start, time_t end);

    void addSale(int itemId, double amount);
    void setTotalSales(double amount);
    void incrementItemsSold(int quantity);

    void generate() override;
    bool validate() const override;

    double getTotalSales() const;
    int getItemsSold() const;
    const std::map<int, double>& getDailySales() const;
};

#endif //LAB3_SALES_REPORT_H
