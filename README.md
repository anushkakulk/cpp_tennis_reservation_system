# CS3520-Summer-2023-FinalProject
Repository for CS3520 Final Project - Court Reservation System
Authored by Anushka Kulkarni, Deion Smith, and Tania Gole


# Instructions

1) using the makefile, compile
2) run the executable ./final
3) follow the instructions written in terminal for each input

    - When reserving, the time you input will be noted as the start time of the reservation. Reservations last 30 minutes. Open play hours are regarded as  a series of reservations with start times from 6 to 8:30 pm. 
    
    - HERE IS THE FORMAT FOR ENTERING RESERVATION TIMES (pressing the [enter] key between each number) :
        - month: int [from 1 to 12]
        -  day: int [from 1 to 31]
        - year: int [2023]
        - hour: int [from 6 to 23]
        - minute: int [either 0 or 30]
        - EXAMPLE: June 30, 2023 at 1:30 pm should be inputted as 
          - 6 [enter key] 30 [enter key] 2023 [enter key] 13 [enter key] 0 [enter key]
        
## General Rules/Implementations
- initially, you must login. You can either create a new account by providing a new id, name, and membership type, or you can login to an existing account (we check for unique ids)
- you will be presented with a menu, which is a numbers list of options specific to your membership type. enter the number that corresponds to the option
you wish to do.
- to switch users, you must exit to terminal (either press [6] from user menu or ctrl-c) and login as different user


## members
- a member can reserve a court (only 1 reservation per week, can be reserved 7 days in advance, can reserve during open-play hours or coaching hours if reserved within 48 hours of the designated hours if there is availability). Checks are implemented to ensure a reservation is valid
- a member can cancel their reservation if made within the same session. They can either cancel it themselves or send a request to a randomly chosen officer.
- a member can request a timechange, cancellation, or a reservation via an officer. An officer will be randomly chosen to handle their request.

## coaches
- a coach can reserve a court (no reservation limit, can be reserved 7 days in advance, can only reserve coaching hours (weekdays with start times from 9 am to 11:30). Checks are implemented to ensure a reservation is valid.
- a coach can cancel their reservation if made within the same session. They can either cancel it themselves or send a request to a randomly chosen officer.
- a coach can request a timechange, cancellation, or a reservation via an officer. An officer will be randomly chosen to handle their request.

## officers
- an officer is a member, and is capable of doing everything a member can.
- an officer can also reserve open play sessions, which are a series of 30 minute reservations with start times from 6 to 8:30 pm. They can book these on any day, and can reserve 7 days in advance. 
