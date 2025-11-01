#include "AudioBook.h"
#include <algorithm>

AudioBook::AudioBook(const std::string& title,
                     unsigned long long duration,
                     unsigned long long coverID,
                     const std::shared_ptr<BookAuthor>& author,
                     const std::shared_ptr<Broadcaster>& narrator)
        : Audio(duration, title, coverID),
          author(author),
          narrator(narrator),
          currentChapter(0) {

    if (author) {
        author->publishBook(this);
    }
    if (narrator) {
        narrator->addNarratedBook(this);
    }
}

bool AudioBook::addChapter(const std::string& chapterTitle) {
    if (chapterTitle.empty()) {
        return false;
    }

    auto it = std::find(chapters.begin(), chapters.end(), chapterTitle);
    if (it != chapters.end()) {
        return false;
    }

    chapters.push_back(chapterTitle);
    return true;
}

bool AudioBook::removeChapter(unsigned int chapterIndex) {
    if (chapterIndex >= chapters.size()) {
        return false;
    }

    chapters.erase(chapters.begin() + chapterIndex);

    if (currentChapter >= chapters.size()) {
        currentChapter = chapters.empty() ? 0 : chapters.size() - 1;
    }

    return true;
}

bool AudioBook::setCurrentChapter(unsigned int chapter) {
    if (chapter >= chapters.size()) {
        return false;
    }

    currentChapter = chapter;
    return true;
}

std::string AudioBook::getCurrentChapter() const {
    if (chapters.empty()) {
        return "";
    }
    return chapters[currentChapter];
}