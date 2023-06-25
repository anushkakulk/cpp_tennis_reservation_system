#include "user.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <fstream>  // For std::ifstream
#include <sstream>  // For std::istringstream
#include <string>   // For std::string and std::getline
#include <vector>   // For std::vector
#include <iostream> // For std::cout
#include <chrono>   // For std::chrono
#include <iomanip>
#include "reservation.hpp" // For Reservation
#include "court.hpp"       // For Court
#include "user.hpp"        // For User

using namespace std;

User::User(int id, const std::string &name, const std::string &type, std::vector<Court *> courts) : id(id), name(name), membership_type(type), all_courts(courts) {}

// copy constructor
User::User(const User &other)
    : id(other.id), name(other.name), membership_type(other.membership_type)
{
    for (const auto &court : other.all_courts)
    {
        all_courts.push_back(new Court(*court));
    }
}

// copy assignment operatior
User &User::operator=(const User &other)
{
    if (this == &other)
    {
        return *this;
    }

    id = other.id;
    name = other.name;
    membership_type = other.membership_type;

    // clear pointer allocation
    for (auto court : all_courts)
    {
        delete court;
    }
    all_courts.clear();

    for (const auto &court : other.all_courts)
    {
        all_courts.push_back(new Court(*court));
    }

    return *this;
}

// move constructor
User::User(User &&other) noexcept
    : id(other.id), name(std::move(other.name)), membership_type(std::move(other.membership_type)),
      all_courts(std::move(other.all_courts))
{
    other.id = 0;
}

// move assignment operator
User &User::operator=(User &&other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    id = other.id;
    name = std::move(other.name);
    membership_type = std::move(other.membership_type);

    // clear pointer allocation
    for (auto court : all_courts)
    {
        delete court;
    }
    all_courts.clear();

    all_courts = std::move(other.all_courts);

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

std::string User::get_membership()
{
    return membership_type;
}

// returns all courts accessible by this user
std::vector<Court *> User::get_courts()
{
    return all_courts;
}

User registerUser() {
    std::string choice;
    std::cout << "Welcome to the court reservation system!" << std::endl;
    std::cout << "1. Register" << std::endl;
    std::cout << "2. Login" << std::endl;
    std::cout << "Please enter your choice (1 or 2): ";
    std::cin >> choice;

    if (choice == "1") {
        // User wants to register
        std::string uniqueId;
        std::string username;
        std::string membershipType;

        std::cout << "Enter your ID (must be a number and less than 4 digits): ";
        while (true) {
            std::cin >> uniqueId;
            if (uniqueId == "Q")
                return User(-1, "", "", std::vector<Court*>()); // Return an invalid user if user quits

            // Check if the ID is a number and has less than 4 digits
            bool isValidId = true;
            for (char c : uniqueId) {
                if (!std::isdigit(c)) {
                    isValidId = false;
                    break;
                }
            }
            if (isValidId && uniqueId.size() < 4) {
                // Check if the ID already exists in users.txt
                std::ifstream readFile("users.txt");
                if (readFile.is_open()) {
                    std::string line;
                    while (std::getline(readFile, line)) {
                        std::string id;
                        std::istringstream iss(line);

                        if (std::getline(iss, id, ' ')) {
                            if (id == uniqueId) {
                                std::cout << "ID already exists. Please enter a different ID (or enter Q to quit): ";
                                break;
                            }
                        }
                    }
                    readFile.close();

                    if (line.empty())
                        break; // ID is unique
                }
                else {
                    std::cout << "Failed to open the file for reading." << std::endl;
                    return User(-1, "", "", std::vector<Court*>()); // Return an invalid user
                }
            }

            std::cout << "Invalid ID. Please enter a number with less than 4 digits (or enter Q to quit): ";
        }

        std::cout << "Enter your name: ";
        std::cin >> username;

        std::cout << "Enter membership type (member, coach, or officer): ";
        while (true) {
            std::cin >> membershipType;
            if (membershipType == "member" || membershipType == "coach" || membershipType == "officer")
                break;
            else
                std::cout << "Invalid membership type. Please enter member, coach, or officer: ";
        }

        std::ofstream outFile("users.txt", std::ios::app);
        if (outFile.is_open()) {
            outFile << uniqueId << ' ' << username << ' ' << membershipType << std::endl;
            outFile.close();
            std::cout << "User registered successfully, welcome!" << std::endl;
        }
        else {
            std::cout << "Failed to open the file for writing." << std::endl;
            return User(-1, "", "", std::vector<Court*>()); // Return an invalid user
        }

        return User(std::stoi(uniqueId), username, membershipType, std::vector<Court*>());
    }
    else if (choice == "2") {
        // User wants to log in
        std::string uniqueId;
        std::string username;

        std::cout << "Enter your ID: ";
        std::cin >> uniqueId;

        std::cout << "Enter your name: ";
        std::cin >> username;

        std::ifstream readFile("users.txt");
        bool userExists = false;
        int userId = -1;
        std::string membershipType;
        std::vector<Court*> courts;

        if (readFile.is_open()) {
            std::string line;
            while (std::getline(readFile, line)) {
                std::string id, name, membership;
                std::istringstream iss(line);

                if (std::getline(iss, id, ' ') &&
                    std::getline(iss, name, ' ') &&
                    std::getline(iss, membership, ' ')) {
                    if (id == uniqueId && name == username) {
                        userExists = true;
                        userId = std::stoi(id);
                        membershipType = membership;
                        break;
                    }
                }
            }
            readFile.close();
        }
        else {
            std::cout << "Failed to open the file for reading." << std::endl;
            return User(-1, "", "", std::vector<Court*>()); // Return an invalid user
        }

        if (userExists) {
            std::cout << "User logged in successfully, welcome back!" << std::endl;
            return User(userId, username, membershipType, courts);
        }
        else {
            std::cout << "User does not exist. Please register or try again." << std::endl;
            return User(-1, "", "", std::vector<Court*>()); // Return an invalid user
        }
    }
    else {
        std::cout << "Invalid choice. Please try again." << std::endl;
        return User(-1, "", "", std::vector<Court*>()); // Return an invalid user
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
    // Get current time
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    // Add 24 hours to current time
    std::chrono::system_clock::time_point next_day = now + std::chrono::hours(24);

    // Iterate through each court
    for (auto &court : all_courts)
    {
        // Get the filename of court's reservation file
        std::string filename = "court" + std::to_string(court->get_court_num()) + ".txt";

        // Open the file
        std::ifstream file(filename);

        if (file.is_open())
        {
            std::string line;

            // Read each line (reservation) in the file
            while (getline(file, line))
            {
                // Parse the reservation details from the line
                // This part depends on how you've formatted the toString() function in Reservation class

                std::istringstream ss(line);

                // Assuming that the start time is second in the formatted string from Reservation::toString()
                std::string ignore, start_time_str;
                std::getline(ss, ignore, ',');
                std::getline(ss, start_time_str, ',');

                // Assuming start time string is formatted as "%Y-%m-%d %H:%M:%S", convert it to time_point
                std::tm tm = {};
                std::istringstream start_time_ss(start_time_str);
                // start_time_ss >> std::get_time(&tm, " %Y-%m-%d %H:%M:%S");
                auto start_time = std::chrono::system_clock::from_time_t(std::mktime(&tm));

                // If the start time of the reservation is within the next 24 hours
                if (start_time >= now && start_time <= next_day)
                {
                    std::cout << line << std::endl;
                }
            }

            file.close();
        }
        else
        {
            std::cout << "Unable to open file" << std::endl;
        }
    }
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

bool User::checkReservationWithinHours(std::tm *localTime, int court_num)
{
    // all of the courts
    std::vector<std::string> courtFiles = {"court1.txt", "court2.txt", "court3.txt"};

    for (const auto &courtFile : courtFiles)
    {
        std::ifstream file(courtFile);
        if (!file.is_open())
        {
            throw std::runtime_error("Failed to open " + courtFile);
        }

        std::string line;
        while (std::getline(file, line))
        {
            size_t startTimePos = line.find("Start Time: ");
            size_t courtPos = line.find("Court: ");
            if (startTimePos != std::string::npos && courtPos != std::string::npos)
            {
                startTimePos += 12; // Move past "Start Time: "
                std::string startTimeSubstring = line.substr(startTimePos, 19);

                std::tm startTime = {};

                // parse the string
                std::sscanf(startTimeSubstring.c_str(), "%d-%d-%d %d:%d:%d",
                            &startTime.tm_year, &startTime.tm_mon, &startTime.tm_mday,
                            &startTime.tm_hour, &startTime.tm_min, &startTime.tm_sec);

                startTime.tm_mon -= 1;
                startTime.tm_year -= 1900;

                std::string courtSubstring = line.substr(courtPos + 7);
                int reservationCourtNum = std::stoi(courtSubstring);

                // make sure the formats match
                auto formatTime = [](const std::tm *time)
                {
                    char buffer[20];
                    std::strftime(buffer, sizeof(buffer), "%Y-%-m-%-d %H:%M:%S", time);
                    return std::string(buffer);
                };

                std::string localTimeString = formatTime(localTime);
                std::string startTimeString = formatTime(&startTime);


                // Compare the resrvation in file to given info
                if (localTimeString == startTimeString && reservationCourtNum == court_num)
                {
                    file.close();
                    return true;
                }
            }
        }
        file.close();
    }
    return false;
}