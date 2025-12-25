#pragma once
#include "types.hpp"

#pragma pack(push, 1)
struct MWCB_DECLINE_LEVEL_MESSAGE
{
	char message_type;
	uint16_t stock_locate;
	uint16_t tracking_number;
	uint48_t timestamp;
	ITCHPrice8 level1;
	ITCHPrice8 level2;
	ITCHPrice8 level3;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct MWCB_STATUS_MESSAGE
{
	char message_type;
	uint16_t stock_locate;
	uint16_t tracking_number;
	uint48_t timestamp;
	char breached_level;
};
#pragma pack(pop)

namespace mwcb_decline_level
{
	static __forceinline void on_mwcb_decline_level(const char* frame)
	{
		return;
	}
}

namespace mwcb_status
{
	static __forceinline void on_mwcb_status(const char* frame)
	{
		return;
	}
}