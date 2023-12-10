//
// Created by Abhijith  K A on 15/07/23.
//

#ifndef DHCPALLOCATOR_VEBTREEUTIL_H
#define DHCPALLOCATOR_VEBTREEUTIL_H

#include <cstdint>
#include <bit>
#include <concepts>
#include <stdexcept>


namespace VEBTreeUtils {

    template<typename T>
    bool IsPowerOfTwo(T value) requires std::unsigned_integral<T> {
        return std::has_single_bit(value);
    }

    template<typename T>
    T GetBitWidthOfPowerOfTwoNextToValue(T value) requires std::unsigned_integral<T> {
        return std::bit_width(std::bit_ceil(value));
    }

    template<typename T>
    bool IsEven(T value) requires std::unsigned_integral<T> {
        T one = 1;
        return !(value & one);
    }

    template<typename T>
    std::pair<T, T> SplitIntoSquareOfPowersOfTwo(T value) requires std::unsigned_integral<T> {
        if (value < 2) {
            throw std::invalid_argument("Values less than 2 cannot be split");
        }
        if (IsPowerOfTwo(value) || value == std::numeric_limits<T>::max()) {
            T two = 2;
            T one = 1;
            T bitWidth = std::bit_width(value - 1);
            if (IsEven(bitWidth)) {
                T half = bitWidth >> 1;
                T squareRoot = 1 << (half);
                return {squareRoot, squareRoot};
            } else {

                T half = bitWidth >> 1;
                T greaterHalf = half + 1;

                T LessThanSquareRoot = one << (half);
                T greaterThanSquareRoot = one << (greaterHalf);


                return {LessThanSquareRoot, greaterThanSquareRoot};
            }
        }
        throw std::invalid_argument("Values should be power of 2");
    }

    template<typename T>
    std::pair<T, T> SplitIntoHighAndLow(T value, T universe) requires std::unsigned_integral<T> {
     if (universe <= 2) {
           throw std::invalid_argument("Universe less than equal to 2 cannot be split");
       }
        /**
         * should be >= but need to have uint64_t bit universe and values to work in that.
         */
        if(value > universe){
            throw std::invalid_argument("value should come under universe");
        }

        T two = 2;
        T one = 1;

        T bitWidth = std::bit_width(universe - one);
        if (IsEven(bitWidth)) {

            T half = bitWidth >> one;
            T squareRootGreater = one << (half);
            T lowMask = squareRootGreater - one;
            T low = value & lowMask;

            T highMask = lowMask;
            T highInput = value >> half;
            T high = highInput & highMask;

            return {high, low};
        } else {

            T lesserHalf = bitWidth >> one;
            T greaterHalf = lesserHalf + one;
            T LessThanSquareRoot = one << (greaterHalf);
            T lowMask = LessThanSquareRoot - one;
            T highMask = lowMask >> one;
            T low = value & lowMask;
            T highInput = value >> greaterHalf;
            T high = highInput & highMask;

            return {high, low};
        }

    }

}



#endif //DHCPALLOCATOR_VEBTREEUTIL_H
