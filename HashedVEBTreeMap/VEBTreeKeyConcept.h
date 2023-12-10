//
// Created by Abhijith  K A on 10/12/23.
//

#ifndef HASHEDVEBTREEMAP_VEBTREEKEYCONCEPT_H
#define HASHEDVEBTREEMAP_VEBTREEKEYCONCEPT_H

#include <concepts>




template<typename T>
concept HasUnsignedIntegralConversion = requires(T t) {
    static_cast<std::integral_constant<bool, std::is_unsigned_v<decltype(static_cast<unsigned char>(t))> ||
                                             std::is_unsigned_v<decltype(static_cast<unsigned short>(t))> ||
                                             std::is_unsigned_v<decltype(static_cast<unsigned int>(t))> ||
                                             std::is_unsigned_v<decltype(static_cast<unsigned long>(t))> ||
                                             std::is_unsigned_v<decltype(static_cast<unsigned long long>(t))>>>(*t);

};

template<typename T>
//concept VEBTreeKey = std::unsigned_integral<T> || HasUnsignedIntegralConversion<T>;
concept VEBTreeKey = std::unsigned_integral<T>;

#endif //HASHEDVEBTREEMAP_VEBTREEKEYCONCEPT_H
