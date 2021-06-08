#define CATCH_CONFIG_MAIN
#include <gtest/gtest.h>
#include <adder/adder.h>
#include <GLFW/glfw3.h>

TEST(AdderTests, VerifyAdderOutput) {  
    EXPECT_FLOAT_EQ(adder(5.2, 6.2), 11.4);
}