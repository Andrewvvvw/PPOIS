#include "UnitTest++.h"
#include "..\..\..\src\User\RegisteredUser\Broadcaster\Broadcaster.h"
#include "..\..\..\src\Audio\AudioBook\AudioBook.h"

using namespace std;

SUITE(BroadcasterTest) {
    TEST(ConstructorAndGetters) {
        Broadcaster broadcaster("id1", "test_user", "test@example.com", "password123", "Test Broadcaster");

        CHECK_EQUAL("id1", broadcaster.getId());
        CHECK_EQUAL("test_user", broadcaster.getUsername());
        CHECK_EQUAL("test@example.com", broadcaster.getEmail());
        CHECK_EQUAL("password123", broadcaster.getPassword());
        CHECK_EQUAL("Test Broadcaster", broadcaster.getDisplayName());
        CHECK_EQUAL("", broadcaster.getNarrationStyle());
        CHECK_EQUAL(0u, broadcaster.getYearsOfExperience());
        CHECK_EQUAL("Broadcaster", broadcaster.getUserType());
        CHECK(broadcaster.canUploadContent());
    }

    TEST(UpdateNarrationStyle) {
        Broadcaster broadcaster("id1", "test_user", "test@example.com", "password123", "Test Broadcaster");

        broadcaster.updateNarrationStyle("Dramatic");
        CHECK_EQUAL("Dramatic", broadcaster.getNarrationStyle());

        broadcaster.updateNarrationStyle("Calm and soothing");
        CHECK_EQUAL("Calm and soothing", broadcaster.getNarrationStyle());
    }

    TEST(UpdateExperience) {
        Broadcaster broadcaster("id1", "test_user", "test@example.com", "password123", "Test Broadcaster");

        broadcaster.updateExperience(5);
        CHECK_EQUAL(5u, broadcaster.getYearsOfExperience());

        broadcaster.updateExperience(10);
        CHECK_EQUAL(10u, broadcaster.getYearsOfExperience());
    }

    TEST(AddNarratedBook) {
        auto author = make_shared<BookAuthor>("a1", "author1", "author@example.com", "pass123");
        auto broadcaster = make_shared<Broadcaster>("b1", "broadcaster1", "broadcaster@example.com", "pass123", "Broadcaster One");
        auto book1 = make_shared<AudioBook>("Book 1", 3600, 1, author, broadcaster);
        auto book2 = make_shared<AudioBook>("Book 2", 7200, 2, author, broadcaster);

        CHECK(broadcaster->addNarratedBook(book1));
        CHECK_EQUAL(1u, broadcaster->getNarratedTitles().size());

        CHECK(broadcaster->addNarratedBook(book2));
        CHECK_EQUAL(2u, broadcaster->getNarratedTitles().size());

        CHECK(!broadcaster->addNarratedBook(book1));
        CHECK_EQUAL(2u, broadcaster->getNarratedTitles().size());

        CHECK(!broadcaster->addNarratedBook(nullptr));
    }

    TEST(RemoveNarratedBook) {
        auto author = make_shared<BookAuthor>("a1", "author1", "author@example.com", "pass123");
        auto broadcaster = make_shared<Broadcaster>("b1", "broadcaster1", "broadcaster@example.com", "pass123", "Broadcaster One");
        auto book1 = make_shared<AudioBook>("Book 1", 3600, 1, author, broadcaster);

        broadcaster->addNarratedBook(book1);
        CHECK_EQUAL(1u, broadcaster->getNarratedTitles().size());

        CHECK(broadcaster->removeNarratedBook("Book 1"));
        CHECK_EQUAL(0u, broadcaster->getNarratedTitles().size());

        CHECK(!broadcaster->removeNarratedBook("Nonexistent Book"));
    }

    TEST(GetNarratedTitles) {
        auto author = make_shared<BookAuthor>("a1", "author1", "author@example.com", "pass123");
        auto broadcaster = make_shared<Broadcaster>("b1", "broadcaster1", "broadcaster@example.com", "pass123", "Broadcaster One");
        auto book1 = make_shared<AudioBook>("Book 1", 3600, 1, author, broadcaster);
        auto book2 = make_shared<AudioBook>("Book 2", 7200, 2, author, broadcaster);

        broadcaster->addNarratedBook(book1);
        broadcaster->addNarratedBook(book2);

        auto titles = broadcaster->getNarratedTitles();
        CHECK_EQUAL(2u, titles.size());
        CHECK(find(titles.begin(), titles.end(), "Book 1") != titles.end());
        CHECK(find(titles.begin(), titles.end(), "Book 2") != titles.end());
    }

    TEST(GetNarratedBook) {
        auto author = make_shared<BookAuthor>("a1", "author1", "author@example.com", "pass123");
        auto broadcaster = make_shared<Broadcaster>("b1", "broadcaster1", "broadcaster@example.com", "pass123", "Broadcaster One");
        auto book1 = make_shared<AudioBook>("Book 1", 3600, 1, author, broadcaster);

        broadcaster->addNarratedBook(book1);

        auto foundBook = broadcaster->getNarratedBook("Book 1");
        CHECK(foundBook != nullptr);
        CHECK_EQUAL("Book 1", foundBook->getName());

        auto notFoundBook = broadcaster->getNarratedBook("Nonexistent Book");
        CHECK(notFoundBook == nullptr);
    }

    TEST(GetNarratedBookEmpty) {
        Broadcaster broadcaster("id1", "test_user", "test@example.com", "password123", "Test Broadcaster");

        auto notFoundBook = broadcaster.getNarratedBook("Nonexistent Book");
        CHECK(notFoundBook == nullptr);
    }
}
