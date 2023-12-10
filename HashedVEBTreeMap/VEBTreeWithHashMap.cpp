//
// Created by Abhijith  K A on 14/07/23.
//

#include "VEBTreeWithHashMap.h"
#include "VEBTreeValueObject.h"
#include "VEBTreeUtil.h"
#include <memory>
#include <bit>

template <VEBTreeKey KeyType, VEBTreeValue ValueType,typename Hash, typename Equal>
VEBTreeWithHashMap<KeyType,ValueType, Hash, Equal>::VEBTreeWithHashMap(KeyType universe) :root_veb_tree_(
      std::move(std::make_unique<VEBTreeWithHashMapNode<KeyType,ValueType, Hash, Equal>>(std::bit_ceil(universe)))
        ){
   if(root_veb_tree_->GetUniverse() < universe) {
       KeyType actualUniverse = std::numeric_limits<KeyType>::max();
        VEBTreeWithHashMapNode<KeyType, ValueType, Hash, Equal> vebTreeWithHashMapNode{actualUniverse};
        root_veb_tree_ = std::move(std::make_unique<VEBTreeWithHashMapNode<KeyType,ValueType,Hash,Equal>>(std::move(vebTreeWithHashMapNode)));

   }
}

template <VEBTreeKey KeyType, VEBTreeValue ValueType,typename Hash, typename Equal>
VEBTreeWithHashMap<KeyType,ValueType, Hash, Equal>::VEBTreeWithHashMap(KeyType universe, Hash hashObj, Equal equalObj):root_veb_tree_(
        std::move(std::make_unique<VEBTreeWithHashMapNode<KeyType,ValueType, Hash, Equal>>(std::bit_ceil(universe), hashObj, equalObj))
){
    if(root_veb_tree_->GetUniverse() < universe) {
        KeyType actualUniverse = std::numeric_limits<KeyType>::max();
        VEBTreeWithHashMapNode<KeyType, ValueType, Hash, Equal> vebTreeWithHashMapNode{actualUniverse, hashObj, equalObj};
        root_veb_tree_ = std::move(std::make_unique<VEBTreeWithHashMapNode<KeyType,ValueType,Hash,Equal>>(std::move(vebTreeWithHashMapNode)));

    }
}



template <VEBTreeKey KeyType, VEBTreeValue ValueType,typename Hash, typename Equal>
VEBTreeWithHashMap<KeyType,ValueType, Hash, Equal>::VEBTreeWithHashMap(VEBTreeWithHashMap && other)  noexcept = default;

template <VEBTreeKey KeyType, VEBTreeValue ValueType,typename Hash, typename Equal>
VEBTreeWithHashMap<KeyType,ValueType, Hash, Equal>& VEBTreeWithHashMap<KeyType,ValueType, Hash, Equal>::operator = (VEBTreeWithHashMap&& other) noexcept{
    if(this != &other){
        root_veb_tree_ = std::move(other.root_veb_tree_);
    }
    return *this;
}

template <VEBTreeKey KeyType, VEBTreeValue ValueType,typename Hash, typename Equal>
KeyType VEBTreeWithHashMap<KeyType,ValueType, Hash, Equal>::High(KeyType key, KeyType universe) {
    auto [high, low] = VEBTreeUtils::SplitIntoHighAndLow(key, universe);
    return high;
}

template <VEBTreeKey KeyType, VEBTreeValue ValueType,typename Hash, typename Equal>
KeyType  VEBTreeWithHashMap<KeyType,ValueType, Hash, Equal>::Low(KeyType key, KeyType universe) {
    auto [high, low] = VEBTreeUtils::SplitIntoHighAndLow(key, universe);
    return low;
}

template <VEBTreeKey KeyType, VEBTreeValue ValueType,typename Hash, typename Equal>
KeyType VEBTreeWithHashMap<KeyType,ValueType, Hash, Equal>::Index(KeyType clusterIndex, KeyType lowKey, KeyType universe) {
    auto [clusterCount, ItemsCount] = VEBTreeUtils::SplitIntoSquareOfPowersOfTwo(universe);
    return clusterIndex * ItemsCount + lowKey;
}

template <VEBTreeKey KeyType, VEBTreeValue ValueType,typename Hash, typename Equal>
KeyType  VEBTreeWithHashMap<KeyType,ValueType, Hash, Equal>::GetItemsCount(KeyType universe){
    auto [clusterCount, ItemsCount] = VEBTreeUtils::SplitIntoSquareOfPowersOfTwo(universe);
    return ItemsCount;
}

template <VEBTreeKey KeyType, VEBTreeValue ValueType,typename Hash, typename Equal>
KeyType  VEBTreeWithHashMap<KeyType,ValueType, Hash, Equal>::GetClusterCount(KeyType universe){
    auto [clusterCount, ItemsCount] = VEBTreeUtils::SplitIntoSquareOfPowersOfTwo(universe);
    return clusterCount;
}

template <VEBTreeKey KeyType, VEBTreeValue ValueType,typename Hash, typename Equal>
std::tuple<bool, KeyType, ValueType> VEBTreeWithHashMap<KeyType,ValueType, Hash, Equal>::FindKey(KeyType key){

    if(root_veb_tree_.get()) {

        VEBTreeWithHashMapNode<KeyType,ValueType, Hash, Equal> *currentNode = root_veb_tree_.get();
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

            KeyType clusterIndex = High(key, currentNode->GetUniverse());
            KeyType clusterKey = Low(key, currentNode->GetUniverse());

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

template <VEBTreeKey KeyType, VEBTreeValue ValueType,typename Hash, typename Equal>
std::pair<bool, std::reference_wrapper<ValueType>>   VEBTreeWithHashMap<KeyType,ValueType, Hash, Equal>::GetValue(KeyType key){
    bool notFound = false;
    if(root_veb_tree_.get()) {

        VEBTreeWithHashMapNode<KeyType, ValueType, Hash, Equal> *currentNode = root_veb_tree_.get();
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

            KeyType clusterIndex = High(key, currentNode->GetUniverse());
            KeyType clusterKey = Low(key, currentNode->GetUniverse());

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

template <VEBTreeKey KeyType, VEBTreeValue ValueType,typename Hash, typename Equal>
void  VEBTreeWithHashMap<KeyType,ValueType, Hash, Equal>::Insert(KeyType key, ValueType value){
    InsertHelper(*root_veb_tree_, key, value);
}
template <VEBTreeKey KeyType, VEBTreeValue ValueType,typename Hash, typename Equal>
void VEBTreeWithHashMap<KeyType,ValueType, Hash, Equal>::Delete(KeyType key){
    DeleteHelper(*root_veb_tree_, key);
}

template <VEBTreeKey KeyType, VEBTreeValue ValueType,typename Hash, typename Equal>
std::tuple<VEBTreeNodeKeyType, KeyType, ValueType> VEBTreeWithHashMap<KeyType,ValueType, Hash, Equal>::Successor(KeyType key){
    return GetSuccessorHelper(*root_veb_tree_, key);
}

template <VEBTreeKey KeyType, VEBTreeValue ValueType,typename Hash, typename Equal>
std::tuple<VEBTreeNodeKeyType, KeyType, ValueType> VEBTreeWithHashMap<KeyType,ValueType, Hash, Equal>::Predecessor(KeyType  key){
    return GetPredecessorHelper(*root_veb_tree_, key);
}

template <VEBTreeKey KeyType, VEBTreeValue ValueType,typename Hash, typename Equal>
bool  VEBTreeWithHashMap<KeyType,ValueType, Hash, Equal>::IsEmpty() const{
    return !root_veb_tree_->IsSet();
}

template <VEBTreeKey KeyType, VEBTreeValue ValueType,typename Hash, typename Equal>
void  VEBTreeWithHashMap<KeyType,ValueType, Hash, Equal>::InsertHelper(VEBTreeWithHashMapNode<KeyType,ValueType, Hash, Equal>& currentNode, KeyType key, ValueType value){
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
        KeyType temp = currentNode.GetMinKey();
        ValueType tempValueType = currentNode.GetMinValue();
        currentNode.SetMinKey(key);
        currentNode.SetMinValue(value);
        key = temp;
        value = tempValueType;
    }
    if(key > currentNode.GetMaxKey()){
        KeyType maxKeyCopy = currentNode.GetMaxKey();
        ValueType maxValCopy = currentNode.GetMaxValue();
        currentNode.SetMaxKey(key);
        currentNode.SetMaxValue(value);
        key = maxKeyCopy;
        value = maxValCopy;
    }

    KeyType clusterIndex = High(key, currentNode.GetUniverse());
    KeyType lowIndex = Low(key, currentNode.GetUniverse());

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

template <VEBTreeKey KeyType, VEBTreeValue ValueType,typename Hash, typename Equal>
void  VEBTreeWithHashMap<KeyType,ValueType, Hash, Equal>::DeleteHelper(VEBTreeWithHashMapNode<KeyType,ValueType, Hash, Equal>& currentNode, KeyType key){
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
        KeyType  newMaxKeyCluster = currentNode.GetSummary().GetMaxKey();
        KeyType newMaxKeyIndex = currentNode.GetCluster(newMaxKeyCluster).GetMaxKey();
        ValueType newMaxValue = currentNode.GetCluster(newMaxKeyCluster).GetMaxValue();
        KeyType newMaxKeyIndexInCurrentUniverse = Index(newMaxKeyCluster, newMaxKeyIndex, currentNode.GetUniverse());
        currentNode.SetMaxKey(newMaxKeyIndexInCurrentUniverse);
        currentNode.SetMaxValue(newMaxValue);
        key = newMaxKeyIndexInCurrentUniverse;
    }

    else if(currentNode.GetMinKey() == key){
        KeyType newMinKeyCluster = currentNode.GetSummary().GetMinKey();
        KeyType newMinKeyIndex = currentNode.GetCluster(newMinKeyCluster).GetMinKey();
        ValueType newMinValue = currentNode.GetCluster(newMinKeyCluster).GetMinValue();
        KeyType  newMinKeyIndexInCurrentUniverse = Index(newMinKeyCluster, newMinKeyIndex, currentNode.GetUniverse());
        currentNode.SetMinKey(newMinKeyIndexInCurrentUniverse);
        currentNode.SetMinValue(newMinValue);
        key = newMinKeyIndexInCurrentUniverse;
    }

    KeyType clusterIndex = High(key, currentNode.GetUniverse());
    KeyType lowIndex = Low(key, currentNode.GetUniverse());

    DeleteHelper(currentNode.GetCluster(clusterIndex), lowIndex);
    if(!currentNode.GetCluster(clusterIndex).IsSet()){
        currentNode.UnsetCluster(clusterIndex);
        DeleteHelper(currentNode.GetSummary(), clusterIndex);
        if(!currentNode.GetSummary().IsSet()){
            currentNode.UnsetSummary();
        }
    }
}

template <VEBTreeKey KeyType, VEBTreeValue ValueType,typename Hash, typename Equal>
std::tuple<VEBTreeNodeKeyType, KeyType, ValueType>  VEBTreeWithHashMap<KeyType,ValueType, Hash, Equal>::GetSuccessorHelper(VEBTreeWithHashMapNode<KeyType,ValueType, Hash, Equal>& currentNode, KeyType key){
    if(currentNode.IsSet()) {
        if (currentNode.GetMaxKey() < key) {
            return {VEBTreeNodeKeyType::POSITIVE_INFINITY, KeyType{}, ValueType{}};
        }
        if (currentNode.GetMaxKey() == key) {
            return {VEBTreeNodeKeyType::NORMAL, currentNode.GetMaxKey(), currentNode.GetMaxValue()};
        }
        if (currentNode.GetMinKey() >= key) {
            return {VEBTreeNodeKeyType::NORMAL, currentNode.GetMinKey(), currentNode.GetMinValue()};
        }

        KeyType clusterIndex = High(key, currentNode.GetUniverse());
        KeyType lowIndex = Low(key, currentNode.GetUniverse());
        if (currentNode.IsClusterSet(clusterIndex) &&
            Index(clusterIndex, currentNode.GetCluster(clusterIndex).GetMaxKey(), currentNode.GetUniverse()) >= key) {
            auto [nodeType, keyFromCluster, value] = GetSuccessorHelper(currentNode.GetCluster(clusterIndex), lowIndex);
            KeyType clusterKeyIndexInCurrentUniverse = Index(clusterIndex, keyFromCluster, currentNode.GetUniverse());
            return {nodeType, clusterKeyIndexInCurrentUniverse, value};
        }

        if (currentNode.IsSummarySet()) {
            if (clusterIndex + 1 >= GetClusterCount(currentNode.GetUniverse())) {
                return {VEBTreeNodeKeyType::NORMAL, currentNode.GetMaxKey(), currentNode.GetMaxValue()};
            } else {
                auto [nodeType, nextClusterIndex, nextClusterValue] = GetSuccessorHelper(currentNode.GetSummary(),
                                                                                         clusterIndex + 1);
                if (nodeType == VEBTreeNodeKeyType::NORMAL) {
                    KeyType minKeyInNextCluster = currentNode.GetCluster(nextClusterIndex).GetMinKey();
                    KeyType minKeyIndexInCurrentUniverse = Index(nextClusterIndex, minKeyInNextCluster,
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

        return {VEBTreeNodeKeyType::POSITIVE_INFINITY, KeyType{}, ValueType{}};
    }
}

template <VEBTreeKey KeyType, VEBTreeValue ValueType,typename Hash, typename Equal>
std::tuple<VEBTreeNodeKeyType, KeyType, ValueType> VEBTreeWithHashMap<KeyType,ValueType, Hash, Equal>::GetPredecessorHelper(VEBTreeWithHashMapNode<KeyType,ValueType, Hash, Equal>& currentNode, KeyType key){

    if(currentNode.IsSet()){
        if(currentNode.GetMinKey() > key){
            return {VEBTreeNodeKeyType::NEGATIVE_INFINITY, KeyType{}, ValueType{}};
        }
        if(currentNode.GetMinKey() == key){
            return {VEBTreeNodeKeyType::NORMAL, currentNode.GetMinKey(), currentNode.GetMinValue()};
        }
        if(currentNode.GetMaxKey() <= key){
            return {VEBTreeNodeKeyType::NORMAL, currentNode.GetMaxKey(), currentNode.GetMaxValue()};
        }

        KeyType  clusterIndex = High(key, currentNode.GetUniverse());
        KeyType  lowIndex = Low(key, currentNode.GetUniverse());
        if(currentNode.IsClusterSet(clusterIndex) && Index(clusterIndex, currentNode.GetCluster(clusterIndex).GetMinKey(),currentNode.GetUniverse()) <= key){
            auto [nodeType, keyFromCluster, value] = GetPredecessorHelper(currentNode.GetCluster(clusterIndex), lowIndex);
            KeyType clusterKeyIndexInCurrentUniverse = Index(clusterIndex, keyFromCluster, currentNode.GetUniverse());
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
                        KeyType maxKeyInPreviousCluster = currentNode.GetCluster(previousClusterIndex).GetMaxKey();
                        KeyType maxKeyIndexInCurrentUniverse = Index(previousClusterIndex, maxKeyInPreviousCluster, currentNode.GetUniverse());
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

        return {VEBTreeNodeKeyType::NEGATIVE_INFINITY, KeyType{}, ValueType{}};
    }

}

template class VEBTreeWithHashMap<uint32_t ,int>;
template class VEBTreeWithHashMap<uint32_t, uint32_t>;
template class VEBTreeWithHashMap<uint32_t, VEBTreeValueObject>;



