#include "UnitTest++.h"
#include "..\..\Source\Report\EmployeePerformanceReport\EmployeePerformanceReport.h"

SUITE(EmployeePerformanceReportTest) {
    TEST(TestConstructor) {
        EmployeePerformanceReport report("Test User", 123);

        CHECK_EQUAL("Employee Performance Report", report.getTitle());
        CHECK_EQUAL("Test User", report.getGeneratedBy());
        CHECK(report.validate());
        CHECK_EQUAL(0.0, report.getOverallRating());
        CHECK_EQUAL(0, report.getTotalTasksCompleted());
        CHECK(report.getPerformanceMetrics().empty());
        CHECK(!report.getIsFinalized());
    }

    TEST(TestAddMetric) {
        EmployeePerformanceReport report("Test User", 123);

        report.addMetric("Efficiency", 85.5);
        report.addMetric("Quality", 92.0);

        const auto& metrics = report.getPerformanceMetrics();
        CHECK_EQUAL(2, metrics.size());
        CHECK_CLOSE(85.5, metrics.at("Efficiency"), 0.001);
        CHECK_CLOSE(92.0, metrics.at("Quality"), 0.001);
    }

    TEST(TestUpdateRating) {
        EmployeePerformanceReport report("Test User", 123);

        report.addMetric("Efficiency", 80.0);
        report.addMetric("Quality", 90.0);

        CHECK_CLOSE(85.0, report.getOverallRating(), 0.001);

        report.addMetric("Punctuality", 100.0);
        CHECK_CLOSE(90.0, report.getOverallRating(), 0.001);
    }

    TEST(TestUpdateRatingWithNoMetrics) {
        EmployeePerformanceReport report("Test User", 123);

        CHECK_EQUAL(0.0, report.getOverallRating());

        report.addMetric("Test", 100.0);
        report.addMetric("Test", 0.0);

        report = EmployeePerformanceReport("Test User", 123);
        CHECK_EQUAL(0.0, report.getOverallRating());
    }

    TEST(TestIncrementTasksCompleted) {
        EmployeePerformanceReport report("Test User", 123);

        CHECK_EQUAL(0, report.getTotalTasksCompleted());

        report.incrementTasksCompleted();
        CHECK_EQUAL(1, report.getTotalTasksCompleted());

        report.incrementTasksCompleted();
        report.incrementTasksCompleted();
        CHECK_EQUAL(3, report.getTotalTasksCompleted());
    }

    TEST(TestGenerate) {
        EmployeePerformanceReport report("Test User", 123);

        CHECK(!report.getIsFinalized());

        report.generate();

        CHECK(report.getIsFinalized());
    }

    TEST(TestValidate) {
        {
            EmployeePerformanceReport validReport("Test User", 123);
            CHECK(validReport.validate());
        }

        {
            EmployeePerformanceReport invalidReport("", 123);
            CHECK(!invalidReport.validate());
        }

        {
            EmployeePerformanceReport invalidReport("Test User", 0);
            CHECK(!invalidReport.validate());
        }

        {
            EmployeePerformanceReport invalidReport("", 0);
            CHECK(!invalidReport.validate());
        }

        {
            EmployeePerformanceReport report("Test User", 123);
            report.generate();
            CHECK(report.validate());
        }
    }

    TEST(TestGetPerformanceMetrics) {
        EmployeePerformanceReport report("Test User", 123);

        const auto& metrics1 = report.getPerformanceMetrics();
        CHECK(metrics1.empty());

        report.addMetric("Test1", 1.0);
        report.addMetric("Test2", 2.0);

        const auto& metrics2 = report.getPerformanceMetrics();
        CHECK_EQUAL(2, metrics2.size());
        CHECK_CLOSE(1.0, metrics2.at("Test1"), 0.001);
        CHECK_CLOSE(2.0, metrics2.at("Test2"), 0.001);

        const auto& metrics3 = report.getPerformanceMetrics();
        CHECK_EQUAL(2, metrics3.size());
    }
}
