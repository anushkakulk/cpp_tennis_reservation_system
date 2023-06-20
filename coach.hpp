#ifndef COACH_HPP
#define COACH_HPP

#include "user.hpp"
#include <vector>
#include <memory>

class Coach : public User {
private:
    // all reservations of this coach
    std::vector<std::shared_ptr<Reservation>> coach_reservations;

public:
    Coach(int id);
    // displays the coach specific menu
    void view_menu() override;
    // displays the coach specific schedule
    void view_schedule() override;
    // reserves a spot for this coach from start to end
    void reserve() override;
    // sends a message to an officer for cancellation
    void request_cancellation();
    // sends a message to an officer for a timechange
    void request_timechange();
};

#endif  // COACH_HPP
