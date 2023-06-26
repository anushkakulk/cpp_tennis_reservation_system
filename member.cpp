#include "member.hpp"
#include "officer.hpp"
#include <chrono>
#include <ctime>
#include <fstream> // For std::ifstream
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream> // For std::istringstream
#include <string>  // For std::string and std::getline
#include <vector>  // For std::vector
using namespace std;

Member::Member(int id, const std::string &name, char skill,
               std::vector<Court *> courts, std::vector<Officer *> officers)
    : User(id, name, "member", courts), skill_level(skill),
      all_officers(officers) {}

// copy constructor
Member::Member(const Member &other)
    : User(other), skill_level(other.skill_level) {}
// copy assignment operator
Member &Member::operator=(const Member &other)
{
  if (this == &other)
  {
    return *this;
  }
  User::operator=(other);
  all_officers = other.all_officers;

  all_officers.clear();

  // copy
  for (const auto *o : other.all_officers)
  {
    all_officers.push_back(new Officer(*o));
  }
  skill_level = other.skill_level;
  return *this;
}
// move constructor
Member::Member(Member &&other) noexcept
    : User(std::move(other)), skill_level(std::move(other.skill_level)),
      all_officers(std::move(other.all_officers))
{
  other.skill_level = 'F';
  other.all_officers.clear();
}
// move assignment operator
Member &Member::operator=(Member &&other) noexcept
{
  if (this == &other)
  {
    return *this;
  }
  User::operator=(std::move(other));
  skill_level = (std::move(other.skill_level));

  all_officers = std::move(other.all_officers);

  other.skill_level = 'F';

  other.all_officers.clear();

  return *this;
}

Member::~Member() = default;

char Member::get_skill() { return skill_level; }

// member specific menu options
void Member::view_menu()
{
  std::cout << std::endl;
  cout << "Menu Style Options: Choose a feature (1-4) associated with your "
          "choice"
       << endl;
  std::cout << std::endl;
  cout << "Member Menu: " << endl;
  cout << "1. View Schedule" << endl;
  cout << "2. Reserve a Court" << endl;
  cout << "3. Cancel a Reservation" << endl;
  cout << "4. Join a Reservation" << endl;
  cout << "5. Send a Request to an Officer" << endl;
  cout << "6. Quit to Terminal" << endl;
  int choice;
  cin >> choice;

  // schedule view
  if (choice == 1)
  {
    view_schedule();
  }
  else if (choice == 2)
  {
    reserve();
  }
  else if (choice == 3)
  {
    cancel_reservation();
  }
  else if (choice == 4)
  {
    joinReservation(get_courts()); 
  }
  else if (choice == 5)
  {
    request();
  }
  else if (choice = 6)
  {
    return; 
  } else {
    std::cout << "Invalid choice try again" << std::endl;
    view_menu(); 
  }
}

void Member::view_schedule()
{
  std::cout << "Court Schedule For Next 7 Days - Member Version" << std::endl;
  std::cout << std::endl;
  // Iterate through each court
  for (auto &court : this->get_courts())
  {
    // Get the filename of court's reservation file
    std::string filename =
        "court" + std::to_string(court->get_court_num()) + ".txt";

    // Open the file
    std::ifstream file(filename);

    if (file.is_open())
    {

      std::string line;
      std::cout << "Court " + std::to_string(court->get_court_num()) << " Reservations" << std::endl;
      std::cout << "--------------------" << std::endl;

      if (file.peek() == std::ifstream::traits_type::eof())
      {
        std::cout << "No reservations found for this court." << std::endl;
        std::cout << std::endl;
      }
      else
      {
        // Read each line (reservation) in the file
        while (getline(file, line))
        {
          // Parse the reservation details from the line
          std::istringstream ss(line);
          std::cout << line << std::endl;
          std::cout << std::endl;
        }
      }
        file.close();
      }
      else
      {
        std::cout << "Unable to open file" << std::endl;
      }
    }
    std::cout << std::endl;
    this->view_menu();
  }

  void Member::reserve()
  {
    cout << "Making a Reservation:" << endl;
    std::cout << "Enter which court you want to reserve: (1, 2, or 3): ";
    int court_num;
    std::cin >> court_num;
    if (court_num != 1 && court_num != 2 && court_num != 3)
    {
      cout << "Invalid choice. Please try again." << endl;
      std::cout << std::endl;
      this->view_menu();
    }
    else
    {
      std::cout << "Enter the start time you want in the valid format (month "
                   "[from 1-12], day, year [2023], hour [from 6 to 23], minute "
                   "[either 0 or 30])"
                << std::endl;
      int month, day, year, hour, minute;
      std::cin >> month >> day >> year >> hour >> minute;
      if (month < 1 || month > 12 || day < 1 || day > 31 || year != 2023 || hour < 6 || hour > 23 || (minute != 0 && minute != 30))
      {
        std::cout << "Invalid input format. Please try again." << std::endl;
        std::cout << std::endl;
        this->view_menu();
      }
      Court *desiredCourt = nullptr;

      for (const auto &c : User::get_courts())
      {
        if (court_num == c->get_court_num())
        {
          desiredCourt = c;
          break;
        }
      }

      if (desiredCourt != nullptr)
      {
        std::tm time{};
        time.tm_year = year - 1900; // years since 1900
        time.tm_mon = month - 1;    // months since January
        time.tm_mday = day;
        time.tm_hour = hour - 1;
        time.tm_min = minute; //;p[\]-
        std::time_t timeT = std::mktime(&time);
        std::chrono::system_clock::time_point startTime =
            std::chrono::system_clock::from_time_t(timeT);
        // max 7 days in advance
        auto maxReservationTime =
            std::chrono::system_clock::now() + std::chrono::hours(7 * 24);
        // makes a time
        std::time_t startTimeT = std::chrono::system_clock::to_time_t(startTime);
        // gets the local time
        std::tm *localTime = std::localtime(&startTimeT);

        // extract the day of the week from the std::tm object
        int dayOfWeek = localTime->tm_wday;
        // makes sure its in the future
        if (startTime <= std::chrono::system_clock::now())
        {
          std::cout << "Invalid reservation time, can only reserve in the future"
                    << std::endl;
          std::cout << std::endl;
          this->view_menu();
          
        }

        // enforce the 7 day rule
        else if (startTime > maxReservationTime)
        {
          std::cout << "Reservations can only be made up to 7 days in advance."
                    << std::endl;
          std::cout << std::endl;
          this->view_menu();
          
        }
        // enforce the 2 reservation per 7 days
        else if (this->checkReservationWithinWeek(this->getId(), localTime))
        {
          std::cout << "You already have 2 reservations within the next week." << std::endl;
          std::cout << "Therefore you cannot reserve." << std::endl;
          std::cout << std::endl;
          this->view_menu();
          
          // enforce the 1 reservation per day
        } else if (this->checkReservationWithinDay(this->getId(), localTime))
        {
          std::cout << "You already have 1 reservation within 24 hours of the requested time." << std::endl;
          std::cout << "Therefore you cannot reserve." << std::endl;
          std::cout << std::endl;
          this->view_menu();
        }
        // prevent reserving during coaching hours 48+ hours in advance
        else if (startTime >
                     std::chrono::system_clock::now() + std::chrono::hours(48) &&
                 (localTime->tm_wday >= 1 && localTime->tm_wday <= 5 &&
                  ((localTime->tm_hour >= 9 && localTime->tm_hour < 11) ||
                   (localTime->tm_hour == 11 && localTime->tm_min <= 30) ||
                   (localTime->tm_hour >= 15 && localTime->tm_hour < 17) ||
                   (localTime->tm_hour == 17 && localTime->tm_min <= 30))))
        {
          std::cout
              << "You are trying to reserve a spot that is for coaching hours."
              << std::endl;
          std::cout
              << "Try again 48 hours before the reservation for availability."
              << std::endl;
          std::cout << std::endl;
          this->view_menu();
         
        } // prevent reserving during open play hours 48+ hours in advance
        else if ((startTime > std::chrono::system_clock::now() +
                                  std::chrono::hours(48)) &&
                 ((localTime->tm_hour >= 18 && localTime->tm_hour < 20) ||
                  (localTime->tm_hour == 20 && localTime->tm_min <= 30)))
        {
          std::cout
              << "You are trying to reserve a spot that is for open play hours."
              << std::endl;
          std::cout
              << "Try again 48 hours before the reservation for availability."
              << std::endl;
          std::cout << std::endl;
          this->view_menu();
         
        }
        // enforce the one reservation at a time rule
        else if (this->checkReservationWithinHours(localTime, desiredCourt->get_court_num()))
        {
          std::cout << "A reservation is already booked during the requested time" << std::endl;
          std::cout << "Check the schedule again and book during a time with no reservations" << std::endl;
          std::cout << std::endl;
          this->view_menu();
          
        }
        else
        {

          // TODO, check that no one is on the court then
          my_reservations.push_back(new Reservation(this->getId(), startTime, dayOfWeek, desiredCourt, this->get_membership(), false, this->get_name()));
          cout << endl;
          this->view_menu();
        }
      }
      else
      {
        std::cout << "Error, no court of the given number exists" << std::endl;
        std::cout << std::endl;
        this->view_menu();
      }
    }
  }

  void Member::cancel_reservation()
  {
    cout << "Cancelling a Reservation:" << endl;
    cout << endl;

    if (my_reservations.size() == 0) {
             std::cout << std::endl;
            std::cout << "You have no cancellable reservations" << std::endl;
            std::cout << std::endl;
            this->view_menu();
            
    } else { 
    cout << "Here are your reservations:" << endl;

    for (size_t i = 0; i < my_reservations.size(); ++i)
    {
      cout << "[" << (i + 1) << "] "
           << "Reservation Details:" << endl;
      cout << "Player ID(s): ";
      for (size_t j = 0; j < my_reservations[i]->get_players().size(); ++j)
      {
        cout << my_reservations[i]->get_players()[j];
        if (j < my_reservations[i]->get_players().size() - 1)
        {
          cout << ", ";
        }
      }

      cout << endl;
      std::time_t startTime =
          std::chrono::system_clock::to_time_t(my_reservations[i]->get_start());
      std::tm *timeInfo = std::localtime(&startTime);

      cout << "Start Time: " << std::ctime(&startTime) << "on day "
           << timeInfo->tm_wday << " (0 = Sun, 1 = Mon, ..., 6 = Sat)" << endl;
      cout << endl;
    }

    cout << "Enter the number of the reservation you want to cancel (or 0 to "
            "cancel): ";
    unsigned int input;
    cin >> input;
    // make sure its valid
    if (input >= 1 && input <= my_reservations.size())
    {
      // get the res
      Reservation *selectedReservation = my_reservations[input - 1];
      // get the court this res is on
      Court *reservationCourt = selectedReservation->court;
      // erase it from the court's vector
      reservationCourt->delete_reservation(selectedReservation);

      // erase the reservation from the coach's vector of reservations
      my_reservations.erase(my_reservations.begin() + (input - 1));
      delete selectedReservation;
      cout << "Reservation cancelled." << endl;
      std::cout << std::endl;
      this->view_menu();
    }
    else if (input == 0)
    {
      cout << "Reservation cancellation was cancelled." << endl;
      cout << endl;
      this->view_menu();
    }
    else
    {
      cout << "Invalid input. Reservation cancellation was aborted." << endl;
      cout << endl;
      this->view_menu();
    }
  }
  }

  void Member::request()
  {

    cout << "Sending Officer requests" << endl;
    cout << endl;
    cout << "Enter the number associated with your option choice (1-3)" << endl;
    cout << "What kind of modification would you like to do today? " << endl;
    cout << "1. Change an existing reservation's time" << endl;
    cout << "2. Cancel an existing reservation's via an officer" << endl;
    cout << "3. Make a reservation via an officer" << endl;
    unsigned int mod;
    cin >> mod;
    if (mod == 1)
    {
      cout << "What reservation would you like to modify? Enter the "
              "corresponding number"
           << endl;

      for (size_t i = 0; i < my_reservations.size(); ++i)
      {
        cout << "[" << (i + 1) << "] "
             << "Reservation Details:" << endl;
        cout << "Player ID(s): ";
        for (size_t j = 0; j < my_reservations[i]->get_players().size(); ++j)
        {
          cout << my_reservations[i]->get_players()[j];
          if (j < my_reservations[i]->get_players().size() - 1)
          {
            cout << ", ";
          }
        }

        cout << endl;
        std::time_t startTime =
            std::chrono::system_clock::to_time_t(my_reservations[i]->get_start());
        std::tm *timeInfo = std::localtime(&startTime);

        cout << "Start Time: " << std::ctime(&startTime) << "on day "
             << timeInfo->tm_wday << " (0 = Sun, 1 = Mon, ..., 6 = Sat)" << endl;
        cout << endl;
      }

      cout << "Enter the number of the reservation you want to modify: ";
      unsigned int input;
      cin >> input;
      if (input == 0 || input < my_reservations.size())
      {
        std::cout << "invalid input" << std::endl;
        this->view_menu();
      }
      std::time_t old_time = std::chrono::system_clock::to_time_t(
          my_reservations[input]->get_start());

      int c_num = my_reservations[input]->court->get_court_num();
      std::chrono::system_clock::time_point old_start =
          std::chrono::system_clock::from_time_t(old_time);
      std::cout << "Enter the start time you want in the valid format (month "
                   "[from 1-12], day, year [2023], hour [from 6 to 23], minute "
                   "[either 0 or 30])"
                << std::endl;
      int month, day, year, hour, minute;
      std::cin >> month >> day >> year >> hour >> minute;
      if (month < 1 || month > 12 || day < 1 || day > 31 || year != 2023 || hour < 6 || hour > 23 || (minute != 0 && minute != 30))
      {
        std::cout << "Invalid input format. Please try again." << std::endl;
        std::cout << std::endl;
        this->view_menu();
      }

      std::tm time{};
      time.tm_year = year - 1900; // years since 1900
      time.tm_mon = month - 1;    // months since January
      time.tm_mday = day;
      time.tm_hour = hour - 1;
      time.tm_min = minute;
      std::time_t timeT = std::mktime(&time);
      std::chrono::system_clock::time_point new_start =
          std::chrono::system_clock::from_time_t(timeT);
      std::time_t new_start_time_t = std::chrono::system_clock::to_time_t(new_start);
      std::tm *new_start_local_time = std::localtime(&new_start_time_t);

      // max 7 days in advance
      auto maxReservationTime =
          std::chrono::system_clock::now() + std::chrono::hours(7 * 24);

      // makes sure its in the future
      if (new_start <= std::chrono::system_clock::now())
      {
        std::cout << "Invalid reservation time, can only reserve in the future"
                  << std::endl;
        std::cout << std::endl;
        this->view_menu();
      }

      // enforce the 7 day rule
      else if (new_start > maxReservationTime)
      {
        std::cout << "Reservations can only be made up to 7 days in advance."
                  << std::endl;
        std::cout << std::endl;
        this->view_menu();
      }
      // prevent reserving during coaching hours 48+ hours in advance
      else if (new_start >
                   std::chrono::system_clock::now() + std::chrono::hours(48) &&
               (new_start_local_time->tm_wday >= 1 && new_start_local_time->tm_wday <= 5 &&
                ((new_start_local_time->tm_hour >= 9 && new_start_local_time->tm_hour < 11) ||
                 (new_start_local_time->tm_hour == 11 && new_start_local_time->tm_min <= 30) ||
                 (new_start_local_time->tm_hour >= 15 && new_start_local_time->tm_hour < 17) ||
                 (new_start_local_time->tm_hour == 17 && new_start_local_time->tm_min <= 30))))
      {
        std::cout
            << "You are trying to reserve a spot that is for coaching hours."
            << std::endl;
        std::cout
            << "Try again 48 hours before the reservation for availability."
            << std::endl;
        std::cout << std::endl;
        this->view_menu();
      } // prevent reserving during open play hours 48+ hours in advance
      else if ((new_start > std::chrono::system_clock::now() +
                                std::chrono::hours(48)) &&
               ((new_start_local_time->tm_hour >= 18 && new_start_local_time->tm_hour < 20) ||
                (new_start_local_time->tm_hour == 20 && new_start_local_time->tm_min <= 30)))
      {
        std::cout
            << "You are trying to reserve a spot that is for open play hours."
            << std::endl;
        std::cout
            << "Try again 48 hours before the reservation for availability."
            << std::endl;
        std::cout << std::endl;
        this->view_menu();
      }
      // enforce the 1 reservation a week rule
      else if (this->checkReservationWithinHours(new_start_local_time, c_num))
      {
        std::cout << "A reservation is already booked during the requested time" << std::endl;
        std::cout << "Check the schedule again and book during a time with no reservations" << std::endl;
        std::cout << std::endl;
        this->view_menu();
      }
      else
      {

        std::srand(static_cast<unsigned>(std::time(nullptr)));
        // choose a random officer
        Officer *selectedOfficer =
            nullptr; // Declare selectedOfficer outside the if statement

        if (!all_officers.empty())
        {
          std::size_t randomIndex = std::rand() % all_officers.size();
          selectedOfficer = all_officers[randomIndex];

          std::cout << "Officer ID: " << selectedOfficer->getId()
                    << " will handle your request" << std::endl;
        }
        else
        {
          std::cout << "No officers available." << std::endl;
        }

        if (selectedOfficer != nullptr)
        {
          selectedOfficer->modify_reservation(this->getId(), old_start,
                                              new_start);
          this->view_menu();
        }
      }
    }
    else if (mod == 2)
    {
      cout << "What reservation would you like to cancel? Enter the "
              "corresponding number"
           << endl;

      for (size_t i = 0; i < my_reservations.size(); ++i)
      {
        cout << "[" << (i + 1) << "] "
             << "Reservation Details:" << endl;
        cout << "Player ID(s): ";
        for (size_t j = 0; j < my_reservations[i]->get_players().size(); ++j)
        {
          cout << my_reservations[i]->get_players()[j];
          if (j < my_reservations[i]->get_players().size() - 1)
          {
            cout << ", ";
          }
        }

        cout << endl;
        std::time_t startTime =
            std::chrono::system_clock::to_time_t(my_reservations[i]->get_start());
        std::tm *timeInfo = std::localtime(&startTime);

        cout << "Start Time: " << std::ctime(&startTime) << "on day "
             << timeInfo->tm_wday << " (0 = Sun, 1 = Mon, ..., 6 = Sat)" << endl;
        cout << endl;
      }

      cout << "Enter the number of the reservation you want to cancel: ";
      unsigned int input;
      cin >> input;
      if (input == 0 || input < my_reservations.size())
      {
        std::cout << "invalid input" << std::endl;
        this->view_menu();
      }
      std::srand(static_cast<unsigned>(std::time(nullptr)));
      // choose a random officer
      Officer *selectedOfficer =
          nullptr; // Declare selectedOfficer outside the if statement

      if (!all_officers.empty())
      {
        std::size_t randomIndex = std::rand() % all_officers.size();
        selectedOfficer = all_officers[randomIndex];

        std::cout << "Officer ID: " << selectedOfficer->getId()
                  << " will handle your cancellation request" << std::endl;
        std::cout << "Check back later to see if it was handled" << std::endl;
      }
      else
      {
        std::cout << "No officers available." << std::endl;
      }

      if (selectedOfficer != nullptr)
      {
        selectedOfficer->handle_request(this->getId(),
                                        this->my_reservations[input], true);
        std::cout << "Cancellation request sent successfully" << std::endl;
        // get the res
        Reservation *selectedReservation = my_reservations[input - 1];
        // get the court this res is on
        Court *reservationCourt = selectedReservation->court;
        // erase it from the court's vector
        reservationCourt->delete_reservation(selectedReservation);

        // erase the reservation from the coach's vector of reservations
        my_reservations.erase(my_reservations.begin() + (input - 1));
        delete selectedReservation;
        std::cout << std::endl;
        this->view_menu();
      }
    }
    else if (mod == 3)
    {
      cout << "Making a Reservation:" << endl;
      std::cout << "Enter which court you want to reserve: (1, 2, or 3): ";
      int court_num;
      std::cin >> court_num;
      if (court_num != 1 && court_num != 2 && court_num != 3)
      {
        cout << "Invalid choice. Please try again." << endl;
        std::cout << std::endl;
        this->view_menu();
      }
      else
      {

        std::cout << "Enter the start time you want in the valid format (month "
                     "[from 1-12], day, year [2023], hour [from 6 to 23], minute "
                     "[either 0 or 30])"
                  << std::endl;
        int month, day, year, hour, minute;
        std::cin >> month >> day >> year >> hour >> minute;
        if (month < 1 || month > 12 || day < 1 || day > 31 || year != 2023 || hour < 6 || hour > 23 || (minute != 0 && minute != 30))
        {
          std::cout << "Invalid input format. Please try again." << std::endl;
          std::cout << std::endl;
          this->view_menu();
        }

        Court *desiredCourt = nullptr;

        for (const auto &c : User::get_courts())
        {
          if (court_num == c->get_court_num())
          {
            desiredCourt = c;
            break;
          }
        }

        if (desiredCourt != nullptr)
        {
          std::tm time{};
          time.tm_year = year - 1900; // years since 1900
          time.tm_mon = month - 1;    // months since January
          time.tm_mday = day;
          time.tm_hour = hour - 1;
          // time.tm_min = minute;/;p[\]-
          std::time_t timeT = std::mktime(&time);
          std::chrono::system_clock::time_point startTime =
              std::chrono::system_clock::from_time_t(timeT);
          // max 7 days in advance
          auto maxReservationTime =
              std::chrono::system_clock::now() + std::chrono::hours(7 * 24);
          // makes a time
          std::time_t startTimeT =
              std::chrono::system_clock::to_time_t(startTime);
          // gets the local time
          std::tm *localTime = std::localtime(&startTimeT);

          // extract the day of the week from the std::tm object
          int dayOfWeek = localTime->tm_wday;
          // makes sure its in the future
          if (startTime <= std::chrono::system_clock::now())
          {
            std::cout
                << "Invalid reservation time, can only reserve in the future"
                << std::endl;
            std::cout << std::endl;
            this->view_menu();
          }

          // enforce the 7 day rule
          else if (startTime > maxReservationTime)
          {
            std::cout << "Reservations can only be made up to 7 days in advance."
                      << std::endl;
            std::cout << std::endl;
            this->view_menu();
          }
          // within a week
          else if (this->checkReservationWithinWeek(this->getId(), localTime))
          {
            std::cout << "You already have 1 reservation within the next week." << std::endl;
            std::cout << "Therefore you cannot reserve." << std::endl;
            std::cout << std::endl;
            this->view_menu();
            // enforce the 1 reservation per day
        } else if (this->checkReservationWithinDay(this->getId(), localTime))
        {
          std::cout << "You already have 1 reservation within 24 hours of the requested time." << std::endl;
          std::cout << "Therefore you cannot reserve." << std::endl;
          std::cout << std::endl;
          this->view_menu();
        }
          // prevent reserving during coaching hours 48+ hours in advance
          else if (startTime > std::chrono::system_clock::now() +
                                   std::chrono::hours(48) &&
                   (localTime->tm_wday >= 1 && localTime->tm_wday <= 5 &&
                    ((localTime->tm_hour >= 9 && localTime->tm_hour < 11) ||
                     (localTime->tm_hour == 11 && localTime->tm_min <= 30) ||
                     (localTime->tm_hour >= 15 && localTime->tm_hour < 17) ||
                     (localTime->tm_hour == 17 && localTime->tm_min <= 30))))
          {
            std::cout
                << "You are trying to reserve a spot that is for coaching hours."
                << std::endl;
            std::cout
                << "Try again 48 hours before the reservation for availability."
                << std::endl;
            std::cout << std::endl;
            this->view_menu();
          } // prevent reserving during open play hours 48+ hours in advance
          else if ((startTime > std::chrono::system_clock::now() +
                                    std::chrono::hours(48)) &&
                   ((localTime->tm_hour >= 18 && localTime->tm_hour < 20) ||
                    (localTime->tm_hour == 20 && localTime->tm_min <= 30)))
          {
            std::cout
                << "You are trying to reserve a spot that is for open play hours."
                << std::endl;
            std::cout
                << "Try again 48 hours before the reservation for availability."
                << std::endl;
            std::cout << std::endl;
            this->view_menu();
          } // enforce the one resrvation at a time
          else if (this->checkReservationWithinHours(localTime, desiredCourt->get_court_num()))
          {
            std::cout << "A reservation is already booked during the requested time" << std::endl;
            std::cout << "Check the schedule again and book during a time with no reservations" << std::endl;
            std::cout << std::endl;
            this->view_menu();
          }
          else
          {

            std::srand(static_cast<unsigned>(std::time(nullptr)));
            // choose a random officer
            Officer *selectedOfficer =
                nullptr; // Declare selectedOfficer outside the if statement

            if (!all_officers.empty())
            {
              std::size_t randomIndex = std::rand() % all_officers.size();
              selectedOfficer = all_officers[randomIndex];

              std::cout << "Officer ID: " << selectedOfficer->getId()
                        << " will handle your reservation request" << std::endl;
              std::cout << "Check back later to see if it was handled"
                        << std::endl;
            }
            else
            {
              std::cout << "No officers available." << std::endl;
            }

            if (selectedOfficer != nullptr)
            {
              selectedOfficer->handle_request(
                  this->getId(),
                  (new Reservation(this->getId(), startTime, dayOfWeek,
                                   desiredCourt, this->get_membership(), false, this->get_name())),
                  false);
              std::cout << "Reservation request sent successfully" << std::endl;
              std::cout << std::endl;
              this->view_menu();
            }
          }
        }
      }
    }
    else
    {
      std::cout << "invalid request" << std::endl;
      this->view_menu();
    }
  }

bool Member::checkReservationWithinWeek(int id, std::tm* localTime)
{
    std::vector<std::string> courtFiles = {"court1.txt", "court2.txt", "court3.txt"};

    int reservationCount = 0;  // Counter for the number of reservations within a week

    for (const auto& courtFile : courtFiles)
    {
        std::ifstream file(courtFile);
        if (!file.is_open())
        {
            throw std::runtime_error("Failed to open " + courtFile);
        }

        std::string line;
        while (std::getline(file, line))
        {
            size_t playerIdPos = line.find("Player ID: ");
            if (playerIdPos != std::string::npos)
            {
                std::string playerIdSubstring = line.substr(playerIdPos + 11);
                int playerId = std::stoi(playerIdSubstring);
                if (playerId == id)
                {
                    size_t startTimePos = line.find("Start Time: ");
                    if (startTimePos != std::string::npos)
                    {
                        startTimePos += 12;
                        std::string startTimeSubstring = line.substr(startTimePos, 19);

                        std::tm startTime = {};
                        std::sscanf(startTimeSubstring.c_str(), "%d-%d-%d %d:%d:%d",
                                    &startTime.tm_year, &startTime.tm_mon, &startTime.tm_mday,
                                    &startTime.tm_hour, &startTime.tm_min, &startTime.tm_sec);

                        startTime.tm_mon -= 1;
                        startTime.tm_year -= 1900;

                        std::time_t startTimeT = std::mktime(&startTime);
                        std::time_t currentTimeT = std::mktime(localTime);
                        std::int64_t diffHours = std::abs(currentTimeT - startTimeT) / (60 * 60);

                        std::string openPlaySubstring = line.substr(line.find("Open Play: ") + 11, 3);
                        bool isOpenPlay = (openPlaySubstring == "Yes");

                        if (!isOpenPlay && diffHours >= 0 && diffHours <= 168)
                        {
                            reservationCount++;  // Increment the reservation count

                            if (reservationCount >= 2)
                            {
                                file.close();
                                return true;
                            }
                        }
                    }
                }
            }
        }

        file.close();
    }

    return false;
}


bool Member::checkReservationWithinDay(int id, std::tm* localTime)
{
    std::vector<std::string> courtFiles = {"court1.txt", "court2.txt", "court3.txt"};

    for (const auto& courtFile : courtFiles)
    {
        std::ifstream file(courtFile);
        if (!file.is_open())
        {
            throw std::runtime_error("Failed to open " + courtFile);
        }

        std::string line;
        while (std::getline(file, line))
        {
            size_t playerIdPos = line.find("Player ID: ");
            if (playerIdPos != std::string::npos)
            {
                std::string playerIdSubstring = line.substr(playerIdPos + 11);
                int playerId = std::stoi(playerIdSubstring);
                if (playerId == id)
                {
                    size_t startTimePos = line.find("Start Time: ");
                    if (startTimePos != std::string::npos)
                    {
                        startTimePos += 12;
                        std::string startTimeSubstring = line.substr(startTimePos, 19);

                        std::tm startTime = {};
                        std::sscanf(startTimeSubstring.c_str(), "%d-%d-%d %d:%d:%d",
                                    &startTime.tm_year, &startTime.tm_mon, &startTime.tm_mday,
                                    &startTime.tm_hour, &startTime.tm_min, &startTime.tm_sec);

                        startTime.tm_mon -= 1;
                        startTime.tm_year -= 1900;

                        std::string openPlaySubstring = line.substr(line.find("Open Play: ") + 11, 3);
                        bool isOpenPlay = (openPlaySubstring == "Yes");

                        if (!isOpenPlay && startTime.tm_mon == localTime->tm_mon && startTime.tm_mday == localTime->tm_mday)
                        {
                            file.close();
                            return true;
                        }
                    }
                }
            }
        }

        file.close();
    }

    return false;
}

void Member::joinReservation(std::vector<Court*> all_courts)
{

    // Check if the member has more than 2 reservations within a week
    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);
    if (checkReservationWithinWeek(getId(), localTime))
    {
        std::cout << "You have reached the maximum number of reservations within a week." << std::endl;
        std::cout << "You cannot join another reservation at this time." << std::endl;
        return;
    }

    // Check if the member is trying to reserve a reservation within 24 hours of their own existing one
    if (checkReservationWithinDay(getId(), localTime))
    {
        std::cout << "You have already reserved a court within the next 24 hours." << std::endl;
        std::cout << "You cannot join another reservation at this time." << std::endl;
        return;
    }
    
    // Ask the user to select a court
    int courtChoice;
    std::cout << "Enter the number of the court you want to join a reservation on: ";
    std::cin >> courtChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Validate the user's choice
    if (courtChoice < 1 || courtChoice > all_courts.size())
    {
        std::cout << "Invalid court choice!" << std::endl;
        return;
    }

    // Get the selected court
    Court* selectedCourt = all_courts[courtChoice - 1];

    // Read reservations from file for the selected court
    std::string filename = "court" + std::to_string(selectedCourt->get_court_num()) + ".txt";
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Error opening reservations file!" << std::endl;
        return;
    }

    std::vector<std::string> reservations;
    std::string line;
    int reservationNumber = 1;
    while (std::getline(file, line))
    {
        // Store each reservation in a vector
        reservations.push_back(line);

        // Print the reservation with a number prefix
        std::cout << reservationNumber << ". " << line << std::endl;
        reservationNumber++;
    }
    file.close();

    // Ask the user to select a reservation to join
    int reservationChoice;
    std::cout << "Enter the number of the reservation you want to join: ";
    std::cin >> reservationChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Validate the user's choice
    if (reservationChoice < 1 || reservationChoice > static_cast<int>(reservations.size()))
    {
        std::cout << "Invalid reservation choice!" << std::endl;
        return;
    }

    // Get the selected reservation
    std::string selectedReservation = reservations[reservationChoice - 1];

    // Join the selected reservation
    std::string playerId = std::to_string(getId());
    selectedReservation += ", playing with Player ID: " + playerId;

    // Update the reservations file with the modified reservation
    std::ofstream outfile(filename);
    if (!outfile.is_open())
    {
        std::cout << "Error opening reservations file for writing!" << std::endl;
        return;
    }

    for (const std::string& reservation : reservations)
    {
        if (reservation == reservations[reservationChoice - 1])
        {
            // Write the modified reservation with the added player ID
            outfile << selectedReservation << std::endl;
        }
        else
        {
            // Write the other reservations as they were
            outfile << reservation << std::endl;
        }
    }
    outfile.close();

    std::cout << "You have successfully joined the reservation:" << std::endl;
    std::cout << selectedReservation << std::endl;

    view_menu();

}



