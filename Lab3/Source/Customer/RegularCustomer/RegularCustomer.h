#ifndef LAB3_REGULARCUSTOMER_H
#define LAB3_REGULARCUSTOMER_H

#include "../Customer.h"
#include <vector>
#include <string>

class RegularCustomer : public Customer {
    std::vector <int> favoriteItems;

public:
    RegularCustomer(const std::string& name, int id, double totalSpent = 0.0);
    void addFavoriteItem(int itemId);
};
#endif //LAB3_REGULARCUSTOMER_H
