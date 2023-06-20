#ifndef OFFICER_HPP
#define OFFICER_HPP

#include "member.hpp"

class Officer : public Member {
public:
    Officer(int id, char skill);
    // reserved open play time for the given id for the given start/end datetimes
    void reserve_openplay(int id, std::chrono::system_clock::time_point start_time);
    // changes the time for the given id at the given start/end datetimes to 
    // a reservation at the new start and end times 
    void modify_reservation(int id, std::chrono::system_clock::time_point start_time, std::chrono::system_clock::time_point new_start);
};

#endif  // OFFICER_H
