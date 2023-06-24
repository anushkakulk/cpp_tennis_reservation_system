#ifndef OFFICER_HPP
#define OFFICER_HPP

#include <vector>
#include <chrono>
#include <string>
#include "member.hpp"

class Court; // Forward declaration of the Court class

class Officer : public Member {
    public:
    std::vector<User*> all_users;
public:
    // RULE OF 5 IMPLEMENTED IN MEMBER CLASS
    Officer(int id, const std::string& name, char skill, std::vector<Court*> courts, std::vector<Officer*> officers);
    // displays the coach specific menu
    void view_menu() override;
    // reserved open play time for the given id for the given start/end datetimes
    void reserve_openplay();
    // timechanges for the given id for the given start
    void handle_request(int id, std::chrono::system_clock::time_point start_time, bool cancel);
    // reserves or deleted time for the given id for the given start
    void handle_requests();
    // changes the time for the given id at the given start/end datetimes to 
    // a reservation at the new start and end times 
    void modify_reservation(int id, std::chrono::system_clock::time_point start_time);
};

#endif  // OFFICER_HPP
