#ifndef COACH_HPP
#define COACH_HPP

#include "user.hpp"
#include <vector>
#include <memory>

class Coach : public User {
private:
    // all reservations of this coach
    std::vector<Reservation*> coach_reservations;

public:
    Coach(int id, const std::string& name);
    // displays the coach specific menu
    void view_menu() override;
    // displays the coach specific schedule
    void view_schedule() override;
    // reserves a spot for this coach from start to end
    void reserve() override;
    // cancels a session for this member during the given start end time (if valid)
    void cancel_reservation() override;
    // sends a message to an officer for a timechange
    void request_timechange();
};

#endif  // COACH_HPP
