#ifndef COACH_HPP
#define COACH_HPP

#include "reservation.hpp"
#include "user.hpp"
#include "officer.hpp"
#include <vector>
#include <memory>

class Coach : public User {
public:
    // all reservations of this coach
    std::vector<std::shared_ptr<Reservation>> coach_reservations;
    std::vector<std::shared_ptr<Officer>> all_officers;

public:
    Coach(int id, const std::string& name, std::vector<std::shared_ptr<Court>> courts, std::vector<std::shared_ptr<Officer>> officers);
    // displays the coach specific menu
    void view_menu() override;
    // displays the coach specific schedule
    void view_schedule() override;
    // reserves a spot for this coach from start to end
    void reserve() override;
    // cancels a session for this member during the given start end time (if valid)
    void cancel_reservation() override;
    // sends a message to an officer for a time change
    void request_timechange();
};

#endif  // COACH_HPP
