#pragma once
#include "types.hpp"

#pragma pack(push, 1)
struct BROKEN_TRADE
{
	char message_type;
	BigEndian<uint16_t> stock_locate;
	BigEndian<uint16_t> tracking_number;
	uint48_t timestamp;
	BigEndian<uint64_t> match_number;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct NOII
{
	char message_type;
	BigEndian<uint16_t> stock_locate;
	BigEndian<uint16_t> tracking_number;
	uint48_t timestamp;
	BigEndian<uint64_t> paired_shares;
	BigEndian<uint64_t> imbalance_shares;
	char imbalance_direction;
	char stock[8];
	BigEndian<uint32_t> far_price;
	BigEndian<uint32_t> near_price;
	BigEndian<uint32_t> current_reference_price;
	char cross_type;
	char price_variation_indicator;

};
#pragma pack(pop)

namespace broken_trade
{
	static __forceinline void on_broken_trade(const char* frame)
	{
		return;
	}
}

namespace noii
{
	static __forceinline void on_noii(const char* frame)
	{
		return;
	}
}