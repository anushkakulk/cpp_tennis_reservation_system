#ifndef MEMBER_HPP
#define MEMBER_HPP

#include "user.hpp"
#include "reservation.hpp"
#include "court.hpp"
#include "officer.hpp"
#include <vector>
#include <memory>
#include <ctime>
#include <chrono>

class Member : public User {
public:
    char skill_level;
    std::vector<Reservation*> my_reservations;

public:
    Member(int id, char skill);
    // returns this member's skill level: either 'A' 'B' or 'C'
    char get_skill();
    // displays the the member specific menu
    void view_menu() override;
    // displays the member specific schedule 
    void view_schedule() override;
    // reserves a session for this member during the given start end time (if valid)
    void reserve() override;
    // cancels a session for this member 
    void cancel_reservation() override;
    // sends a message to an officer to request a timechange, giving it this member's id and the start end time
    void request_timechange();
    // getters
    const std::vector<Reservation*>& get_reservations() const;
    const std::vector<Officer*>& getAllOfficers() const;
    

};

#endif  // MEMBER_H
