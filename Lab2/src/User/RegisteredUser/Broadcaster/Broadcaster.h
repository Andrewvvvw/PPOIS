#ifndef BROADCASTER_H
#define BROADCASTER_H

#include "../RegisteredUser.h"
#include "../../../Audio/AudioBook/AudioBook.h"
#include <vector>
#include <memory>
#include <string>

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

    std::string getDisplayName() const { return displayName; }
    std::string getNarrationStyle() const { return narrationStyle; }
    unsigned int getYearsOfExperience() const { return yearsOfExperience; }

    void updateNarrationStyle(const std::string& style);
    void updateExperience(unsigned int years);

    bool addNarratedBook(const std::shared_ptr<AudioBook>& book);
    bool removeNarratedBook(const std::string& bookTitle);

    std::vector<std::string> getNarratedTitles() const;
    std::shared_ptr<AudioBook> getNarratedBook(const std::string& title) const;

    std::string getUserType() const override { return "Broadcaster"; }
    bool canUploadContent() const override { return true; }
};

#endif // BROADCASTER_H