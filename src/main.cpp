//
// Created by Abhijith  K A on 10/12/23.
//

#include "VEBTreeWithHashMap.h"
#include <iostream>


int main(){

    constexpr uint32_t universe = 16;

   VEBTreeWithHashMap<uint32_t,int> vebTreeWithHashMap{16};

   vebTreeWithHashMap.Insert(1,5);

   auto response = vebTreeWithHashMap.GetValue(1);

   if(response.first){
       std::cout<<response.second<<"\n";
   }
   else{
       std::cout<<"no value for key "<<response.first<<"\n";
   }
}