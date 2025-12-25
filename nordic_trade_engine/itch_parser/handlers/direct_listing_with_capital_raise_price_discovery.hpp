#pragma once
#include "types.hpp"

#pragma pack(push, 1)
struct DIRECT_LISTING_WITH_CAPITAL_RAISE_PRICE_DISCOVERY
{
	char message_type;
	BigEndian<uint16_t> stock_locate;
	BigEndian<uint16_t> tracking_number;
	uint48_t timestamp;
	char stock[8];
	char open_eligibility_status;
	BigEndian<uint32_t> minimum_allowable_price;
	BigEndian<uint32_t> maximum_allowable_price;
	BigEndian<uint32_t> near_execution_price;
	BigEndian<uint64_t> near_execution_time;
	BigEndian<uint32_t> lower_price_range_collar;
	BigEndian<uint32_t> upper_price_range_collar;
};
#pragma pack(pop)

namespace direct_listing_with_capital_raise_price_discovery
{
	static __forceinline void on_direct_listing_with_capital_raise_price_discovery(const char* frame)
	{
		return;
	}
}