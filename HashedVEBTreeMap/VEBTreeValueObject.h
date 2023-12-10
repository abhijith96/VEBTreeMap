//
// Created by Abhijith  K A on 16/07/23.
//

#ifndef DHCPALLOCATOR_VEBTREEVALUEOBJECT_H
#define DHCPALLOCATOR_VEBTREEVALUEOBJECT_H

#include "VEBTreeValueObject.h"
#include "IPAddress.h"

class VEBTreeValueObject {
private:
    ip_t capacity_;
public:
    explicit VEBTreeValueObject(ip_t capacity);
    VEBTreeValueObject();
    VEBTreeValueObject& operator = (VEBTreeValueObject&& other) noexcept = default;
    VEBTreeValueObject(const VEBTreeValueObject& other);
    VEBTreeValueObject & operator = (const VEBTreeValueObject& other);

    [[nodiscard]] ip_t GetCapacity() const;
};


#endif //DHCPALLOCATOR_VEBTREEVALUEOBJECT_H
