#pragma once
#include "types.hpp"

#pragma pack(push, 1)
struct STOCK_TRADING_ACTION_MESSAGE
{
	char message_type;
	uint16_t stock_locate;
	uint16_t tracking_number;
	uint48_t timestamp;
	char stock[8];
	char trading_state;
	char reserved;
	char reason[4];
};
#pragma pack(pop)

namespace stock_trading_action_message
{
	static __forceinline void on_stock_trading_action_message(const char* frame)
	{
		return;
	}
}