#include "coach.hpp"
#include <iostream>
#include <ctime>
#include <chrono>
using namespace std;

Coach::Coach(int id, const std::string &name, std::vector<Court *> courts, std::vector<Officer *> officers) : User(id, name, "coach", courts), all_officers(officers) {}

// Coach specific menu options
void Coach::view_menu()
{
    cout << "Enter the number associated with your option choice (1-4)" << endl;
    cout << "Coach Menu: " << endl;
    cout << "1. View Schedule" << endl;
    cout << "2. Reserve a Court" << endl;
    cout << "3. Cancel a Reservation" << endl;
    cout << "4. Request Time Change" << endl;
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
        std::cout << std::endl;
        this->view_menu();
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

        std::cout << "Enter the start time you want in valid format, pressing [enter] in between each input (month [from 1-12], day, year [2023], hour [from 0 to 23], minute [either 0 or 30])" << std::endl;
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
            time.tm_hour = hour;
            time.tm_min = minute;
            std::time_t timeT = std::mktime(&time);
            std::chrono::system_clock::time_point startTime = std::chrono::system_clock::from_time_t(timeT);
            std::time_t startTimeT = std::chrono::system_clock::to_time_t(startTime);
            std::tm *localTime = std::localtime(&startTimeT);

            // the day of the week (from 0 to 6)
            int dayOfWeek = localTime->tm_wday;
            // the hour
            int hour = localTime->tm_hour;
            // the minute
            int minute = localTime->tm_min;
            auto maxReservationTime = std::chrono::system_clock::now() + std::chrono::hours(7 * 24);

            // makes sure its in the future
            if (startTime <= std::chrono::system_clock::now())
            {
                std::cout << "Invalid reservation time, can only reserve in the future" << std::endl;
                std::cout << std::endl;
                this->view_menu();
            }

            // enforce 7 day rule

            else if (startTime > maxReservationTime)
            {
                std::cout << "Reservations can only be made up to 7 days in advance." << std::endl;
                std::cout << std::endl;
                this->view_menu();
            }

            // this checks that reservation is only on weekday during coaching hours
            else if (!((hour >= 9 && hour < 11) || (hour == 11 && minute <= 30) || (hour >= 15 && hour < 17) || (hour == 17 && minute <= 30)) || !(dayOfWeek >= 1 && dayOfWeek <= 5))
            {
                std::cout << "Invalid reservation time. Reservations are allowed between 9am-11:30am and 3pm-5:30pm, Monday to Friday." << std::endl;
                std::cout << std::endl;
                this->view_menu();
            }
            else
            {

                // TODO, check that no one is on the court then
                coach_reservations.push_back(new Reservation(this->getId(), startTime, dayOfWeek, desiredCourt));
            }
        }
        else
        {
            std::cout << "Error, no court of the given number exists" << std::endl;
            this->view_menu();
        }
    }
}

void Coach::cancel_reservation()
{

    // cout << "Cancelling a Reservation:" << endl;
    // cout << endl;
    // cout << "Here are your reservations:" << endl;

    // for (size_t i = 0; i < coach_reservations.size(); ++i)
    // {
    //    cout << "[" << (i + 1) << "] " << *coach_reservations[i] << endl;

    // }

    // cout << "Enter the number of the reservation you want to cancel (or 0 to cancel): ";
    // int input;
    // cin >> input;
    // // make sure its valid
    // if (input >= 1 && input <= coach_reservations.size())
    // {
    //     // get the res
    //     shared_ptr<Reservation> &selectedReservation = coach_reservations[input - 1];
    //     // get the court this res is on
    //     shared_ptr<Court> reservationCourt = selectedReservation->court;
    //     // erase it from the court's vector
    //     reservationCourt->delete_reservation(selectedReservation);

    //     // erase the reservation from the coach's vector of reservations
    //     coach_reservations.erase(coach_reservations.begin() + (input - 1));

    //     cout << "Reservation cancelled." << endl;

    // }else if (input == 0)
    //     {
    //         cout << "Reservation cancellation was cancelled." << endl;
    //         cout << endl;
    //         this->view_menu();
    //     }
    //     else
    //     {
    //         cout << "Invalid input. Reservation cancellation was aborted." << endl;
    //         cout << endl;
    //         this->view_menu();
    //     }
    

}

void Coach::request_timechange()
{
    // How to handle requests from member/coach to an officer? as in, should we
    // have the user automatically send 008/009 a a request, passing in their id and new start
    // time?
    // the issue is, how do we refer to the officer object to call the officer method that
    // makes a time change???
}