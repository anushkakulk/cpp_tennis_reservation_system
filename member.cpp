#include "member.hpp"
#include <iostream>
using namespace std;

Member::Member(int id, char skill) : User(id, "member"), skill_level(skill) {}

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
    cout << "3. Request Cancellation\n";
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
        request_cancellation();
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

        cout << "Enter the start time you want in the valid format (month, day, year, hour, minute)" std::cin >> month >> day >> year >> hour >> minute;
        std::tm time{};
        time.tm_year = year - 1900; //  years since 1900
        time.tm_mon = month - 1;    //  months since january
        time.tm_mday = day;
        time.tm_hour = hour;
        time.tm_min = minute;
        std::time_t timeT = std::mktime(&time);
        std::chrono::system_clock::time_point startTime = std::chrono::system_clock::from_time_t(timeT);

        //TODO, implement reservaion valid checks
        Reservation new_reservation(this->getId(), startTime);
        std::shared_ptr<Reservation> reservationPtr = std::shared_ptr<Reservation>(new Reservation(new_reservation));
        my_reservations.push_back(reservationPtr);
    }
}

void Member::request_cancellation()
{
    
}

void Member::request_timechange()
{
   
}
