//
// Created by Abhijith  K A on 16/07/23.
//

#include "VEBTreeValueObject.h"

VEBTreeValueObject::VEBTreeValueObject(ip_t capacity) :capacity_(capacity) {

}

VEBTreeValueObject::VEBTreeValueObject() :capacity_(1){

}

ip_t VEBTreeValueObject::GetCapacity() const {
    return capacity_;
}

VEBTreeValueObject::VEBTreeValueObject(const VEBTreeValueObject &other) = default;

VEBTreeValueObject &VEBTreeValueObject::operator=(const VEBTreeValueObject &other) = default;
