#include <iostream>

#include "aoc2021.h"

int main()
{
    const std::string filedir = "../inputs";
    for (auto i : days) {
        auto result = i.second(filedir);
        std::cout << "Day " << i.first << ": " << result.first << " " << result.second << std::endl;
    }
    
    return 0;
}