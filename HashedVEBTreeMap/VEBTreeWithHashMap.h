//
// Created by Abhijith  K A on 14/07/23.
//

#ifndef DHCPALLOCATOR_VEBTREEWITHHASHMAP_H
#define DHCPALLOCATOR_VEBTREEWITHHASHMAP_H

#include "VEBTreeWithHashMapNode.h"
#include "VEBTreeNodeKeyType.h"
#include <memory>

template <VEBTreeKey KeyType, VEBTreeValue ValueType,typename Hash = std::hash<KeyType>, typename Equal = std::equal_to<KeyType>>
class VEBTreeWithHashMap {
private:
   std::unique_ptr<VEBTreeWithHashMapNode<KeyType, ValueType, Hash, Equal>> root_veb_tree_;
   void InsertHelper(VEBTreeWithHashMapNode<KeyType,ValueType, Hash, Equal>& currentNode, KeyType key, ValueType value);

   void DeleteHelper(VEBTreeWithHashMapNode<KeyType,ValueType, Hash, Equal>& currentNode, KeyType key);

    std::tuple<VEBTreeNodeKeyType, KeyType, ValueType> GetSuccessorHelper(VEBTreeWithHashMapNode<KeyType,ValueType, Hash, Equal>& currentNode, KeyType key);

    std::tuple<VEBTreeNodeKeyType, KeyType, ValueType> GetPredecessorHelper(VEBTreeWithHashMapNode<KeyType,ValueType, Hash, Equal>& currentNode, KeyType key);

    KeyType High(KeyType key, KeyType universe);

    KeyType Low(KeyType key, KeyType universe);

    KeyType Index(KeyType key, KeyType lowKey, KeyType universe);

    KeyType GetItemsCount(KeyType universe);

    KeyType GetClusterCount(KeyType universe);

public:
   explicit VEBTreeWithHashMap(KeyType universe);

   explicit VEBTreeWithHashMap(KeyType universe, Hash hashObj, Equal equalObj);

   VEBTreeWithHashMap(VEBTreeWithHashMap && other) noexcept;

   VEBTreeWithHashMap& operator = (VEBTreeWithHashMap&& other) noexcept;



    std::tuple<bool, KeyType, ValueType> FindKey(KeyType key);

   std::pair<bool, std::reference_wrapper<ValueType>> GetValue(KeyType key);


    void Insert(KeyType key, ValueType value);

    void Delete(KeyType key);

    std::tuple<VEBTreeNodeKeyType, KeyType, ValueType> Successor(KeyType key);

    std::tuple<VEBTreeNodeKeyType, KeyType , ValueType> Predecessor(KeyType key);

    [[nodiscard]] bool IsEmpty() const;
};


#endif //DHCPALLOCATOR_VEBTREEWITHHASHMAP_H
