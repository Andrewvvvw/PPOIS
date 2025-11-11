#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <string>
#include <vector>
#include <chrono>

class Feedback {
private:
    int id;
    int customerId;
    int rating;
    std::string comment;
    std::chrono::system_clock::time_point timestamp;
    bool isVerified;

public:
    Feedback(int id, int customerId, int rating, const std::string& comment);

    bool verify();
    bool isVerifiedPurchase() const;
    void setRating(int newRating);
    bool isRecent() const;

    int getId() const;
    int getCustomerId() const;
    int getRating() const;
    std::string getComment() const;
};

#endif // FEEDBACK_H
