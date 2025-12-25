#include "parser.h"

ITCH_PARSER::ITCH_PARSER(const wchar_t* path) 
    : buf(nullptr), file(NULL), mapped_file(NULL)
{
    fs.QuadPart = 0;

    for (int i = 0; i < 256; i++)
    {
        handler_list[i] = handler_unknown;
    }

    handler_list['S'] = system_message::on_system_message;
    handler_list['R'] = stock_directory_message::on_stock_directory_message;
    handler_list['H'] = stock_trading_action_message::on_stock_trading_action_message;
    handler_list['Y'] = reg_sho_short_sale_price_test_restricted_indicator::on_reg_sho_short_sale_price_test_restricted_indicator;
    handler_list['L'] = market_participant_position::on_market_participant_position;
    handler_list['V'] = mwcb_decline_level::on_mwcb_decline_level;
    handler_list['W'] = mwcb_status::on_mwcb_status;
    handler_list['K'] = ipo_quoting_period_update::on_ipo_quoting_period_update;
    handler_list['J'] = luld_action_collar::on_luld_action_collar;
    handler_list['h'] = operational_halt::on_operational_halt;
    handler_list['A'] = add_order_no_mpid::on_add_order_no_mpid;
    handler_list['F'] = add_order_mpid::on_add_order_mpid;
    handler_list['E'] = executed_order::on_executed_order;
    handler_list['C'] = executed_order_price_message::on_executed_order_price_message;
    handler_list['X'] = cancelled_order::on_cancelled_order;
    handler_list['D'] = deleted_order::on_deleted_order;
    handler_list['U'] = replace_order::on_replace_order;
    handler_list['P'] = trade_message::on_trade_message;
    handler_list['Q'] = cross_trade_message::on_cross_trade_message;
    handler_list['B'] = broken_trade::on_broken_trade;
    handler_list['I'] = noii::on_noii;
    handler_list['O'] = direct_listing_with_capital_raise_price_discovery::on_direct_listing_with_capital_raise_price_discovery;

    itch_file = path;

    file = CreateFile(itch_file, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (!file)
    {
        std::cerr << "Can't open file!\n";
        return;
    }

    GetFileSizeEx(file, &fs);

    mapped_file = CreateFileMapping(file, NULL, PAGE_READONLY, 0, 0, NULL);
    if (!mapped_file)
    {
        std::cerr << "Can't create file mapping!\n";
        return;
    }

    buf = (char*)MapViewOfFile(mapped_file, FILE_MAP_READ, 0, 0, 0x40000000);
    if (!buf)
    {
        std::cerr << "Can't map file to memory!\n";
        return;
    }
}

ITCH_PARSER::~ITCH_PARSER()
{
    if (buf) UnmapViewOfFile(buf);
    if (mapped_file) CloseHandle(mapped_file);
    if (file) CloseHandle(file);
}

void ITCH_PARSER::run()
{
    if (!buf || !file || !mapped_file)
        return;

    char* cursor = buf;
    char* end = buf + 0x40000000;// fs.QuadPart;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    while (cursor < end)
    {
        uint16_t raw_len;
        std::memcpy(&raw_len, cursor, sizeof(uint16_t));
        uint16_t message_length = _byteswap_ushort(raw_len);

        if (end - cursor < 2 + message_length) break;

        char* frame = cursor + 2;
        char message_type = *frame;

        handler_list[static_cast<uint8_t>(message_type)](frame);

        cursor += message_length + 2;
    }

    std::chrono::steady_clock::time_point end_t = std::chrono::steady_clock::now();

    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds> (end_t - begin).count() << "[ms]" << std::endl;
}