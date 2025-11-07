#ifndef BOOK_AUTHOR_H
#define BOOK_AUTHOR_H

#include "../RegisteredUser.h"
#include <vector>
#include <memory>
#include <string>

class AudioBook;

class BookAuthor : public RegisteredUser {
private:
    std::string biography;
    std::vector <std::shared_ptr<AudioBook> > publishedBooks;
    std::string primaryGenre;

public:
    BookAuthor(const std::string& id,
              const std::string& username,
              const std::string& email,
              const std::string& password);

    std::string getBiography() const;
    std::string getPrimaryGenre() const;

    void updateBiography(const std::string& newBio);
    void updatePrimaryGenre(const std::string& genre);

    bool publishBook(const std::shared_ptr<AudioBook>& book);
    bool removeBook(const std::string& bookTitle);

    std::vector<std::string> getPublishedTitles() const;
    std::shared_ptr<AudioBook> getBook(const std::string& title) const;

    std::string getUserType() const override;
    bool canUploadContent() const override;
};

#endif //BOOK_AUTHOR_H
