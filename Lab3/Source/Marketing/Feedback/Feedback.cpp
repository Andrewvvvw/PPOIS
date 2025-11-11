#include "Feedback.h"

Feedback::Feedback(int id, int customerId, int rating, const std::string& comment)
    : id(id), customerId(customerId), rating(rating), comment(comment) {
    timestamp = std::chrono::system_clock::now();
    isVerified = false;
}

bool Feedback::verify() {
    if (isVerified) return false;
    isVerified = true;
    return true;
}

bool Feedback::isVerifiedPurchase() const {
    return isVerified;
}

void Feedback::setRating(int newRating) {
    if (newRating >= 1 && newRating <= 5) {
        rating = newRating;
    }
}

bool Feedback::isRecent() const {
    auto now = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::hours>(now - timestamp).count();
    return duration < 24 * 7;
}

int Feedback::getId() const {
    return id;
}
int Feedback::getCustomerId() const {
    return customerId;
}
int Feedback::getRating() const {
    return rating;
}
std::string Feedback::getComment() const {
    return comment;
}
