#ifndef OFFICER_HPP
#define OFFICER_HPP

#include <vector>
#include <chrono>
#include <string>
#include "member.hpp"

class Court; // Forward declaration of the Court class

class Officer : public Member
{
public:
    std::vector<User *> all_users;
    std::vector<Reservation *> cancel_requests;
    std::vector<Reservation *> add_requests;

public:
    // RULE OF 5 IMPLEMENTED IN MEMBER CLASS
    Officer(int id, const std::string &name, char skill, std::vector<Court *> courts, std::vector<Officer *> officers);

    ~Officer(); // Destructor

    Officer(const Officer &other); // Copy constructor

    Officer &operator=(const Officer &other); // Copy assignment operator

    Officer(Officer &&other) noexcept; // Move constructor

    Officer &operator=(Officer &&other) noexcept; // Move assignment operator
    // displays the coach specific menu
    void view_menu() override;
    // reserved open play time for the given id for the given start/end datetimes
    void reserve_openplay();
    // adds the given request to respective array to be cancelled or added
    void handle_request(int id, Reservation *r, bool cancel);
    // can either reserve or delete reservations based on requests
    void handle_requests();
    // changes the time for the given id at the given start/end datetimes to
    // a reservation at the new start and end times
    void modify_reservation(int id, std::chrono::system_clock::time_point old_time, std::chrono::system_clock::time_point start_time);
};

#endif // OFFICER_HPP
