#pragma once
#include "types.hpp"

#pragma push(pack, 1)
struct REG_SHO_SHORT_SALE_PRICE_TEST_RESTRICTED_INDICATOR
{
	char message_type;
	uint16_t locate_code;
	uint16_t tracking_number;
	uint48_t timestamp;
	char stock[8];
	char reg_sho_action;
};
#pragma pop

namespace reg_sho_short_sale_price_test_restricted_indicator
{
	static __forceinline void on_reg_sho_short_sale_price_test_restricted_indicator(const char* frame)
	{
		return;
	}
}