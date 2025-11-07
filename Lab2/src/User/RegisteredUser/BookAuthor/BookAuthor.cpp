#include "BookAuthor.h"
#include <algorithm>
#include "../../../Audio/AudioBook/AudioBook.h"

BookAuthor::BookAuthor(const std::string& id,
                      const std::string& username,
                      const std::string& email,
                      const std::string& password)
    : RegisteredUser(id, username, email, password){}

void BookAuthor::updateBiography(const std::string& newBio) {
    biography = newBio;
}

void BookAuthor::updatePrimaryGenre(const std::string& genre) {
    primaryGenre = genre;
}

bool BookAuthor::publishBook(const std::shared_ptr<AudioBook>& book) {
    if (!book) {
        return false;
    }

    for (const auto& existingBook : publishedBooks) {
        if (existingBook->getName() == book->getName()) {
            return false;
        }
    }

    publishedBooks.push_back(book);
    return true;
}

bool BookAuthor::removeBook(const std::string& bookTitle) {
    auto it = std::find_if(publishedBooks.begin(),
                           publishedBooks.end(),
                         [&](const auto& book)
                         { return book->getName() == bookTitle; });

    if (it != publishedBooks.end()) {
        publishedBooks.erase(it);
        return true;
    }

    return false;
}

std::vector<std::string> BookAuthor::getPublishedTitles() const {
    std::vector<std::string> titles;
    for (const auto& book : publishedBooks) {
        titles.push_back(book->getName());
    }
    return titles;
}

std::shared_ptr<AudioBook> BookAuthor::getBook(const std::string& title) const {
    auto it = std::find_if(publishedBooks.begin(),
                           publishedBooks.end(),
                         [&](const auto& book)
                         { return book->getName() == title; });

    return (it != publishedBooks.end()) ? *it : nullptr;
}
