#include "RegularCustomer.h"

RegularCustomer::RegularCustomer(const std::string& name, int id, double totalSpent)
    : Customer(name, id, totalSpent) {}

void RegularCustomer::addFavoriteItem(int itemId) {
    if (std::find(favoriteItems.begin(), favoriteItems.end(), itemId) == favoriteItems.end()) {
        favoriteItems.push_back(itemId);
    }
}
