#include "itch_parser/parser.h"

int main()
{
    _::pool = ORDER_POOL(100'000'000);

    ITCH_PARSER parser(L"F:\\Programming\\nordic_trade_engine\\nordic_trade_engine\\itch_data\\01302019.NASDAQ_ITCH50");
    parser.run();

    _::market.get_book(3419)->print_top_of_book();
    _::market.get_book(14)->print_top_of_book();

    system("pause");
}