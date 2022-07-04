#include <iostream>
#include <ctime>
#include <string>
#include <iomanip>

std::tm get_end_time(char *argv[]) {
    std::tm t{};
    std::string time ="";
    for (int i = 0; i < 5; i++) {
        time += argv[1][i];
    }
    t.tm_min = std::stoi(time.substr(0, 2));
    t.tm_sec = std::stoi(time.substr(3, 2));
    return t;
}

int main(int argc, char *argv[]) {

    if (argc <= 1) {
        std::cout << "Argumets required" << std::endl;
        return -1;
    }

    std::tm start{};
    std::tm end = get_end_time(argv);

    int tick = 1;
    std::time_t start_point = std::time(nullptr);

    while (std::difftime(std::mktime(&end), std::mktime(&start)) != 0) {

        double delay = std::difftime(std::time(nullptr), start_point);
        
        if (delay >= tick) {
            end.tm_sec--;
            tick++;
            if (end.tm_sec == -1 && end.tm_min != 0) {
                end.tm_min--;
                end.tm_sec = 59;
            }
            std::cout  << std::put_time(&end, "%M:%S") << std::endl;
        }
    }
    std::cout << "DING!DING!DING!" << std::endl;

    return 0;
}
