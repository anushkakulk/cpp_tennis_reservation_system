#include "reservation.hpp"
#include <algorithm>
#include <iostream>


Reservation::Reservation(int player_id, const std::chrono::system_clock::time_point& startDateTime, int day, std::shared_ptr<Court> c)
    : start_datetime(startDateTime), day_of_week(day), court(c) {
    // adds this players id to reservation
    player_ids.push_back(player_id);
    // adds this rseervation to the courts 
    court->add_reservation(std::shared_ptr<Reservation>(this));
    std::time_t startTime = std::chrono::system_clock::to_time_t(start_datetime);
    std::cout << "Reservation made by ID: " << player_id
              << " at " << std::ctime(&startTime) << "on day " << day << " (0 = sun, 1 = mon, ... 6 = sat)" << std::endl;
}

void Reservation::add_user(User& u) {
    //  max of 2 players in a reservation
    if (player_ids.size() < 2) {
        player_ids.push_back(u.getId());
    }
}

void Reservation::remove_user(User& u) {
    // Ensure there is at least 1 user remaining in the reservation
    if (player_ids.size() > 1) {
        auto it = std::find(player_ids.begin(), player_ids.end(), u.getId());
        if (it != player_ids.end()) {
            player_ids.erase(it);
        }
    }
}

std::vector<int> Reservation::get_players() {
    return player_ids;
}

void Reservation::delete_reservation() {
    court->delete_reservation(std::shared_ptr<Reservation>(this));
}

std::chrono::system_clock::time_point Reservation::get_start() {
    return start_datetime;
}

bool Reservation::is_openplay() {
    return open_play;
}

void Reservation::set_start(int id, std::chrono::system_clock::time_point time) {
    // find the reservation with the given id and time, and change it
}

bool Reservation::operator==(const Reservation& other) const {
    return id == other.id;
}