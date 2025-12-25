#pragma once
#include "types.hpp"

#pragma pack(push, 1)
struct REG_SHO_SHORT_SALE_PRICE_TEST_RESTRICTED_INDICATOR
{
	char message_type;
	BigEndian<uint16_t> locate_code;
	BigEndian<uint16_t> tracking_number;
	uint48_t timestamp;
	char stock[8];
	char reg_sho_action;
};
#pragma pack(pop)

namespace reg_sho_short_sale_price_test_restricted_indicator
{
	static __forceinline void on_reg_sho_short_sale_price_test_restricted_indicator(const char* frame)
	{
		return;
	}
}