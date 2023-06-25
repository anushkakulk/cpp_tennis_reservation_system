#ifndef RESERVATION_HPP
#define RESERVATION_HPP

#include <vector>
#include <chrono>
#include <string>
#include "user.hpp"
#include "court.hpp"
class User;
class Court;

class Reservation
{
private:
    // list of user ids involved in this reservation
    std::vector<int> player_ids;
    // start and end times
    std::chrono::system_clock::time_point start_datetime;
    // represents day of the week (0 = sunday, ... 6 = saturday)
    int day_of_week;
    // is this reservation for open play or not?
    bool open_play;
    // users membership type
    std::string membership_type;

public:
    // the court this reservation is for
    Court *court;

public:
    // RULE OF 5
    Reservation(int player_id, const std::chrono::system_clock::time_point &startDateTime, int day, Court *c, const std::string &membership);
    Reservation(const Reservation &other);                // Copy constructor
    Reservation &operator=(const Reservation &other);     // Copy assignment operator
    Reservation(Reservation &&other) noexcept;            // Move constructor
    Reservation &operator=(Reservation &&other) noexcept; // Move assignment operator
    ~Reservation();                                       // Destructor
    // adds another username to users (enforce max is 2)
    void add_user(User &u);
    // removes a user from this reservation (needs 1 user to still be on this tho)
    void remove_user(User &u);
    // returns ids of players on this reservation
    std::vector<int> get_players();
    // removes this reservation
    void delete_reservation();
    // returns the start datetime
    std::chrono::system_clock::time_point get_start();
    // returns openplay bool
    bool is_openplay();
    // changes the start time for this reservation (only if valid time)
    void set_start(int id, std::chrono::system_clock::time_point time);
    // override '==' operator to compare
    bool operator==(const Reservation &other) const;
    // returns the id of this reservation
    int get_player_id() const;
    // convert reservation to string
    std::string toString() const;
    // get user membership type
    std::string get_membership_type() const;
};

#endif // RESERVATION_H
