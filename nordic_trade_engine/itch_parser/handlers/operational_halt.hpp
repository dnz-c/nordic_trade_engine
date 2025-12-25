#pragma once
#include "types.hpp"

#pragma pack(push, 1)
struct OPERATIONAL_HALT
{
	char message_type;
	uint16_t stock_locate;
	uint16_t tracking_number;
	uint48_t timestamp;
	char stock[8];
	char market_code;
	char operational_halt_action;
};
#pragma pack(pop)

namespace operational_halt
{
	static __forceinline void on_operational_halt(const char* frame)
	{
		return;
	}
}