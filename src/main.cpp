//
// Created by Abhijith  K A on 10/12/23.
//

#include "VEBTreeWithHashMap.h"


int main(){

    constexpr veb_hm_t  universe = 16;

   VEBTreeWithHashMap<int> vebTreeWithHashMap{16};

   vebTreeWithHashMap.Insert(1,5);

   auto response = vebTreeWithHashMap.GetValue(1);

   if(response.first){
       std::cout<<response.second<<"\n";
   }
   else{
       std::cout<<"no value for key "<<response.first<<"\n";
   }
}