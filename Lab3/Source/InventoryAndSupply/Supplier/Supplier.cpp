#include "Supplier.h"
#include "../../Exceptions/Exceptions.h"

Supplier::Supplier(const std::string& supplierId, const std::string& name,
                 const std::string& contactPerson, const std::string& phoneNumber)
    : supplierId(supplierId), contactPerson(contactPerson) {
        if(name == "")
            throw ExceptionEmptyName("Supplier name can't be empty");
        else
            this->name = name;
            
        if(phoneNumber == "")
            throw ExceptionEmptyPhoneNumber("Supplier phone number can't be empty");
        else
            this->phoneNumber = phoneNumber;
    }

void Supplier::addSuppliedItem(const std::string& itemName) {
    if (!suppliesItem(itemName)) {
        suppliedItems.push_back(itemName);
    }
}

bool Supplier::removeSuppliedItem(const std::string& itemName) {
    auto it = std::remove(suppliedItems.begin(), suppliedItems.end(), itemName);
    if (it != suppliedItems.end()) {
        suppliedItems.erase(it, suppliedItems.end());
        return true;
    }
    return false;
}

bool Supplier::suppliesItem(const std::string& itemName) const {
    return std::find(suppliedItems.begin(), suppliedItems.end(), itemName) != suppliedItems.end();
}

void Supplier::updateContactInfo(const std::string& newContact, const std::string& newPhone) {
    contactPerson = newContact;
    phoneNumber = newPhone;
}

std::string Supplier::getSupplierId() const {
    return supplierId;
}

std::string Supplier::getName() const {
    return name;
}

std::string Supplier::getContactPerson() const {
    return contactPerson;
}

std::string Supplier::getPhoneNumber() const {
    return phoneNumber;
}

const std::vector<std::string>& Supplier::getSuppliedItems() const {
    return suppliedItems;
}
