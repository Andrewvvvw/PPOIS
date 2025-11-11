#ifndef LAB3_GUEST_H
#define LAB3_GUEST_H
#include "../Customer.h"
#include <vector>
#include <string>

class Guest : public Customer {
    std::string email;
    int visitCount;
    bool newsletterSubscribed;
    std::vector <std::string> preferences;

public:
    Guest(const std::string& name, int id, const std::string& email);
    void incrementVisitCount();
    void subscribeToNewsletter();
    void addPreference(const std::string& preference);
    bool hasPreference(const std::string& preference) const;
};

#endif //LAB3_GUEST_H
