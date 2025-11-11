#include "SalesReport.h"
#include <ctime>

SalesReport::SalesReport(const std::string& generatedBy, time_t start, time_t end)
    : Report("Sales Report", generatedBy), startDate(start), endDate(end), totalSales(0.0), itemsSold(0) {}

void SalesReport::addSale(int itemId, double amount) {
    if (itemId <= 0 || amount <= 0) return;

    auto it = dailySales.find(itemId);
    if (it != dailySales.end()) {
        it->second += amount;
    } else {
        dailySales[itemId] = amount;
    }

    totalSales += amount;
}

void SalesReport::setTotalSales(double amount) {
    if (amount >= 0) {
        totalSales = amount;
    }
}

void SalesReport::incrementItemsSold(int quantity) {
    if (quantity > 0) {
        itemsSold += quantity;
    }
}

void SalesReport::generate() {
    isFinalized = true;
}

bool SalesReport::validate() const {
    return Report::validate() && startDate <= endDate && totalSales >= 0 && itemsSold >= 0;
}

double SalesReport::getTotalSales() const {
    return totalSales;
}

int SalesReport::getItemsSold() const {
    return itemsSold;
}

const std::map<int, double>& SalesReport::getDailySales() const {
    return dailySales;
}
