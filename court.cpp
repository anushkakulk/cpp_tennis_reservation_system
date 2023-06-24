#include "court.hpp"
#include "reservation.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

Court::Court(int num) : court_num(num) {}

// copy constrcutor
Court::Court(const Court& other) : court_num(other.court_num) {
    for (const auto* reservation : other.res) {
        res.push_back(new Reservation(*reservation));
    }
}
// copy assignemnt operator
Court& Court::operator=(const Court& other) {
    if (this == &other) {
        return *this;
    }
    court_num = other.court_num;

    // Clean up existing reservations
    for (auto* reservation : res) {
        delete reservation;
    }
    res.clear();

    // Deep copy the reservations
    for (const auto* reservation : other.res) {
        res.push_back(new Reservation(*reservation));
    }

    return *this;
}

// move constructor
Court::Court(Court&& other) noexcept
    : court_num(std::move(other.court_num)), res(std::move(other.res)) {
    other.court_num = 0;
    other.res.clear();
}
// move assignment operator
Court& Court::operator=(Court&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    court_num = std::move(other.court_num);
    other.court_num = 0;
    res = std::move(other.res);

    other.court_num = 0;
    other.res.clear();

    return *this;
}
// destructor
Court::~Court() = default;
// checks if time is between 30 minutes from the reservations start time
bool Court::is_reserved(std::chrono::system_clock::time_point time)
{
    for (const auto &reservation : res)
    {
        std::chrono::system_clock::time_point start = reservation->get_start();
        std::chrono::system_clock::time_point end = start + std::chrono::minutes(30);

        if (time >= start && time < end)
        {
            return true;
        }
    }
    return false;
}

// adds reservation to its list of reservatiosn
void Court::add_reservation(Reservation *r)
{
    res.push_back(r);
    saveReservationToFile(r);
}

// deletes the given from its list of reservations
void Court::delete_reservation(Reservation *r)
{
    auto it = std::find(res.begin(), res.end(), r);
    if (it != res.end())
    {
        res.erase(it);
    }
    removeReservationFromFile(r); 
}

// returns its court number
int Court::get_court_num()
{
    return court_num;
}

// returns list of reservations
std::vector<Reservation *> Court::get_reservations()
{
    return res;
}

void Court::saveReservationToFile(Reservation* r) {
    std::string filename = "court" + std::to_string(court_num) + ".txt";
    std::ofstream file(filename, std::ios_base::app);

    if (file.is_open()) {
        file << r->toString() << "\n";
        file.close();
    }
    else {
        std::cout << "Unable to open file" << std::endl;
    }
}

void Court::removeReservationFromFile(Reservation* r) {
    std::string filename = "court" + std::to_string(court_num) + ".txt";
    std::ifstream fileIn(filename);
    std::ofstream fileOut("temp.txt");

    if (fileIn.is_open() && fileOut.is_open()) {
        std::string line;
        while (getline(fileIn, line)) {
            if (line != r->toString()) {
                fileOut << line << "\n";
            }
        }
        fileIn.close();
        fileOut.close();

        std::remove(filename.c_str());
        std::rename("temp.txt", filename.c_str());
    }
    else {
        std::cout << "Unable to open file" << std::endl;
    }
}
