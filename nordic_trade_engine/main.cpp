#include "itch_parser/parser.h"

int main()
{
    if (!itch_parser::init_parser())
    {
        std::cerr << "Failed to initialize handler map!\n";
        return -1;
    }

    itch_parser::run_parser(L"F:\\Programming\\nordic_trade_engine\\nordic_trade_engine\\itch_data\\01302019.NASDAQ_ITCH50");

    system("pause");
}