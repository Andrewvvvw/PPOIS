#ifndef GUEST_H
#define GUEST_H

#include "../User.h"

class Guest : public User {
private:
    time_t sessionStartTime;
    unsigned int viewLimit;

public:
    Guest();

    time_t getSessionDuration() const;
    unsigned int getViewLimit() const { return viewLimit; }

    std::string getUserType() const override { return "Guest"; }
    bool canComment() const override { return false; }

    bool canViewContent() const;
    void incrementViewCount();

    virtual bool getIsPremium() const override { return false; }
};

#endif // GUEST_H
