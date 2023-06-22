#include "court.hpp"
#include <algorithm>
Court::Court(int num) : court_num(num) {}

// checks if time is between 30 minutes from the reservations start time
bool Court::is_reserved(std::chrono::system_clock::time_point time) {
    for (const auto& reservation : res) {
        std::chrono::system_clock::time_point start = reservation->get_start();
        std::chrono::system_clock::time_point end = start + std::chrono::minutes(30);

        if (time >= start && time < end) {
            return true;
        }
    }
    return false;
}

// adds reservation to its list of reservatiosn
void Court::add_reservation(std::shared_ptr<Reservation> r) {
    res.push_back(r);
}

// deletes the given reservation from its list of reservations
void Court::delete_reservation(std::shared_ptr<Reservation> r) {
    auto it = std::find(res.begin(), res.end(), r);
    if (it != res.end()) {
        res.erase(it);
    }
}

// returns its court number
int Court::get_court_num() {
    return court_num;
}

// returns list of reservations
std::vector<std::shared_ptr<Reservation>> Court::get_reservations() {
    return res;
}