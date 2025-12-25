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
#pragma pop

#pragma pack(push, 1)
struct ITCHPrice4
{
    uint32_t data; // big endian

    __forceinline std::pair<uint32_t, uint32_t> get_whole_dec() const 
    {
        uint32_t host_price = _byteswap_ulong(data);
        return std::make_pair<uint32_t, uint32_t>(host_price / 10000, host_price % 10000);
    }
};
#pragma pop

#pragma pack(push, 1)
struct ITCHPrice8
{
    uint64_t data;

    __forceinline std::pair<uint64_t, uint64_t> get_whole_dec() const
    {
        uint64_t host_price = _byteswap_uint64(data);
        return { host_price / 100000000, host_price % 100000000 };
    }
};
#pragma pack(pop)