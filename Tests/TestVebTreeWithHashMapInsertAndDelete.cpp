//
// Created by Abhijith  K A on 15/07/23.
//

#include <gtest/gtest.h>
#include <map>
#include "VEBTreeWithHashMap.h"

constexpr veb_hm_t universe = 16;

using veb_value_t = uint32_t;

class VEBWithHashMapTest : public ::testing::Test {
protected:
    void SetUp() override {
    }

    std::vector<veb_hm_t> GenerateSeries(veb_hm_t start, veb_hm_t count, veb_hm_t increment) {
        std::vector<veb_hm_t> result;
        result.resize(count);
        veb_hm_t current_val = start;
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
            vebTreeWithHashMap_->Insert(key, value);
            map_.insert({key, value});
        }
    }

    void DeleteElements (const std::vector<veb_hm_t>& keys, const std::vector<veb_value_t>& values){
        for(size_t i = 0; i < keys.size(); ++i){
            veb_hm_t  key = keys[i];
            veb_hm_t value = values[i];
            vebTreeWithHashMap_->Delete(key);
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
            std::tie (status, treeKey, vebValue) = vebTreeWithHashMap_->FindKey(key);
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

    bool CheckElementsAreNotPresent(const std::vector<veb_hm_t>& keys, const std::vector<veb_value_t>& values){
        for(size_t i = 0; i < keys.size(); ++i){
            veb_hm_t  key = keys[i];
            veb_hm_t value = values[i];
            veb_hm_t treeKey;
            bool status;
            veb_value_t vebValue;
            std::tie (status,  treeKey ,vebValue) = vebTreeWithHashMap_->FindKey(key);
            auto iter = map_.find(key);
            if(iter != map_.end() || status){
                return false;
            }
        }
        return true;
    }

    void TearDown() override {
        vebTreeWithHashMap_.reset();
    }
    std::unique_ptr<VEBTreeWithHashMap<veb_value_t>> vebTreeWithHashMap_;
    std::map<veb_hm_t , veb_value_t > map_;

};

TEST_F(VEBWithHashMapTest, Construction) {

    EXPECT_NO_THROW(
            vebTreeWithHashMap_ = std::move(std::make_unique<VEBTreeWithHashMap<veb_value_t>>(universe));
    );

}

TEST_F(VEBWithHashMapTest, InsertOneElement) {

    vebTreeWithHashMap_ = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(universe);
    vebTreeWithHashMap_->Insert(2, 100);
    map_.insert({2,100});

    auto [status, key, value] = vebTreeWithHashMap_->FindKey(2);
    auto iter = map_.find(2);
    EXPECT_TRUE(iter != map_.end());
    EXPECT_TRUE(status);
    EXPECT_TRUE(value == iter->second);

}

TEST_F(VEBWithHashMapTest, InsertTwoElement) {

    vebTreeWithHashMap_ = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(universe);
    vebTreeWithHashMap_->Insert(2, 100);
    map_.insert({2,100});
    vebTreeWithHashMap_->Insert(3, 100);
    map_.insert({3,101});

    auto [status, key, value] = vebTreeWithHashMap_->FindKey(2);
    auto iter = map_.find(2);
    EXPECT_TRUE(iter != map_.end());
    EXPECT_TRUE(status);
    EXPECT_TRUE(value == iter->second);

    auto [status_2, key_2, value_2] = vebTreeWithHashMap_->FindKey(3);
    auto iter2 = map_.find(3);
    EXPECT_TRUE(iter != map_.end());
    EXPECT_TRUE(status);
    EXPECT_TRUE(value_2 == iter->second);

}


TEST_F(VEBWithHashMapTest, InsertEightElementEven) {

    vebTreeWithHashMap_ = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(universe);
    auto keys = GenerateSeries(0,8,2);
    auto values = GenerateSeries(100, 8, 1);
    InsertElements(keys, values);
    EXPECT_TRUE(CompareElements(keys, values));

}

TEST_F(VEBWithHashMapTest, InsertEightElementEvenTwice) {

    vebTreeWithHashMap_ = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(universe);
    auto keys = GenerateSeries(0,8,2);
    auto values = GenerateSeries(100, 8, 1);
    InsertElements(keys, values);
    InsertElements(keys, values);
    EXPECT_TRUE(CompareElements(keys, values));

}

TEST_F(VEBWithHashMapTest, InsertEightElementEvenFourElementsTwice) {

    // Checks that Insert does not overwrite

    vebTreeWithHashMap_ = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(universe);
    auto keys = GenerateSeries(0,8,2);
    auto values = GenerateSeries(100, 8, 1);
    InsertElements(keys, values);
    EXPECT_TRUE(CompareElements(keys, values));
    auto keys_2 = GenerateSeries(0, 4,4);
    auto values_2 = GenerateSeries(1000,4,1);
    InsertElements(keys_2, values_2);
    EXPECT_TRUE(CompareElements(keys_2, values_2));
}


TEST_F(VEBWithHashMapTest, InsertEightElementEvenReverse) {

    vebTreeWithHashMap_ = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(universe);
    auto keys = GenerateSeries(0,8,2);
    std::reverse(keys.begin(), keys.end());
    auto values = GenerateSeries(100, 8, 1);
    InsertElements(keys, values);
    EXPECT_TRUE(CompareElements(keys, values));

}

TEST_F(VEBWithHashMapTest, InsertEightElementOdd) {

    vebTreeWithHashMap_ = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(universe);
    auto keys = GenerateSeries(1,8,2);
    auto values = GenerateSeries(100, 8, 1);
    InsertElements(keys, values);
    EXPECT_TRUE(CompareElements(keys, values));

}

TEST_F(VEBWithHashMapTest, InsertEightElementOddReverse) {

    vebTreeWithHashMap_ = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(universe);
    auto keys = GenerateSeries(1,8,2);
    std::reverse(keys.begin(), keys.end());
    auto values = GenerateSeries(100, 8, 1);
    InsertElements(keys, values);
    EXPECT_TRUE(CompareElements(keys, values));

}

TEST_F(VEBWithHashMapTest, InsertSixteenElements) {

    vebTreeWithHashMap_ = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(universe);
    auto keys = GenerateSeries(0,16,1);
    auto values = GenerateSeries(100, 16, 1);
    InsertElements(keys, values);
    EXPECT_TRUE(CompareElements(keys, values));

}

TEST_F(VEBWithHashMapTest, InsertSixteenElementsReverse) {

    vebTreeWithHashMap_ = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(universe);
    auto keys = GenerateSeries(0,16,1);
    std::reverse(keys.begin(), keys.end());
    auto values = GenerateSeries(100, 16, 1);
    InsertElements(keys, values);
    EXPECT_TRUE(CompareElements(keys, values));

}

TEST_F(VEBWithHashMapTest, Insert256Elements) {

    vebTreeWithHashMap_ = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(256);
    auto keys = GenerateSeries(0,256,1);
    auto values = GenerateSeries(100, 256, 1);
    InsertElements(keys, values);
    EXPECT_TRUE(CompareElements(keys, values));

}

TEST_F(VEBWithHashMapTest, DeleteFromEmptyTree){

    vebTreeWithHashMap_ = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(universe);
    EXPECT_NO_THROW(vebTreeWithHashMap_->Delete(1));
}

TEST_F(VEBWithHashMapTest, DeleteOneElement){

    vebTreeWithHashMap_ = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(universe);
    vebTreeWithHashMap_->Insert(1,100);
    auto [status,key, value] = vebTreeWithHashMap_->FindKey(1);
    EXPECT_TRUE(status);
   vebTreeWithHashMap_->Delete(1);
    auto [status_2, key_2, value_2] = vebTreeWithHashMap_->FindKey(1);
    EXPECT_FALSE(status_2);

}

TEST_F(VEBWithHashMapTest, InsertEightOddElementsAndDeleteThem){
    vebTreeWithHashMap_ = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(universe);
    auto keys = GenerateSeries(1,8,2);
    auto values = GenerateSeries(100, 8, 1);
    InsertElements(keys, values);
    EXPECT_TRUE(CompareElements(keys, values));
    DeleteElements(keys, values);
    EXPECT_TRUE(CheckElementsAreNotPresent(keys, values));
}

TEST_F(VEBWithHashMapTest, InsertEightEvenElementsAndDeleteThem){
    vebTreeWithHashMap_ = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(universe);
    auto keys = GenerateSeries(0,8,2);
    auto values = GenerateSeries(100, 8, 1);
    InsertElements(keys, values);
    EXPECT_TRUE(CompareElements(keys, values));
    DeleteElements(keys, values);
    EXPECT_TRUE(CheckElementsAreNotPresent(keys, values));
}

TEST_F(VEBWithHashMapTest, InsertSixteenElementsAndDeleteThem){
    vebTreeWithHashMap_ = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(universe);
    auto keys = GenerateSeries(0,16,1);
    auto values = GenerateSeries(100, 16, 1);
    InsertElements(keys, values);
    EXPECT_TRUE(CompareElements(keys, values));
    DeleteElements(keys, values);
    EXPECT_TRUE(CheckElementsAreNotPresent(keys, values));
}

TEST_F(VEBWithHashMapTest, InsertEightOddElementsAndDeleteThemInReverse){
    vebTreeWithHashMap_ = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(universe);
    auto keys = GenerateSeries(1,8,2);
    auto values = GenerateSeries(100, 8, 1);
    InsertElements(keys, values);
    EXPECT_TRUE(CompareElements(keys, values));
    std::reverse(keys.begin(), keys.end());
    DeleteElements(keys, values);
    EXPECT_TRUE(CheckElementsAreNotPresent(keys, values));
}

TEST_F(VEBWithHashMapTest, InsertSixteenElementsAndDeleteThemReverse){
    vebTreeWithHashMap_ = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(universe);
    auto keys = GenerateSeries(0,16,1);
    auto values = GenerateSeries(100, 16, 1);
    InsertElements(keys, values);
    EXPECT_TRUE(CompareElements(keys, values));
    std::reverse(keys.begin(), keys.end());
    DeleteElements(keys, values);
    EXPECT_TRUE(CheckElementsAreNotPresent(keys, values));
}

TEST_F(VEBWithHashMapTest, InsertSixteenElementsAndDeleteFour){
    vebTreeWithHashMap_ = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(universe);
    auto keys = GenerateSeries(0,16,1);
    auto values = GenerateSeries(100, 16, 1);
    InsertElements(keys, values);
    EXPECT_TRUE(CompareElements(keys, values));
    auto keys_2 = GenerateSeries(1,4,4);
    auto values_2 = GenerateSeries(101,4,4);
    DeleteElements(keys_2, values_2);
    EXPECT_TRUE(CheckElementsAreNotPresent(keys_2, values_2));
}

TEST_F(VEBWithHashMapTest, InsertSixteenElementsAndDeleteFourteen){
    vebTreeWithHashMap_ = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(universe);
    auto keys = GenerateSeries(0,16,1);
    auto values = GenerateSeries(100, 16, 1);
    InsertElements(keys, values);
    EXPECT_TRUE(CompareElements(keys, values));
    auto keys_2 = GenerateSeries(0,7,1);
    auto values_2 = GenerateSeries(100, 7, 1);
    auto keys_3 = GenerateSeries(9,7,1);
    auto values_3 = GenerateSeries(109, 7, 1);
    DeleteElements(keys_2, values_2);
    DeleteElements(keys_3, values_3);
    EXPECT_TRUE(CompareElements({7,8}, {107,108}));
    EXPECT_TRUE(CheckElementsAreNotPresent(keys_2,values_2));
    EXPECT_TRUE(CheckElementsAreNotPresent(keys_3,values_3));
}

TEST_F(VEBWithHashMapTest, InsertEightEvenElementsAndDeleteThemInReverse){
    vebTreeWithHashMap_ = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(universe);
    auto keys = GenerateSeries(0,8,2);
    auto values = GenerateSeries(100, 8, 1);
    InsertElements(keys, values);
    EXPECT_TRUE(CompareElements(keys, values));
    std::reverse(keys.begin(), keys.end());
    DeleteElements(keys, values);
    EXPECT_TRUE(CheckElementsAreNotPresent(keys, values));
}

TEST_F(VEBWithHashMapTest, Insert256ElementsAndDeleteThem){
  vebTreeWithHashMap_ = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(256);
    auto keys = GenerateSeries(0,256,1);
    auto values = GenerateSeries(100, 256, 1);
    InsertElements(keys, values);
    EXPECT_TRUE(CompareElements(keys, values));
    DeleteElements(keys, values);
    EXPECT_TRUE(CheckElementsAreNotPresent(keys, values));
}

TEST_F(VEBWithHashMapTest, Insert256ElementsAndDeleteThemInReverse){
  vebTreeWithHashMap_ = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(256);
    auto keys = GenerateSeries(0,256,1);
    auto values = GenerateSeries(100, 256, 1);
    InsertElements(keys, values);
    EXPECT_TRUE(CompareElements(keys, values));
    std::reverse(keys.begin(), keys.end());
    DeleteElements(keys, values);
    EXPECT_TRUE(CheckElementsAreNotPresent(keys, values));
}

TEST_F(VEBWithHashMapTest, Insert256ElementsAndDelete128OddOnes){
  vebTreeWithHashMap_ = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(256);
    auto keys = GenerateSeries(0,256,1);
    auto values = GenerateSeries(100, 256, 1);
    InsertElements(keys, values);
    EXPECT_TRUE(CompareElements(keys, values));
    auto keys_2 = GenerateSeries(1,128,2);
    auto values_2 = GenerateSeries(101,128,2);
    DeleteElements(keys_2, values_2);
    EXPECT_TRUE(CheckElementsAreNotPresent(keys_2, values_2));
    auto keys_not_deleted = GenerateSeries(0,128,2);
    auto values_not_deleted = GenerateSeries(100,128,2);
    EXPECT_TRUE(CompareElements(keys_not_deleted, values_not_deleted));

}

TEST_F(VEBWithHashMapTest, Insert256ElementsAndDelete128EvenOnes){
  vebTreeWithHashMap_ = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(256);
    auto keys = GenerateSeries(0,256,1);
    auto values = GenerateSeries(100, 256, 1);
    InsertElements(keys, values);
    EXPECT_TRUE(CompareElements(keys, values));
    auto keys_2 = GenerateSeries(0,128,2);
    auto values_2 = GenerateSeries(100,128,2);
    DeleteElements(keys_2, values_2);
    EXPECT_TRUE(CheckElementsAreNotPresent(keys_2, values_2));
    auto keys_not_deleted = GenerateSeries(1,128,2);
    auto values_not_deleted = GenerateSeries(101,128,2);
    EXPECT_TRUE(CompareElements(keys_not_deleted, values_not_deleted));
}

TEST_F(VEBWithHashMapTest, Universe32){
    vebTreeWithHashMap_ = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(32);
    auto keys = GenerateSeries(0,32,1);
    auto values = GenerateSeries(100, 32, 1);
    InsertElements(keys, values);
    EXPECT_TRUE(CompareElements(keys, values));
    auto keys_2 = GenerateSeries(0,16,2);
    auto values_2 = GenerateSeries(100,16,2);
    DeleteElements(keys_2, values_2);
    EXPECT_TRUE(CheckElementsAreNotPresent(keys_2, values_2));
    auto keys_not_deleted = GenerateSeries(1,16,2);
    auto values_not_deleted = GenerateSeries(101,16,2);
    EXPECT_TRUE(CompareElements(keys_not_deleted, values_not_deleted));
}

TEST_F(VEBWithHashMapTest, Universe32DeleteOdd){
    vebTreeWithHashMap_ = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(32);
    auto keys = GenerateSeries(0,32,1);
    auto values = GenerateSeries(100, 32, 1);
    InsertElements(keys, values);
    EXPECT_TRUE(CompareElements(keys, values));
    auto keys_2 = GenerateSeries(1,16,2);
    auto values_2 = GenerateSeries(101,16,2);
    DeleteElements(keys_2, values_2);
    EXPECT_TRUE(CheckElementsAreNotPresent(keys_2, values_2));
    auto keys_not_deleted = GenerateSeries(0,16,2);
    auto values_not_deleted = GenerateSeries(100,16,2);
    EXPECT_TRUE(CompareElements(keys_not_deleted, values_not_deleted));
}

TEST_F(VEBWithHashMapTest, Universe32DeleteOddReverse){
    vebTreeWithHashMap_ = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(32);
    auto keys = GenerateSeries(0,32,1);
    auto values = GenerateSeries(100, 32, 1);
    InsertElements(keys, values);
    EXPECT_TRUE(CompareElements(keys, values));
    auto keys_2 = GenerateSeries(1,16,2);
    auto values_2 = GenerateSeries(101,16,2);
    std::reverse(keys_2.begin(), keys_2.end());
    std::reverse(values_2.begin(), values_2.end());
    DeleteElements(keys_2, values_2);
    EXPECT_TRUE(CheckElementsAreNotPresent(keys_2, values_2));
    auto keys_not_deleted = GenerateSeries(0,16,2);
    auto values_not_deleted = GenerateSeries(100,16,2);
    EXPECT_TRUE(CompareElements(keys_not_deleted, values_not_deleted));
}

TEST_F(VEBWithHashMapTest, Universe128Delete){
    vebTreeWithHashMap_ = std::make_unique<VEBTreeWithHashMap<veb_value_t>>(128);
    auto keys = GenerateSeries(0,128,1);
    auto values = GenerateSeries(100, 128, 1);
    InsertElements(keys, values);
    EXPECT_TRUE(CompareElements(keys, values));
    auto keys_2 = GenerateSeries(0,16,1);
    auto values_2 = GenerateSeries(100,16,1);
    std::reverse(keys_2.begin(), keys_2.end());
    std::reverse(values_2.begin(), values_2.end());
    DeleteElements(keys_2, values_2);
    EXPECT_TRUE(CheckElementsAreNotPresent(keys_2, values_2));

    auto keys_3 = GenerateSeries(112,16,1);
    auto values_3 = GenerateSeries(212,16,1);
    DeleteElements(keys_3, values_3);
    EXPECT_TRUE(CheckElementsAreNotPresent(keys_3, values_3));
    auto keys_not_deleted = GenerateSeries(16,96,1);
    auto values_not_deleted = GenerateSeries(116,96,1);
    EXPECT_TRUE(CompareElements(keys_not_deleted, values_not_deleted));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
