#include "UnitTest++.h"
#include "../../src/AudioCollection/AuthorizationManager/AuthorizationManager.h"
#include "../../src/User/RegisteredUser/RegisteredUser.h"

SUITE(AuthorizationManagerTest) {
    TEST(TestConstructor) {
        AuthorizationManager authManager(3);
                CHECK_EQUAL(false, authManager.login("test@example.com", "password"));
    }

    TEST(TestRegisterUser) {
        AuthorizationManager authManager(3);
        RegisteredUser user("1", "testuser", "test@example.com", "password123");

        bool result = authManager.registerUser(user);
                CHECK_EQUAL(true, result);

        bool duplicateResult = authManager.registerUser(user);
                CHECK_EQUAL(false, duplicateResult);
    }

    TEST(TestLoginSuccess) {
        AuthorizationManager authManager(3);
        RegisteredUser user("1", "testuser", "test@example.com", "password123");
        authManager.registerUser(user);

        bool loginResult = authManager.login("test@example.com", "password123");
                CHECK_EQUAL(true, loginResult);
    }

    TEST(TestLoginWrongPassword) {
        AuthorizationManager authManager(3);
        RegisteredUser user("1", "testuser", "test@example.com", "password123");
        authManager.registerUser(user);

        bool loginResult = authManager.login("test@example.com", "wrongpassword");
                CHECK_EQUAL(false, loginResult);
    }

    TEST(TestLoginNonExistentUser) {
        AuthorizationManager authManager(3);
        bool loginResult = authManager.login("nonexistent@example.com", "password");
                CHECK_EQUAL(false, loginResult);
    }

    TEST(TestMultipleUsers) {
        AuthorizationManager authManager(3);
        RegisteredUser user1("1", "user1", "user1@example.com", "pass1");
        RegisteredUser user2("2", "user2", "user2@example.com", "pass2");

        authManager.registerUser(user1);
        authManager.registerUser(user2);

                CHECK_EQUAL(true, authManager.login("user1@example.com", "pass1"));
                CHECK_EQUAL(true, authManager.login("user2@example.com", "pass2"));
                CHECK_EQUAL(false, authManager.login("user1@example.com", "wrongpass"));
                CHECK_EQUAL(false, authManager.login("user2@example.com", "wrongpass"));
    }

    TEST(TestEmptyCredentials) {
        AuthorizationManager authManager(3);
        RegisteredUser user("0", "", "", "");

        bool registerResult = authManager.registerUser(user);
                CHECK_EQUAL(true, registerResult);

        bool loginResult = authManager.login("", "");
                CHECK_EQUAL(true, loginResult);
    }

    TEST(TestCaseSensitiveLogin) {
        AuthorizationManager authManager(3);
        RegisteredUser user("1", "testuser", "Test@Example.com", "Password123");
        authManager.registerUser(user);

                CHECK_EQUAL(true, authManager.login("Test@Example.com", "Password123"));
                CHECK_EQUAL(false, authManager.login("test@example.com", "Password123"));
                CHECK_EQUAL(false, authManager.login("Test@Example.com", "password123"));
    }
}