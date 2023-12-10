//
// Created by Abhijith  K A on 10/12/23.
//

#ifndef HASHEDVEBTREEMAP_VEBTREEVALUECONCEPT_H
#define HASHEDVEBTREEMAP_VEBTREEVALUECONCEPT_H

#include <concepts>
#include <memory>

template<typename T>
concept VEBTreeValue = requires() {
    typename std::unique_ptr<T>;
};

#endif //HASHEDVEBTREEMAP_VEBTREEVALUECONCEPT_H
