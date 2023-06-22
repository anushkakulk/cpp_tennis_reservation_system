#include <vector>
#include <iostream>
#include <memory>
#include "user.hpp"
#include "member.hpp"
#include "coach.hpp"
#include "reservation.hpp"
#include "court.hpp"

using namespace std; 
int main() {
std::shared_ptr<Court> one = std::shared_ptr<Court>(new Court(1));
std::shared_ptr<Court> two = std::shared_ptr<Court>(new Court(2));
std::shared_ptr<Court> three = std::shared_ptr<Court>(new Court(3));
std::vector<std::shared_ptr<Court>> all_courts = {one, two, three};

std::shared_ptr<Officer> i = std::shared_ptr<Officer>(new Officer(8, "grant", 'A', all_courts, std::vector<std::shared_ptr<Officer>>()));
std::shared_ptr<Officer> j = std::shared_ptr<Officer>(new Officer(9, "ian", 'A', all_courts, std::vector<std::shared_ptr<Officer>>{i}));
std::vector<std::shared_ptr<Officer>> all_officers = {i, j};

std::shared_ptr<Member> a = std::shared_ptr<Member>(new Member(1, "alice", 'A', all_courts, all_officers));
std::shared_ptr<Member> b = std::shared_ptr<Member>(new Member(2, "bob", 'B', all_courts, all_officers));
std::shared_ptr<Member> c = std::shared_ptr<Member>(new Member(3, "carol", 'C', all_courts, all_officers));
std::shared_ptr<Member> d = std::shared_ptr<Member>(new Member(3, "dana", 'A', all_courts, all_officers));
std::shared_ptr<Member> e = std::shared_ptr<Member>(new Member(4, "edgar", 'B', all_courts, all_officers));
std::shared_ptr<Member> f = std::shared_ptr<Member>(new Member(5, "frank", 'C', all_courts, all_officers));

std::shared_ptr<Coach> g = std::shared_ptr<Coach>(new Coach(6, "grant", all_courts, all_officers));
std::shared_ptr<Coach> h = std::shared_ptr<Coach>(new Coach(7, "hank", all_courts, all_officers));

std::vector<std::shared_ptr<User>> all_users = {a, b, c, d, e, f, g, h, i, j};

cout << "Welcome to the court reservation system!" << endl;
cout << "Please enter your user id: (should be from 1 through 9)" << endl;
int login_id;
cin >> login_id;
for (const std::shared_ptr<User>& user : all_users) {
    if (user->getId() == login_id) {
        user->view_menu();
        break;  
    }
}


// iterate through users and see who's id matches the login, then call their respective
// view_menu() method!!


// TIME REPRESENTATION (THIS IS HOW WE REPRESENT DATES, TIMES, AND DAYS OF THE WEEK): 
// cout << "Enter the start time you want in the valid format (month, day, year, hour, minute)" << endl;
//         int month, day, year, hour, minute;
//         cin >> month >> day >> year >> hour >> minute;
//         std::tm time{};
//         time.tm_year = year - 1900; //  years since 1900
//         time.tm_mon = month - 1;    //  months since january
//         time.tm_mday = day;
//         time.tm_hour = hour;
//         time.tm_min = minute;
//         std::time_t timeT = std::mktime(&time);
//         std::chrono::system_clock::time_point startTime = std::chrono::system_clock::from_time_t(timeT);
//         //std::time_t startTimeT = std::chrono::system_clock::to_time_t(startTime);
//         // std::tm* localTime = std::localtime(&startTimeT);

//         // Extract the day of the week from the std::tm object
//         // int dayOfWeek = localTime->tm_wday;


//  -   lowkey not everything needs to work but i feel like we should get the basic
//      user makes/cancels a reservation and can view the schedule done asap!!  

// TODO - IF SOMEONE COULD ASK THE TAS ABT ANY OF THESE THATD BE GREAT LOL

//  - implement some sort of login in here (where user inputs any num 001 through 009)
//       then, we can call somthing like a->User::viewMenu() and it should show their
//       appropriate menu (ANUSHKA WILL DO THIS :) )

//  -  how exactly do we store each user's reservations in the txt file? its more like
//      we want to store the created user object somewhere to preserve data !!!!!!!
//      WHAT IS THE BEST WAY TO DO THIS??

//  -  figure out the modifying logic for users to officers? how can we refer to 
//       created officer objects, since they are the ones to make a time change?
//       should a user have a list of officers that they can refer too?

//  -   possibly change all raw pointers to smart pointers. idrk how smart pointers
//       work exactly but lowkey we coudl get memory leaks with raw? 

//  -   implement all the checks for valid reservations and stuff   


// LOGIC QUESTIONS

//  -    the sending requests to officers/logic
//  -    is using chrono::time::time_pt (EXAMPLE GIVEN IN RESRERVATION.HPP &
//       MEMBER.CPP) the best way to represent date and time?
}