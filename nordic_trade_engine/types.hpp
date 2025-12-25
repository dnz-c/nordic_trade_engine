#pragma once
#include <intrin.h>
#include <utility>

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

#pragma pack(push, 1)
struct uint48_t 
{
    uint8_t data[6];

    __forceinline uint64_t value() const {
        return ((uint64_t)data[0] << 40) |
            ((uint64_t)data[1] << 32) |
            ((uint64_t)data[2] << 24) |
            ((uint64_t)data[3] << 16) |
            ((uint64_t)data[4] << 8) |
            ((uint64_t)data[5]);
    }
};
#pragma pack(pop)

#pragma pack(push, 1)
template <typename T>
struct BigEndian {
    T raw_value;

    // Implicit conversion operator: Allows you to treat this struct as a normal number
    operator T() const {
        if constexpr (sizeof(T) == 2) return _byteswap_ushort(raw_value);
        if constexpr (sizeof(T) == 4) return _byteswap_ulong(raw_value);
        if constexpr (sizeof(T) == 8) return _byteswap_uint64(raw_value);
        return raw_value;
    }
};
#pragma pack(pop)