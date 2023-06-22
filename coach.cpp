#include "coach.hpp"
#include <iostream>
#include <ctime>
#include <chrono>
using namespace std;

Coach::Coach(int id, const std::string& name, char skill) : User(id, name, "coach"), skill_level(skill) {}

// Coach specific menu options
void Coach::view_menu()
{
    cout << "Enter the number associated with your option choice (1-4)";
    cout << "Coach Menu:\n";
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

void Coach::view_schedule()
{
    // print out the schedule by iterating through courts and iterating through each courts reservations
    // for the next 24 hours
    
}

void Coach::reserve()
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

        cout << "Enter the start time you want in the valid format (month, day, year, hour, minute)" << endl;
        int month, day, year, hour, minute;
        cin >> month >> day >> year >> hour >> minute;
        std::tm time{};
        time.tm_year = year - 1900; //  years since 1900
        time.tm_mon = month - 1;    //  months since january
        time.tm_mday = day;
        time.tm_hour = hour;
        time.tm_min = minute;
        std::time_t timeT = std::mktime(&time);
        std::chrono::system_clock::time_point startTime = std::chrono::system_clock::from_time_t(timeT);

        //TODO, implement reservaion valid checks
        Reservation new_reservation(User::getId(), startTime);
        my_reservations.push_back(new_reservation);
        
    }
}

void Coach::cancel_reservation()
{
    
}

void Coach::request_timechange()
{
// How to handle requests from member/coach to an officer? as in, should we
// have the user automatically send 008/009 a a request, passing in their id and new start 
// time? 
// the issue is, how do we refer to the officer object to call the officer method that
// makes a time change??? 

   
}
