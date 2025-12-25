#pragma once
#include "types.hpp"

#pragma push(pack, 1)
struct TRADE_MESSAGE
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
	uint64_t match_number;
};
#pragma pop

#pragma push(pack, 1)
struct CROSS_TRADE_MESSAGE
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
	uint64_t match_number;
	char cross_type;
};
#pragma pop

namespace trade_message
{
	static __forceinline void on_trade_message(const char* frame)
	{
		return;
	}
}

namespace cross_trade_message
{
	static __forceinline void on_cross_trade_message(const char* frame)
	{
		return;
	}
}