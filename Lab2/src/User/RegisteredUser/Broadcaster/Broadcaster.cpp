#include "Broadcaster.h"
#include <algorithm>
#include "../../../Audio/AudioBook/AudioBook.h"

Broadcaster::Broadcaster(const std::string& id,
                         const std::string& username,
                         const std::string& email,
                         const std::string& password,
                         const std::string& displayName)
        : RegisteredUser(id, username, email, password),
          displayName(displayName),
          yearsOfExperience(0) {}

void Broadcaster::updateNarrationStyle(const std::string& style) {
    narrationStyle = style;
}

void Broadcaster::updateExperience(unsigned int years) {
    yearsOfExperience = years;
}

bool Broadcaster::addNarratedBook(const std::shared_ptr<AudioBook>& book) {
    if (!book) {
        return false;
    }

    auto it = std::find_if(narratedBooks.begin(),
                           narratedBooks.end(),
                           [&](const auto& b)
                           { return b->getName() == book->getName(); });

    if (it != narratedBooks.end()) {
        return false;
    }

    narratedBooks.push_back(book);
    return true;
}

bool Broadcaster::removeNarratedBook(const std::string& bookTitle) {
    auto it = std::find_if(narratedBooks.begin(),
                           narratedBooks.end(),
                           [&](const auto& book)
                           { return book->getName() == bookTitle; });

    if (it != narratedBooks.end()) {
        narratedBooks.erase(it);
        return true;
    }

    return false;
}

std::vector<std::string> Broadcaster::getNarratedTitles() const {
    std::vector<std::string> titles;
    for (const auto& book : narratedBooks) {
        titles.push_back(book->getName());
    }
    return titles;
}

std::shared_ptr<AudioBook> Broadcaster::getNarratedBook(const std::string& title) const {
    auto it = std::find_if(narratedBooks.begin(),
                           narratedBooks.end(),
                           [&](const auto& book)
                           { return book->getName() == title; });

    return (it != narratedBooks.end()) ? *it : nullptr;
}