#ifndef BROADCASTER_H
#define BROADCASTER_H

#include "../RegisteredUser.h"
#include <vector>
#include <memory>
#include <string>

class AudioBook;

class Broadcaster : public RegisteredUser {
private:
    std::string displayName;
    std::string narrationStyle;
    std::vector<std::shared_ptr<AudioBook> > narratedBooks;
    unsigned int yearsOfExperience;

public:
    Broadcaster(const std::string& id,
                const std::string& username,
                const std::string& email,
                const std::string& password,
                const std::string& displayName);

    std::string getDisplayName() const;
    std::string getNarrationStyle() const;
    unsigned int getYearsOfExperience() const;

    void updateNarrationStyle(const std::string& style);
    void updateExperience(unsigned int years);

    bool addNarratedBook(const std::shared_ptr<AudioBook>& book);
    bool removeNarratedBook(const std::string& bookTitle);

    std::vector<std::string> getNarratedTitles() const;
    std::shared_ptr<AudioBook> getNarratedBook(const std::string& title) const;

    std::string getUserType() const override;
    bool canUploadContent() const override;
};

#endif // BROADCASTER_H