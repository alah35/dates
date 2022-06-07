#include <iostream>
#include <ctime>
#include <string>
#include <map>
#include <iomanip>

int interpret(std::string s) {
    if (s == "begin")
        return 0;
    if (s == "end")
        return 1;
    if (s == "status")
        return 2;
    if (s == "exit")
        return -1;
    return -2;
}

void show_log(std::map<std::tm*, std::string> &m) {
    for (auto it = m.begin(); it != m.end(); it++)
        std::cout << std::put_time(it->first, "%H:%M:%S") << " " << it->second << std::endl; 
}

int main() {
    bool is_tracking = 0, kill = 0;
    std::string taskName;
    std::map<std::tm*, std::string> log;
    std::string command = "";
    std::time_t start, end;

    while (!kill) {

        std::cout << "Wait for a command..." << std::endl;
        std::cin >> command;

        int c = interpret(command);

        switch (c) {
            case 0:
                if (is_tracking) {
                    end = std::time(nullptr);
                    std::time_t d = static_cast<std::time_t>(std::difftime(start, end));
                    std::tm* t = std::localtime(&d);
                    log[t] = taskName; // вероятно, такой способ создание элементов в контейнере log неверен, так как где то в указатели закралась ошибка и новые элементы
                    // на тоже место, t как будто бы всегда один и тот же, просто меняет значение. Уверен, это из-за того, что t как объект не меняет свой адрес, а только меняет значения.
                    is_tracking = 0;
                } 
                std::cout << "Enter task name:" << std::endl;
                std::cin >> taskName;
                start = std::time(nullptr);
                is_tracking = 1;
                break;
            case 1:
                if (is_tracking) {
                    end = std::time(nullptr);
                    std::time_t d = static_cast<std::time_t>(std::difftime(start, end));
                    std::tm* t = std::localtime(&d);
                    log[t] = taskName;
                    is_tracking = 0;
                } else 
                    std::cout << "You haven't started a task yet" << std::endl;
                break;
            case 2:
                show_log(log);
                if (is_tracking)  
                    std::cout << taskName << "in progress" <<  std::endl; 
                break;
            case -1:
                kill = 1;
                break;
            default:
                std::cout << "Something get wrong" << std::endl;
                break;
        }
    }
    return 0;
}
