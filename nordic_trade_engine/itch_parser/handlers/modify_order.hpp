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
	BigEndian<uint32_t> cancelled_shares;
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
		const EXECUTED_ORDER* executed_order = reinterpret_cast<const EXECUTED_ORDER*>(frame);
		LIMIT_ORDER_BOOK* book = _::market.get_book(executed_order->stock_locate);
		if (!book) return;

		book->execute_order(executed_order->order_reference_number, executed_order->executed_shares);
	}
}

namespace executed_order_price_message
{
	static __forceinline void on_executed_order_price_message(const char* frame)
	{
		const EXECUTED_ORDER_PRICE_MESSAGE* executed_order = reinterpret_cast<const EXECUTED_ORDER_PRICE_MESSAGE*>(frame);
		LIMIT_ORDER_BOOK* book = _::market.get_book(executed_order->stock_locate);
		if (!book) return;

		book->execute_order(executed_order->order_reference_number, executed_order->executed_shares);
	}
}

namespace cancelled_order
{
	static __forceinline void on_cancelled_order(const char* frame)
	{
		const CANCELLED_ORDER* cancel = reinterpret_cast<const CANCELLED_ORDER*>(frame);
		LIMIT_ORDER_BOOK* book = _::market.get_book(cancel->stock_locate);
		if (book) 
			book->cancel_order(cancel->order_reference_number, cancel->cancelled_shares);
	}
}

namespace deleted_order
{
	static __forceinline void on_deleted_order(const char* frame)
	{
		const DELETED_ORDER* deleted = reinterpret_cast<const DELETED_ORDER*>(frame);
		LIMIT_ORDER_BOOK* book = _::market.get_book(deleted->stock_locate);
		if (book)
			book->cancel_order(deleted->order_reference_number, UINT32_MAX);
	}
}

namespace replace_order
{
	static __forceinline void on_replace_order(const char* frame)
	{
		const REPLACE_ORDER* order = reinterpret_cast<const REPLACE_ORDER*>(frame);

		LIMIT_ORDER_BOOK* book = _::market.get_book(order->stock_locate);
		if (!book) return;
		
		auto it = book->order_map.find(order->original_order_reference_number);
		if (it == book->order_map.end()) return;

		ORDER* o = it->second;

		if (o->is_bid) book->replace_order<SIDE_BID>(o, order->original_order_reference_number, order->new_order_reference_number, order->shares, order->price);
		else book->replace_order<SIDE_ASK>(o, order->original_order_reference_number, order->new_order_reference_number, order->shares, order->price);
	}
}