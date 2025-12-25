#pragma once
#include "types.hpp"
#include <iostream>

#pragma pack(push, 1)
struct EXECUTED_ORDER
{
	char message_type;
	BigEndian<uint16_t> stock_locate;
	BigEndian<uint16_t> tracking_number;
	uint48_t timestamp;
	BigEndian<uint64_t> order_reference_number;
	BigEndian<uint32_t> executed_shares;
	BigEndian<uint64_t> match_number;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct EXECUTED_ORDER_PRICE_MESSAGE
{
	char message_type;
	BigEndian<uint16_t> stock_locate;
	BigEndian<uint16_t> tracking_number;
	uint48_t timestamp;
	BigEndian<uint64_t> order_reference_number;
	BigEndian<uint32_t> executed_shares;
	BigEndian<uint64_t> match_number;
	char printable;
	BigEndian<uint32_t> execution_price;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct CANCELLED_ORDER
{
	char message_type;
	BigEndian<uint16_t> stock_locate;
	BigEndian<uint16_t> tracking_number;
	uint48_t timestamp;
	BigEndian<uint64_t> order_reference_number;
	BigEndian<uint32_t> cancelled_shared;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct DELETED_ORDER
{
	char message_type;
	BigEndian<uint16_t> stock_locate;
	BigEndian<uint16_t> tracking_number;
	uint48_t timestamp;
	BigEndian<uint64_t> order_reference_number;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct REPLACE_ORDER
{
	char message_type;
	BigEndian<uint16_t> stock_locate;
	BigEndian<uint16_t> tracking_number;
	uint48_t timestamp;
	BigEndian<uint64_t> original_order_reference_number;
	BigEndian<uint64_t> new_order_reference_number;
	BigEndian<uint32_t> shares;
	BigEndian<uint32_t> price;
};
#pragma pack(pop)

namespace executed_order
{
	static __forceinline void on_executed_order(const char* frame)
	{
		return;
	}
}

namespace executed_order_price_message
{
	static __forceinline void on_executed_order_price_message(const char* frame)
	{
		return;
	}
}

namespace cancelled_order
{
	static __forceinline void on_cancelled_order(const char* frame)
	{
		return;
	}
}

namespace deleted_order
{
	static __forceinline void on_deleted_order(const char* frame)
	{
		return;
	}
}

namespace replace_order
{
	static __forceinline void on_replace_order(const char* frame)
	{
		const REPLACE_ORDER* order = reinterpret_cast<const REPLACE_ORDER*>(frame);
		return;
	}
}