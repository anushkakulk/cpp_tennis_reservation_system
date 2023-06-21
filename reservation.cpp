#include "reservation.hpp"

Reservation::Reservation(int player_id, const std::chrono::system_clock::time_point& startDateTime, Court* c)
    : start_datetime(startDateTime), court(c) {

    player_ids.push_back(player_id);
    c->add_reservation(this);
}

void Reservation::add_user(User& u) {
    //  max of 2 players in a reservation
    if (player_ids.size() < 2) {
        player_ids.push_back(u.get_id());
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
    court->delete_reservation(this);
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
