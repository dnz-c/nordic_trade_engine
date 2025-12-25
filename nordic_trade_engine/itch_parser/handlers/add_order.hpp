#pragma once
#include "types.hpp"
#include "includes.h"

#pragma pack(push, 1)
struct ADD_ORDER_NO_MPID
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
};
#pragma pack(pop)

#pragma pack(push, 1)
struct ADD_ORDER_MPID
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
	char attribution[4];
};
#pragma pack(pop)

namespace add_order_no_mpid
{
	static __forceinline void on_add_order_no_mpid(const char* frame)
	{
		const ADD_ORDER_NO_MPID* order = reinterpret_cast<const ADD_ORDER_NO_MPID*>(frame);
		LIMIT_ORDER_BOOK* book = _::market.get_book(order->stock_locate);
		if (!book) return;

		if (order->buy_sell_indicator == 'B') book->add_order<SIDE_BID>(order->order_reference_number, order->price, order->shares);
		else book->add_order<SIDE_ASK>(order->order_reference_number, order->price, order->shares);
	}
}

namespace add_order_mpid
{
	static __forceinline void on_add_order_mpid(const char* frame)
	{
		const ADD_ORDER_NO_MPID* order = reinterpret_cast<const ADD_ORDER_NO_MPID*>(frame);
		LIMIT_ORDER_BOOK* book = _::market.get_book(order->stock_locate);
		if (!book) return;

		if (order->buy_sell_indicator == 'B') book->add_order<SIDE_BID>(order->order_reference_number, order->price, order->shares);
		else book->add_order<SIDE_ASK>(order->order_reference_number, order->price, order->shares);
	}
}