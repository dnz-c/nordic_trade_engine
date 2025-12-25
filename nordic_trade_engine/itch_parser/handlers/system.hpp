#pragma once
#include "types.hpp"

#pragma pack(push, 1)
struct SYSTEM_MESSAGE
{
	char message_type;
	uint16_t stock_locate;
	uint16_t tracking_number;
	uint48_t timestamp;
	char event_code;
};
#pragma pack(pop)

namespace system_message
{
	static __forceinline void on_system_message(const char* frame)
	{
		return;
	}
}