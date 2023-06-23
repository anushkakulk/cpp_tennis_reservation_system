#include "court.hpp"
#include <algorithm>

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
    : court_num(std::move(other.court_num)),
    res(std::move(other.res)) {
    other.court_num = 0;
    other.res.clear();
}
// move assignment operator
Court& Court::operator=(Court&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    court_num = (std::move(other.court_num));
    res = std::move(other.res);

    other.court_num = 0;
    other.res.clear();

    return *this;
}
// destructor
Court::~Court() {
    for (auto* reservation : res) {
        delete reservation;
    }
}
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
}

// deletes the given from its list of reservations
void Court::delete_reservation(Reservation *r)
{
    auto it = std::find(res.begin(), res.end(), r);
    if (it != res.end())
    {
        res.erase(it);
    }
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