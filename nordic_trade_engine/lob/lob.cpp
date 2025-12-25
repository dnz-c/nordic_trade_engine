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
    std::cout << "Registered > " << clean_symbol << " [" << locate_id << "]" << std::endl;

    books[locate_id] = new LIMIT_ORDER_BOOK(clean_symbol.c_str(), _::pool);
}

LIMIT_ORDER_BOOK* MARKET::get_book(uint16_t locate_id)
{
    return books[locate_id];
}

void LIMIT_ORDER_BOOK::link_order(LIMIT_LEVEL& level, ORDER* order)
{
    level.total_volume += order->shares;
    
    if (level.tail)
    {
        level.tail->next = order;
        order->prev = level.tail;
        order->next = nullptr;
        level.tail = order;
    }
    else
    {
        level.head = order;
        level.tail = order;
        order->prev = nullptr;
        order->next = nullptr;
    }
}

void LIMIT_ORDER_BOOK::unlink_order(ORDER* o)
{
    LIMIT_LEVEL* level = o->parent;

    if (level->head == o) level->head = o->next;
    if (level->tail == o) level->tail = o->prev;

    if (o->prev) o->prev->next = o->next;
    if (o->next) o->next->prev = o->prev;
}

void LIMIT_ORDER_BOOK::execute_order(uint64_t id, uint32_t executed_shares)
{
    auto it = order_map.find(id);
    if (it == order_map.end()) return;

    ORDER* o = it->second;

    // order overfilled
    if (executed_shares > o->shares) 
    {
        o->shares = 0;
    }
    else 
    {
        o->shares -= executed_shares;
    }

    o->parent->total_volume -= executed_shares;

    if (o->shares == 0)
    {
        unlink_order(o);
        order_map.erase(it);

        if (o->parent->total_volume == 0) 
        {
            // TODO: Lazy deletion (flag for deletion on a seperate task
        }

        pool.return_order(o);
    }
}

void LIMIT_ORDER_BOOK::cancel_order(uint64_t id, uint32_t cancelled_shares)
{
    auto it = order_map.find(id);
    if (it == order_map.end()) return;

    ORDER* o = it->second;

    uint32_t reduction = (cancelled_shares >= o->shares) ? o->shares : cancelled_shares;

    o->shares -= reduction;

    o->parent->total_volume -= reduction;

    if (o->shares == 0) 
    {
        unlink_order(o);
        order_map.erase(it);
        pool.return_order(o);
    }
}

void LIMIT_ORDER_BOOK::print_top_of_book()
{
    std::cout << "\n\nBID\t\t\t|\n";
    if (bids.empty()) 
    {
        std::cout << "Currently no bids\t|" << std::endl;
    }
    else
    {
        int c = 0;
        for (auto& it : bids)
        {
            if (c == 2) break;
            const LIMIT_LEVEL& bid = it.second;
            const uint32_t price = it.first;

            if (bid.total_volume == 0) continue;

            ORDER* current = bid.head;
            int count = 0;

            while (current != nullptr)
            {
                count++;
                current = current->next;
            }
            std::cout << bid.total_volume << " Shares @ " << (price / 10000) << "." << (price % 10000) << " $" << "\t|\n";
            c++;
        }
    }

    std::cout << "-----------------------\t|\nASK\t\t\t\n";
    if (asks.empty())
    {
        std::cout << "Currently no asks\t|" << std::endl;
    }
    else
    {
        int c = 0;
        for (auto& it : asks)
        {
            if (c == 2) break;
            const LIMIT_LEVEL& ask = it.second;
            const uint32_t price = it.first;

            if (ask.total_volume == 0) continue;

            ORDER* current = ask.head;
            int count = 0;

            while (current != nullptr)
            {
                count++;
                current = current->next;
            }
            std::cout << ask.total_volume << " Shares @ " << (price / 10000) << "." << (price % 10000) << " $" << "\t|\n";
            c++;
        }
    }
}