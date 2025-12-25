#pragma once
#include "types.hpp"

#pragma pack(push, 1)
struct MARKET_PARTICIPANT_POSITION_MESSAGE
{
	char message_type;
	uint16_t stock_locate;
	uint16_t tracking_number;
	uint48_t timestamp;
	char mpid[4];
	char stock[8];
	char primary_market_maker;
	char market_maker_mode;
	char market_participant_state;
};
#pragma pack(pop)

namespace market_participant_position
{
	static __forceinline void on_market_participant_position(const char* frame)
	{
		return;
	}
}