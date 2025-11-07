#include "UnitTest++.h"
#include "../../src/Audio/AudioBook/AudioBook.h"
#include "../../src/User/RegisteredUser/BookAuthor/BookAuthor.h"
#include "../../src/User/RegisteredUser/Broadcaster/Broadcaster.h"
#include "../../src/Exceptions/Exceptions.h"
#include <memory>

SUITE(AudioBookTest) {
    TEST(ConstructorAndGetters) {
        auto author = std::make_shared<BookAuthor>("author1", "Author Name", "author@example.com", "password123");
        auto narrator = std::make_shared<Broadcaster>("narrator1", "Narrator Name", "narrator@example.com", "password123", "Narrator Display Name");
        auto book = std::make_shared<AudioBook>("Test Book", 3600, 1, author, narrator);
        book->registerWithAuthorAndNarrator();

                CHECK_EQUAL("Test Book", book->getName());
                CHECK_EQUAL(3600, book->getDuration());
                CHECK_EQUAL(1, book->getCoverID());
                CHECK_EQUAL("Author Name", book->getAuthor());
                CHECK_EQUAL(0, book->getChapterCount());
                CHECK_EQUAL(author, book->getBookAuthor());
                CHECK_EQUAL(narrator, book->getNarrator());
    }

    TEST(AddAndRemoveChapters) {
        auto author = std::make_shared<BookAuthor>("author1", "Author", "author@example.com", "password123");
        auto narrator = std::make_shared<Broadcaster>("narrator1", "Narrator", "narrator@example.com", "password123", "Narrator Display");
        auto book = std::make_shared<AudioBook>("Test Book", 3600, 1, author, narrator);
        book->registerWithAuthorAndNarrator();

        bool added = book->addChapter("Chapter 1");
                CHECK(added);
                CHECK_EQUAL(1, book->getChapterCount());

        added = book->addChapter("Chapter 2");
                CHECK(added);
                CHECK_EQUAL(2, book->getChapterCount());

        bool removed = book->removeChapter(0);
                CHECK(removed);
                CHECK_EQUAL(1, book->getChapterCount());
                CHECK_EQUAL("Chapter 2", book->getChapters()[0]);
    }

    TEST(AddDuplicateChapter) {
        auto author = std::make_shared<BookAuthor>("author1", "Author", "author@example.com", "password123");
        auto narrator = std::make_shared<Broadcaster>("narrator1", "Narrator", "narrator@example.com", "password123", "Narrator Display");
        auto book = std::make_shared<AudioBook>("Test Book", 3600, 1, author, narrator);
        book->registerWithAuthorAndNarrator();

        book->addChapter("Chapter 1");
        bool added = book->addChapter("Chapter 1");
                CHECK(!added);
                CHECK_EQUAL(1, book->getChapterCount());
    }

    TEST(RemoveInvalidChapter) {
        auto author = std::make_shared<BookAuthor>("author1", "Author", "author@example.com", "password123");
        auto narrator = std::make_shared<Broadcaster>("narrator1", "Narrator", "narrator@example.com", "password123", "Narrator Display");
        auto book = std::make_shared<AudioBook>("Test Book", 3600, 1, author, narrator);
        book->registerWithAuthorAndNarrator();

        book->addChapter("Chapter 1");
        bool removed = book->removeChapter(1);
                CHECK(!removed);
                CHECK_EQUAL(1, book->getChapterCount());
    }

    TEST(SetAndGetCurrentChapter) {
        auto author = std::make_shared<BookAuthor>("author1", "Author", "author@example.com", "password123");
        auto narrator = std::make_shared<Broadcaster>("narrator1", "Narrator", "narrator@example.com", "password123", "Narrator Display");
        auto book = std::make_shared<AudioBook>("Test Book", 3600, 1, author, narrator);
        book->registerWithAuthorAndNarrator();

        book->addChapter("Chapter 1");
        book->addChapter("Chapter 2");

        book->setCurrentChapter(1);
                CHECK_EQUAL("Chapter 2", book->getCurrentChapter());

                CHECK_THROW(book->setCurrentChapter(2), ExceptionIncorrectChapterNumber);
    }

    TEST(GetCurrentChapterNoChapters) {
        auto author = std::make_shared<BookAuthor>("author1", "Author", "author@example.com", "password123");
        auto narrator = std::make_shared<Broadcaster>("narrator1", "Narrator", "narrator@example.com", "password123", "Narrator Display");
        auto book = std::make_shared<AudioBook>("Test Book", 3600, 1, author, narrator);
        book->registerWithAuthorAndNarrator();

                CHECK_THROW(book->getCurrentChapter(), ExceptionIncorrectAudioBookChapters);
    }

    TEST(AuthorAndNarratorRelationships) {
        auto author = std::make_shared<BookAuthor>("author1", "Author", "author@example.com", "password123");
        auto narrator = std::make_shared<Broadcaster>("narrator1", "Narrator", "narrator@example.com", "password123", "Narrator Display");
        auto book = std::make_shared<AudioBook>("Test Book", 3600, 1, author, narrator);
        book->registerWithAuthorAndNarrator();

        auto authorBooks = author->getPublishedTitles();
                CHECK_EQUAL(1, authorBooks.size());
                CHECK_EQUAL(book->getName(), authorBooks[0]);

        auto narratorBooks = narrator->getNarratedTitles();
                CHECK_EQUAL(1, narratorBooks.size());
                CHECK_EQUAL(book->getName(), narratorBooks[0]);
    }

    TEST(EmptyAuthorName) {
        auto author = std::make_shared<BookAuthor>("", "", "author@example.com", "password123");
        auto narrator = std::make_shared<Broadcaster>("narrator1", "Narrator", "narrator@example.com", "password123", "Narrator Display");
        auto book = std::make_shared<AudioBook>("Test Book", 3600, 1, author, narrator);
        book->registerWithAuthorAndNarrator();

                CHECK_EQUAL("", book->getAuthor());
    }
}