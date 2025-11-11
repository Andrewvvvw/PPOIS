#include "UnitTest++.h"
#include "Source/Employee/Waiter/Waiter.h"
#include "Source/Order/Order.h"
#include "Source/Customer/Customer.h"

SUITE(WaiterTest) {
    TEST(ConstructorAndGetters) {
        Waiter waiter("John Doe", 15.0, 2);

        CHECK_EQUAL("John Doe", waiter.getName());
        CHECK_EQUAL("Waiter", waiter.getRole());
        CHECK_EQUAL(15.0, waiter.getHourlyRate());
        CHECK_EQUAL(2, waiter.getYearsOfExperience());
        CHECK(waiter.getIsActive());
        CHECK_EQUAL(0, waiter.getActiveOrdersCount());
        CHECK_EQUAL(0.0, waiter.getTotalTips());
        CHECK_EQUAL(-1, waiter.getCurrentTable());
    }

    TEST(TableAssignment) {
        Waiter waiter("Jane Smith", 12.0, 1);

        CHECK_EQUAL(-1, waiter.getCurrentTable());
        CHECK_EQUAL(0, waiter.getTablesServed());

        waiter.assignTable(5);
        CHECK_EQUAL(5, waiter.getCurrentTable());
        CHECK_EQUAL(1, waiter.getTablesServed());

        waiter.assignTable(8);
        CHECK_EQUAL(8, waiter.getCurrentTable());
        CHECK_EQUAL(2, waiter.getTablesServed());

        waiter.assignTable(-1);
        CHECK_EQUAL(-1, waiter.getCurrentTable());
        CHECK_EQUAL(3, waiter.getTablesServed());
    }

    TEST(OrderManagement) {
        Waiter waiter("Bob Johnson", 14.0, 3);
        Customer customer("Test Customer", 123);
        Order order1(1, &customer);
        Order order2(2, &customer);

        CHECK_EQUAL(0, waiter.getActiveOrdersCount());

        waiter.addOrder(nullptr);
        CHECK_EQUAL(0, waiter.getActiveOrdersCount());

        waiter.addOrder(&order1);
        CHECK_EQUAL(1, waiter.getActiveOrdersCount());

        waiter.addOrder(&order2);
        CHECK_EQUAL(2, waiter.getActiveOrdersCount());

        waiter.completeOrder(&order1);
        CHECK_EQUAL(1, waiter.getActiveOrdersCount());

        waiter.completeOrder(&order2);
        CHECK_EQUAL(0, waiter.getActiveOrdersCount());

        waiter.completeOrder(&order1);
        CHECK_EQUAL(0, waiter.getActiveOrdersCount());
    }

    TEST(TipsManagement) {
        Waiter waiter("Alice Brown", 13.0, 2);

        CHECK_EQUAL(0.0, waiter.getTotalTips());

        waiter.receiveTip(5.0);
        CHECK_EQUAL(5.0, waiter.getTotalTips());

        waiter.receiveTip(3.5);
        CHECK_EQUAL(8.5, waiter.getTotalTips());

        waiter.receiveTip(-2.0);
        CHECK_EQUAL(8.5, waiter.getTotalTips());

        waiter.receiveTip(0.0);
        CHECK_EQUAL(8.5, waiter.getTotalTips());

        waiter.receiveTip(1000000.0);
        CHECK_EQUAL(1000008.5, waiter.getTotalTips());
    }

    TEST(EdgeCases) {
        Waiter minWaiter("", 0.0, 0);
        CHECK_EQUAL("", minWaiter.getName());
        CHECK_EQUAL(0.0, minWaiter.getHourlyRate());
        CHECK_EQUAL(0, minWaiter.getYearsOfExperience());
        CHECK_EQUAL(0, minWaiter.getActiveOrdersCount());
        CHECK_EQUAL(0.0, minWaiter.getTotalTips());
        CHECK_EQUAL(-1, minWaiter.getCurrentTable());

        Waiter maxWaiter("A very long name that exceeds any reasonable limit",
                         1000.0,
                         50);
        CHECK(maxWaiter.getName().length() > 0);

        maxWaiter.assignTable(0);
        maxWaiter.assignTable(INT_MAX);

        Customer customer("Test Customer", 456);
        Order order(1, &customer);
        for (int i = 0; i < 1000; ++i) {
            maxWaiter.addOrder(&order);
        }
        CHECK_EQUAL(1000, maxWaiter.getActiveOrdersCount());
    }

    TEST(employeeInheritance) {
        Waiter waiter("Test Waiter", 15.0, 5);
        Employee* employee = &waiter;

        CHECK_EQUAL("Test Waiter", employee->getName());
        CHECK_EQUAL("Waiter", employee->getRole());
        CHECK_EQUAL(15.0, employee->getHourlyRate());
        CHECK_EQUAL(5, employee->getYearsOfExperience());
        CHECK(employee->getIsActive());

        employee->setName("New Name");
        CHECK_EQUAL("New Name", employee->getName());

        employee->setHourlyRate(20.0);
        CHECK_EQUAL(20.0, employee->getHourlyRate());

        employee->setYearsOfExperience(10);
        CHECK_EQUAL(10, employee->getYearsOfExperience());

        employee->setIsActive(false);
        CHECK(!employee->getIsActive());

        employee->addExperience(2);
        CHECK_EQUAL(12, employee->getYearsOfExperience());
    }
}