#include "user.hpp"
#include <iostream>
#include <fstream>
#include <vector> 
#include <sstream>

User::User(int id, const std::string &name, const std::string &type, std::vector<Court *> courts) : id(id), name(name), membership_type(type), all_courts(courts) {}

// // copy constructor
// User::User(const User &other)
//     : id(other.id), name(other.name), membership_type(other.membership_type)
// {
//     for (const auto &court : other.all_courts)
//     {
//         all_courts.push_back(new Court(*court));
//     }
// }

// // copy assignment operatior
// User &User::operator=(const User &other)
// {
//     if (this == &other)
//     {
//         return *this;
//     }

//     id = other.id;
//     name = other.name;
//     membership_type = other.membership_type;

//     // clear pointer allocation
//     for (auto court : all_courts)
//     {
//         delete court;
//     }
//     all_courts.clear();

//     for (const auto &court : other.all_courts)
//     {
//         all_courts.push_back(new Court(*court));
//     }

//     return *this;
// }

// // move constructor
// User::User(User &&other) noexcept
//     : id(other.id), name(std::move(other.name)), membership_type(std::move(other.membership_type)),
//       all_courts(std::move(other.all_courts))
// {
//     other.id = 0;
// }

// // move assignment operator
// User &User::operator=(User &&other) noexcept
// {
//     if (this == &other)
//     {
//         return *this;
//     }

//     id = other.id;
//     name = std::move(other.name);
//     membership_type = std::move(other.membership_type);

//     // clear pointer allocation
//     for (auto court : all_courts)
//     {
//         delete court;
//     }
//     all_courts.clear();

//     all_courts = std::move(other.all_courts);

//     other.id = 0;

//     return *this;
// }

// // destructor
// User::~User()
// {
//     for (auto court : all_courts)
//     {
//         delete court;
//     }
//     all_courts.clear();
// }

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

std::string User::get_membership()
{
   return membership_type; 

}

// returns all courts accessible by this user
std::vector<Court *> User::get_courts()
{
    return all_courts;
}

User  registerUser() {
  std::string uniqueId;
  std::string username;
  std::string membershipType;

  std::cout << "Enter your ID: ";
  std::cin >> uniqueId;

  std::cout << "Enter your name: ";
  std::cin >> username;

  std::cout << "Enter membership type (member, coach, or officer): ";
  std::cin >> membershipType;

  std::ifstream readFile("users.txt");
  bool userExists = false;

  if (readFile.is_open()) {
    std::string line;
    while (std::getline(readFile, line)) {
        std::string id, name, membership;
        std::istringstream iss(line);

        if (std::getline(iss, id, ' ') &&
            std::getline(iss, name, ' ') &&
            std::getline(iss, membership, ' ')) {
            if (id == uniqueId && name == username && membership == membershipType) {
                userExists = true; 
                break;
            }
        }
    }
    readFile.close();
  } else {
    std::cout << "Failed to open the file for reading." << std::endl;
    return User(-1, "", "", std::vector<Court *>()); // Return an invalid user
  }

  if (userExists) {
    std::cout << "User exists, welcome!" << std::endl;
    return User(std::stoi(uniqueId), username, membershipType, std::vector<Court *>());
  } else {
    User newUser(std::stoi(uniqueId), username, membershipType, std::vector<Court *>());
    std::ofstream outFile("users.txt", std::ios::app);
    if (outFile.is_open()) {
      outFile << newUser.toString();
      outFile.close();
      std::cout << "User registered successfully, welcome!" << std::endl;
    } else {
      std::cout << "Failed to open the file for writing." << std::endl;
    }

    return newUser;
  }
}

// displays the user-specific menu
void User::view_menu()
{
    std::cout << "Enter the number associated with your option choice (1-4)" << std::endl; 
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
