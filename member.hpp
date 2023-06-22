#ifndef MEMBER_HPP
#define MEMBER_HPP

#include <vector>
#include <ctime>
#include <chrono>
#include <memory>


#include "user.hpp"
#include "reservation.hpp"
#include "court.hpp"


class Officer; // Forward declaration of the Officer class
class Court; // Forward declaration of the Court class

class Member : public User {
public:
    char skill_level;
    std::vector<std::shared_ptr<Reservation>> my_reservations;
    std::vector<std::shared_ptr<Officer>> all_officers;

public:
    Member(int id, const std::string& name, char skill, std::vector<std::shared_ptr<Court>> courts, std::vector<std::shared_ptr<Officer>> officers);
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
    const std::vector<std::shared_ptr<Reservation>> get_reservations() const;
    const std::vector<std::shared_ptr<Officer>> getAllOfficers() const;
};

#endif  // MEMBER_HPP