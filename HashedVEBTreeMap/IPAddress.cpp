//
// Created by Abhijith  K A on 11/07/23.
//

#include "IPAddress.h"

IPAddress::IPAddress(ip_t value) :value_(value){

}

ip_t IPAddress::GetValue() const {
    return value_;
}
