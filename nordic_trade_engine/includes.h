#pragma once
#include <Windows.h>
#include <iostream>
#include <chrono>
#include <string_view>

#include "types.hpp"
#include "lob/lob.h"

namespace _
{
	inline MARKET market;
	inline std::vector<std::string_view> tracked_stocks = { "AAPL", "MSFT", "GOOG", "TSLA" };
	inline ORDER_POOL pool;
}