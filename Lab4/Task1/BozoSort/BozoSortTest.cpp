#include "UnitTest++.h"
#include <vector>
#include "BozoSort.h"
#include "Utils.h"
#include "../User.h"
#include <string>
#include <algorithm>

SUITE(BozoSortTest) {
    TEST(SortEmptyVector) {
        std::vector<int> emptyVec;
        bozoSort(emptyVec);
                CHECK(emptyVec.empty());

        int emptyArr[0] = {};
        bozoSort(emptyArr, 0);
    }

    TEST(SortSingleElementVector) {
        std::vector<int> single = {42};
        bozoSort(single);
                CHECK_EQUAL(42, single[0]);

        int singleArr[1] = {42};
        bozoSort(singleArr, 1);
                CHECK_EQUAL(42, singleArr[0]);
    }

    TEST(SortAlreadySortedVector) {
        std::vector<int> sorted = {1, 2, 3, 4, 5};
        bozoSort(sorted);
                CHECK(isVectorSorted(sorted));

        int sortedArr[] = {1, 2, 3, 4, 5};
        bozoSort(sortedArr, 5);
                CHECK(isArraySorted(sortedArr, 5));
    }

    TEST(SortReverseSortedVector) {
        std::vector<int> reverse = {5, 4, 3, 2, 1};
        bozoSort(reverse);
                CHECK(isVectorSorted(reverse));

        int reverseArr[] = {5, 4, 3, 2, 1};
        bozoSort(reverseArr, 5);
                CHECK(isArraySorted(reverseArr, 5));
    }

    TEST(SortRandomVector) {
        std::vector<int> random = {3, 1, 4, 1, 5, 9, 2, 6, 5};
        bozoSort(random);
                CHECK(isVectorSorted(random));

        int randomArr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5};
        bozoSort(randomArr, 9);
                CHECK(isArraySorted(randomArr, 9));
    }

    TEST(SortVectorWithDuplicates) {
        std::vector<int> withDups = {2, 2, 1, 1, 3, 3, 2};
        bozoSort(withDups);
                CHECK(isVectorSorted(withDups));

        int withDupsArr[] = {2, 2, 1, 1, 3, 3, 2};
        bozoSort(withDupsArr, 7);
                CHECK(isArraySorted(withDupsArr, 7));
    }

    TEST(SortDoubleVector) {
        std::vector<double> doubles = {3.14, 1.41, 2.71, 0.58, 1.73};
        bozoSort(doubles);
                CHECK(isVectorSorted(doubles));

        double doublesArr[] = {3.14, 1.41, 2.71, 0.58, 1.73};
        bozoSort(doublesArr, 5);
                CHECK(isArraySorted(doublesArr, 5));
    }

    TEST(SortUserVector) {
        std::vector<User> users = {
                User("Alice", 25, 3),
                User("Bob", 30, 1),
                User("Charlie", 20, 2)
        };

        bozoSort(users);
                CHECK(isVectorSorted(users));

        User usersArr[3] = {
                User("Alice", 25, 3),
                User("Bob", 30, 1),
                User("Charlie", 20, 2)
        };

        bozoSort(usersArr, 3);
                CHECK(isArraySorted(usersArr, 3));
    }

}