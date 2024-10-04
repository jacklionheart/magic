// tests/rules/test_mana.cpp
#include "rules/engine/mana.h"
#include <gtest/gtest.h>

// Test for ManaCost::parse()
TEST(ManaCostTest, Parse) {
    ManaCost cost = ManaCost::parse("3RG");
    EXPECT_EQ(cost.generic, 3);
    EXPECT_EQ(cost.cost[Color::RED], 1);
    EXPECT_EQ(cost.cost[Color::GREEN], 1);
    EXPECT_EQ(cost.toString(), "3RG");
}

// Test for Mana::can_pay() and Mana::pay()
TEST(ManaTest, CanPayAndPay) {
    ManaCost cost = ManaCost::parse("2WU");
    Mana mana_pool;
    mana_pool.mana[Color::WHITE] = 1;
    mana_pool.mana[Color::BLUE] = 1;
    mana_pool.mana[Color::COLORLESS] = 2;

    EXPECT_TRUE(mana_pool.canPay(cost));
    mana_pool.pay(cost);
    EXPECT_EQ(mana_pool.mana[Color::WHITE], 0);
    EXPECT_EQ(mana_pool.mana[Color::BLUE], 0);
    EXPECT_EQ(mana_pool.mana[Color::COLORLESS], 0);
}

// Test for Mana::can_pay() when payment is not possible
TEST(ManaTest, CannotPay) {
    ManaCost cost = ManaCost::parse("1BB");
    Mana mana_pool;
    mana_pool.mana[Color::BLACK] = 1;
    mana_pool.mana[Color::COLORLESS] = 1;

    EXPECT_FALSE(mana_pool.canPay(cost));
}