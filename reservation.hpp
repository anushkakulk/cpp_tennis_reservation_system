#ifndef RESERVATION_HPP
#define RESERVATION_HPP

#include <vector>
#include <chrono>
#include "user.hpp"
#include "court.hpp"

class Reservation {
private:
    // list of user ids involved in this reservation
    std::vector<int> player_ids;
    // start and end times - format is: 
    // EXAMPLE: std::chrono::system_clock::time_point june19 = std::chrono::system_clock::from_time_t(std::mktime(std::tm{0, 0, 0, 19, 5, 2023}));
    // format is hour, minute, second, day, month - 1, year
    std::chrono::system_clock::time_point start_datetime;
    // represents day of the week (0 = sunday, ... 6 = saturday)
    int day_of_week; 
    // is this reservation for open play or not?
    bool open_play;
    // the court this reservation is for
    Court* court;
    // reservation id
    int id;
public:
    Reservation(int player_id, const std::chrono::system_clock::time_point& startDateTime, int day, Court* c);
    // adds another username to users (enforce max is 2) 
    void add_user(User& u);
    // removes a user from this reservation (needs 1 user to still be on this tho)
    void remove_user(User& u);
    // returns ids of players on this reservation
    std::vector<int> get_players();
    // removes this reservation
    void delete_reservation();
    // returns the start datetime
    std::chrono::system_clock::time_point get_start();
    // returns openplay bool
    bool is_openplay();
    // changes the start time for this reservation (first checks that id is from an officer)
    void set_start(int id, std::chrono::system_clock::time_point time);
    // override '==' operator to compare 
    bool operator==(const Reservation& other) const;
    // returns the id of this reservation
    int get_id();
};

#endif  // RESERVATION_H
