#include <iostream>
#include <ctime>
#include <iomanip>
#include <string>

int main() {
    std::tm start{};//zero initialization
    std::tm end{};

    std::cout << "Enter the time (mm:ss): ";
    std::cin >> std::get_time(&end, "%M:%S");
    int tick = 0;
    std::time_t _s= std::time(nullptr);
    while (std::difftime(std::mktime(&end), std::mktime(&start)) != 0) {
       if (std::difftime(std::time(nullptr), _s) >= tick) {
           end.tm_sec--;
           tick++;
           if (end.tm_sec == -1 && end.tm_min != 0) {
               end.tm_min--;
               end.tm_sec = 59;
           }
           std::cout << std::put_time(&end, "%M:%S") << std::endl;
       }
    }
    std::cout << "DING!DING!DING!"  << std::endl;
    
    return 0;
}
