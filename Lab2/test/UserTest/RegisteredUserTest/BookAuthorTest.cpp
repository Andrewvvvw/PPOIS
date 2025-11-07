#include "UnitTest++.h"
#include "../../src/User/RegisteredUser/BookAuthor/BookAuthor.h"
#include "../../src/Audio/AudioBook/AudioBook.h"

SUITE(BookAuthorTest) {
    TEST(ConstructorAndGetters) {
        BookAuthor author("auth123", "johndoe", "john@example.com", "password123");
        CHECK_EQUAL("johndoe", author.getUsername());
        CHECK_EQUAL("john@example.com", author.getEmail());
        CHECK_EQUAL("auth123", author.getId());
        CHECK_EQUAL("BookAuthor", author.getUserType());
        CHECK(author.canUploadContent());
    }

    TEST(UpdateBiography) {
        BookAuthor author("auth123", "johndoe", "john@example.com", "password123");
        author.updateBiography("Best-selling author of sci-fi novels");
        CHECK_EQUAL("Best-selling author of sci-fi novels", author.getBiography());

        author.updateBiography("");
        CHECK_EQUAL("", author.getBiography());
    }

    TEST(UpdatePrimaryGenre) {
        BookAuthor author("auth123", "johndoe", "john@example.com", "password123");
        author.updatePrimaryGenre("Science Fiction");
        CHECK_EQUAL("Science Fiction", author.getPrimaryGenre());

        author.updatePrimaryGenre("");
        CHECK_EQUAL("", author.getPrimaryGenre());
    }

    TEST(PublishBook) {
        auto author = std::make_shared<BookAuthor>("auth123", "johndoe", "john@example.com", "password123");
        auto narrator = std::make_shared<Broadcaster>("narr1", "narrator1", "narr@example.com", "pass123", "Narrator One");
        auto book1 = std::make_shared<AudioBook>("Book 1", 3600, 1, author, narrator);
        auto book2 = std::make_shared<AudioBook>("Book 2", 7200, 2, author, narrator);

                CHECK(author->publishBook(book1));
                CHECK(author->publishBook(book2));

        auto book1Clone = std::make_shared<AudioBook>("Book 1", 3600, 1, author, narrator);
                CHECK(!author->publishBook(book1Clone));

                CHECK(!author->publishBook(nullptr));

        auto titles = author->getPublishedTitles();
                CHECK_EQUAL(2, titles.size());
                CHECK(std::find(titles.begin(), titles.end(), "Book 1") != titles.end());
                CHECK(std::find(titles.begin(), titles.end(), "Book 2") != titles.end());
    }

    TEST(RemoveBook) {
        auto author = std::make_shared<BookAuthor>("auth123", "johndoe", "john@example.com", "password123");
        auto narrator = std::make_shared<Broadcaster>("narr1", "narrator1", "narr@example.com", "pass123", "Narrator One");
        auto book1 = std::make_shared<AudioBook>("Book 1", 3600, 1, author, narrator);
        auto book2 = std::make_shared<AudioBook>("Book 2", 7200, 2, author, narrator);

        author->publishBook(book1);
        author->publishBook(book2);

                CHECK(author->removeBook("Book 1"));
                CHECK(!author->removeBook("Nonexistent Book"));

        auto titles = author->getPublishedTitles();
                CHECK_EQUAL(1, titles.size());
                CHECK_EQUAL("Book 2", titles[0]);
    }

    TEST(GetBook) {
        auto author = std::make_shared<BookAuthor>("auth123", "johndoe", "john@example.com", "password123");
        auto narrator = std::make_shared<Broadcaster>("narr1", "narrator1", "narr@example.com", "pass123", "Narrator One");
        auto book1 = std::make_shared<AudioBook>("Book 1", 3600, 1, author, narrator);

        author->publishBook(book1);

        auto foundBook = author->getBook("Book 1");
                CHECK(foundBook != nullptr);
                CHECK_EQUAL("Book 1", foundBook->getName());

        auto notFoundBook = author->getBook("Nonexistent Book");
                CHECK(notFoundBook == nullptr);
    }

    TEST(GetPublishedTitles) {
        auto author = std::make_shared<BookAuthor>("auth123", "johndoe", "john@example.com", "password123");
        auto narrator = std::make_shared<Broadcaster>("narr1", "narrator1", "narr@example.com", "pass123", "Narrator One");

                CHECK(author->getPublishedTitles().empty());

        auto book1 = std::make_shared<AudioBook>("Book A", 3600, 1, author, narrator);
        auto book2 = std::make_shared<AudioBook>("Book B", 7200, 2, author, narrator);

        author->publishBook(book1);
        author->publishBook(book2);

        auto titles = author->getPublishedTitles();
                CHECK_EQUAL(2, titles.size());
                CHECK(std::find(titles.begin(), titles.end(), "Book A") != titles.end());
                CHECK(std::find(titles.begin(), titles.end(), "Book B") != titles.end());
    }

    TEST(GetUserTypeAndUploadPermission) {
        BookAuthor author("auth123", "johndoe", "john@example.com", "password123");
        CHECK_EQUAL("BookAuthor", author.getUserType());
        CHECK(author.canUploadContent());
    }
}
