#include "user.hpp"
#include <iostream>

User::User(int id, const std::string& name, const std::string& type, std::vector<std::shared_ptr<Court>> courts) : id(id), name(name), membership_type(type), all_courts(courts) {}

// returns this user's id
int User::getId() {
    return id;
}

// returns this user's name
std::string User::get_name() {
    return name;
}

// returns all courts accessible by this user
std::vector<std::shared_ptr<Court>> User::get_courts() {
    return all_courts;
}

// displays the user-specific menu
void User::view_menu() {
    std::cout << "Enter the number associated with your option choice (1-4)";
    std::cout << "User Menu:\n";
    std::cout << "1. View Schedule\n";
    std::cout << "2. Reserve a Court\n";
    std::cout << "3. Cancel a Reservation\n";
    int choice;
    std::cin >> choice;

    // schedule view
    if (choice == 1) {
        view_schedule();
    }
    else if (choice == 2) {
        reserve();
    }
    else if (choice == 3) {
        cancel_reservation();
    }
    else {
        std::cout << "Invalid choice. Please try again.\n";
    }
}

// displays the user-specific schedule
void User::view_schedule() {
    // print out the schedule by iterating through courts and iterating through each courts reservations
    // for the next 24 hours
}

// reserves a court for this user
void User::reserve() {
    std::cout << "Making a Reservation:" << std::endl;
    std::cout << "Enter the court number you want (1-3)" << std::endl;
    int courtNum;
    std::cin >> courtNum;
    if (courtNum != 1 || courtNum != 2 || courtNum != 3) {
        std::cout << "Invalid choice. Please try again." << std::endl;
    }
    else {
        std::cout << "Enter the time you want to reserve (0-23)" << std::endl;
        int time;
        std::cin >> time;
        if (time < 0 || time > 23) {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
        else {
            // reserve the court
        }
    }
}

// cancels a reservation for this user
void User::cancel_reservation() {
    std::cout << "Cancelling a Reservation:" << std::endl;
    std::cout << "Enter the court number you want to cancel (1-3)" << std::endl;
    int courtNum;
    std::cin >> courtNum;
    if (courtNum != 1 || courtNum != 2 || courtNum != 3) {
        std::cout << "Invalid choice. Please try again." << std::endl;
    }
    else {
        std::cout << "Enter the time you want to cancel (0-23)" << std::endl;
        int time;
        std::cin >> time;
        if (time < 0 || time > 23) {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
        else {
            // cancel the reservation
        }
    }
}
