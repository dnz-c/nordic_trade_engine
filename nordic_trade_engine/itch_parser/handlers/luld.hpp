#pragma once
#include "types.hpp"

#pragma push(pack, 1)
struct LULD_ACTION_COLLAR
{
	char message_type;
	uint16_t stock_locate;
	uint16_t tracking_number;
	uint48_t timestamp;
	char stock[8];
	ITCHPrice4 auction_collar_reference_price;
	ITCHPrice4 upper_auction_collar_price;
	ITCHPrice4 lower_auction_collar_price;
	uint32_t auction_collar_extension;
};
#pragma pop

namespace luld_action_collar
{
	static __forceinline void on_luld_action_collar(const char* frame)
	{
		return;
	}
}