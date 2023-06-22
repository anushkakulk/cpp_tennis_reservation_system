#ifndef COURT_HPP
#define COURT_HPP

#include <vector>
#include <chrono>
#include <memory>
#include "reservation.hpp"

class Court {
private:
    // this court num (either 1, 2, or 3)
    int court_num;
    // all reservations on this court
    std::vector<Reservation*> res;

public:
    Court(int num);
    // returns true if this court is reserved during the given datetime
    bool is_reserved(std::chrono::system_clock::time_point time);
    // adds a reservation to this court's reservations
    void add_reservation(Reservation* r);
    // removes the given reservation from this court's reservations
    void delete_reservation(Reservation* r);
    // returns this court's num
    int get_court_num();
    // returns all of this court's reservations
    std::vector<Reservation*> get_reservations();
};

#endif  // COURT_H
