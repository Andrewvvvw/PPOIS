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
    unsigned int getViewLimit() const;

    std::string getUserType() const override;
    bool canComment() const override;

    bool canViewContent() const;
    void incrementViewCount();

    virtual bool getIsPremium() const override;
};

#endif // GUEST_H
