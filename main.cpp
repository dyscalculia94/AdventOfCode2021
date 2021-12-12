#include <iostream>

#include "aoc2021.h"

int main()
{
    const int days_done = days.size();
    const std::string filedir = "../inputs";
    for (int i = 1; i <= days_done; i++) {
        auto result = days[i](filedir);
        std::cout << "Day " << i << ": " << result.first << " " << result.second << std::endl;
    }
    
    return 0;
}