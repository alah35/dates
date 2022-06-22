#include <iostream>
#include <ctime>
#include <string>
#include <map>
#include <iomanip>
#include <climits>
#include <vector>
#include <cmath>

int main() {
    std::map<std::string, std::tm> birthdays_list; // a list to save names and bds

    while(true) {
        std::cout << "Enter your friend name: ";
        std::string name;
        std::cin.ignore();
        std::getline(std::cin, name);

        if (name == "exit" || name == "end")
            break;

        std::time_t t = std::time(nullptr);
        std::tm birthday = *std::localtime(&t); // bring to our time zone
        std::cout << "Enter friends birthday: ";
        std::cin >> std::get_time(&birthday, "%Y/%m/%d"); // put there bd date (in our time zone already) 

        birthdays_list[name] = birthday;// make a record in the list

    }

        std::time_t t = std::time(nullptr);
        std::tm present_time = *std::localtime(&t);
        std::tm nearest_bd = *std::localtime(&t); // suppose that the 
        nearest_bd.tm_mon = 12;                   // nearest bd is
        nearest_bd.tm_mday = 31;                  // on the 31 of December

        std::vector<std::string> bd_people; //a list of people with the nearest bds  

        for (auto it: birthdays_list) {

            if (it.second.tm_mon == present_time.tm_mon && it.second.tm_mday == present_time.tm_mday)
                std::cout << "Today is " << it.first << "'s birthday!" << std::endl;
            else {

                if (it.second.tm_mon > nearest_bd.tm_mon)
                    continue;

                if (it.second.tm_mon < nearest_bd.tm_mon) {
                    if (it.second.tm_mon == present_time.tm_mon && it.second.tm_mday > present_time.tm_mday) {
                        nearest_bd = it.second;
                        bd_people.clear();
                        bd_people.push_back(it.first);
                        continue;
                    } 

                    if (it.second.tm_mon > present_time.tm_mon) {
                        nearest_bd = it.second;
                        bd_people.clear();
                        bd_people.push_back(it.first);
                        continue;
                    }
                }

                    if (it.second.tm_mon == nearest_bd.tm_mon) {
                        if (it.second.tm_mon == present_time.tm_mon && 
                                it.second.tm_mday > present_time.tm_mday &&
                                it.second.tm_mday < nearest_bd.tm_mday) {
                            nearest_bd = it.second;
                            bd_people.clear();
                            bd_people.push_back(it.first);
                            continue;
                        } 
                        if (it.second.tm_mon > present_time.tm_mon && 
                            it.second.tm_mday < nearest_bd.tm_mday) {
                            nearest_bd = it.second;
                            bd_people.clear();
                            bd_people.push_back(it.first);
                            continue;
                        }
                        if (it.second.tm_mday == nearest_bd.tm_mday)
                            bd_people.push_back(it.first);
                }
            }
        }

        if (bd_people.empty())
            std::cout << "No more bithdays this year" << std::endl;
        else { 
            for (auto i: bd_people) 
                std::cout << i << " is celebrating his birthday on " << std::put_time(&birthdays_list[i], "%d of %B") << std::endl;
        }
    return 0;
}
