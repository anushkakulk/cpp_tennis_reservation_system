# C++ Project
Repository for A C++ Court Reservation System.
Authored by Anushka Kulkarni, Deion Smith, and Tania Gole.

- LINK TO DESIGN DOCUMENT: https://docs.google.com/document/d/1u0eHVkeY4SWDgvGEsEyG8rWjzQZj6YxOhFQ3dTH9hXE/edit

- LINK TO VIDEO DEMO: 
https://drive.google.com/file/d/1-KS_2rWAYS4J9cmqZUP24jmeFeIZze5J/view?usp=sharing


# Instructions

1) using the makefile, compile
2) run the executable ./final
3) follow the instructions written in terminal for each input

    - _When reserving, the time you input will be noted as the **_start time_** of the reservation_. Reservations last 30 minutes. Open play hours are regarded as a series of reservations with start times from 6 to 8:30 pm. 
    
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
- to switch users, you must exit to terminal (either press the option to return to terminal from menu, or ctrl-c) and login as different user
- a line on the schedule will look like this: 
  Player ID: 39, Membership Type: member, Player Name: kris, Open Play: No, Start Time: 2023-06-29 14:30:00, Day: 4, Court: 1
    - each line shows the reserver's id, membership type, name, whether or not the reservation was an open play session, the start date and time, the day of the week, and the court number
    - the day of the week is written as a number from 0 to 6 [0 = sun, 1 = mon, 2 = tue, 3 = wed, 4 = thur, 5 = fri, 6 = sat]

## members
- a member can view the schedule, which will show _all_ reservations made for the next 7 days for each court, sorted by earliest to latest. 
- a member can reserve a court (only 2 reservations per week, only 1 reservation per day, can be reserved 7 days in advance, can reserve during open-play hours or coaching hours if reserved within 48 hours of the designated hours if there is availability). Checks are implemented to ensure a reservation is valid
- a member can  cancel their reservation _if it was made within the same session_. They can either cancel it themselves or send a request to a randomly chosen officer.
- a member can _join_ an existing reservation as well. They will be presented with all reservations and will be noted as a player on the selected reservation. This joined member _can not_ cancel that reservation.
- a member can request a timechange, cancellation, or a reservation via an officer. An officer will be randomly chosen to handle their request.

## coaches
- a coach can view the schedule, which will _only_ show _all coaching session_ reservations made for the next 7 days for each court, sorted by earliest to latest. 
- a coach can reserve a court (no reservation limit, can be reserved 7 days in advance, can only reserve coaching hours (weekdays with start times from 9 am to 11:30). Checks are implemented to ensure a reservation is valid.
- a coach can cancel their reservation _if it was made within the same session_. They can either cancel it themselves or send a request to a randomly chosen officer.
- a coach can request a timechange, cancellation, or a reservation via an officer. An officer will be randomly chosen to handle their request.

## officers
- an officer is a member, and therefore is capable of doing everything a member can.
- an officer can also reserve open play sessions, which are a series of 30 minute reservations with start times from 6 to 8:30 pm. They can book these on any day, and can reserve 7 days in advance. To reserve an open play session, the officer only needs to input the month, day, and year. These open play sessions do not count towards an officer's limit of 2 personal reservations per week.
- an officer can handle any incoming requests. if an officer was chosen to handle a request then a request is added to their vector of requests. 


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
- TO LOGIN IN, ENTER THE ID AND FIRST NAME (ex: to login to anushka the officer, follow the written instructions and input '12' for id and 'anushka' for name)

### Video Demo ###

https://drive.google.com/file/d/1-KS_2rWAYS4J9cmqZUP24jmeFeIZze5J/view?usp=sharing

^^This video demo showcases the registering of a coach ‘travis’ and the logging into officer ‘kris’ and members ‘kim’ and ‘kendall’. 

Here is what occurs in the demo: 

	- Travis makes reservations, views the coach schedule, cancels a reservation himself, requests cancellation via an officer. 
	
	- Kim makes reservations, views the schedule

	- Kris reserves open-play sessions, reserves a personal session, handles any incoming requests, and views the schedule

	- Kendall makes reservations, joins one of Kim’s reservations, and views the schedule
