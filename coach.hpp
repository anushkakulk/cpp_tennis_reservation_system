#ifndef COACH_HPP
#define COACH_HPP

#include "reservation.hpp"
#include "user.hpp"
#include "officer.hpp"
#include <vector>
#include <memory>

class Coach : public User
{
public:

    std::vector<Officer *> all_officers;

public:
    Coach(int id, const std::string &name, std::vector<Court *> courts, std::vector<Officer *> officers);
    // RULE OF 5
    Coach(const Coach &other);                // copy
    Coach &operator=(const Coach &other);     // copy assign. op.
    Coach(Coach &&other) noexcept;            // move
    Coach &operator=(Coach &&other) noexcept; // move assign. op.
    ~Coach();                                 // destruct
    // displays the coach specific menu
    void view_menu() override;
    // displays the coach specific schedule (only coach sessions)
    void view_schedule() override;
    // reserves a spot for this coach from start to end
    void reserve() override;
    // cancels a session for this member during the given start end time (if valid)
    void cancel_reservation() override;
    // sends a message to an officer for a timechange/cancellation/reservation
    void request();
};

#endif // COACH_HPP