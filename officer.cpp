#include "officer.hpp"
#include <iostream>
#include <algorithm>
using namespace std;

Officer::Officer(int id, const std::string &name, char skill, std::vector<Court *> courts, std::vector<Officer *> officers) : Member(id, name, skill, courts, officers) {}

Officer::Officer(const Officer &other)
    : Member(other), all_users(), cancel_requests(), add_requests()
{

    for (User *user : other.all_users)
    {
        all_users.push_back(new User(*user));
    }

    for (Reservation *reservation : other.cancel_requests)
    {
        cancel_requests.push_back(new Reservation(*reservation));
    }

    for (Reservation *reservation : other.add_requests)
    {
        add_requests.push_back(new Reservation(*reservation));
    }
}

Officer &Officer::operator=(const Officer &other)
{
    if (this != &other)
    {
        Member::operator=(other);

        all_users.clear();

        cancel_requests.clear();

        add_requests.clear();

        for (User *user : other.all_users)
        {
            all_users.push_back(new User(*user));
        }

        for (Reservation *reservation : other.cancel_requests)
        {
            cancel_requests.push_back(new Reservation(*reservation));
        }

        for (Reservation *reservation : other.add_requests)
        {
            add_requests.push_back(new Reservation(*reservation));
        }
    }
    return *this;
}

Officer::~Officer() = default;
Officer::Officer(Officer &&other) noexcept
    : Member(std::move(other)), all_users(std::move(other.all_users)),
      cancel_requests(std::move(other.cancel_requests)), add_requests(std::move(other.add_requests))
{

    other.all_users.clear();
    other.cancel_requests.clear();
    other.add_requests.clear();
}

Officer &Officer::operator=(Officer &&other) noexcept
{
    if (this != &other)
    {
        Member::operator=(std::move(other));

        all_users.clear();

        cancel_requests.clear();

        add_requests.clear();

        all_users = std::move(other.all_users);
        cancel_requests = std::move(other.cancel_requests);
        add_requests = std::move(other.add_requests);

        other.all_users.clear();
        other.cancel_requests.clear();
        other.add_requests.clear();
    }
    return *this;
}
void Officer::view_menu()
{
    cout << "Enter the number associated with your option choice (1-4)" << endl;
    cout << "Officer Menu: " << endl;
    cout << "1. View Schedule" << endl;
    cout << "2. Reserve a Court for yourself" << endl;
    cout << "3. Cancel your Reservation" << endl;
    cout << "4. Handle incoming requests" << endl;
    cout << "5. Return to terminal" << endl;
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
        handle_requests();
    }
    else if (choice == 5)
    {
        return;
    }
    else
    {
        cout << "Invalid choice. Please try again. \n";
        std::cout << std::endl;
        this->view_menu();
    }
}

void Officer::reserve_openplay()
{
    cout << "Making a Reservation for Open Play (any day, 6-9pm if free):" << endl;
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
            time.tm_min = minute;
            std::time_t timeT = std::mktime(&time);
            std::chrono::system_clock::time_point startTime = std::chrono::system_clock::from_time_t(timeT);
            // max 7 days in advance
            auto maxReservationTime = std::chrono::system_clock::now() + std::chrono::hours(7 * 24);
            // makes a time
            std::time_t startTimeT = std::chrono::system_clock::to_time_t(startTime);
            // gets the local time to extract day of week
            std::tm *localTime = std::localtime(&startTimeT);

            // Extract the day of the week from the std::tm object
            int dayOfWeek = localTime->tm_wday;

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

            // this checks that reservation is only during open play hours
            else if (!((hour == 18 && minute >= 0) || (hour >= 19 && hour < 20) || (hour == 20 && minute <= 30)))
            {
                std::cout << "Invalid reservation time. Open Play Reservations are allowed between 6pm and 9pm." << std::endl;
                std::cout << std::endl;
                this->view_menu();
            }
            // enforce the one reservation at a time rule
            else if (this->checkReservationWithinHours(localTime, desiredCourt->get_court_num()))
            {
                std::cout << "A reservation is already booked during the requested time" << std::endl;
                std::cout << "Check the schedule again and book during a time with no reservations" << std::endl;
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

void Officer::handle_requests()
{
}
void Officer::handle_request(int id, Reservation *r, bool cancel)
{
    if (cancel)
    {
        cancel_requests.push_back(r);
    }
    else
    {
        add_requests.push_back(r);
    }
}

void Officer::modify_reservation(int id, std::chrono::system_clock::time_point old_start, std::chrono::system_clock::time_point new_start)
{
    for (User *user : all_users)
    {
        if (user->getId() == id)
        {
            for (Reservation *reservation : user->my_reservations)
            {
                if (reservation->get_start() == old_start)
                {
                    reservation->set_start(user->getId(), new_start);

                    auto it = std::find_if(user->my_reservations.begin(), user->my_reservations.end(),
                                           [reservation](const Reservation *r)
                                           { return r == reservation; });
                    if (it != user->my_reservations.end())
                    {
                        user->my_reservations.erase(it);
                    }
                    // Add the modified reservation back to the vector
                    user->my_reservations.push_back(reservation);
                    return;
                }
            }
        }
    }
}
