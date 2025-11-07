#include "UnitTest++.h"
#include "../../../src/User/RegisteredUser/RegisteredUser.h"
#include "../../../src/Audio/Album/MusicTrack/MusicTrack.h"
#include "../../src/Exceptions/Exceptions.h"

SUITE(RegisteredUserTest) {
    TEST(Constructor) {
        RegisteredUser user("user1", "testuser", "test@example.com", "password123");

                CHECK_EQUAL("user1", user.getId());
                CHECK_EQUAL("testuser", user.getUsername());
                CHECK_EQUAL("test@example.com", user.getEmail());
                CHECK_EQUAL("password123", user.getPassword());
                CHECK_EQUAL("RegisteredUser", user.getUserType());
                CHECK_EQUAL(false, user.getIsPremium());
                CHECK_EQUAL(true, user.canComment());
                CHECK_EQUAL(false, user.canUploadContent());
    }

    TEST(SetEmail) {
        RegisteredUser user("user1", "testuser", "test@example.com", "password123");
        user.setEmail("new@example.com");
                CHECK_EQUAL("new@example.com", user.getEmail());
    }

    TEST(SetPassword) {
        RegisteredUser user("user1", "testuser", "test@example.com", "password123");
        user.setPassword("newpassword");
                CHECK_EQUAL("newpassword", user.getPassword());
    }

    TEST(SetPremium) {
        RegisteredUser user("user1", "testuser", "test@example.com", "password123");

        CHECK_THROW(user.setPremium(true), ExceptionNotEnoughMoney);
        CHECK_THROW(user.setPremium(false),std::runtime_error);
    }

    TEST(FavoriteListOperations) {
        RegisteredUser user("user1", "testuser", "test@example.com", "password123");
        auto audio1 = std::make_shared<MusicTrack>("Track 1", 180, 1, "Artist 1", "Pop", 2023);
        auto audio2 = std::make_shared<MusicTrack>("Track 2", 200, 2, "Artist 2", "Rock", 2023);

        user.addToFavorites(audio1);
        user.addToFavorites(audio2);

        auto favorites = user.getFavoriteTracks();
                CHECK_EQUAL(2, favorites.size());
                CHECK_EQUAL(audio1, favorites[0]);
                CHECK_EQUAL(audio2, favorites[1]);

        user.removeFromFavorites(audio1);
        favorites = user.getFavoriteTracks();
                CHECK_EQUAL(1, favorites.size());
                CHECK_EQUAL(audio2, favorites[0]);
    }

    TEST(RemoveNonExistentFavorite) {
        RegisteredUser user("user1", "testuser", "test@example.com", "password123");
        auto audio1 = std::make_shared<MusicTrack>("Track 1", 180, 1, "Artist 1", "Pop", 2023);
        auto audio2 = std::make_shared<MusicTrack>("Track 2", 200, 2, "Artist 2", "Rock", 2023);

        user.addToFavorites(audio1);
        user.removeFromFavorites(audio2);

        auto favorites = user.getFavoriteTracks();
                CHECK_EQUAL(1, favorites.size());
                CHECK_EQUAL(audio1, favorites[0]);
    }

    TEST(GetEmptyFavoriteList) {
        RegisteredUser user("user1", "testuser", "test@example.com", "password123");
        auto favorites = user.getFavoriteTracks();
                CHECK(favorites.empty());
    }

    TEST(AddSameFavoriteMultipleTimes) {
        RegisteredUser user("user1", "testuser", "test@example.com", "password123");
        auto audio = std::make_shared<MusicTrack>("Track 1", 180, 1, "Artist", "Pop", 2023);

        user.addToFavorites(audio);
        user.addToFavorites(audio);

        auto favorites = user.getFavoriteTracks();
                CHECK_EQUAL(2, favorites.size());
                CHECK_EQUAL(audio, favorites[0]);
                CHECK_EQUAL(audio, favorites[1]);
    }
}