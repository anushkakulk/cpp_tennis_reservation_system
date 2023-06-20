#ifndef RESERVATION_HPP
#define RESERVATION_HPP

#include <vector>
#include <chrono>
#include <memory>
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
    // is this reservation for open play or not?    
    bool open_play;
    // the court this reservation is for
    std::shared_ptr<Court> court;

public:
    Reservation(int player_id, const std::chrono::system_clock::time_point& startDateTime, std::shared_ptr<Court> c);
    // adds another username to users (enforce max is 2) 
    void add_user(std::shared_ptr<User> u);
    // removes a user from this reservation (needs 1 user to still be on this tho)
    void remove_user(std::shared_ptr<User> u);
    // returns ids of players on this reservation
    std::vector<int> get_players();
    // removes this reservation
    void delete_reservation();
    // returns the start datetime
    std::chrono::system_clock::time_point get_start();
    // returns openplay bool
    bool is_openplay();
    // changes the start time for this resrvation (first checks that id is from an officer)
    void set_start(int id, std::chrono::system_clock::time_point time);
};

#endif  // RESERVATION_H
