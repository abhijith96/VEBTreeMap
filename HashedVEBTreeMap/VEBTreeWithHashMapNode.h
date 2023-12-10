//
// Created by Abhijith  K A on 14/07/23.
//

#ifndef DHCPALLOCATOR_VEBTREEWITHHASHMAPNODE_H
#define DHCPALLOCATOR_VEBTREEWITHHASHMAPNODE_H

#include <unordered_map>
#include <concepts>
#include <memory>
#include "VEBTreeKeyConcept.h"
#include "VEBTreeValueConcept.h"



template <VEBTreeKey KeyType, VEBTreeValue ValueType,typename Hash = std::hash<KeyType>, typename Equal = std::equal_to<KeyType>>
class VEBTreeWithHashMapNode{
private:
    KeyType universe_;
    bool is_set_;
    KeyType min_;
    KeyType max_;
    std::unique_ptr<ValueType> min_value_;
    std::unique_ptr<ValueType> max_value_;

    std::unique_ptr<VEBTreeWithHashMapNode> summary_;

    std::unordered_map<KeyType, VEBTreeWithHashMapNode<KeyType, ValueType>, Hash, Equal> cluster_map_;


public:
   explicit VEBTreeWithHashMapNode(KeyType universe) :universe_(universe), is_set_(false),
   min_(), max_(){
   }

    explicit VEBTreeWithHashMapNode(KeyType universe, Hash hashObj, Equal equalObj) :universe_(universe), is_set_(false),
                                                       min_(), max_(), cluster_map_(16, hashObj, equalObj){
    }

   VEBTreeWithHashMapNode& operator = (VEBTreeWithHashMapNode&& other) noexcept = default;


   VEBTreeWithHashMapNode(VEBTreeWithHashMapNode && other) noexcept = default;


   [[nodiscard]] KeyType GetUniverse() const{
       return universe_;
   }

    [[nodiscard]] bool IsSet() const{
       return is_set_;
   }

   void Unset(){
       is_set_ = false;
   }

   [[nodiscard]] bool IsClusterSet(KeyType clusterIndex) const{
       return cluster_map_.find(clusterIndex) != cluster_map_.end();
   }

   void SetCluster(KeyType clusterIndex, KeyType itemsCount){
       cluster_map_.emplace(clusterIndex,itemsCount);
   }

   void UnsetCluster(KeyType clusterIndex){
       cluster_map_.erase(clusterIndex);
   }

   void UnsetSummary(){
       summary_.reset();
   }

   VEBTreeWithHashMapNode<KeyType, ValueType>& GetCluster(KeyType clusterIndex){
       auto itr = cluster_map_.find(clusterIndex);
       assert(itr != cluster_map_.end());
       return itr->second;
   }

   VEBTreeWithHashMapNode<KeyType,ValueType>& GetSummary(){
       assert(summary_);
       return *summary_;
   }

   void SetSummary (KeyType clusterCount){
       summary_ = std::move(std::make_unique<VEBTreeWithHashMapNode<KeyType,ValueType>>(clusterCount));
   }

   [[nodiscard]] bool IsSummarySet() const{
       return summary_.get() != nullptr;
   }

   void SetMinKey(KeyType key) {
        min_ = key;
        is_set_ = true;
   }

   void SetMaxKey(KeyType key){
       max_ = key;
       is_set_ = true;
   }

   void SetMinValue(ValueType valueType){
       min_value_ = std::move(std::make_unique<ValueType>(valueType));
   }

   void SetMaxValue(ValueType valueType){
       max_value_ = std::move(std::make_unique<ValueType>(valueType));
   }

   [[nodiscard]] KeyType GetMinKey() const{
       return min_;
   }

   [[nodiscard]] KeyType GetMaxKey() const{
       return max_;
   }

   [[nodiscard]] ValueType GetMinValue() const{
       return *min_value_;
   }

    [[nodiscard]] ValueType& GetMinValue(){
        return *min_value_;
    }

   [[nodiscard]] ValueType GetMaxValue() const{
       return *max_value_;
   }


    [[nodiscard]] ValueType& GetMaxValue(){
        return *max_value_;
    }

};


#endif //DHCPALLOCATOR_VEBTREEWITHHASHMAPNODE_H
