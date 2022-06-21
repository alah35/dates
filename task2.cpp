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
        std::tm nearest_bd = present_time;
        nearest_bd.tm_mon = present_time.tm_mon - 1; // suppose, that the nearest bd
        nearest_bd.tm_mday = present_time.tm_mday -1; // was last month minus 1 day

        std::vector<std::string> bd_people; //a list of people with the nearest bds  
        for (auto it: birthdays_list) {

            if (it.second.tm_mon == present_time.tm_mon && it.second.tm_mday == present_time.tm_mday)
                std::cout << "Today is " << it.first << "'s birthday!" << std::endl;
            else {

                int diff_near_present_m = nearest_bd.tm_mon - present_time.tm_mon;
                int diff_this_present_m = it.second.tm_mon - present_time.tm_mon;

                if (diff_this_present_m < 0) // if this date earlier than present
                    continue;

                if (diff_near_present_m > diff_this_present_m) { // if this date aerlier than nearest bd
                    nearest_bd = it.second;
                    continue;
                }

                if (diff_near_present_m == diff_near_present_m) { // if these same months

                    if (it.second.tm_mday > nearest_bd.tm_mday) 
                        continue;

                    if (it.second.tm_mday < nearest_bd.tm_mday) {
                        nearest_bd = it.second;
                        continue;
                    }

                    if (it.second.tm_mday == nearest_bd.tm_mday) { // if this date and the nearest bd are the same date
                        bd_people.push_back(it.first); // add this people to the list of people with nearest bd 
                        continue;
                    }
                }
            }
        }
        
        for (auto i: bd_people) 
            std::cout << i << " is celebrating his birthday on " << std::put_time(&birthdays_list[i], "%d of %B") << std::endl;
    return 0;
}
