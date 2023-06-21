#include "member.hpp"
#include <iostream>
#include <ctime>
#include <chrono>
using namespace std;

Member::Member(int id, const std::string& name, char skill) : User(id, name, "member"), skill_level(skill) {}

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
    if (courtNum != 1 || courtNum != 2 || courtNum != 3)
    {
        cout << "Invalid choice. Please try again." << endl;
    }
    else
    {

    std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point maxReservationTime = currentTime + std::chrono::hours(24 * 7);

    std::cout << "Enter the start time you want in the valid format (month [from 1-12], day, year [2023], hour [from 0 to 23], minute [either 0 or 30])" << std::endl;
    int month, day, year, hour, minute;
    std::cin >> month >> day >> year >> hour >> minute;

    std::cout << "Enter which court you want to reserve: (1, 2, or 3)"
    int court_num;
    std::cin >> court_num;
    std::tm time{};
    time.tm_year = year - 1900; // years since 1900
    time.tm_mon = month - 1;    // months since January
    time.tm_mday = day;
    time.tm_hour = hour;
    time.tm_min = minute;
    std::time_t timeT = std::mktime(&time);
    std::chrono::system_clock::time_point startTime = std::chrono::system_clock::from_time_t(timeT);

    // enforce 7 day in advance limit
    if (startTime > maxReservationTime) {
        std::cout << "Reservations can only be made up to 7 days in advance." << std::endl;
        return 0;
    }
        std::tm* localTime = std::localtime(&startTime);

        Extract the day of the week from the std::tm object
        int dayOfWeek = localTime->tm_wday;

        // TODO, check that no one is on the court then
        Reservation new_reservation(User::getId(), startTime, dayOfWeek, court_num);
        my_reservations.push_back(new_reservation);
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
