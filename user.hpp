#ifndef USER_HPP
#define USER_HPP

#include "reservation.hpp"
#include "court.hpp"
#include <string>
#include <chrono>
#include <memory>


#include <vector>

class Court;
class Reservation;

class User {
private:
    // unique id for each user
    int id;
    // name for a user
    std::string name;
    // string, either "member" "coach" "officer"
    std::string membership_type;
    // all courts
    std::vector<std::shared_ptr<Court>> all_courts;

public:

    User(int id, const std::string& name, const std::string& type, std::vector<std::shared_ptr<Court>> courts);
    // returns this user's id 
    int getId();
    // returns this user's id 
    std::string get_name();
    // returns this user's id 
    std::vector<std::shared_ptr<Court>>  get_courts();

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