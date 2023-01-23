/**
 * @file test_storage.cpp
 * @author Muhammad Ziaus Siam (ziaus.siam@bjitgroup.com)
 * @brief Implementation of Non-volatile memory
 * @version 1.0
 * @date 2023-01-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <gmock/gmock.h>
#include <Terminal.hpp>
#include <Storage.hpp>

class TestStorage : public ::testing::Test
{
protected:
    Terminal terminal;
    void SetUp() override {}
        
    void TearDown() override {}
};

TEST_F(TestStorage, ReadStroage)
{
    Storage storage(terminal);
    storage.read();
}