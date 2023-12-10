//
// Created by Abhijith  K A on 15/07/23.
//

#ifndef DHCPALLOCATOR_VEBTREENODEKEYTYPE_H

#define DHCPALLOCATOR_VEBTREENODEKEYTYPE_H

#include <cstdint>

enum class VEBTreeNodeKeyType : uint8_t {
    NORMAL = 0,
    POSITIVE_INFINITY = 1,
    NEGATIVE_INFINITY = 2
};




#endif //DHCPALLOCATOR_VEBTREENODEKEYTYPE_H
