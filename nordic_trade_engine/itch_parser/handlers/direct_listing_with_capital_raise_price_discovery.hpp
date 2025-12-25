#pragma once
#include "types.hpp"

#pragma push(pack, 1)
struct DIRECT_LISTING_WITH_CAPITAL_RAISE_PRICE_DISCOVERY
{
	char message_type;
	uint16_t stock_locate;
	uint16_t tracking_number;
	uint48_t timestamp;
	char stock[8];
	char open_eligibility_status;
	ITCHPrice4 minimum_allowable_price;
	ITCHPrice4 maximum_allowable_price;
	ITCHPrice4 near_execution_price;
	uint64_t near_execution_time;
	ITCHPrice4 lower_price_range_collar;
	ITCHPrice4 upper_price_range_collar;
};
#pragma pop

namespace direct_listing_with_capital_raise_price_discovery
{
	static __forceinline void on_direct_listing_with_capital_raise_price_discovery(const char* frame)
	{
		return;
	}
}