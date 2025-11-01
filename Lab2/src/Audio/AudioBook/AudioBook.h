#ifndef AUDIO_BOOK_H
#define AUDIO_BOOK_H

#include "../Audio.h"
#include "../../User/RegisteredUser/BookAuthor/BookAuthor.h"
#include "../../User/RegisteredUser/Broadcaster/Broadcaster.h"
#include <vector>
#include <memory>
#include <string>

class BookAuthor;
class Broadcaster;

class AudioBook : public Audio {
private:
    std::shared_ptr<BookAuthor> author;
    std::shared_ptr<Broadcaster> narrator;
    std::vector<std::string> chapters;
    unsigned int currentChapter;

public:
    AudioBook(const std::string& title,
             unsigned long long duration,
             unsigned long long coverID,
             const std::shared_ptr<BookAuthor>& author,
             const std::shared_ptr<Broadcaster>& narrator);

    const std::shared_ptr<BookAuthor>& getBookAuthor() const { return author; }
    const std::shared_ptr<Broadcaster>& getNarrator() const { return narrator; }

    bool addChapter(const std::string& chapterTitle);
    bool removeChapter(unsigned int chapterIndex);

    bool setCurrentChapter(unsigned int chapter);
    std::string getCurrentChapter() const;

    unsigned int getChapterCount() const { return chapters.size(); }
    std::vector<std::string> getChapters() const { return chapters; }
};

#endif // AUDIO_BOOK_H
