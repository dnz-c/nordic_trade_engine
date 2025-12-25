#pragma once
#include "includes.h"

#include "handlers/system.hpp"
#include "handlers/stock_directory.hpp"
#include "handlers/stock_trading_action.hpp"
#include "handlers/reg_sho_short_sale_price_test_restricted_indicator.hpp"
#include "handlers/market_participant_position.hpp"
#include "handlers/mwcb.hpp"
#include "handlers/quoting_period.hpp"
#include "handlers/luld.hpp"
#include "handlers/operational_halt.hpp"
#include "handlers/add_order.hpp"
#include "handlers/modify_order.hpp"
#include "handlers/trade_messages.hpp"
#include "handlers/broken_trade.hpp"
#include "handlers/direct_listing_with_capital_raise_price_discovery.hpp"

static __forceinline void handler_unknown(const char* frame)
{
	std::cerr << "Unknown message: " << *(char*)frame << std::endl;
}

typedef void (*t_handler)(const char*);
static t_handler handler_list[256];

class ITCH_PARSER
{
private:
	LARGE_INTEGER fs;
	HANDLE file;
	HANDLE mapped_file;
	char* buf;

	t_handler handler_list[256];
	const wchar_t* itch_file;

public:
	ITCH_PARSER(const wchar_t* path);
	~ITCH_PARSER();

public:
	void run();
};