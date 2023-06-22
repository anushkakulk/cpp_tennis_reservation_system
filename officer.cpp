#include "officer.hpp"

Officer::Officer(int id, const std::string& name, char skill, std::vector<Court*> courts, std::vector<Officer*> officers) : Member(id, name, skill, courts, officers) {}

void Officer::reserve_openplay(int id, std::chrono::system_clock::time_point start_time) {
   // the given id is for the player that they would be reserving for
}

void Officer::modify_reservation(int id, std::chrono::system_clock::time_point start_time, std::chrono::system_clock::time_point new_start) {
  // should change the time of a reservation? 
}