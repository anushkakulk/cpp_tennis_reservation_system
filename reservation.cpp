#include "reservation.hpp"
#include <algorithm>
#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <ctime>


Reservation::Reservation(int player_id, const std::chrono::system_clock::time_point &startDateTime, int day, Court *c, const std::string& membership)
    : start_datetime(startDateTime), day_of_week(day), court(c), membership_type(membership) 
{
    
    // adds this players id to reservation
    player_ids.push_back(player_id);
    // adds this rseervation to the courts
    c->add_reservation(this);
    std::time_t startTime = std::chrono::system_clock::to_time_t(start_datetime);
    std::cout << "Reservation made by ID: " << player_id
              << " at " << std::ctime(&startTime) << "on day " << day << " (0 = sun, 1 = mon, ... 6 = sat)" << std::endl;
}

void Reservation::add_user(User &u)
{
    //  max of 2 players in a reservation
    if (player_ids.size() < 2)
    {
        player_ids.push_back(u.getId());
    }
}
// copy constructor
Reservation::Reservation(const Reservation &other)
    : player_ids(other.player_ids),
      start_datetime(other.start_datetime),
      day_of_week(other.day_of_week),
      open_play(other.open_play),
      court(other.court) {}

// copy assignmetn operator
Reservation &Reservation::operator=(const Reservation &other)
{
    if (this == &other)
    {
        return *this;
    }

    player_ids = other.player_ids;
    start_datetime = other.start_datetime;
    day_of_week = other.day_of_week;
    open_play = other.open_play;
    court = other.court;

    return *this;
}
// move constrcutr
Reservation::Reservation(Reservation &&other) noexcept
    : player_ids(std::move(other.player_ids)),
      start_datetime(std::move(other.start_datetime)),
      day_of_week(other.day_of_week),
      open_play(other.open_play),
      court(other.court)
{
    other.court = nullptr;
}
// move assignment operator
Reservation &Reservation::operator=(Reservation &&other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    player_ids = std::move(other.player_ids);
    start_datetime = std::move(other.start_datetime);
    day_of_week = other.day_of_week;
    open_play = other.open_play;
   
    court = other.court;

    other.court = nullptr;

    return *this;
}
// Destructor
Reservation::~Reservation() = default;

void Reservation::remove_user(User &u)
{
    // Ensure there is at least 1 user remaining in the reservation
    if (player_ids.size() > 1)
    {
        auto it = std::find(player_ids.begin(), player_ids.end(), u.getId());
        if (it != player_ids.end())
        {
            player_ids.erase(it);
        }
    }
}

std::vector<int> Reservation::get_players()
{
    return player_ids;
}

void Reservation::delete_reservation()
{
    court->delete_reservation(this);
}

std::chrono::system_clock::time_point Reservation::get_start()
{
    return start_datetime;
}

bool Reservation::is_openplay()
{
    return open_play;
}

void Reservation::set_start(int id, std::chrono::system_clock::time_point time)
{
    std::time_t startTimeT = std::chrono::system_clock::to_time_t(time);
    std::tm *localTime = std::localtime(&startTimeT);
    int hour = localTime->tm_hour;
    int minute = localTime->tm_min;
    int dayOfWeek = localTime->tm_wday;

    // in the future
    if (time <= std::chrono::system_clock::now())
    {
        std::cout << "Invalid reservation time, can only reserve in the future" << std::endl;
        std::cout << std::endl;
        return;
    }

    // week in advance only
    std::chrono::system_clock::time_point maxReservationTime = std::chrono::system_clock::now() + std::chrono::hours(7 * 24);
    if (time > maxReservationTime)
    {
        std::cout << "Reservations can only be made up to 7 days in advance." << std::endl;
        std::cout << std::endl;
        return;
    }

    if (id == 6 || id == 7) {
        // check if the reservation is within coaching hours (9am-11:30am and 3pm-5:30pm, Monday to Friday)
        if (!((hour >= 9 && hour <= 11) || (hour == 15 && minute >= 0 && minute <= 30) || (hour == 17 && minute == 0)) || !(dayOfWeek >= 1 && dayOfWeek <= 5))
        {
            std::cout << "Invalid reservation time. Reservations are allowed between 9am-11:30am and 3pm-5:30pm, Monday to Friday." << std::endl;
            std::cout << std::endl;
            return;
        }
    }
    else if (id == 8 || id == 9) {
        // check if the reservation is within open play hours (6pm-9:30pm)
        if (!((hour == 18 && minute >= 0) || (hour >= 19 && hour < 21) || (hour == 21 && minute <= 30)))
        {
            std::cout << "Invalid reservation time. Open Play Reservations are allowed between 6pm and 9:30pm." << std::endl;
            std::cout << std::endl;
            return;
        }
    }
    // cool, so update the time
    start_datetime = time;
    day_of_week = dayOfWeek;
}


std::string Reservation::toString() const {
    std::stringstream ss;

    // Convert the time_point to time_t to print it
    std::time_t start_time_t = std::chrono::system_clock::to_time_t(start_datetime);
    std::tm * ptm = std::localtime(&start_time_t);

    // Assume court_num is the identifier for Court
    int court_num = court->get_court_num();

    char buffer[32]; // buffer for time

    // Format the start_datetime using "%Y-%m-%d %H:%M:%S" format
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ptm);

    ss << "Player ID: " << get_player_id()
       << ", Membership Type: " << get_membership_type() // Print the user type
       << ", Start Time: " << buffer
       << ", Day: " << day_of_week
       << ", Court: " << court_num;

    return ss.str();
}

int Reservation::get_player_id() const {
    if (!player_ids.empty()) {
        return player_ids[0];
    } else {
        // Handle case when there is no player in the list
        // For instance, you can return -1 or throw an exception
        return -1;
    }
}

std::string Reservation::get_membership_type() const {
    return membership_type;
}


