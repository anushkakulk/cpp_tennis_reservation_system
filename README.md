# CS3520-Summer-2023-FinalProject
Repository for CS3520 Final Project - Court Reservation System.
Authored by Anushka Kulkarni, Deion Smith, and Tania Gole.


# Instructions

1) using the makefile, compile
2) run the executable ./final
3) follow the instructions written in terminal for each input

    - _When reserving, the time you input will be noted as the **_start time_** of the reservation_. Reservations last 30 minutes. Open play hours are regarded as  a series of reservations with start times from 6 to 8:30 pm. 
    
    - HERE IS THE FORMAT FOR ENTERING RESERVATION TIMES (pressing the [enter] key between each number) :
        - month: int [from 1 to 12]
        - day: int [from 1 to 31]
        - year: int [2023]
        - hour: int [from 6 to 23]
        - minute: int [either 0 or 30]
        - EXAMPLE: June 30, 2023 at 1:30 pm should be inputted as 
          - 6 [enter key] 30 [enter key] 2023 [enter key] 13 [enter key] 30 [enter key]
        
## General Rules/Implementations
- initially, you must login. You can either create a new account by providing a new id, name, and membership type, or you can login to an existing account (we check for unique ids)
- you will be presented with a menu, which is a numbers list of options specific to your membership type. enter the number that corresponds to the option
you wish to do.
- to switch users, you must exit to terminal (either press the option [5] from member/coach menu, [6] from officer menu, or ctrl-c) and login as different user


## members
- a member can view the schedule, which will show _all_ reservations made for the next 7 days for each court, sorted by earliest to latest. 
- a member can reserve a court (only 1 reservation per week, can be reserved 7 days in advance, can reserve during open-play hours or coaching hours if reserved within 48 hours of the designated hours if there is availability). Checks are implemented to ensure a reservation is valid
- a member can  cancel their reservation if it was made within the same session. They can either cancel it themselves or send a request to a randomly chosen officer.
- a member can request a timechange, cancellation, or a reservation via an officer. An officer will be randomly chosen to handle their request.

## coaches
- a coach can view the schedule, which will _only_ show _all coaching session_ reservations made for the next 7 days for each court, sorted by earliest to latest. 
- a coach can reserve a court (no reservation limit, can be reserved 7 days in advance, can only reserve coaching hours (weekdays with start times from 9 am to 11:30). Checks are implemented to ensure a reservation is valid.
- a coach can cancel their reservation if it was made within the same session. They can either cancel it themselves or send a request to a randomly chosen officer.
- a coach can request a timechange, cancellation, or a reservation via an officer. An officer will be randomly chosen to handle their request.

## officers
- an officer is a member, and therefore is capable of doing everything a member can.
- an officer can also reserve open play sessions, which are a series of 30 minute reservations with start times from 6 to 8:30 pm. They can book these on any day, and can reserve 7 days in advance. To reserve an open play session, the officer only needs to input the month, day, and year. These open play sessions do not count towards an officer's limit of 1 personal reservation per week.
- an officer can handle any incoming requests. if an officer was chosen to handle a request then a request is added to their 


## LIST OF USERS THAT CAN BE USED TO LOGIN AND TEST FUNCTIONALITY: (names must be lower case)
- 1 alice member
- 2 bob member
- 3 carol member
- 4 dana member
- 5 edgar member
- 6 frank coach
- 7 grant coach
- 8 hank officer
- 9 ian officer
- 10 tania member
- 100 pete coach
- 12 anushka officer
- _Or, you could create a new user_
