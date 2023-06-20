#ifndef MEMBER_HPP
#define MEMBER_HPP

#include "user.hpp"
#include <vector>
#include <memory>
#include <ctime>
#include <chrono>

class Member : public User {
private:
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
};

#endif  // MEMBER_H
