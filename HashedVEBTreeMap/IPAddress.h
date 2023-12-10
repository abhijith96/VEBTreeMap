//
// Created by Abhijith  K A on 11/07/23.
//

#ifndef DHCPALLOCATOR_IPADDRESS_H
#define DHCPALLOCATOR_IPADDRESS_H

#include <cstdint>

using ip_t = uint32_t;

class IPAddress {
private:
    ip_t value_;

public:
    explicit IPAddress(ip_t value);

    IPAddress(IPAddress&& other) =default;

    IPAddress& operator= (IPAddress&& other) = default;

    IPAddress(IPAddress& other) = default;

    IPAddress& operator = (const IPAddress& other) = default;

    IPAddress(const IPAddress& other) = default;

    [[nodiscard]] ip_t GetValue() const;


};


#endif //DHCPALLOCATOR_IPADDRESS_H
