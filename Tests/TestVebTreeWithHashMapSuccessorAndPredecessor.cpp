//
// Created by Abhijith  K A on 15/07/23.
//

#include <gtest/gtest.h>
#include "VEBTreeWithHashMap.h"


constexpr veb_hm_t  universe = 16;

using veb_value_t = uint32_t;

class DSModelVebTreeImplTest : public ::testing::Test {
protected:
    void SetUp() override {
    }

    std::vector<veb_hm_t > GenerateSeries(veb_hm_t  start, veb_hm_t  count, veb_hm_t  increment) {
        std::vector<veb_hm_t > result;
        result.resize(count);
        veb_hm_t  current_val = start;
        for(auto& i : result){
            i = current_val;
            current_val += increment;
        }
        return result;
    }

    void InsertElements (const std::vector<veb_hm_t>& keys, const std::vector<veb_value_t>& values){
        for(size_t i = 0; i < keys.size(); ++i){
            veb_hm_t  key = keys[i];
            veb_hm_t value = values[i];
            DsImplVebTree->Insert(key, value);
            map_.insert({key, value});
        }
    }

    void DeleteElements (const std::vector<veb_hm_t>& keys, const std::vector<veb_value_t>& values){
        for(size_t i = 0; i < keys.size(); ++i){
            veb_hm_t  key = keys[i];
            veb_hm_t value = values[i];
            DsImplVebTree->Delete(key);
            map_.erase(key);
        }
    }
    bool CompareElements(const std::vector<veb_hm_t>& keys, const std::vector<veb_value_t>& values){
        for(size_t i = 0; i < keys.size(); ++i){
            veb_hm_t  key = keys[i];
            veb_hm_t value = values[i];
            bool status;
            veb_hm_t treeKey;
            veb_value_t vebValue;
            std::tie (status, treeKey, vebValue) = DsImplVebTree->FindKey(key);
            auto iter = map_.find(key);
            if(iter == map_.end()){
                return false;
            }
            else if(!status) return false;
            else if(vebValue != iter->second){
                return false;
            }
        }
        return true;
    }

    bool CheckElementsAreNotPresent(const std::vector<veb_hm_t >& keys, const std::vector<veb_value_t>& values){
        for(size_t i = 0; i < keys.size(); ++i){
            veb_hm_t   key = keys[i];
            veb_hm_t  value = values[i];
            bool status;
            veb_hm_t  treeKey;
            veb_value_t vebValue;
            std::tie (status, treeKey, vebValue) = DsImplVebTree->FindKey(key);
            auto iter = map_.find(key);
            if(iter != map_.end() || status){
                return false;
            }
        }
        return true;
    }

    bool CheckIfSuccessorsMatch(const std::vector<veb_hm_t >& keys, const std::vector<veb_hm_t >& sucKeys, const std::vector<veb_value_t>& sucValues){
        for(size_t i = 0; i < keys.size(); ++i){
            veb_hm_t   key = keys[i];
            VEBTreeNodeKeyType nodeKeyType;
            veb_hm_t  sucKey;
            veb_value_t sucValue;
            std::tie (nodeKeyType, sucKey, sucValue) = DsImplVebTree->Successor(key);
            EXPECT_EQ(VEBTreeNodeKeyType::NORMAL, nodeKeyType);
            EXPECT_EQ(sucKey , sucKeys[i]);
            EXPECT_EQ(sucValue, sucValues[i]);
        }
        return true;
    }

    bool CheckIfPredecessorsMatch(const std::vector<veb_hm_t >& keys, const std::vector<veb_hm_t >& predKeys, const std::vector<veb_value_t>& predValues){
        for(size_t i = 0; i < keys.size(); ++i){
            veb_hm_t   key = keys[i];
            VEBTreeNodeKeyType nodeKeyType;
            veb_hm_t  predKey;
            veb_value_t predValue;
            std::tie (nodeKeyType, predKey, predValue) = DsImplVebTree->Predecessor(key);
            EXPECT_EQ(VEBTreeNodeKeyType::NORMAL, nodeKeyType);
            EXPECT_EQ(predKey , predKeys[i]);
            EXPECT_EQ(predValue, predValues[i]);
        }
        return true;
    }

    void TearDown() override {
        DsImplVebTree.reset();
    }
    std::unique_ptr<VEBTreeWithHashMap<veb_value_t>> DsImplVebTree;
    std::map<veb_hm_t  , veb_value_t > map_;

};

TEST_F(DSModelVebTreeImplTest, SuccesorOfEmptyTree) {

    DsImplVebTree = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(universe);

auto [nodeType, sucKey, sucVal] = DsImplVebTree->Successor(0);
EXPECT_TRUE(nodeType == VEBTreeNodeKeyType::POSITIVE_INFINITY);


}

TEST_F(DSModelVebTreeImplTest, SuccesorOfTreeWithOneVal) {

    DsImplVebTree = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(universe);

DsImplVebTree->Insert(10, 1);
auto [nodeType, sucKey, sucVal] = DsImplVebTree->Successor(11);
EXPECT_TRUE(nodeType == VEBTreeNodeKeyType::POSITIVE_INFINITY);

{
auto [nodeType_2, sucKey_2, sucVal_2] = DsImplVebTree->Successor(10);
EXPECT_TRUE(nodeType_2 == VEBTreeNodeKeyType::NORMAL);
EXPECT_EQ(sucKey_2, 10);
EXPECT_EQ(sucVal_2, 1);

}

{

auto [nodeType_3, sucKey_3, sucVal_3] = DsImplVebTree->Successor(1);

EXPECT_TRUE(nodeType_3 == VEBTreeNodeKeyType::NORMAL);
EXPECT_EQ(sucKey_3, 10);
EXPECT_EQ(sucVal_3, 1);

}


}

TEST_F(DSModelVebTreeImplTest, SuccesorOfTreeWithEightElements) {

    DsImplVebTree = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(universe);

auto keys = GenerateSeries(0,8,2);
auto values = GenerateSeries(100,8,2);
InsertElements(keys, values);
EXPECT_TRUE(CompareElements(keys, values));

auto sucInput = GenerateSeries(1,7, 2);
auto sucKeysOutput = GenerateSeries(2, 7, 2);
auto sucValuesOutput = GenerateSeries(102,7,2);
EXPECT_TRUE(CheckIfSuccessorsMatch(sucInput, sucKeysOutput, sucValuesOutput));
EXPECT_TRUE(CheckIfSuccessorsMatch(keys, keys, values));

}

TEST_F(DSModelVebTreeImplTest, SuccesorOfTreeWithEightElementsOdd) {

    DsImplVebTree = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(universe);

auto keys = GenerateSeries(1,8,2);
auto values = GenerateSeries(101,8,2);
InsertElements(keys, values);
EXPECT_TRUE(CompareElements(keys, values));

auto sucInput = GenerateSeries(0,8, 2);
auto sucKeysOutput = GenerateSeries(1, 8, 2);
auto sucValuesOutput = GenerateSeries(101,8,2);
EXPECT_TRUE(CheckIfSuccessorsMatch(sucInput, sucKeysOutput, sucValuesOutput));

}

TEST_F(DSModelVebTreeImplTest, SuccesorOfTreeWithFourElements) {

    DsImplVebTree = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(universe);

auto keys = GenerateSeries(1,4,4);
auto values = GenerateSeries(101,4,4);
InsertElements(keys, values);
EXPECT_TRUE(CompareElements(keys, values));

auto sucInput = GenerateSeries(0,14,1);
std::vector<veb_hm_t > sucKeysOutput = {1,1,5,5,5,5,9,9,9,9,13,13,13,13};
std::vector<veb_value_t >sucValuesOutput = {101,101,105,105,105,105,109,109,109,109,113,113,113,113};
EXPECT_TRUE(CheckIfSuccessorsMatch(sucInput, sucKeysOutput, sucValuesOutput));

}

TEST_F(DSModelVebTreeImplTest, SuccesorOfTreeWithUniverse256) {

    DsImplVebTree = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(256);

auto keys = GenerateSeries(10,25,10);
auto values = GenerateSeries(100,25,10);
InsertElements(keys, values);
EXPECT_TRUE(CompareElements(keys, values));

for(int i = 1; i <= 10; ++i) {
auto sucInput = GenerateSeries(i, 24, 10);
std::vector<veb_hm_t > sucKeysOutput = GenerateSeries(10, 24, 10);
std::vector<veb_value_t> sucValuesOutput = GenerateSeries(100, 24, 10);
EXPECT_TRUE(CheckIfSuccessorsMatch(sucInput, sucKeysOutput, sucValuesOutput));
}

}

TEST_F(DSModelVebTreeImplTest, PredecessorOfEmptyTree) {

    DsImplVebTree = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(universe);

auto [nodeType, sucKey, sucVal] = DsImplVebTree->Predecessor(0);
EXPECT_TRUE(nodeType == VEBTreeNodeKeyType::NEGATIVE_INFINITY);


}

TEST_F(DSModelVebTreeImplTest, PredecessorOfTreeWithOneVal) {

    DsImplVebTree = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(universe);

DsImplVebTree->Insert(10, 1);
auto [nodeType, sucKey, sucVal] = DsImplVebTree->Predecessor(9);
EXPECT_TRUE(nodeType == VEBTreeNodeKeyType::NEGATIVE_INFINITY);

{
auto [nodeType_2, sucKey_2, sucVal_2] = DsImplVebTree->Predecessor(11);
EXPECT_TRUE(nodeType_2 == VEBTreeNodeKeyType::NORMAL);
EXPECT_EQ(sucKey_2, 10);
EXPECT_EQ(sucVal_2, 1);

}

{

auto [nodeType_3, sucKey_3, sucVal_3] = DsImplVebTree->Predecessor(10);

EXPECT_TRUE(nodeType_3 == VEBTreeNodeKeyType::NORMAL);
EXPECT_EQ(sucKey_3, 10);
EXPECT_EQ(sucVal_3, 1);

}

}

TEST_F(DSModelVebTreeImplTest, PredecessorOfTreeWithEightElements) {

    DsImplVebTree = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(universe);

auto keys = GenerateSeries(0,8,2);
auto values = GenerateSeries(100,8,2);
InsertElements(keys, values);
EXPECT_TRUE(CompareElements(keys, values));

auto prdInput = GenerateSeries(1, 7, 2);
auto predKeysOutput = GenerateSeries(0, 7, 2);
auto predValuesOutput = GenerateSeries(100, 7, 2);
EXPECT_TRUE(CheckIfPredecessorsMatch(prdInput, predKeysOutput, predValuesOutput));
EXPECT_TRUE(CheckIfPredecessorsMatch(keys, keys, values));

}

TEST_F(DSModelVebTreeImplTest, PredecessorOfTreeWithSixteen) {

    DsImplVebTree = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(universe);

auto keys = GenerateSeries(0,16,1);
auto values = GenerateSeries(100,16,1);
InsertElements(keys, values);
EXPECT_TRUE(CompareElements(keys, values));

EXPECT_TRUE(CheckIfPredecessorsMatch(keys, keys, values));


}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

