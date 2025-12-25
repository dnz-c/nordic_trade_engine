#pragma once
#include <string>
#include <map>
#include <unordered_map>

struct ORDER {
    uint64_t id;
    uint64_t shares;
    uint32_t price;
    ORDER* next;
    ORDER* prev;
};

struct LIMIT_LEVEL {
    uint32_t price;
    uint64_t total_volume;
    ORDER* head;
    ORDER* tail;
};

class LIMIT_ORDER_BOOK 
{
private:
    std::string symbol;
    std::unordered_map<uint64_t, ORDER*> order_map;
    std::map<uint32_t, LIMIT_LEVEL> bids;
    std::map<uint32_t, LIMIT_LEVEL> asks;

public:
    LIMIT_ORDER_BOOK(std::string ticker) : symbol(ticker) {}

    void add_order(uint64_t id, bool is_buy, uint32_t price, uint32_t shares);
    void execute_order(uint64_t id, uint32_t executed_shares);
    void cancel_order(uint64_t id, uint32_t cancelled_shares);

    void print_top_of_book();
};

class MARKET {
private:
    std::unordered_map<uint16_t, LIMIT_ORDER_BOOK*> books;

public:
    void register_stock(uint16_t locate_id, const char* symbol);
    LIMIT_ORDER_BOOK* get_book(uint16_t locate_id);
};