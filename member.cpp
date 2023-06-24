#include "member.hpp"
#include "officer.hpp"
#include <iostream>
#include <ctime>
#include <chrono>
#include <random>
#include <fstream>      // For std::ifstream
#include <sstream>      // For std::istringstream
#include <string>       // For std::string and std::getline
#include <vector>       // For std::vector
#include <iomanip>
using namespace std;

Member::Member(int id, const std::string &name, char skill, std::vector<Court *> courts, std::vector<Officer *> officers) : User(id, name, "member", courts), skill_level(skill), all_officers(officers) {}

// copy constructor
Member::Member(const Member& other)
    : User(other), skill_level(other.skill_level) {
   
}
// copy assignment operator
Member& Member::operator=(const Member& other) {
    if (this == &other) {
        return *this;
    }
    User::operator=(other);
    all_officers = other.all_officers;

    // // free up vector<officer> allocation
    // for (auto* o : all_officers) {
    //     delete o;
    // }
    all_officers.clear();

    // copy 
    for (const auto* o : other.all_officers) {
        all_officers.push_back(new Officer(*o));
    }
    skill_level=other.skill_level;
    return *this;
}
// move constructor
Member::Member(Member&& other) noexcept
    : User(std::move(other)), skill_level(std::move(other.skill_level)),
       all_officers(std::move(other.all_officers)) {
    other.skill_level = 'F';
    other.all_officers.clear();
}
// move assignment operator
Member& Member::operator=(Member&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    User::operator=(std::move(other));
    skill_level = (std::move(other.skill_level));
   
    all_officers = std::move(other.all_officers);

    other.skill_level = 'F';
   
    other.all_officers.clear();

    return *this;
}

Member::~Member() = default;

char Member::get_skill()
{
    return skill_level;
}

// member specific menu options
void Member::view_menu()
{
    std::cout << std::endl; 
    cout << "Menu Style Options: Choose a feature (1-4) associated with your choice" << endl;
    std::cout << std::endl; 
    cout << "Member Menu: " << endl;
    cout << "1. View Schedule" << endl;
    cout << "2. View all of your reservations" << endl;
    cout << "3. Reserve a Court" << endl;
    cout << "4. Cancel a Reservation" << endl;
    cout << "5. Send a Request to an Officer" << endl;
    cout << "6. Quit to Terminal" << endl;
    int choice;
    cin >> choice;

    // schedule view
    if (choice == 1) {
       view_schedule();
    } else if (choice == 2) {
        view_my_reservations();
    } else if (choice == 3) {
        reserve();
    } else if (choice == 4) {
       cancel_reservation();
    } else if (choice == 5) {
       //request_timechange();
    } else if (choice == 6) {
      return;
    } else {
        cout << "Invalid choice. Please try again. \n";
        std::cout << std::endl;
        this->view_menu();
    }
}

void Member::view_schedule()
{
    // Get the ID of the current member
    int current_player_id = this->getId();

    // Iterate through each court
    for (auto &court : this->get_courts()) {
        // Get the filename of court's reservation file
        std::string filename = "court" + std::to_string(court->get_court_num()) + ".txt";

        // Open the file
        std::ifstream file(filename);

        if (file.is_open()) {
            std::string line;

            // Read each line (reservation) in the file
            while (getline(file, line)) {
                // Parse the reservation details from the line
                std::istringstream ss(line);

                // Assuming that the player ID is first in the formatted string
                std::string player_id_str;
                std::getline(ss, player_id_str, ',');
                // Extract the ID after "Player ID: "
                int player_id = std::stoi(player_id_str.substr(11));

                // Assuming the membership type is second in the formatted string
                std::string membership_type_str;
                std::getline(ss, membership_type_str, ',');
                // Extract the membership type after "Membership Type: "
                std::string extracted_membership_type = membership_type_str.substr(18);

                // If the player ID matches the current member's ID and the membership type matches the given type, print the line
                if (player_id == current_player_id && extracted_membership_type == this->get_membership()) {
                    std::cout << line << std::endl;
                }
            }

            file.close();
        }
        else {
            std::cout << "Unable to open file" << std::endl;
        }
    }
}



void Member::reserve()
{
    cout << "Making a Reservation:" << endl;
    std::cout << "Enter which court you want to reserve: (1, 2, or 3): ";
    int court_num;
    std::cin >> court_num;
    if (court_num != 1 && court_num != 2 && court_num != 3)
    {
        cout << "Invalid choice. Please try again." << endl;
        std::cout << std::endl;
        this->view_menu();
    }
    else
    {

        std::cout << "Enter the start time you want in the valid format (month [from 1-12], day, year [2023], hour [from 0 to 23], minute [either 0 or 30])" << std::endl;
        int month, day, year, hour, minute;
        std::cin >> month >> day >> year >> hour >> minute;

        Court *desiredCourt = nullptr;

        for (const auto &c : User::get_courts())
        {
            if (court_num == c->get_court_num())
            {
                desiredCourt = c;
                break;
            }
        }

        if (desiredCourt != nullptr)
        {
            std::tm time{};
            time.tm_year = year - 1900; // years since 1900
            time.tm_mon = month - 1;    // months since January
            time.tm_mday = day;
            time.tm_hour = hour - 1;
            // time.tm_min = minute;/;p[\]-
            std::time_t timeT = std::mktime(&time);
            std::chrono::system_clock::time_point startTime = std::chrono::system_clock::from_time_t(timeT);
            // max 7 days in advance
            auto maxReservationTime = std::chrono::system_clock::now() + std::chrono::hours(7 * 24);
            // makes a time
            std::time_t startTimeT = std::chrono::system_clock::to_time_t(startTime);
            // gets the local time 
            std::tm *localTime = std::localtime(&startTimeT);

            // extract the day of the week from the std::tm object
            int dayOfWeek = localTime->tm_wday;
            // makes sure its in the future
            if (startTime <= std::chrono::system_clock::now())
            {
                std::cout << "Invalid reservation time, can only reserve in the future" << std::endl;
                std::cout << std::endl;
                this->view_menu();
            }

            // enforce the 7 day rule
            else if (startTime > maxReservationTime)
            {
                std::cout << "Reservations can only be made up to 7 days in advance." << std::endl;
                std::cout << std::endl;
                this->view_menu();
            }
            // prevent reserving during coaching hours 48+ hours in advance
            else if (
                startTime > std::chrono::system_clock::now() + std::chrono::hours(48) &&
                (localTime->tm_wday >= 1 && localTime->tm_wday <= 5 && (
                (localTime->tm_hour >= 9 && localTime->tm_hour < 11) ||
                (localTime->tm_hour == 11 && localTime->tm_min <= 30) ||
                (localTime->tm_hour >= 15 && localTime->tm_hour < 17) ||
                (localTime->tm_hour == 17 && localTime->tm_min <= 30)))) {
                    std::cout << "You are trying to reserve a spot that is for coaching hours." << std::endl;
                    std::cout << "Try again 48 hours before the reservation for availability." << std::endl;
                    std::cout << std::endl;
                    this->view_menu();
            } // prevent reserving during open play hours 48+ hours in advance
            else if (
                startTime > std::chrono::system_clock::now() + std::chrono::hours(48) &&
                 (localTime->tm_hour >= 18 && localTime->tm_hour < 20) ||
                  (localTime->tm_hour == 20 && localTime->tm_min <= 30)){
                    std::cout << "You are trying to reserve a spot that is for open play hours." << std::endl;
                    std::cout << "Try again 48 hours before the reservation for availability." << std::endl;
                    std::cout << std::endl;
                    this->view_menu();
            }
            else
            {

                // TODO, check that no one is on the court then
                my_reservations.push_back(new Reservation(this->getId(), startTime, dayOfWeek, desiredCourt, this->get_membership()));

                cout << endl;
                this->view_menu();
            }
        }
        else
        {
            std::cout << "Error, no court of the given number exists" << std::endl;
            std::cout << std::endl;
            this->view_menu();
        }
    }
}

void Member::cancel_reservation()
{
    cout << "Cancelling a Reservation:" << endl;
    cout << endl;
    cout << "Here are your reservations:" << endl;

    for (size_t i = 0; i < my_reservations.size(); ++i)
    {
        cout << "[" << (i + 1) << "] "
             << "Reservation Details:" << endl;
        cout << "Player ID(s): ";
        for (size_t j = 0; j < my_reservations[i]->get_players().size(); ++j)
        {
            cout << my_reservations[i]->get_players()[j];
            if (j < my_reservations[i]->get_players().size() - 1)
            {
                cout << ", ";
            }
        }

        cout << endl;
        std::time_t startTime = std::chrono::system_clock::to_time_t(my_reservations[i]->get_start());
        std::tm *timeInfo = std::localtime(&startTime);

        cout << "Start Time: " << std::ctime(&startTime) << "on day " << timeInfo->tm_wday << " (0 = Sun, 1 = Mon, ..., 6 = Sat)" << endl;
        cout << endl;
    }

    cout << "Enter the number of the reservation you want to cancel (or 0 to cancel): ";
    unsigned int input;
    cin >> input;
    // make sure its valid
    if (input >= 1 && input <= my_reservations.size())
    {
        // get the res
        Reservation *selectedReservation = my_reservations[input - 1];
        // get the court this res is on
        Court *reservationCourt = selectedReservation->court;
        // erase it from the court's vector
        reservationCourt->delete_reservation(selectedReservation);

        // erase the reservation from the coach's vector of reservations
        my_reservations.erase(my_reservations.begin() + (input - 1));

        cout << "Reservation cancelled." << endl;
        std::cout << std::endl;
        this->view_menu();
    }
    else if (input == 0)
    {
        cout << "Reservation cancellation was cancelled." << endl;
        cout << endl;
        this->view_menu();
    }
    else
    {
        cout << "Invalid input. Reservation cancellation was aborted." << endl;
        cout << endl;
        this->view_menu();
    }
}
/*
void Member::request_timechange()
{
    
    cout << "Sending Officer requests" << endl;
    cout << endl;
    cout << "Enter the number associated with your option choice (1-3)" << endl;
    cout << "What kind of modification would you like to do today? " << endl;
    cout << "1. Change an existing reservation's time" << endl;
    cout << "2. Cancel an existing reservation's via an officer" << endl;
    cout << "3. Make a reservation via an officer" << endl;
    unsigned int mod;
    cin >> mod;
    if (mod == 1) {
    cout << "What reservation would you like to modify? Enter the corresponding number" << endl;

    for (size_t i = 0; i < my_reservations.size(); ++i)
    {
        cout << "[" << (i + 1) << "] "
             << "Reservation Details:" << endl;
        cout << "Player ID(s): ";
        for (size_t j = 0; j < my_reservations[i]->get_players().size(); ++j)
        {
            cout << my_reservations[i]->get_players()[j];
            if (j < my_reservations[i]->get_players().size() - 1)
            {
                cout << ", ";
            }
        }

        cout << endl;
        std::time_t startTime = std::chrono::system_clock::to_time_t(my_reservations[i]->get_start());
        std::tm *timeInfo = std::localtime(&startTime);

        cout << "Start Time: " << std::ctime(&startTime) << "on day " << timeInfo->tm_wday << " (0 = Sun, 1 = Mon, ..., 6 = Sat)" << endl;
        cout << endl;
    }

    cout << "Enter the number of the reservation you want to modify: ";
    unsigned int input;
    cin >> input;   
    std::time_t old_time = std::chrono::system_clock::to_time_t(my_reservations[input]->get_start());
    std::chrono::system_clock::time_point old_start = std::chrono::system_clock::from_time_t(old_time);
    std::cout << "Enter the start time you want in the valid format (month [from 1-12], day, year [2023], hour [from 0 to 23], minute [either 0 or 30])" << std::endl;
    int month, day, year, hour, minute;
    std::cin >> month >> day >> year >> hour >> minute;
    
            std::tm time{};
            time.tm_year = year - 1900; // years since 1900
            time.tm_mon = month - 1;    // months since January
            time.tm_mday = day;
            time.tm_hour = hour - 1;
            time.tm_min = minute;
            std::time_t timeT = std::mktime(&time);
            std::chrono::system_clock::time_point new_start = std::chrono::system_clock::from_time_t(timeT);
            // max 7 days in advance
            auto maxReservationTime = std::chrono::system_clock::now() + std::chrono::hours(7 * 24);

            // makes sure its in the future
            if (new_start <= std::chrono::system_clock::now())
            {
                std::cout << "Invalid reservation time, can only reserve in the future" << std::endl;
                std::cout << std::endl;
                this->view_menu();
            }

            // enforce the 7 day rule
            else if (new_start > maxReservationTime)
            {
                std::cout << "Reservations can only be made up to 7 days in advance." << std::endl;
                std::cout << std::endl;
                this->view_menu();
            }
        else {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        // choose a random officer
        Officer* selectedOfficer = nullptr; // Declare selectedOfficer outside the if statement

    if (!all_officers.empty()) {
    std::size_t randomIndex = std::rand() % all_officers.size();
    selectedOfficer = all_officers[randomIndex];
    std::cout << "Officer ID: " << selectedOfficer->getId() << " will handle your request" << std::endl;
    } else {
    std::cout << "No officers available." << std::endl;
    }

    if (selectedOfficer != nullptr) {
    selectedOfficer->modify_reservation(this->getId(), old_start, new_start);
    this->view_menu();
    }
    } 
    } else if (mod == 2) {
        this->cancel_reservation();
    } else if (mod == 3) {
        this->reserve();
    } else {
        return;
     }
 }
}
*/  
