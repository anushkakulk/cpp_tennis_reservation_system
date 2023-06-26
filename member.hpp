#ifndef MEMBER_HPP
#define MEMBER_HPP

#include <vector>
#include <ctime>
#include <chrono>
#include <random>
#include <ctime>

#include "user.hpp"
#include "reservation.hpp"
#include "court.hpp"

class Officer;
class Court;

class Member : public User
{
public:
    char skill_level;
    std::vector<Officer *> all_officers;

public:
    Member(int id, const std::string &name, char skill, std::vector<Court *> courts, std::vector<Officer *> officers);
    // RULE OF 5
    Member(const Member &other);                // copy
    Member &operator=(const Member &other);     // copy assign. op.
    Member(Member &&other) noexcept;            // move
    Member &operator=(Member &&other) noexcept; // move assign. op.
    virtual ~Member();                          // destruct
    // returns this member's skill level: either 'A' 'B' or 'C'
    char get_skill();
    // displays the the member specific menu
    void view_menu() override;
    // displays complete schedules
    void view_schedule() override;
    // reserves a session for this member during the given start end time (if valid)
    void reserve() override;
    // cancels a session for this member
    void cancel_reservation() override;
    // sends a request to an officer to request a timechange, cancellation, or reservation
    void request();
    // returns true if the member has more than 2 reservations within a weeks time
    bool checkReservationWithinWeek(int id, std::tm *localTime);
    // returns true if the member is trying to reserve a resrvation within 24 hours of their own existing one
    bool checkReservationWithinDay(int id, std::tm *localTime);
    // allows a member to join an existing reservation
    void joinReservation(std::vector<Court*> all_courts);
};

#endif // MEMBER_HPP
