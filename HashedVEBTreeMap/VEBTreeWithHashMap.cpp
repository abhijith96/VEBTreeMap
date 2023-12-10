//
// Created by Abhijith  K A on 14/07/23.
//

#include  "VEBTreeWithHashMap.h"
#include "VEBTreeValueObject.h"
#include "VEBTreeUtil.h"
#include <iostream>
#include <memory>
#include "VEBTreeWithHashMap.h"
#include <bit>

template <typename ValueType>
VEBTreeWithHashMap<ValueType>::VEBTreeWithHashMap(veb_hm_t universe) :root_veb_tree_(
      std::move(std::make_unique<VEBTreeWithHashMapNode<ValueType>>(std::bit_ceil(universe)))
        ){
   if(root_veb_tree_->GetUniverse() < universe) {
       veb_hm_t actualUniverse = std::numeric_limits<veb_hm_t>::max();
        VEBTreeWithHashMapNode<ValueType> vebTreeWithHashMapNode{actualUniverse};
        root_veb_tree_ = std::move(std::make_unique<VEBTreeWithHashMapNode<ValueType>>(std::move(vebTreeWithHashMapNode)));

   }


}

template <typename ValueType>
VEBTreeWithHashMap<ValueType>::VEBTreeWithHashMap(VEBTreeWithHashMap && other)  noexcept = default;

template <typename ValueType>
VEBTreeWithHashMap<ValueType>& VEBTreeWithHashMap<ValueType>::operator = (VEBTreeWithHashMap&& other) noexcept{
    if(this != &other){
        root_veb_tree_ = std::move(other.root_veb_tree_);
    }

    std::cout<<"check moves\n";

    return *this;
}
template <typename ValueType>
veb_hm_t VEBTreeWithHashMap<ValueType>::High(veb_hm_t key, veb_hm_t universe) {
    auto [high, low] = VEBTreeUtils::SplitIntoHighAndLow(key, universe);
    return high;
//   veb_hm_t sqrt =  static_cast<veb_hm_t>(std::sqrt(universe));
//   return key / sqrt;
}

template <typename ValueType>
veb_hm_t  VEBTreeWithHashMap<ValueType>::Low(veb_hm_t key, veb_hm_t universe) {
    auto [high, low] = VEBTreeUtils::SplitIntoHighAndLow(key, universe);
    return low;
//    veb_hm_t sqrt =  static_cast<veb_hm_t>(std::sqrt(universe));
//    return key % sqrt;
}

template <typename ValueType>
veb_hm_t VEBTreeWithHashMap<ValueType>::Index(veb_hm_t clusterIndex, veb_hm_t lowKey, veb_hm_t universe) {
    auto [clusterCount, ItemsCount] = VEBTreeUtils::SplitIntoSquareOfPowersOfTwo(universe);
    return clusterIndex * ItemsCount + lowKey;
}

template <typename ValueType>
veb_hm_t  VEBTreeWithHashMap<ValueType>::GetItemsCount(veb_hm_t universe){
    auto [clusterCount, ItemsCount] = VEBTreeUtils::SplitIntoSquareOfPowersOfTwo(universe);
    return ItemsCount;
}

template <typename ValueType>
veb_hm_t  VEBTreeWithHashMap<ValueType>::GetClusterCount(veb_hm_t universe){
    auto [clusterCount, ItemsCount] = VEBTreeUtils::SplitIntoSquareOfPowersOfTwo(universe);
    return clusterCount;
}

template <typename ValueType>
std::tuple<bool, veb_hm_t, ValueType> VEBTreeWithHashMap<ValueType>::FindKey(veb_hm_t key){

    if(root_veb_tree_.get()) {

        VEBTreeWithHashMapNode<ValueType> *currentNode = root_veb_tree_.get();
        while (true) {
            if (!currentNode->IsSet()) {
                return {false, key, {}};
            }
            if (key < currentNode->GetMinKey() || key > currentNode->GetMaxKey()) {
                return {false, key, {}};
            }
            if (key == currentNode->GetMinKey()) {
                return {true, currentNode->GetMinKey(), currentNode->GetMinValue()};
            }
            if (key == currentNode->GetMaxKey()) {
                return {true, currentNode->GetMaxKey(), currentNode->GetMaxValue()};
            }

            veb_hm_t clusterIndex = High(key, currentNode->GetUniverse());
            veb_hm_t clusterKey = Low(key, currentNode->GetUniverse());

            if (currentNode->IsClusterSet(clusterIndex)) {
                currentNode = &currentNode->GetCluster(clusterIndex);
                key = clusterKey;
            } else {
                return {false, key, {}};
            }
        }
    }
    return {false, key, {}};
}

template <typename ValueType>
std::pair<bool, std::reference_wrapper<ValueType>>   VEBTreeWithHashMap<ValueType>::GetValue(veb_hm_t key){
    bool notFound = false;
    if(root_veb_tree_.get()) {

        VEBTreeWithHashMapNode<ValueType> *currentNode = root_veb_tree_.get();
        while (true) {
            if (!currentNode->IsSet()) {
                notFound = true;
                break;
            }
            if (key < currentNode->GetMinKey() || key > currentNode->GetMaxKey()) {
               notFound = true;
               break;
            }
            if (key == currentNode->GetMinKey()) {
               return {true, {currentNode->GetMinValue()}};
            }
            if (key == currentNode->GetMaxKey()) {
               return {true, {currentNode->GetMaxValue()}};
            }

            veb_hm_t clusterIndex = High(key, currentNode->GetUniverse());
            veb_hm_t clusterKey = Low(key, currentNode->GetUniverse());

            if (currentNode->IsClusterSet(clusterIndex)) {
                currentNode = &currentNode->GetCluster(clusterIndex);
                key = clusterKey;
            } else {
                notFound = true;
                break;
            }
        }
    }
    ValueType valueType;
    return {false, valueType};

}

template <typename ValueType>
void  VEBTreeWithHashMap<ValueType>::Insert(veb_hm_t key, ValueType value){
    InsertHelper(*root_veb_tree_, key, value);
}
template <typename ValueType>
void VEBTreeWithHashMap<ValueType>::Delete(veb_hm_t key){
    DeleteHelper(*root_veb_tree_, key);
}

template <typename ValueType>
std::tuple<VEBTreeNodeKeyType, veb_hm_t, ValueType> VEBTreeWithHashMap<ValueType>::Successor(veb_hm_t key){
    return GetSuccessorHelper(*root_veb_tree_, key);
}

template <typename ValueType>
std::tuple<VEBTreeNodeKeyType, veb_hm_t , ValueType> VEBTreeWithHashMap<ValueType>::Predecessor(veb_hm_t key){
    return GetPredecessorHelper(*root_veb_tree_, key);
}

template <typename ValueType>
bool  VEBTreeWithHashMap<ValueType>::IsEmpty() const{
    return !root_veb_tree_->IsSet();
}

template <typename ValueType>
void  VEBTreeWithHashMap<ValueType>::InsertHelper(VEBTreeWithHashMapNode<ValueType>& currentNode, veb_hm_t key, ValueType value){
    if(key > currentNode.GetUniverse()){
        return;
    }
    if(!currentNode.IsSet()){
        currentNode.SetMinKey(key);
        currentNode.SetMaxKey(key);
        currentNode.SetMaxValue(value);
        currentNode.SetMinValue(value);
        return;
    }
    if(currentNode.GetMaxKey() == currentNode.GetMinKey()){
        if(key > currentNode.GetMinKey()){
            currentNode.SetMaxKey(key);
            currentNode.SetMaxValue(value);
        }
        else if(key < currentNode.GetMinKey()){
            currentNode.SetMinKey(key);
            currentNode.SetMinValue(value);
        }
        return;
    }
    if(key < currentNode.GetMinKey()){
        veb_hm_t temp = currentNode.GetMinKey();
        ValueType tempValueType = currentNode.GetMinValue();
        currentNode.SetMinKey(key);
        currentNode.SetMinValue(value);
        key = temp;
        value = tempValueType;
    }
    if(key > currentNode.GetMaxKey()){
        veb_hm_t maxKeyCopy = currentNode.GetMaxKey();
        ValueType maxValCopy = currentNode.GetMaxValue();
        currentNode.SetMaxKey(key);
        currentNode.SetMaxValue(value);
        key = maxKeyCopy;
        value = maxValCopy;
    }

    veb_hm_t clusterIndex = High(key, currentNode.GetUniverse());
    veb_hm_t lowIndex = Low(key, currentNode.GetUniverse());

    if(currentNode.IsClusterSet(clusterIndex)){
        InsertHelper(currentNode.GetCluster(clusterIndex), lowIndex, value);
    }
    else{
        currentNode.SetCluster(clusterIndex, GetItemsCount(currentNode.GetUniverse()));
        if(!currentNode.IsSummarySet())
            currentNode.SetSummary(GetClusterCount(currentNode.GetUniverse()));
        InsertHelper(currentNode.GetCluster(clusterIndex), lowIndex, value);
        InsertHelper(currentNode.GetSummary(), clusterIndex, value);
    }

}

template <typename ValueType>
void  VEBTreeWithHashMap<ValueType>::DeleteHelper(VEBTreeWithHashMapNode<ValueType>& currentNode, veb_hm_t key){
    if(!currentNode.IsSet()) return;

    if(key < currentNode.GetMinKey() || key > currentNode.GetMaxKey()) return;

    if(currentNode.GetMaxKey() == currentNode.GetMinKey()){
        if(key == currentNode.GetMaxKey()){
            currentNode.Unset();
        }
        return;
    }
    if(!currentNode.IsSummarySet()){
        if(currentNode.GetMaxKey() == key){
            currentNode.SetMaxKey(currentNode.GetMinKey());
            currentNode.SetMaxValue(currentNode.GetMinValue());
        }
        else if(currentNode.GetMinKey() == key){
            currentNode.SetMinKey(currentNode.GetMaxKey());
            currentNode.SetMinValue(currentNode.GetMaxValue());
        }
        return;
    }
    if(currentNode.GetMaxKey() == key){
        veb_hm_t  newMaxKeyCluster = currentNode.GetSummary().GetMaxKey();
        veb_hm_t newMaxKeyIndex = currentNode.GetCluster(newMaxKeyCluster).GetMaxKey();
        ValueType newMaxValue = currentNode.GetCluster(newMaxKeyCluster).GetMaxValue();
        veb_hm_t newMaxKeyIndexInCurrentUniverse = Index(newMaxKeyCluster, newMaxKeyIndex, currentNode.GetUniverse());
        currentNode.SetMaxKey(newMaxKeyIndexInCurrentUniverse);
        currentNode.SetMaxValue(newMaxValue);
        key = newMaxKeyIndexInCurrentUniverse;
    }

    else if(currentNode.GetMinKey() == key){
        veb_hm_t newMinKeyCluster = currentNode.GetSummary().GetMinKey();
        veb_hm_t newMinKeyIndex = currentNode.GetCluster(newMinKeyCluster).GetMinKey();
        ValueType newMinValue = currentNode.GetCluster(newMinKeyCluster).GetMinValue();
        veb_hm_t  newMinKeyIndexInCurrentUniverse = Index(newMinKeyCluster, newMinKeyIndex, currentNode.GetUniverse());
        currentNode.SetMinKey(newMinKeyIndexInCurrentUniverse);
        currentNode.SetMinValue(newMinValue);
        key = newMinKeyIndexInCurrentUniverse;
    }

    veb_hm_t clusterIndex = High(key, currentNode.GetUniverse());
    veb_hm_t lowIndex = Low(key, currentNode.GetUniverse());

    DeleteHelper(currentNode.GetCluster(clusterIndex), lowIndex);
    if(!currentNode.GetCluster(clusterIndex).IsSet()){
        currentNode.UnsetCluster(clusterIndex);
        DeleteHelper(currentNode.GetSummary(), clusterIndex);
        if(!currentNode.GetSummary().IsSet()){
            currentNode.UnsetSummary();
        }
    }
}

template <typename ValueType>
std::tuple<VEBTreeNodeKeyType, veb_hm_t, ValueType>  VEBTreeWithHashMap<ValueType>::GetSuccessorHelper(VEBTreeWithHashMapNode<ValueType>& currentNode, veb_hm_t key){
    if(currentNode.IsSet()) {
        if (currentNode.GetMaxKey() < key) {
            return {VEBTreeNodeKeyType::POSITIVE_INFINITY, veb_hm_t{}, ValueType{}};
        }
        if (currentNode.GetMaxKey() == key) {
            return {VEBTreeNodeKeyType::NORMAL, currentNode.GetMaxKey(), currentNode.GetMaxValue()};
        }
        if (currentNode.GetMinKey() >= key) {
            return {VEBTreeNodeKeyType::NORMAL, currentNode.GetMinKey(), currentNode.GetMinValue()};
        }

        veb_hm_t clusterIndex = High(key, currentNode.GetUniverse());
        veb_hm_t lowIndex = Low(key, currentNode.GetUniverse());
        if (currentNode.IsClusterSet(clusterIndex) &&
            Index(clusterIndex, currentNode.GetCluster(clusterIndex).GetMaxKey(), currentNode.GetUniverse()) >= key) {
            auto [nodeType, keyFromCluster, value] = GetSuccessorHelper(currentNode.GetCluster(clusterIndex), lowIndex);
            veb_hm_t clusterKeyIndexInCurrentUniverse = Index(clusterIndex, keyFromCluster, currentNode.GetUniverse());
            return {nodeType, clusterKeyIndexInCurrentUniverse, value};
        }

        if (currentNode.IsSummarySet()) {
            if (clusterIndex + 1 >= GetClusterCount(currentNode.GetUniverse())) {
                return {VEBTreeNodeKeyType::NORMAL, currentNode.GetMaxKey(), currentNode.GetMaxValue()};
            } else {
                auto [nodeType, nextClusterIndex, nextClusterValue] = GetSuccessorHelper(currentNode.GetSummary(),
                                                                                         clusterIndex + 1);
                if (nodeType == VEBTreeNodeKeyType::NORMAL) {
                    veb_hm_t minKeyInNextCluster = currentNode.GetCluster(nextClusterIndex).GetMinKey();
                    veb_hm_t minKeyIndexInCurrentUniverse = Index(nextClusterIndex, minKeyInNextCluster,
                                                                  currentNode.GetUniverse());
                    return {nodeType, minKeyIndexInCurrentUniverse,
                            currentNode.GetCluster(nextClusterIndex).GetMinValue()};
                } else {
                    return {VEBTreeNodeKeyType::NORMAL, currentNode.GetMaxKey(), currentNode.GetMaxValue()};
                }
            }
        } else {
            return {VEBTreeNodeKeyType::NORMAL, currentNode.GetMaxKey(), currentNode.GetMaxValue()};
        }

    }
    else{

        return {VEBTreeNodeKeyType::POSITIVE_INFINITY, veb_hm_t{}, ValueType{}};
    }
}

template <typename ValueType>
std::tuple<VEBTreeNodeKeyType, veb_hm_t, ValueType>  VEBTreeWithHashMap<ValueType>::GetPredecessorHelper(VEBTreeWithHashMapNode<ValueType>& currentNode, veb_hm_t key){

    if(currentNode.IsSet()){
        if(currentNode.GetMinKey() > key){
            return {VEBTreeNodeKeyType::NEGATIVE_INFINITY, veb_hm_t{}, ValueType{}};
        }
        if(currentNode.GetMinKey() == key){
            return {VEBTreeNodeKeyType::NORMAL, currentNode.GetMinKey(), currentNode.GetMinValue()};
        }
        if(currentNode.GetMaxKey() <= key){
            return {VEBTreeNodeKeyType::NORMAL, currentNode.GetMaxKey(), currentNode.GetMaxValue()};
        }

        veb_hm_t  clusterIndex = High(key, currentNode.GetUniverse());
        veb_hm_t  lowIndex = Low(key, currentNode.GetUniverse());
        if(currentNode.IsClusterSet(clusterIndex) && Index(clusterIndex, currentNode.GetCluster(clusterIndex).GetMinKey(),currentNode.GetUniverse()) <= key){
            auto [nodeType, keyFromCluster, value] = GetPredecessorHelper(currentNode.GetCluster(clusterIndex), lowIndex);
            veb_hm_t clusterKeyIndexInCurrentUniverse = Index(clusterIndex, keyFromCluster, currentNode.GetUniverse());
            return {nodeType, clusterKeyIndexInCurrentUniverse, value};
        }
        else{
            if(currentNode.IsSummarySet()){
                if(clusterIndex == 0){
                    return {VEBTreeNodeKeyType::NORMAL, currentNode.GetMinKey(), currentNode.GetMinValue()};
                }
                else{
                    auto [nodeType, previousClusterIndex, previousClusterValue] = GetSuccessorHelper(currentNode.GetSummary(),
                                                                                             clusterIndex - 1);
                    if(nodeType == VEBTreeNodeKeyType::NORMAL){
                        veb_hm_t maxKeyInPreviousCluster = currentNode.GetCluster(previousClusterIndex).GetMaxKey();
                        veb_hm_t maxKeyIndexInCurrentUniverse = Index(previousClusterIndex, maxKeyInPreviousCluster, currentNode.GetUniverse());
                        return {nodeType, maxKeyIndexInCurrentUniverse, currentNode.GetCluster(previousClusterIndex).GetMaxValue()};
                    }
                    else{
                        return {VEBTreeNodeKeyType::NORMAL, currentNode.GetMinKey(), currentNode.GetMinValue()};
                    }
                }
            }
            else{
                return {VEBTreeNodeKeyType::NORMAL, currentNode.GetMinKey(), currentNode.GetMinValue()};
            }
        }
    }
    else{

        return {VEBTreeNodeKeyType::NEGATIVE_INFINITY, veb_hm_t{}, ValueType{}};
    }

}

template class VEBTreeWithHashMap<int>;
template class VEBTreeWithHashMap<veb_hm_t>;
template class VEBTreeWithHashMap<VEBTreeValueObject>;



