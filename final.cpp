#include <vector>
#include <iostream>
#include "user.hpp"
#include "member.hpp"
#include "coach.hpp"
#include "reservation.hpp"
#include "court.hpp"

using namespace std;

char randomSkill()
{
    char skillLevels[] = {'A', 'B', 'C'};
    int numLevels = sizeof(skillLevels) / sizeof(skillLevels[0]);
    int randomIndex = rand() % numLevels;
    return skillLevels[randomIndex];
}

int main()
{
    // initalize all practice data
    Court one = Court(1);
    Court two = Court(2);
    Court three = Court(3);
    vector<Court *> all_courts = {&one, &two, &three};
    
    
    std::vector<Officer *> all_officers;
    std::vector<User *> all_users;
    Officer def1 = Officer(13, "kim", 'A', all_courts, vector<Officer *>());
    Officer def2 = Officer(14, "kendall", 'A', all_courts, vector<Officer *>());
    all_officers.emplace_back(&def1);
    all_officers.emplace_back(&def2);
    /*
    Officer i = Officer(8, "grant", 'A', all_courts, vector<Officer*>());
    Officer j = Officer(9, "ian", 'A', all_courts, vector<Officer*>{&i});
    vector<Officer *> all_officers = {&i, &j};


    Member a = Member(1, "alice", 'A', all_courts, all_officers);
    Member b = Member(2, "bob", 'B', all_courts, all_officers);
    Member c = Member(3, "carol", 'C', all_courts, all_officers);
    Member d = Member(3, "dana", 'A', all_courts, all_officers);
    Member e = Member(4, "edgar", 'B', all_courts, all_officers);
    Member f = Member(5, "frank", 'C', all_courts, all_officers);
    Coach g = Coach(6, "grant", all_courts, all_officers);
    Coach h = Coach(7, "hank", all_courts, all_officers);

    vector<User*> all_users = {&a, &b, &c, &d, &e, &f, &g, &h, &i, &j};
    vector<User*> all_players = {&a, &b, &c, &d, &e, &f, &g, &h};
    i.all_users = all_players;
    j.all_users = all_players;
    */

    // I THINK THERE SHOULD BE A CHECK TO MAKESURE YOU ARE A NEW USER VS A
    // RETURNING USER????
    cout << "Welcome to the court reservation system!" << endl;
    cout << "Hours of Operation: 6:00 to 00:00 Daily" << endl;
    cout << "Please enter your details to interact with the system" << endl;
    User newUser = registerUser();

    string membershipType = newUser.get_membership();

    if (membershipType == "member")
    {
        char skill = randomSkill();
        Member member(newUser.getId(), newUser.get_name(), skill, all_courts, all_officers);
        member.view_menu();
        all_users.push_back(&member);
    }
    else if (membershipType == "coach")
    {
        Coach coach(newUser.getId(), newUser.get_name(), all_courts, all_officers);
        coach.view_menu();
        all_users.push_back(&coach);
    }
    else if (membershipType == "officer")
    {
        Officer officer(newUser.getId(), newUser.get_name(), 'A', all_courts, all_officers);
        officer.view_menu();
        all_users.push_back(&officer);
    }
    else
    {
        cout << "Invalid. Returning you to terminal" << endl;
        return -1;
    }

    // delete newUserPtr;

    /* cout << "Please enter your user id: (should be from 1 through 9)" << endl;
    int login_id;
    cin >> login_id;
    for (User *user : all_users)
    {
        if (user->getId() == login_id)
        {
            user->view_menu();
            break;
        }
    }*/

    // iterate through users and see who's id matches the login, then call their respective
    // view_menu() method!!
}
