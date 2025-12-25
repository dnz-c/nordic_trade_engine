#pragma once
#include "types.hpp"

#pragma pack(push, 1)
struct IPO_QUOTING_PERIOD_UPDATE_MESSAGE
{
	char message_type;
	BigEndian<uint16_t> stock_locate;
	BigEndian<uint16_t> tracking_number;
	uint48_t timestamp;
	char stock[8];
	BigEndian<uint32_t> ipo_quotation_release_time;
	char ipo_quotation_release_qualifier;
	BigEndian<uint32_t> ipo_price;
};
#pragma pack(pop)

namespace ipo_quoting_period_update
{
	static __forceinline void on_ipo_quoting_period_update(const char* frame)
	{
		return;
	}
}