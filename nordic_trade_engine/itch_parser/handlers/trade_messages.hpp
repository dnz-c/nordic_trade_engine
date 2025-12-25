#pragma once
#include "types.hpp"

#pragma pack(push, 1)
struct TRADE_MESSAGE
{
	char message_type;
	BigEndian<uint16_t> stock_locate;
	BigEndian<uint16_t> tracking_number;
	uint48_t timestamp;
	BigEndian<uint64_t> order_reference_number;
	char buy_sell_indicator;
	BigEndian<uint32_t> shares;
	char stock[8];
	BigEndian<uint32_t> price;
	BigEndian<uint64_t> match_number;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct CROSS_TRADE_MESSAGE
{
	char message_type;
	BigEndian<uint16_t> stock_locate;
	BigEndian<uint16_t> tracking_number;
	uint48_t timestamp;
	BigEndian<uint64_t> order_reference_number;
	char buy_sell_indicator;
	BigEndian<uint32_t> shares;
	char stock[8];
	BigEndian<uint32_t> price;
	BigEndian<uint64_t> match_number;
	char cross_type;
};
#pragma pack(pop)

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