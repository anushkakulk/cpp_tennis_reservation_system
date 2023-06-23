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
class Court; // Forward declaration of the Court class

class Member : public User {
public:
    char skill_level;
    std::vector<Reservation*> my_reservations;
    std::vector<Officer*> all_officers;

public:
    
    Member(int id, const std::string& name, char skill, std::vector<Court*> courts, std::vector<Officer*> officers);
    // RULE OF 5
    // Member(const Member& other); // copy 
    // Member& operator=(const Member& other); //copy assign. op. 
    // Member(Member&& other) noexcept; // move
    // Member& operator=(Member&& other) noexcept; // move assign. op.
    // ~Member(); // destruct
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
    const std::vector<Reservation*> get_reservations() const;
    const std::vector<Officer*> get_officers() const;
};

#endif  // MEMBER_HPP