#include <iostream>
#include <random>
#include <ctime>
#include <windows.h>

const char symbols[] = { char(0xb2), char(0xdb), char(0x40), char(0xfe), char(0xc5), char(0xce) };

size_t  dim = sizeof(symbols) / sizeof(symbols[0]);

size_t make_move(const size_t& big_prize = 5000, const size_t& prize = 100, const size_t& a_waste = 10   
)
{
    system("cls");  
    char s_1 = symbols[rand() % dim];
    char s_2 = symbols[rand() % dim];
    char s_3 = symbols[rand() % dim];
    std::cout << "\n\t" << s_1 << "\t \n";
    std::cout << "\t" << s_2 << "\t \n";
    std::cout << "\t" << s_3 << "\t \n";
    if ((s_1 == s_2) && (s_2 == s_3))
        return big_prize - a_waste;
    if ((s_1 == s_2) || (s_2 == s_3) || (s_1 == s_3))
        return prize - a_waste;
    return a_waste;
}

int main()
{
    srand(time(NULL));
    unsigned long  cash = 100;     
    std::cout << " To gamble? <Enter>, exit <e>" << std::endl;
    while (std::cin.get() != 'e')
    {
        cash += make_move();
        std::cout << "Profit: " << cash << "\n\n";
        if (cash <= 0)
            break;
    }
    std::cout << "\nGambling game over, you cash " << cash << "$\n";
}