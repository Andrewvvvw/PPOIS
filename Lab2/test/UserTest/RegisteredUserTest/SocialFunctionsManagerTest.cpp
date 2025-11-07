#include "UnitTest++.h"
#include "../../../src/User/RegisteredUser/RegisteredUser.h"
#include "../../../src/Audio/AudioBook/AudioBook.h"
#include "../../../src/User/RegisteredUser/BookAuthor/BookAuthor.h"
#include "../../../src/User/RegisteredUser/Broadcaster/Broadcaster.h"
#include <memory>

TEST(SocialFunctionsManager_FollowUser) {
    auto user1 = std::make_shared<RegisteredUser>("1", "user1", "user1@test.com", "pass1");
    auto user2 = std::make_shared<RegisteredUser>("2", "user2", "user2@test.com", "pass2");

    user1->getSocialFunctionsManager()->followUser(user2);

    auto following = user1->getSocialFunctionsManager()->getFollowing();
    auto followers = user2->getSocialFunctionsManager()->getFollowers();

            CHECK_EQUAL(1, following.size());
            CHECK_EQUAL(1, followers.size());
            CHECK_EQUAL("user2", following[0]->getUsername());
            CHECK_EQUAL("user1", followers[0]->getUsername());
}

TEST(SocialFunctionsManager_UnfollowUser) {
    auto user1 = std::make_shared<RegisteredUser>("1", "user1", "user1@test.com", "pass1");
    auto user2 = std::make_shared<RegisteredUser>("2", "user2", "user2@test.com", "pass2");

    user1->getSocialFunctionsManager()->followUser(user2);
    user1->getSocialFunctionsManager()->unfollowUser(user2);

    auto following = user1->getSocialFunctionsManager()->getFollowing();
    auto followers = user2->getSocialFunctionsManager()->getFollowers();

            CHECK_EQUAL(0, following.size());
            CHECK_EQUAL(0, followers.size());
}

TEST(SocialFunctionsManager_UnfollowNonFollowedUser) {
    auto user1 = std::make_shared<RegisteredUser>("1", "user1", "user1@test.com", "pass1");
    auto user2 = std::make_shared<RegisteredUser>("2", "user2", "user2@test.com", "pass2");
    auto user3 = std::make_shared<RegisteredUser>("3", "user3", "user3@test.com", "pass3");

    user1->getSocialFunctionsManager()->followUser(user2);
    user1->getSocialFunctionsManager()->unfollowUser(user3);

    auto following = user1->getSocialFunctionsManager()->getFollowing();
    auto followers2 = user2->getSocialFunctionsManager()->getFollowers();
    auto followers3 = user3->getSocialFunctionsManager()->getFollowers();

            CHECK_EQUAL(1, following.size());
            CHECK_EQUAL(1, followers2.size());
            CHECK_EQUAL(0, followers3.size());
}

TEST(SocialFunctionsManager_LikeAudio) {
    auto user = std::make_shared<RegisteredUser>("1", "user1", "user1@test.com", "pass1");
    auto author = std::make_shared<BookAuthor>("auth1", "author", "author@test.com", "pass123");
    auto narrator = std::make_shared<Broadcaster>("narr1", "narrator", "narrator@test.com", "pass123", "Narrator Name");
    auto book = std::make_shared<AudioBook>("Test Book", 300, 123, author, narrator);

    user->getSocialFunctionsManager()->likeAudio(book);
    auto liked = user->getSocialFunctionsManager()->getLikedAudio();

            CHECK_EQUAL(1, liked.size());
    if (!liked.empty()) {
                CHECK_EQUAL("Test Book", liked[0]->getName());
                CHECK_EQUAL(300, liked[0]->getDuration());
                CHECK_EQUAL(123, liked[0]->getCoverID());
    }
}

TEST(SocialFunctionsManager_UnlikeAudio) {
    auto user = std::make_shared<RegisteredUser>("1", "user1", "user1@test.com", "pass1");
    auto author1 = std::make_shared<BookAuthor>("auth1", "author1", "author1@test.com", "pass123");
    auto narrator1 = std::make_shared<Broadcaster>("narr1", "narrator1", "narrator1@test.com", "pass123", "Narrator 1");
    auto author2 = std::make_shared<BookAuthor>("auth2", "author2", "author2@test.com", "pass123");
    auto narrator2 = std::make_shared<Broadcaster>("narr2", "narrator2", "narrator2@test.com", "pass123", "Narrator 2");

    auto book1 = std::make_shared<AudioBook>("Test Book 1", 300, 123, author1, narrator1);
    auto book2 = std::make_shared<AudioBook>("Test Book 2", 200, 124, author2, narrator2);

    user->getSocialFunctionsManager()->likeAudio(book1);
    user->getSocialFunctionsManager()->likeAudio(book2);
    user->getSocialFunctionsManager()->unlikeAudio(book1);

    auto liked = user->getSocialFunctionsManager()->getLikedAudio();

            CHECK_EQUAL(1, liked.size());
    if (!liked.empty()) {
                CHECK_EQUAL("Test Book 2", liked[0]->getName());
    }
}

TEST(SocialFunctionsManager_UnlikeNonLikedAudio) {
    auto user = std::make_shared<RegisteredUser>("1", "user1", "user1@test.com", "pass1");
    auto author1 = std::make_shared<BookAuthor>("auth1", "author1", "author1@test.com", "pass123");
    auto narrator1 = std::make_shared<Broadcaster>("narr1", "narrator1", "narrator1@test.com", "pass123", "Narrator 1");
    auto author2 = std::make_shared<BookAuthor>("auth2", "author2", "author2@test.com", "pass123");
    auto narrator2 = std::make_shared<Broadcaster>("narr2", "narrator2", "narrator2@test.com", "pass123", "Narrator 2");

    auto book1 = std::make_shared<AudioBook>("Test Book 1", 300, 123, author1, narrator1);
    auto book2 = std::make_shared<AudioBook>("Test Book 2", 200, 124, author2, narrator2);

    user->getSocialFunctionsManager()->likeAudio(book1);
    user->getSocialFunctionsManager()->unlikeAudio(book2);

    auto liked = user->getSocialFunctionsManager()->getLikedAudio();

            CHECK_EQUAL(1, liked.size());
    if (!liked.empty()) {
                CHECK_EQUAL("Test Book 1", liked[0]->getName());
    }
}

TEST(SocialFunctionsManager_GetFollowingEmpty) {
    auto user = std::make_shared<RegisteredUser>("1", "user1", "user1@test.com", "pass1");
    auto following = user->getSocialFunctionsManager()->getFollowing();
            CHECK_EQUAL(0, following.size());
}

TEST(SocialFunctionsManager_GetFollowersEmpty) {
    auto user = std::make_shared<RegisteredUser>("1", "user1", "user1@test.com", "pass1");
    auto followers = user->getSocialFunctionsManager()->getFollowers();
            CHECK_EQUAL(0, followers.size());
}

TEST(SocialFunctionsManager_GetLikedAudioEmpty) {
    auto user = std::make_shared<RegisteredUser>("1", "user1", "user1@test.com", "pass1");
    auto liked = user->getSocialFunctionsManager()->getLikedAudio();
            CHECK_EQUAL(0, liked.size());
}