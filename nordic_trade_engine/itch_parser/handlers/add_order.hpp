#pragma once
#include "types.hpp"

#pragma push(pack, 1)
struct ADD_ORDER_NO_MPID
{
	char message_type;
	uint16_t stock_locate;
	uint16_t tracking_number;
	uint48_t timestamp;
	uint64_t order_reference_number;
	char buy_sell_indicator;
	uint32_t shares;
	char stock[8];
	ITCHPrice4 price;
};
#pragma pop

#pragma push(pack, 1)
struct ADD_ORDER_MPID
{
	char message_type;
	uint16_t stock_locate;
	uint16_t tracking_number;
	uint48_t timestamp;
	uint64_t order_reference_number;
	char buy_sell_indicator;
	uint32_t shares;
	char stock[8];
	ITCHPrice4 price;
	char attribution[4];
};
#pragma pop

namespace add_order_no_mpid
{
	static __forceinline void on_add_order_no_mpid(const char* frame)
	{
		const ADD_ORDER_NO_MPID* order = reinterpret_cast<const ADD_ORDER_NO_MPID*>(frame);
		return;
	}
}

namespace add_order_mpid
{
	static __forceinline void on_add_order_mpid(const char* frame)
	{
		return;
	}
}