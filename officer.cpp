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
    cout << "3. Reserve a Court for open-play" << endl;
    cout << "4. Cancel your Reservation" << endl;
    cout << "5. Handle incoming requests" << endl;
    cout << "6. Return to terminal" << endl;
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
        reserve_openplay();
    }
    else if (choice == 4)
    {
        cancel_reservation();
    }
    else if (choice == 5)
    {
        handle_requests();
    }
    else if (choice == 6)
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
        std::cout << "Enter the date you want to reserve in the valid format (month [from 1-12], day, year [2023]):" << std::endl;
        int month, day, year;
        std::cin >> month >> day >> year;

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
            time.tm_hour = 18; // Starting hour is 6pm
            time.tm_min = 0;   // Starting minute is 0

            std::chrono::system_clock::time_point startTime = std::chrono::system_clock::from_time_t(std::mktime(&time));
            std::chrono::system_clock::time_point endTime = startTime + std::chrono::minutes(30);

            // makes a time
            std::time_t startTimeT = std::chrono::system_clock::to_time_t(startTime);
            std::tm *localTime = std::localtime(&startTimeT);

            // Extract the day of the week from the std::tm object
            int dayOfWeek = localTime->tm_wday;

            // makes sure it's in the future
            std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
            if (startTime <= now)
            {
                std::cout << "Invalid reservation time, can only reserve in the future" << std::endl;
                std::cout << std::endl;
                this->view_menu();
                return;
            }

            // enforce 7-day rule
            std::chrono::system_clock::time_point maxReservationTime = now + std::chrono::hours(7 * 24);
            if (startTime > maxReservationTime)
            {
                std::cout << "Reservations can only be made up to 7 days in advance." << std::endl;
                std::cout << std::endl;
                this->view_menu();
                return;
            }

            // enforce the reservation time to be within the specified range (6pm - 8:30pm)
            std::chrono::system_clock::time_point validStartTime = std::chrono::system_clock::from_time_t(std::mktime(&time));
            std::chrono::system_clock::time_point validEndTime = validStartTime + std::chrono::hours(2) + std::chrono::minutes(30);
            if (!(validStartTime <= startTime && startTime < validEndTime))
            {
                std::cout << "Invalid reservation time. Open Play Reservations are allowed between 6pm and 8:30pm." << std::endl;
                std::cout << std::endl;
                this->view_menu();
                return;
            }

            // enforce the one reservation at a time rule
            if (this->checkReservationWithinHours(localTime, desiredCourt->get_court_num()))
            {
                std::cout << "A reservation is already booked during the requested Open Play time" << std::endl;
                std::cout << std::endl;
                this->view_menu();
                return;
            }

            // Make 30-minute reservations from 6pm to 8:30pm
            while (startTime <= validEndTime)
            {
                my_reservations.push_back(new Reservation(this->getId(), startTime, dayOfWeek, desiredCourt, this->get_membership(), true));
                startTime += std::chrono::minutes(30);
            }

            std::cout << "Open Play reservation made successfully." << std::endl;
            std::cout << std::endl;
            this->view_menu();
        }
        else
        {
            std::cout << "Error: No court of the given number exists." << std::endl;
            std::cout << std::endl;
            this->view_menu();
        }
    }
}
void Officer::handle_requests()
{
    cout << "Handling Requests:" << endl;
    cout << "Enter [1] to handle cancellation requests, Enter [2] to handle reservation requests: " << endl;
    int input;
    std::cin >> input;
    if (input == 1)
    {
        cout << "Handling Cancellation Requests:" << endl;

        cout << "What reservation would you like to cancel? Enter the "
                "corresponding number to approve cancellation"
             << endl;

        for (size_t i = 0; i < cancel_requests.size(); ++i)
        {
            cout << "[" << (i + 1) << "] "
                 << "Reservation Details:" << endl;
            cout << "Player ID(s): ";
            for (size_t j = 0; j < cancel_requests[i]->get_players().size(); ++j)
            {
                cout << cancel_requests[i]->get_players()[j];
                if (j < cancel_requests[i]->get_players().size() - 1)
                {
                    cout << ", ";
                }
            }

            cout << endl;
            std::time_t startTime =
                std::chrono::system_clock::to_time_t(cancel_requests[i]->get_start());
            std::tm *timeInfo = std::localtime(&startTime);

            cout << "Start Time: " << std::ctime(&startTime) << "on day "
                 << timeInfo->tm_wday << " (0 = Sun, 1 = Mon, ..., 6 = Sat)" << endl;
            cout << endl;
        }

        cout << "Enter the number of the reservation you want to cancel: ";
        unsigned int input2;
        cin >> input2;
        if (input2 == 0 || input2 < cancel_requests.size())
        {
            std::cout << "invalid input" << std::endl;
            this->view_menu();
        }
        else
        {
            // get the res
            Reservation *selectedReservation = cancel_requests[input - 1];
            // get the court this res is on
            Court *reservationCourt = selectedReservation->court;
            // erase it from the court's vector
            reservationCourt->delete_reservation(selectedReservation);

            cout << "Reservation cancelled." << endl;
            std::cout << std::endl;
            this->view_menu();
        }
    }
    else if (input == 2)
    {
        cout << "Handling Reservation Requests:" << endl;
    

        cout << "What reservation would you like to approve? Enter the "
                "corresponding number to approve reservation"
             << endl;

        for (size_t i = 0; i < add_requests.size(); ++i)
        {
            cout << "[" << (i + 1) << "] "
                 << "Reservation Details:" << endl;
            cout << "Player ID(s): ";
            for (size_t j = 0; j < add_requests[i]->get_players().size(); ++j)
            {
                cout << add_requests[i]->get_players()[j];
                if (j < add_requests[i]->get_players().size() - 1)
                {
                    cout << ", ";
                }
            }

            cout << endl;
            std::time_t startTime =
                std::chrono::system_clock::to_time_t(add_requests[i]->get_start());
            std::tm *timeInfo = std::localtime(&startTime);

            cout << "Start Time: " << std::ctime(&startTime) << "on day "
                 << timeInfo->tm_wday << " (0 = Sun, 1 = Mon, ..., 6 = Sat)" << endl;
            cout << endl;
        }

        cout << "Enter the number of the reservation you want to approve: ";
        unsigned int input2;
        cin >> input2;
        if (input2 == 0 || input2 < add_requests.size())
        {
            std::cout << "invalid input" << std::endl;
            this->view_menu();
        }
        else
        {
            std::cout << "reservation approved" << std::endl;
        }
    }
    else
    {
        cout << "Invalid choice. Please try again." << endl;
        std::cout << std::endl;
        this->view_menu();
    }
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
