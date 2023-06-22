#ifndef COURT_HPP
#define COURT_HPP

#include "reservation.hpp"
#include <vector>
#include <chrono>
#include <memory>
#include <memory>


class Reservation;

class Court {
private:
    // this court num (either 1, 2, or 3)
    int court_num;
    // all reservations on this court
   std::vector<std::shared_ptr<Reservation>> res;

public:
    Court(int num);
    // returns true if this court is reserved during the given datetime
    bool is_reserved(std::chrono::system_clock::time_point time);
    // adds a reservation to this court's reservations
    void add_reservation(std::shared_ptr<Reservation> r);
    // removes the given reservation from this court's reservations
    void delete_reservation(std::shared_ptr<Reservation> r);
    // returns this court's num
    int get_court_num();
    // returns all of this court's reservations
    std::vector<std::shared_ptr<Reservation>>  get_reservations();
};

#endif  // COURT_H