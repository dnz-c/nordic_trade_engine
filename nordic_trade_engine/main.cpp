#include "itch_parser/parser.h"

int main()
{
    _::pool = ORDER_POOL(1'000'000);

    ITCH_PARSER parser(L"F:\\Programming\\nordic_trade_engine\\nordic_trade_engine\\itch_data\\01302019.NASDAQ_ITCH50");
    parser.run();

    system("pause");
}