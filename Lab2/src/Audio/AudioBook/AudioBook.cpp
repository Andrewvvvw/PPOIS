#include "AudioBook.h"
#include <algorithm>
#include "../../Exceptions/Exceptions.h"
#include "memory"

AudioBook::AudioBook(const std::string& title,
                     unsigned long long duration,
                     unsigned long long coverID,
                     const std::shared_ptr<BookAuthor>& author,
                     const std::shared_ptr<Broadcaster>& narrator)
        : Audio(duration, title, coverID),
          author(author),
          narrator(narrator),
          currentChapter(0) {

}

void AudioBook::registerWithAuthorAndNarrator() {
    if (author) {
        author->publishBook(shared_from_this());
    }
    if (narrator) {
        narrator->addNarratedBook(shared_from_this());
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

void AudioBook::setCurrentChapter(unsigned int chapter) {
    if (chapter >= chapters.size() || chapter < 0)
        throw ExceptionIncorrectChapterNumber("Incorrect chapter number");

    currentChapter = chapter;
}

std::string AudioBook::getCurrentChapter() const {
    if (chapters.empty())
        throw ExceptionIncorrectAudioBookChapters("Audio book needs to contain chapters");
    return chapters[currentChapter];
}

std::string AudioBook::getAuthor() const {
    return author ? author->getUsername() : "Unknown Author";
}

const std::shared_ptr<BookAuthor>& AudioBook::getBookAuthor() const {
    return author;
}

const std::shared_ptr<Broadcaster>& AudioBook::getNarrator() const {
    return narrator;
}

unsigned int AudioBook::getChapterCount() const {
    return chapters.size();
}

std::vector<std::string> AudioBook::getChapters() const {
    return chapters;
}
