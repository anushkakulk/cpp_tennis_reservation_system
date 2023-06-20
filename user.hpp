#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <chrono>
#include "reservation.hpp"

class User {
private:
    // unique id for each user
    int id;
    // name for a user
    string name;
    // string, either "member" "coach" "officer"
    std::string membership_type;

public:
    User(int id, const std::string& type);
    // returns this user's id 
    int getId();
    // returns this user's id 
    string get_name();
    // reserves a spot for this user at the given start and end time
    virtual void reserve();
    // cancels a spot for this user at the given start and end time
    virtual void cancel_reservation();
    // displays the user-specific menu
    virtual void view_menu();
    // displays the user-specific schedule;
    virtual void view_schedule();
};

#endif  // USER_HPP
