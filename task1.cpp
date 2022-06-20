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

void show_log(std::map<std::time_t, std::string> &m) {
    for (std::map<std::time_t, std::string>::iterator it = m.begin(); it != m.end(); it++)
        std::cout << std::put_time(std::gmtime(&it->first), "%H:%M:%S") << " " << it->second << std::endl;
}

int main() {
    bool is_tracking = 0, kill = 0;
    std::string taskName;
    std::map<std::time_t, std::string> log;
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
                    std::time_t spentTime = static_cast<std::time_t>(std::difftime(end, start));
                    log[spentTime] = taskName;
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
                    std::time_t spentTime = static_cast<std::time_t>(std::difftime(end, start));
                    log[spentTime] = taskName;
                    is_tracking = 0;
                } else 
                    std::cout << "You haven't started a task yet" << std::endl;
                break;
            case 2:
                show_log(log);
                if (is_tracking)  
                    std::cout << taskName << " in progress" <<  std::endl; 
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
