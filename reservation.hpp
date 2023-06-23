#ifndef RESERVATION_HPP
#define RESERVATION_HPP

#include <vector>
#include <chrono>
#include <memory>

#include "user.hpp"
#include "court.hpp"
class User;
class Court;


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
    // reservation id
    int id;

public:
    // the court this reservation is for
    std::shared_ptr<Court> court;

public:
    Reservation(int player_id, const std::chrono::system_clock::time_point& startDateTime, int day, bool open_play, std::shared_ptr<Court> c);
    // adds another username to users (enforce max is 2) 
    void add_user(User& u);
    // removes a user from this reservation (needs 1 user to still be on this tho)
    void remove_user(User& u);
    // returns ids of players on this reservation
    std::vector<int> get_players()  const;
    // removes this reservation
    void delete_reservation();
    // returns the start datetime
    std::chrono::system_clock::time_point get_start()  const;
    // returns openplay bool
    bool is_openplay()  const;
    // returns the day of the week
    int get_day() const;
    // changes the start time for this reservation (first checks that id is from an officer)
    void set_start(int id, std::chrono::system_clock::time_point time);
    // override '==' operator to compare 
    bool operator==(const Reservation& other) const;
    // returns the id of this reservation
    int get_id() const;
    // overloads << operator and outputs reservation information
    friend std::ostream &operator<<(std::ostream &os, const Reservation &reservation);

   
};

#endif  // RESERVATION_H