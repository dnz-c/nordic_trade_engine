#pragma once
#include <string>
#include <map>
#include <unordered_map>
#include <vector>

struct LIMIT_LEVEL;

struct ORDER
{
    uint64_t id;
    uint64_t shares;
    uint32_t price;
    ORDER* next;
    ORDER* prev;
    LIMIT_LEVEL* parent;
    bool is_bid;
};

struct LIMIT_LEVEL 
{
    uint64_t total_volume = 0;
    std::vector<std::pair<uint64_t, ORDER*>> shares_till_executed;
    ORDER* head = nullptr;
    ORDER* tail = nullptr;
};

// TODO: This still allocates internally use custom std::map allocators (std::pmr::monotonic_buffer_resource)
class ORDER_POOL 
{
private:
    std::vector<ORDER> block_memory;
    std::vector<ORDER*> free_list;

public:
    ORDER_POOL() : ORDER_POOL(0) {}

    ORDER_POOL(size_t size)
    {
        block_memory.resize(size); // memory block itself
        free_list.reserve(size);

        for (size_t i = 0; i < size; i++) 
        {
            free_list.push_back(&block_memory[i]);
        }
    }

    ORDER* rent_order() 
    {
        if (free_list.empty()) 
        {
            system("pause");
            throw std::runtime_error("OOM: Order Pool Exhausted");
            exit(-10);
        }
        ORDER* o = free_list.back();
        free_list.pop_back();
        return o;
    }

    void return_order(ORDER* o) 
    {
        o->shares = 0;
        o->price = 0;
        free_list.push_back(o);
    }
};

struct SIDE_BID {};
struct SIDE_ASK {};

class LIMIT_ORDER_BOOK 
{
public:
    std::unordered_map<uint64_t, ORDER*> order_map;

private:
    ORDER_POOL& pool;
    std::string symbol;
    std::map<uint32_t, LIMIT_LEVEL, std::greater<uint32_t>> bids;
    std::map<uint32_t, LIMIT_LEVEL> asks;

private:
    void link_order(LIMIT_LEVEL& level, ORDER* order);
    void unlink_order(ORDER* o);

public:
    LIMIT_ORDER_BOOK(std::string ticker, ORDER_POOL& p) : symbol(ticker), pool(p) {}

    template <typename SIDE>
    void simulate_order(uint32_t price, uint32_t shares);

    template <>
    void simulate_order<SIDE_ASK>(uint32_t price, uint32_t shares)
    {
        ORDER* o = pool.rent_order();
        o->price = price;
        o->shares = shares;

        LIMIT_LEVEL& level = asks[price];
        o->parent = &level;

        link_order(level, o);
        level.shares_till_executed.push_back(std::pair<uint64_t, ORDER*>(level.total_volume, o));
    }

    template <>
    void simulate_order<SIDE_BID>(uint32_t price, uint32_t shares)
    {
        ORDER* o = pool.rent_order();
        o->price = price;
        o->shares = shares;

        LIMIT_LEVEL& level = bids[price];
        o->parent = &level;

        link_order(level, o);
        level.shares_till_executed.push_back(std::pair<uint64_t, ORDER*>(level.total_volume, o));
    }

    template <typename SIDE>
    void add_order(uint64_t id, uint32_t price, uint32_t shares);

    template <>
    __forceinline void add_order<SIDE_BID>(uint64_t id, uint32_t price, uint32_t shares)
    {
        ORDER* o = pool.rent_order();

        o->id = id;
        o->shares = shares;
        o->price = price;
        o->is_bid = true;

        order_map[id] = o;

        LIMIT_LEVEL& level = bids[price];
        o->parent = &level;

        link_order(level, o);
    }

    template <>
    __forceinline void add_order<SIDE_ASK>(uint64_t id, uint32_t price, uint32_t shares)
    {
        ORDER* o = pool.rent_order();

        o->id = id;
        o->shares = shares;
        o->price = price;
        o->is_bid = false;

        order_map[id] = o;

        LIMIT_LEVEL& level = asks[price];
        o->parent = &level;

        link_order(level, o);
    }
    
    template <typename SIDE>
    void replace_order(ORDER* o, uint64_t old_id, uint64_t new_id, uint32_t new_shares, uint32_t new_price);

    template<>
    void replace_order<SIDE_BID>(ORDER* o, uint64_t old_id, uint64_t new_id, uint32_t new_shares, uint32_t new_price)
    {
        o->parent->total_volume -= o->shares;
        unlink_order(o);

        o->id = new_id;
        o->shares = new_shares;
        o->price = new_price;

        order_map.erase(old_id);
        order_map[new_id] = o;

        LIMIT_LEVEL& level = bids[new_price];
        o->parent = &level;
        link_order(level, o);
    }

    template<>
    void replace_order<SIDE_ASK>(ORDER* o, uint64_t old_id, uint64_t new_id, uint32_t new_shares, uint32_t new_price)
    {
        o->parent->total_volume -= o->shares;
        unlink_order(o);

        o->id = new_id;
        o->shares = new_shares;
        o->price = new_price;

        order_map.erase(old_id);
        order_map[new_id] = o;

        LIMIT_LEVEL& level = asks[new_price];
        o->parent = &level;
        link_order(level, o);
    }

    void execute_order(uint64_t id, uint32_t executed_shares);
    void cancel_order(uint64_t id, uint32_t cancelled_shares);

    void print_top_of_book();

public:
    std::string get_symbol()
    {
        return symbol;
    }
};

class MARKET {
private:
    LIMIT_ORDER_BOOK* books[65536];

public:
    void register_stock(uint16_t locate_id, const char* symbol);
    LIMIT_ORDER_BOOK* get_book(uint16_t locate_id);
};