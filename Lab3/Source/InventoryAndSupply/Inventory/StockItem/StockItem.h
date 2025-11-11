#ifndef LAB3_STOCKITEM_H
#define LAB3_STOCKITEM_H
#include <string>

class StockItem {
    std::string name;
    std::string category;
    double quantity;
    std::string unit;
    double minStockLevel;

public:
    StockItem(const std::string& name, const std::string& category, double quantity, const std::string& unit, double minStockLevel);

    void addQuantity(double amount);
    bool needsRestocking() const;
    void updateMinStockLevel(double newLevel);
    double calculateDaysLeft(double dailyUsage) const;
    void setCategory(const std::string& newCategory);

    std::string getName() const;
    std::string getCategory() const;
    double getQuantity() const;
    std::string getUnit() const;
    double getMinStockLevel() const;
};
#endif //LAB3_STOCKITEM_H
