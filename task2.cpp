#include <iostream>
#include <ctime>
#include <string>
#include <map>
#include <iomanip>
#include <climits>

void set_birthday(std::string &user_input, std::tm &bd) {
    for (int i = 0; i < user_input.length(); i += 3) {
        std::string s = user_input.substr(i, 2);
        if (i == 0)
            bd.tm_year = std::stoi(s);
        if (i == 3)
            bd.tm_mon = std::stoi(s);
        if (i == 6) 
            bd.tm_mday = std::stoi(s);
    }
}

int main() {
    std::map<std::string, std::tm> birthdays_list;
    while(true) {
        std::cout << "Enter your friend name: ";
        std::string name;
        std::cin.ignore();
        std::getline(std::cin, name);

        if (name == "exit" || name == "end")
            break;

        std::cout << "Enter friends birthday: ";
        std::string input_bd;
        std::cin >> input_bd;
        std::tm birthday;
        set_birthday(input_bd, birthday);

        birthdays_list[name] = birthday;
    }

        std::time_t t = std::time(nullptr);
        std::tm *present_time = std::localtime(&t);
    return 0;
}
