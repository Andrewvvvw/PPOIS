#ifndef LAB2_ADVERTISEMENT_H
#define LAB2_ADVERTISEMENT_H

#include "string"

class Advertisement {
private:
    std::string id;
    std::string content;
    int duration;

public:
    Advertisement(const std::string& id, const std::string& content, int duration);

    std::string getId() const;
    std::string getContent() const;
    int getDuration() const;

    bool operator==(const Advertisement& other) const;
};

#endif //LAB2_ADVERTISEMENT_H
