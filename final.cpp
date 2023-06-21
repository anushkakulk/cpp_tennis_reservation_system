#include <vector>
#include <iostream>
using namespace std; 

int main () {

// User a = Member(001, "alice");
// User b = Member(002, "bob");
// User c = Member(003, "carol");
// User d = Member(003, "dana");
// User e = Member(004, "edgar");
// User f = Member(005, "frank");
// User g = Coach(006 "grant");
// User h = Coach(007, "hank");
// User i = Officer(008 "grant");
// User j = Officer(009, "ian");
// vector<User*> all_users = {a,b,c,d,e,f,g,h,i,j};


cout << "Welcome to the court reservation system!" << endl;
cout << "Please enter your user id: (should be from 001 through 009)" << endl;
int login_id;
cin >> login_id;
// iterate through users and see who's id matches the login, then call their respective
// view_menu() method!!



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