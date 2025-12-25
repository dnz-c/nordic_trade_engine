#include "includes.h"

void MARKET::register_stock(uint16_t locate_id, const char* symbol)
{
    std::string_view incoming_symbol(symbol, 8);
    auto last_char = incoming_symbol.find_last_not_of(' ');
    if (last_char != std::string_view::npos) {
        incoming_symbol = incoming_symbol.substr(0, last_char + 1);
    }

    auto it = std::find(_::tracked_stocks.begin(), _::tracked_stocks.end(), incoming_symbol);
    
    if (it == _::tracked_stocks.end()) {
        return;
    }

    std::string clean_symbol(incoming_symbol);
    std::cout << "Registered: " << clean_symbol << " [" << locate_id << "]" << std::endl;

    books[locate_id] = new LIMIT_ORDER_BOOK(clean_symbol.c_str(), _::pool);
}

LIMIT_ORDER_BOOK* MARKET::get_book(uint16_t locate_id)
{
    if (books.find(locate_id) != books.end()) {
        return books[locate_id];
    }
    return nullptr;
}

void LIMIT_ORDER_BOOK::link_order(LIMIT_LEVEL& level, ORDER* order)
{
    //level.total_volume += order->shares;
    //
    //if (level.tail)
    //{
    //    level.tail->next = order;
    //    order->prev = level.tail;
    //    order->next = nullptr;
    //    level.tail = order;
    //}
    //else
    //{
    //    level.head = order;
    //    level.tail = order;
    //    order->prev = nullptr;
    //    order->next = nullptr;
    //}
}

void LIMIT_ORDER_BOOK::execute_order(uint64_t id, uint32_t executed_shares)
{
}

void LIMIT_ORDER_BOOK::cancel_order(uint64_t id, uint32_t cancelled_shares)
{
}

void LIMIT_ORDER_BOOK::print_top_of_book()
{
}