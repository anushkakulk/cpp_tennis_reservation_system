#include "court.hpp"
#include "reservation.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

Court::Court(int num) : court_num(num) {}

// copy constrcutor
Court::Court(const Court &other) : court_num(other.court_num)
{
    for (const auto *reservation : other.res)
    {
        res.push_back(new Reservation(*reservation));
    }
}
// copy assignemnt operator
Court &Court::operator=(const Court &other)
{
    if (this == &other)
    {
        return *this;
    }
    court_num = other.court_num;

    // Clean up existing reservations
    for (auto *reservation : res)
    {
        delete reservation;
    }
    res.clear();

    // copy the reservations
    for (const auto *reservation : other.res)
    {
        res.push_back(new Reservation(*reservation));
    }

    return *this;
}

// move constructor
Court::Court(Court &&other) noexcept
    : court_num(std::move(other.court_num)), res(std::move(other.res))
{
    other.court_num = 0;
    other.res.clear();
}
// move assignment operator
Court &Court::operator=(Court &&other) noexcept
{
    if (this == &other)
    {
        return *this;
    }
    court_num = std::move(other.court_num);
    other.court_num = 0;
    res = std::move(other.res);

    other.court_num = 0;
    other.res.clear();

    return *this;
}
// destructor
Court::~Court() = default;
// checks if time is between 30 minutes from the reservations start time
bool Court::is_reserved(std::chrono::system_clock::time_point time)
{
    for (const auto &reservation : res)
    {
        std::chrono::system_clock::time_point start = reservation->get_start();
        std::chrono::system_clock::time_point end = start + std::chrono::minutes(30);

        if (time >= start && time < end)
        {
            return true;
        }
    }
    return false;
}

// adds reservation to its list of reservatiosn
void Court::add_reservation(Reservation *r)
{
    res.push_back(r);
    saveReservationToFile(r);
}

// deletes the given from its list of reservations
void Court::delete_reservation(Reservation *r)
{
    auto it = std::find(res.begin(), res.end(), r);
    if (it != res.end())
    {
        res.erase(it);
    }
    removeReservationFromFile(r);
}

// returns its court number
int Court::get_court_num()
{
    return court_num;
}

// returns list of reservations
std::vector<Reservation *> Court::get_reservations()
{
    return res;
}

void Court::saveReservationToFile(Reservation* r)
{
    std::string filename = "court" + std::to_string(court_num) + ".txt";
    std::fstream file(filename, std::ios_base::in | std::ios_base::out | std::ios_base::app);

    if (file.is_open())
    {
        std::vector<std::string> reservations;
        std::string line;

        // Read all existing reservations into the vector
        while (getline(file, line))
        {
            reservations.push_back(line);
        }

        // Add the new reservation to the vector
        reservations.push_back(r->toString());

        // Sort the reservations based on the start time
        std::sort(reservations.begin(), reservations.end(), [](const std::string& a, const std::string& b) {
            // Parse the start time from each reservation
            std::size_t startPosA = a.find("Start Time: ") + 12;
            std::size_t startPosB = b.find("Start Time: ") + 12;
            std::string startTimeA = a.substr(startPosA, 19);
            std::string startTimeB = b.substr(startPosB, 19);

            return startTimeA < startTimeB;
        });

        // Clear the contents of the file
        file.close();
        std::ofstream clearFile(filename, std::ofstream::out | std::ofstream::trunc);
        clearFile.close();

        // Write the sorted reservations back to the file
        std::ofstream writeFile(filename, std::ios_base::app);
        for (const auto& reservation : reservations)
        {
            writeFile << reservation << "\n";
        }

        writeFile.close();
    }
    else
    {
        std::cout << "Unable to open file" << std::endl;
    }
}

void Court::removeReservationFromFile(Reservation *r)
{
    std::string filename = "court" + std::to_string(court_num) + ".txt";
    std::ifstream fileIn(filename);
    std::ofstream fileOut("temp.txt");

    if (fileIn.is_open() && fileOut.is_open())
    {
        std::string line;
        while (getline(fileIn, line))
        {
            if (line != r->toString())
            {
                fileOut << line << "\n";
            }
        }
        fileIn.close();
        fileOut.close();

        std::remove(filename.c_str());
        std::rename("temp.txt", filename.c_str());
    }
    else
    {
        std::cout << "Unable to open file" << std::endl;
    }
}
