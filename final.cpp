#include <vector>
#include <iostream>
using namespace std; 

int main () {

Court one = Court(1);
Court two = Court(2);
Court three = Court(3);
vector<Court*> all_courts = {one, two, three};

User i = Officer(008 "grant");
User j = Officer(009, "ian");
vector<User*> all_officers = {i,j};

User a = Member(001, "alice", 'A', all_courts, all_officers);
User b = Member(002, "bob", 'B', all_courts, all_officers);
User c = Member(003, "carol",'C', all_courts, all_officers);
User d = Member(003, "dana", 'A', all_courts, all_officers);
User e = Member(004, "edgar", 'B', all_courts, all_officers);
User f = Member(005, "frank", 'C', all_courts, all_officers);
User g = Coach(006 "grant", all_courts, all_officers);
User h = Coach(007, "hank", all_courts, all_officers);

vector<User*> all_users = {a,b,c,d,e,f,g,h,i,j};


cout << "Welcome to the court reservation system!" << endl;
cout << "Please enter your user id: (should be from 001 through 009)" << endl;
int login_id;
cin >> login_id;
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