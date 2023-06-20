#include "user.hpp"
#include <iostream>

User::User(int id, const std::string& type) : id(id), membership_type(type) {}

// returns this user's id
int User::getId() {
    return id;
}

