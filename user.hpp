#ifndef USER_HPP
#define USER_HPP

#include "reservation.hpp"
#include "court.hpp"
#include <string>
#include <chrono>

#include <vector>

class Court;
class Reservation;

class User
{
private:
    // unique id for each user
    int id;
    // name for a user
    std::string name;
    // string, either "member" "coach" "officer"
    std::string membership_type;
    // all courts
    std::vector<Court *> all_courts;

public:
    User(int id, const std::string &name, const std::string &type, std::vector<Court *> courts);

    // RULE OF 5
    // User(const User &other);                // Copy constructor
    // User &operator=(const User &other);     // Copy assignment operator
    // User(User &&other) noexcept;            // Move constructor
    // User &operator=(User &&other) noexcept; // Move assignment operator
    // ~User();                                // Destructor
    // returns this user's id
    int getId();
    // returns this user's id
    std::string get_name();
    // returns this user's id
    std::vector<Court *> get_courts();

    std::string get_membership(); 

    // reserves a spot for this user at the given start and end time
    virtual void reserve();
    // cancels a spot for this user at the given start and end time
    virtual void cancel_reservation();
    // displays the user-specific menu
    virtual void view_menu();
    // displays the user-specific schedule;
    virtual void view_schedule();

    // User registerUser(); 

    std::string toString() const {
    std::string registeredUser = std::to_string(id) + " " + name + " " + membership_type + "\n";
    return registeredUser;
  }
};

User registerUser();
 
#endif // USER_HPP
