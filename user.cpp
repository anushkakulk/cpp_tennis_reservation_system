#include "user.hpp"
#include <iostream>

User::User(int id, const std::string &name, const std::string &type, std::vector<Court *> courts) : id(id), name(name), membership_type(type), all_courts(courts) {}

// copy constructor
User::User(const User& other)
    : id(other.id), name(other.name), membership_type(other.membership_type) {
    for (const auto& court : other.all_courts) {
        all_courts.push_back(new Court(*court));
    }
    for (const auto& reservation : other.my_reservations) {
        my_reservations.push_back(new Reservation(*reservation));
    }
}

// ccopy assignment operator
User& User::operator=(const User& other) {
    if (this == &other) {
        return *this;
    }

    id = other.id;
    name = other.name;
    membership_type = other.membership_type;

    // clear pointer allocations
    for (auto court : all_courts) {
        delete court;
    }
    all_courts.clear();

    for (auto reservation : my_reservations) {
        delete reservation;
    }
    my_reservations.clear();

    // Copy courts
    for (const auto& court : other.all_courts) {
        all_courts.push_back(new Court(*court));
    }

    // Copy reservations
    for (const auto& reservation : other.my_reservations) {
        my_reservations.push_back(new Reservation(*reservation));
    }

    return *this;
}

// move constructor
User::User(User&& other) noexcept
    : id(other.id), name(std::move(other.name)), membership_type(std::move(other.membership_type)),
      all_courts(std::move(other.all_courts)), my_reservations(std::move(other.my_reservations)) {
    other.id = 0;
}

// move assignment operator
User& User::operator=(User&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    id = other.id;
    name = std::move(other.name);
    membership_type = std::move(other.membership_type);

    // clear pointer allocations
    for (auto court : all_courts) {
        delete court;
    }
    all_courts.clear();

    for (auto reservation : my_reservations) {
        delete reservation;
    }
    my_reservations.clear();

    all_courts = std::move(other.all_courts);
    my_reservations = std::move(other.my_reservations);

    other.id = 0;

    return *this;
}


// destructor
User::~User() = default;

// returns this user's id
int User::getId()
{
    return id;
}

// returns this user's name
std::string User::get_name()
{
    return name;
}

// returns all courts accessible by this user
std::vector<Court *> User::get_courts()
{
    return all_courts;
}

// displays the user-specific menu
void User::view_menu()
{
    std::cout << "Enter the number associated with your option choice (1-4)";
    std::cout << "User Menu:\n";
    std::cout << "1. View Schedule\n";
    std::cout << "2. Reserve a Court\n";
    std::cout << "3. Cancel a Reservation\n";
    int choice;
    std::cin >> choice;

    // schedule view
    if (choice == 1)
    {
        view_schedule();
    }
    else if (choice == 2)
    {
        reserve();
    }
    else if (choice == 3)
    {
        cancel_reservation();
    }
    else
    {
        std::cout << "Invalid choice. Please try again.\n";
    }
}

// displays the user-specific schedule
void User::view_schedule()
{
    // print out the schedule by iterating through courts and iterating through each courts reservations
    // for the next 24 hours
}

// reserves a court for this user
void User::reserve()
{
    std::cout << "Making a Reservation:" << std::endl;
    std::cout << "Enter the court number you want (1-3)" << std::endl;
    int courtNum;
    std::cin >> courtNum;
    if (courtNum != 1 && courtNum != 2 && courtNum != 3)
    {
        std::cout << "Invalid choice. Please try again." << std::endl;
    }
    else
    {
        std::cout << "Enter the time you want to reserve (0-23)" << std::endl;
        int time;
        std::cin >> time;
        if (time < 0 || time > 23)
        {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
        else
        {
            // reserve the court
        }
    }
}

// cancels a reservation for this user
void User::cancel_reservation()
{
    std::cout << "Cancelling a Reservation:" << std::endl;
    std::cout << "Enter the court number you want to cancel (1-3)" << std::endl;
    int courtNum;
    std::cin >> courtNum;
    if (courtNum != 1 && courtNum != 2 && courtNum != 3)
    {
        std::cout << "Invalid choice. Please try again." << std::endl;
    }
    else
    {
        std::cout << "Enter the time you want to cancel (0-23)" << std::endl;
        int time;
        std::cin >> time;
        if (time < 0 || time > 23)
        {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
        else
        {
            // cancel the reservation
        }
    }
}
