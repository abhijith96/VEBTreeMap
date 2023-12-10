//
// Created by Abhijith  K A on 15/07/23.
//

#include <gtest/gtest.h>
#include "VEBTreeUtil.h"
#include "VEBTreeWithHashMapNode.h"
#include "VEBTreeValueObject.h"

class VEBUtilsTest : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }


};

TEST_F(VEBUtilsTest, TestHighAndLowValue3Universe4) {

    uint32_t  number = 3;
    uint32_t universe = 4;

    uint32_t  high;
    uint32_t  low;
    std::tie(high, low) =  VEBTreeUtils::SplitIntoHighAndLow(number, universe);
    EXPECT_EQ(high, uint32_t(1));
    EXPECT_EQ(low ,uint32_t(1));
}

TEST_F(VEBUtilsTest, TestHighAndLowValue2Universe4) {

    uint32_t  number = 2;
    uint32_t universe = 4;

    uint32_t  high;
    uint32_t  low;
    std::tie(high, low) =  VEBTreeUtils::SplitIntoHighAndLow(number, universe);
    EXPECT_EQ(high, uint32_t(1));
    EXPECT_EQ(low ,uint32_t(0));
}

TEST_F(VEBUtilsTest, TestHighAndLowValue1Universe4) {

    uint32_t  number = 1;
    uint32_t universe = 4;

    uint32_t  high;
    uint32_t  low;
    std::tie(high, low) =  VEBTreeUtils::SplitIntoHighAndLow(number, universe);
    EXPECT_EQ(high, uint32_t(0));
    EXPECT_EQ(low ,uint32_t(1));
}

TEST_F(VEBUtilsTest, TestHighAndLowValue0Universe4) {

    uint32_t  number = 0;
    uint32_t universe = 4;

    uint32_t  high;
    uint32_t  low;
    std::tie(high, low) =  VEBTreeUtils::SplitIntoHighAndLow(number, universe);
    EXPECT_EQ(high, uint32_t(0));
    EXPECT_EQ(low ,uint32_t(0));
}

TEST_F(VEBUtilsTest, TestHighAndLowValue0Universe8) {

    uint32_t  number = 0;
    uint32_t universe = 8;

    uint32_t  high;
    uint32_t  low;
    std::tie(high, low) =  VEBTreeUtils::SplitIntoHighAndLow(number, universe);
    EXPECT_EQ(high, uint32_t(0));
    EXPECT_EQ(low ,uint32_t(0));
}

TEST_F(VEBUtilsTest, TestHighAndLowValue1Universe8) {

    uint32_t  number = 1;
    uint32_t universe = 8;

    uint32_t  high;
    uint32_t  low;
    std::tie(high, low) =  VEBTreeUtils::SplitIntoHighAndLow(number, universe);
    EXPECT_EQ(high, uint32_t(0));
    EXPECT_EQ(low ,uint32_t(1));
}

TEST_F(VEBUtilsTest, TestHighAndLowValue2Universe8) {

    uint32_t  number = 2;
    uint32_t universe = 8;

    uint32_t  high;
    uint32_t  low;
    std::tie(high, low) =  VEBTreeUtils::SplitIntoHighAndLow(number, universe);
    EXPECT_EQ(high, uint32_t(0));
    EXPECT_EQ(low ,uint32_t(2));
}

TEST_F(VEBUtilsTest, TestHighAndLowValue3Universe8) {

    uint32_t  number = 3;
    uint32_t universe = 8;

    uint32_t  high;
    uint32_t  low;
    std::tie(high, low) =  VEBTreeUtils::SplitIntoHighAndLow(number, universe);
    EXPECT_EQ(high, uint32_t(0));
    EXPECT_EQ(low ,uint32_t(3));
}

TEST_F(VEBUtilsTest, TestHighAndLowValue4Universe8) {

    uint32_t  number = 4;
    uint32_t universe = 8;

    uint32_t  high;
    uint32_t  low;
    std::tie(high, low) =  VEBTreeUtils::SplitIntoHighAndLow(number, universe);
    EXPECT_EQ(high, uint32_t(1));
    EXPECT_EQ(low ,uint32_t(0));
}

TEST_F(VEBUtilsTest, TestHighAndLowValue5Universe8) {

    uint32_t  number = 5;
    uint32_t universe = 8;

    uint32_t  high;
    uint32_t  low;
    std::tie(high, low) =  VEBTreeUtils::SplitIntoHighAndLow(number, universe);
    EXPECT_EQ(high, uint32_t(1));
    EXPECT_EQ(low ,uint32_t(1));
}

TEST_F(VEBUtilsTest, TestHighAndLowValue6Universe8) {

    uint32_t  number = 6;
    uint32_t universe = 8;

    uint32_t  high;
    uint32_t  low;
    std::tie(high, low) =  VEBTreeUtils::SplitIntoHighAndLow(number, universe);
    EXPECT_EQ(high, uint32_t(1));
    EXPECT_EQ(low ,uint32_t(2));
}

TEST_F(VEBUtilsTest, TestHighAndLowValue7Universe8) {

    uint32_t  number = 7;
    uint32_t universe = 8;

    uint32_t  high;
    uint32_t  low;
    std::tie(high, low) =  VEBTreeUtils::SplitIntoHighAndLow(number, universe);
    EXPECT_EQ(high, uint32_t(1));
    EXPECT_EQ(low ,uint32_t(3));
}

TEST_F(VEBUtilsTest, TestHighAndLowValue15Universe16) {

    uint32_t  number = 15;
    uint32_t universe = 16;

    uint32_t  high;
    uint32_t  low;
    std::tie(high, low) =  VEBTreeUtils::SplitIntoHighAndLow(number, universe);
    EXPECT_EQ(high, uint32_t(3));
    EXPECT_EQ(low ,uint32_t(3));
}

TEST_F(VEBUtilsTest, TestHighAndLowValue31Universe32) {

    uint32_t  number = 31;
    uint32_t universe = 32;

    uint32_t  high;
    uint32_t  low;
    std::tie(high, low) =  VEBTreeUtils::SplitIntoHighAndLow(number, universe);
    EXPECT_EQ(high, uint32_t(3));
    EXPECT_EQ(low ,uint32_t(7));
}


TEST_F(VEBUtilsTest, TestHighAndLowValue30Universe32) {

    uint32_t  number = 30;
    uint32_t universe = 32;

    uint32_t  high;
    uint32_t  low;
    std::tie(high, low) =  VEBTreeUtils::SplitIntoHighAndLow(number, universe);
    EXPECT_EQ(high, uint32_t(3));
    EXPECT_EQ(low ,uint32_t(6));
}

TEST_F(VEBUtilsTest, TestHighAndLowValue25Universe32) {

    uint32_t  number = 24;
    uint32_t universe = 32;

    uint32_t  high;
    uint32_t  low;
    std::tie(high, low) =  VEBTreeUtils::SplitIntoHighAndLow(number, universe);
    EXPECT_EQ(high, uint32_t(3));
    EXPECT_EQ(low ,uint32_t(0));
}

TEST_F(VEBUtilsTest, TestHighAndLowValue24Universe32) {

    uint32_t  number = 23;
    uint32_t universe = 32;

    uint32_t  high;
    uint32_t  low;
    std::tie(high, low) =  VEBTreeUtils::SplitIntoHighAndLow(number, universe);
    EXPECT_EQ(high, uint32_t(2));
    EXPECT_EQ(low ,uint32_t(7));
}

TEST_F(VEBUtilsTest, TestHighAndLowValue63Universe64) {

    uint32_t  number = 63;
    uint32_t universe = 64;

    uint32_t  high;
    uint32_t  low;
    std::tie(high, low) =  VEBTreeUtils::SplitIntoHighAndLow(number, universe);
    EXPECT_EQ(high, uint32_t(7));
    EXPECT_EQ(low ,uint32_t(7));
}

TEST_F(VEBUtilsTest, TestHighAndLowValuemax64bitUniversemax64bit) {

    uint64_t  number = std::numeric_limits<uint64_t>::max();
    uint64_t universe = std::numeric_limits<uint64_t>::max();

    uint64_t  high;
    uint64_t  low;
    std::tie(high, low) =  VEBTreeUtils::SplitIntoHighAndLow(number, universe);

    uint64_t  max32Bitnumber = std::numeric_limits<uint32_t>::max();

    EXPECT_EQ(high, max32Bitnumber);
    EXPECT_EQ(low ,max32Bitnumber);
}

TEST_F(VEBUtilsTest, TestHighAndLowValuemax64bitMinus1Universemax64bit) {

    uint64_t  number = std::numeric_limits<uint64_t>::max() - 1;
    uint64_t universe = std::numeric_limits<uint64_t>::max();

    uint64_t  high;
    uint64_t  low;
    std::tie(high, low) =  VEBTreeUtils::SplitIntoHighAndLow(number, universe);

    uint64_t  max32BitNumber = std::numeric_limits<uint32_t>::max();

    EXPECT_EQ(high, max32BitNumber);
    EXPECT_EQ(low , max32BitNumber - 1);
}

TEST_F(VEBUtilsTest, TestHighAndLowValuemax8bitUniversemax16bit) {

    uint32_t  number = std::numeric_limits<uint8_t>::max();
    uint32_t universe = std::numeric_limits<uint16_t>::max();

    uint32_t  high;
    uint32_t  low;
    std::tie(high, low) =  VEBTreeUtils::SplitIntoHighAndLow(number, universe);


    EXPECT_EQ(high, 0);
    EXPECT_EQ(low , number);
}

TEST_F(VEBUtilsTest, TestSplitIntoPowersOfTwo) {


    uint32_t universe = 4;

    uint32_t  high;
    uint32_t  low;
    std::tie(high, low) =  VEBTreeUtils::SplitIntoSquareOfPowersOfTwo(universe);


    EXPECT_EQ(high, 2);
    EXPECT_EQ(low , 2);
}

TEST_F(VEBUtilsTest, TestSplitIntoPowersOfTwoUniverse8) {


    uint32_t universe = 8;

    uint32_t  high;
    uint32_t  low;
    std::tie(high, low) =  VEBTreeUtils::SplitIntoSquareOfPowersOfTwo(universe);


    EXPECT_EQ(high, 2);
    EXPECT_EQ(low , 4);
}

TEST_F(VEBUtilsTest, TestSplitIntoPowersOfTwoUniverse16) {


    uint32_t universe = 16;

    uint32_t  high;
    uint32_t  low;
    std::tie(high, low) =  VEBTreeUtils::SplitIntoSquareOfPowersOfTwo(universe);


    EXPECT_EQ(high, 4);
    EXPECT_EQ(low , 4);
}


TEST_F(VEBUtilsTest, TestSplitIntoPowersOfTwoUniverse32) {


    uint32_t universe = 32;

    uint32_t  high;
    uint32_t  low;
    std::tie(high, low) =  VEBTreeUtils::SplitIntoSquareOfPowersOfTwo(universe);


    EXPECT_EQ(high, 4);
    EXPECT_EQ(low , 8);
}

TEST_F(VEBUtilsTest, TestSplitIntoPowersOfTwoUniverse64) {


    uint32_t universe = 64;

    uint32_t  high;
    uint32_t  low;
    std::tie(high, low) =  VEBTreeUtils::SplitIntoSquareOfPowersOfTwo(universe);


    EXPECT_EQ(high, 8);
    EXPECT_EQ(low , 8);
}

TEST_F(VEBUtilsTest, TestSplitIntoPowersOfTwoUniverse128) {


    uint32_t universe = 128;

    uint32_t  high;
    uint32_t  low;
    std::tie(high, low) =  VEBTreeUtils::SplitIntoSquareOfPowersOfTwo(universe);


    EXPECT_EQ(high, 8);
    EXPECT_EQ(low , 16);
}

TEST_F(VEBUtilsTest, TestSplitIntoPowersOfTwoUniverse256) {


    uint32_t universe = 256;

    uint32_t  high;
    uint32_t  low;
    std::tie(high, low) =  VEBTreeUtils::SplitIntoSquareOfPowersOfTwo(universe);


    EXPECT_EQ(high, 16);
    EXPECT_EQ(low , 16);
}

TEST_F(VEBUtilsTest, TestSplitIntoPowersOfTwoUniverse2power16) {


    uint32_t universe = std::numeric_limits<uint16_t>::max() + 1;

    uint32_t  high;
    uint32_t  low;
    std::tie(high, low) =  VEBTreeUtils::SplitIntoSquareOfPowersOfTwo(universe);


    EXPECT_EQ(high, 256);
    EXPECT_EQ(low , 256);
}

TEST_F(VEBUtilsTest, SimpleTest) {


    uint32_t universe = std::numeric_limits<uint32_t>::max() + 1;



    VEBTreeWithHashMapNode<uint32_t> rootNodeHashed{2};

    std::cout<<"size is hashed tree "<<sizeof rootNodeHashed<<"\n";

}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}