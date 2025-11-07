#include "UnitTest++.h"
#include "../../../src/User/RegisteredUser/RadioHost/RadioHost.h"
#include "../../../src/Audio/Radio/Radio.h"

SUITE(RadioHostTest) {
    TEST(Constructor) {
        RadioHost host("host1", "radio_host", "host@radio.com", "password123", "Pop", "Best Hits");
                CHECK_EQUAL("host1", host.getId());
                CHECK_EQUAL("radio_host", host.getUsername());
                CHECK_EQUAL("host@radio.com", host.getEmail());
                CHECK_EQUAL("password123", host.getPassword());
                CHECK_EQUAL("Pop", host.getFavoriteGenre());
                CHECK_EQUAL("Best Hits", host.getFavoriteStation());
                CHECK(host.getHostedRadios().empty());
    }

    TEST(AddRadio) {
        auto host = std::make_shared<RadioHost>("h1", "host", "test@test.com", "pass", "Rock", "Rock FM");
        auto radio = std::make_shared<Radio>("Rock", "Rock FM", host, "Morning Show", "Best rock hits", 1);

        host->addRadio(radio);
        auto radios = host->getHostedRadios();

                CHECK_EQUAL(1, radios.size());
                CHECK_EQUAL(radio, radios[0]);
    }

    TEST(RemoveRadio) {
        auto host = std::make_shared<RadioHost>("h1", "host", "test@test.com", "pass", "Rock", "Rock FM");
        auto radio1 = std::make_shared<Radio>("Rock", "Rock FM", host, "Morning Show", "Best rock hits", 1);
        auto radio2 = std::make_shared<Radio>("Pop", "Pop FM", host, "Afternoon Show", "Top 40", 2);

        host->addRadio(radio1);
        host->addRadio(radio2);
        host->removeRadio(radio1);

        auto radios = host->getHostedRadios();

                CHECK_EQUAL(1, radios.size());
                CHECK_EQUAL(radio2, radios[0]);
    }

    TEST(SetFavoriteGenre) {
        RadioHost host("h1", "host", "test@test.com", "pass", "Rock", "Rock FM");
        host.setFavoriteGenre("Jazz");
                CHECK_EQUAL("Jazz", host.getFavoriteGenre());
    }

    TEST(SetFavoriteStation) {
        RadioHost host("h1", "host", "test@test.com", "pass", "Rock", "Rock FM");
        host.setFavoriteStation("Jazz FM");
                CHECK_EQUAL("Jazz FM", host.getFavoriteStation());
    }

    TEST(GetHostedRadios_MultipleRadios) {
        auto host = std::make_shared<RadioHost>("h1", "host", "test@test.com", "pass", "Rock", "Rock FM");
        auto radio1 = std::make_shared<Radio>("Rock", "Rock FM", host, "Morning Show", "Best rock hits", 1);
        auto radio2 = std::make_shared<Radio>("Pop", "Pop FM", host, "Afternoon Show", "Top 40", 2);

        host->addRadio(radio1);
        host->addRadio(radio2);

        auto radios = host->getHostedRadios();

                CHECK_EQUAL(2, radios.size());
                CHECK_EQUAL(radio1, radios[0]);
                CHECK_EQUAL(radio2, radios[1]);
    }

    TEST(RemoveNonExistentRadio) {
        auto host = std::make_shared<RadioHost>("h1", "host", "test@test.com", "pass", "Rock", "Rock FM");
        auto radio1 = std::make_shared<Radio>("Rock", "Rock FM", host, "Morning Show", "Best rock hits", 1);
        auto radio2 = std::make_shared<Radio>("Pop", "Pop FM", host, "Afternoon Show", "Top 40", 2);

        host->addRadio(radio1);
        host->removeRadio(radio2);

        auto radios = host->getHostedRadios();
                CHECK_EQUAL(1, radios.size());
                CHECK_EQUAL(radio1, radios[0]);
    }

    TEST(AddSameRadioMultipleTimes) {
        auto host = std::make_shared<RadioHost>("h1", "host", "test@test.com", "pass", "Rock", "Rock FM");
        auto radio = std::make_shared<Radio>("Rock", "Rock FM", host, "Morning Show", "Best rock hits", 1);

        host->addRadio(radio);
        host->addRadio(radio);

        auto radios = host->getHostedRadios();
                CHECK_EQUAL(2, radios.size());
                CHECK_EQUAL(radio, radios[0]);
                CHECK_EQUAL(radio, radios[1]);
    }
}