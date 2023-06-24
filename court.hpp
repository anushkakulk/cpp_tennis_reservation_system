#ifndef COURT_HPP
#define COURT_HPP

#include "reservation.hpp"
#include <vector>
#include <chrono>
#include <memory>

class Reservation;

class Court {
private:
    // this court num (either 1, 2, or 3)
    int court_num;
    // all reservations on this court
    std::vector<Reservation*> res;

public:
    Court(int num);
    // RULE OF 5
    Court(const Court& other); // copy 
    Court& operator=(const Court& other); // copy assignment op
    Court(Court&& other) noexcept; // move
    Court& operator=(Court&& other) noexcept; // move assignment op
    ~Court(); // destruct
    // returns true if this court is reserved during the given datetime
    bool is_reserved(std::chrono::system_clock::time_point time);
    // adds a reservation to this court's reservations
    void add_reservation(Reservation* r);
    // removes the given reservation from this court's reservations
    void delete_reservation(Reservation* r);
    // returns this court's num
    int get_court_num();
    // returns all of this court's  reservations
    std::vector<Reservation*> get_reservations();
    // saves reservation to file
    void saveReservationToFile(Reservation* r);
    // remove reservation from file
    void removeReservationFromFile(Reservation* r);
};

#endif  // COURT_H