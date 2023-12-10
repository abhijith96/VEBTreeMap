//
// Created by Abhijith  K A on 14/07/23.
//

#ifndef DHCPALLOCATOR_VEBTREEWITHHASHMAP_H
#define DHCPALLOCATOR_VEBTREEWITHHASHMAP_H

#include "VEBTreeWithHashMapNode.h"
#include "VEBTreeNodeKeyType.h"
#include <memory>

template <class ValueType>
class VEBTreeWithHashMap {
private:
   std::unique_ptr<VEBTreeWithHashMapNode<ValueType>> root_veb_tree_;
   void InsertHelper(VEBTreeWithHashMapNode<ValueType>& currentNode, veb_hm_t key, ValueType value);

   void DeleteHelper(VEBTreeWithHashMapNode<ValueType>& currentNode, veb_hm_t key);

    std::tuple<VEBTreeNodeKeyType, veb_hm_t, ValueType> GetSuccessorHelper(VEBTreeWithHashMapNode<ValueType>& currentNode, veb_hm_t key);

    std::tuple<VEBTreeNodeKeyType, veb_hm_t, ValueType> GetPredecessorHelper(VEBTreeWithHashMapNode<ValueType>& currentNode, veb_hm_t key);

    veb_hm_t High(veb_hm_t key, veb_hm_t universe);

    veb_hm_t Low(veb_hm_t key, veb_hm_t universe);

    veb_hm_t Index(veb_hm_t key, veb_hm_t lowKey, veb_hm_t universe);

    veb_hm_t GetItemsCount(veb_hm_t universe);

    veb_hm_t GetClusterCount(veb_hm_t universe);

public:
   explicit VEBTreeWithHashMap(veb_hm_t universe);

   VEBTreeWithHashMap(VEBTreeWithHashMap && other) noexcept;

   VEBTreeWithHashMap& operator = (VEBTreeWithHashMap&& other) noexcept;



    std::tuple<bool, veb_hm_t, ValueType> FindKey(veb_hm_t key);

   std::pair<bool, std::reference_wrapper<ValueType>> GetValue(veb_hm_t key);


    void Insert(veb_hm_t key, ValueType value);

    void Delete(veb_hm_t key);

    std::tuple<VEBTreeNodeKeyType, veb_hm_t, ValueType> Successor(veb_hm_t key);

    std::tuple<VEBTreeNodeKeyType, veb_hm_t , ValueType> Predecessor(veb_hm_t key);

    [[nodiscard]] bool IsEmpty() const;
};


#endif //DHCPALLOCATOR_VEBTREEWITHHASHMAP_H
