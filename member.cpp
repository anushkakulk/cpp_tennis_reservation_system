#include "member.hpp"
#include <iostream>
#include <ctime>
#include <chrono>
using namespace std;

Member::Member(int id, const std::string& name, char skill, std::vector<Court*> courts, std::vector<Officer*> officers) : User(id, name, "member", courts), skill_level(skill), all_officers(officers) {}

char Member::get_skill()
{
    return skill_level;
}

// member specific menu options
void Member::view_menu()
{
    cout << "Enter the number associated with your option choice (1-4)";
    cout << "Member Menu:\n";
    cout << "1. View Schedule\n";
    cout << "2. Reserve a Court\n";
    cout << "3. Cancel a Reservation\n";
    cout << "4. Request Time Change\n";
    int choice;
    cin >> choice;

    // schedule view
    if (choice == 1)
    {
        view_schedule();
        
    }
    else if (choice == 2)
    {
        reserve();
    }
    else if (choice == 3)
    {
        cancel_reservation();
    }
    else if (choice == 4)
    {
        request_timechange();
    }
    else
    {
        cout << "Invalid choice. Please try again.\n";
    }
}

void Member::view_schedule()
{
    // print out the schedule by iterating through courts and iterating through each courts reservations
    // for the next 24 hours
}

void Member::reserve()
{
    cout << "Making a Reservation:" << endl;
    cout << "Enter the court number you want (1-3)" << endl;
    int courtNum;
    cin >> courtNum;
    if (courtNum != 1 && courtNum != 2 && courtNum != 3)
    {
        cout << "Invalid choice. Please try again." << endl;
    }
    else
    {

    std::cout << "Enter the start time you want in the valid format (month [from 1-12], day, year [2023], hour [from 0 to 23], minute [either 0 or 30])" << std::endl;
    int month, day, year, hour, minute;
    std::cin >> month >> day >> year >> hour >> minute;

    std::cout << "Enter which court you want to reserve: (1, 2, or 3)";
    int court_num;
    std::cin >> court_num;

Court* desiredCourt = nullptr;  

for (const auto& c : User::get_courts()) {
    if (court_num == c->get_court_num()) {
        desiredCourt = c;  
        break;  
    }
}

if (desiredCourt != nullptr) {
    std::tm time{};
    time.tm_year = year - 1900; // years since 1900
    time.tm_mon = month - 1;    // months since January
    time.tm_mday = day;
    time.tm_hour = hour;
    time.tm_min = minute;
    std::time_t timeT = std::mktime(&time);
    std::chrono::system_clock::time_point startTime = std::chrono::system_clock::from_time_t(timeT);

    // makes sure its in the future
if (startTime <= std::chrono::system_clock::now()) {
    std::cout << "Invalid reservation time, can only reserve in the future" << std::endl;
    return;
}

// enforce the 7 day rule 
auto maxReservationTime = std::chrono::system_clock::now() + std::chrono::hours(7 * 24);
if (startTime > maxReservationTime) {
    std::cout << "Reservations can only be made up to 7 days in advance." << std::endl;
    return;
}

    std::time_t startTimeT = std::chrono::system_clock::to_time_t(startTime);
    std::tm* localTime = std::localtime(&startTimeT);

        // Extract the day of the week from the std::tm object
        int dayOfWeek = localTime->tm_wday;
        // TODO, check that no one is on the court then
        my_reservations.push_back(new Reservation(User::getId(), startTime, dayOfWeek, desiredCourt));

    } else {
        std::cout << "Error, no court of the given number exists" << std::endl;
        return;
    }
}
}

void Member::cancel_reservation()
{
    
}

void Member::request_timechange()
{
// How to handle requests from member/coach to an officer? as in, should we
// have the user automatically send 008/009 a a request, passing in their id and new start 
// time? 
// the issue is, how do we refer to the officer object to call the officer method that
// makes a time change??? 

   
}