#ifndef LAB3_SUPPLIER_H
#define LAB3_SUPPLIER_H

#include <string>
#include <vector>

class Supplier {
    std::string supplierId;
    std::string name;
    std::string contactPerson;
    std::string phoneNumber;
    std::vector <std::string> suppliedItems;

public:
    Supplier(const std::string& supplierId, const std::string& name,
             const std::string& contactPerson, const std::string& phoneNumber);

    void addSuppliedItem(const std::string& itemName);
    bool removeSuppliedItem(const std::string& itemName);
    bool suppliesItem(const std::string& itemName) const;
    void updateContactInfo(const std::string& newContact, const std::string& newPhone);

    std::string getSupplierId() const;
    std::string getName() const;
    std::string getContactPerson() const;
    std::string getPhoneNumber() const;
    const std::vector<std::string>& getSuppliedItems() const;
};

#endif //LAB3_SUPPLIER_H
