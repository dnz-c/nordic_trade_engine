#pragma once
#include "types.hpp"

#pragma pack(push, 1)
struct STOCK_DIRECTORY_MESSAGE
{
	char message_type;
	uint16_t stock_locate;
	uint16_t tracking_number;
	uint48_t timestamp;
	char stock[8];
	char market_category;
	char financial_status_indicator;
	uint32_t round_lot_size;
	char round_lots_only;
	char issue_classification;
	char issue_sub_type[2];
	char authenticity;
	char short_sale_threshold_indicator;
	char ipo_flag;
	char luld_reference_price_tier;
	char etp_flag;
	uint32_t etp_leverage_factor;
	char inverse_indicator;
};
#pragma pop

namespace stock_directory_message
{
	static __forceinline void on_stock_directory_message(const char* frame)
	{
		return;
	}
}