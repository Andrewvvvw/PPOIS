#include "MergeSort.h"
#include "../User.h"
#include <UnitTest++.h>
#include <vector>
#include <string>
#include <algorithm>

SUITE(MergeSortTests) {
    TEST(SortEmptyVector) {
        std::vector<int> empty;
        mergeSort(empty);
        CHECK(empty.empty());
    }

    TEST(SortSingleElementVector) {
        std::vector<int> single = {42};
        mergeSort(single);
        CHECK_EQUAL(42, single[0]);
    }

    TEST(SortAlreadySortedVector) {
        std::vector<int> sorted = {1, 2, 3, 4, 5};
        mergeSort(sorted);
        CHECK(std::is_sorted(sorted.begin(), sorted.end()));
    }

    TEST(SortReverseSortedVector) {
        std::vector<int> reverse = {5, 4, 3, 2, 1};
        mergeSort(reverse);
        CHECK(std::is_sorted(reverse.begin(), reverse.end()));
    }

    TEST(SortRandomOrderVector) {
        std::vector<int> random = {3, 1, 4, 1, 5, 9, 2, 6, 5};
        mergeSort(random);
        CHECK(std::is_sorted(random.begin(), random.end()));
    }

    TEST(SortVectorWithDuplicates) {
        std::vector<int> withDups = {3, 1, 4, 1, 4, 5, 2, 6, 5};
        mergeSort(withDups);
        CHECK(std::is_sorted(withDups.begin(), withDups.end()));
    }

    TEST(SortVectorOfStrings) {
        std::vector<std::string> strings = {"banana", "apple", "cherry", "date"};
        mergeSort(strings);
        CHECK(std::is_sorted(strings.begin(), strings.end()));
    }

    TEST(SortVectorOfUsers) {
        std::vector <User> users = {
                User("Alice", 25, 1003),
                User("Bob", 30, 1001),
                User("Charlie", 20, 1002)
        };

        mergeSort(users);

                CHECK_EQUAL(1001, users[0].getId());
                CHECK_EQUAL(1002, users[1].getId());
                CHECK_EQUAL(1003, users[2].getId());
    }

    TEST(SortEmptyArray) {
        int* empty = new int[0];
        mergeSort(empty, 0);
        delete[] empty;
    }

    TEST(SortSingleElementArray) {
        int* single = new int[1];
        single[0] = 42;
        mergeSort(single, 1);
        CHECK_EQUAL(42, single[0]);
        delete[] single;
    }

    TEST(SortAlreadySortedArray) {
        int sorted[] = {1, 2, 3, 4, 5};
        mergeSort(sorted, 5);
        CHECK(std::is_sorted(sorted, sorted + 5));
    }

    TEST(SortReverseSortedArray) {
        int reverse[] = {5, 4, 3, 2, 1};
        mergeSort(reverse, 5);
        CHECK(std::is_sorted(reverse, reverse + 5));
    }

    TEST(SortRandomOrderArray) {
        int random[] = {3, 1, 4, 1, 5, 9, 2, 6, 5};
        const size_t size = sizeof(random) / sizeof(random[0]);
        mergeSort(random, size);
        CHECK(std::is_sorted(random, random + size));
    }

    TEST(SortArrayOfUsers) {
        User* users = new User[3] {
                {"Alice", 25, 1003},
                {"Bob", 30, 1001},
                {"Charlie", 20, 1002}
        };

        mergeSort(users, 3);

                CHECK_EQUAL(1001, users[0].getId());
                CHECK_EQUAL(1002, users[1].getId());
                CHECK_EQUAL(1003, users[2].getId());

        delete[] users;
    }

    TEST(SortVectorWithEqualElements) {
        std::vector<int> equal = {1, 1, 1, 1, 1};
        mergeSort(equal);
        CHECK(std::is_sorted(equal.begin(), equal.end()));
    }

    TEST(SortVectorWithTwoElements) {
        std::vector<int> two = {2, 1};
        mergeSort(two);
        CHECK(std::is_sorted(two.begin(), two.end()));
    }

    TEST(SortVectorWithThreeElements) {
        std::vector<int> three = {3, 1, 2};
        mergeSort(three);
        CHECK(std::is_sorted(three.begin(), three.end()));
    }

    TEST(SortVectorWithLargeSize) {
        std::vector<int> large(1000);
        for (int i = 0; i < 1000; ++i) {
            large[i] = 999 - i;
        }
        mergeSort(large);
        CHECK(std::is_sorted(large.begin(), large.end()));
    }
}
