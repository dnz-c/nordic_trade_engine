#pragma once
#include "types.hpp"

#pragma pack(push, 1)
struct SYSTEM_MESSAGE
{
	char message_type;
	BigEndian<uint16_t> stock_locate;
	BigEndian<uint16_t> tracking_number;
	uint48_t timestamp;
	char event_code;
};
#pragma pack(pop)

namespace system_message
{
	static __forceinline void on_system_message(const char* frame)
	{
		const SYSTEM_MESSAGE* system = reinterpret_cast<const SYSTEM_MESSAGE*>(frame);
		if (system->event_code == 'Q') std::cout << "[TIME] 09:30:00 - Market Start of Normal Trading Hours" << std::endl;
		else if (system->event_code == 'M') std::cout << "[TIME] 16:00:00 - Market End of Normal Trading Hours" << std::endl;
	}
}