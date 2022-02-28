//
// Created by Francesca on 18/01/2022.
//

#ifndef CODE_PLANET_H
#define CODE_PLANET_H

#include <string>
#include <iostream>

class Planet {
private:
    std::string name, system, method, facility;
    int year, temperature;
    double radius, mass, habitability;

public:

    inline Planet() {};

     inline Planet(std::string name, std::string system, std::string method, int year,
                  std::string facility, double radius, double mass, int temperature)
    {
         if (name == "" || system == "" || facility == "" || method == "" ||
            year < 0 || radius < 0 || mass< 0 || temperature < 0)
         { throw ConstructorFailure(); }
        this->name = name;
        this->system = system;
        this->method = method;
        this->year = year;
        this->facility = facility;
        this->radius = radius;
        this->mass = mass;
        this->temperature = temperature;
        habitability = 0;
    }

/* Getter */
    [[nodiscard]] inline std::string getName() const { return name; }

    [[nodiscard]] inline std::string getSystem() const { return system; }

    [[nodiscard]] inline std::string getMethod() const { return method; }

    [[nodiscard]] inline int getYear() const { return year; }

    [[nodiscard]] inline std::string getFacility() const { return system; }

    [[nodiscard]] inline double getRadius() const { return radius; }

    [[nodiscard]] inline double getMass() const { return mass; }

    [[nodiscard]] inline int getTemperature() const { return temperature; }

    [[nodiscard]] inline double getHabitability() const { return habitability; }

/* Setter */
    void setHabitability(double hab) {
        habitability = hab;
    }

/* I/0 stream operators */
    friend std::ostream& operator<<(std::ostream& os, const Planet& planet)
    {
        return os   << planet.name      << ", "
                    << planet.system    << ", "
                    << planet.method    << ", "
                    << planet.year      << ", "
                    << planet.facility  << ", "
                    << planet.radius    << ", "
                    << planet.mass      << ", "
                    << planet.temperature   << ", "
                    << planet.habitability ;
    }

    friend std::istream& operator>>(std::istream& is, Planet& planet);

    class ConstructorFailure : public std::exception{
    public :
        ConstructorFailure() : exception() {}
    };
};

/* relational operators */
inline bool operator==(const Planet &a, const Planet &b)
{ return a.getHabitability() == b.getHabitability(); }

inline bool operator!=(const Planet &a, const Planet &b)
{ return !(a == b); }

inline bool operator>(const Planet &a, const Planet &b)
{ return a.getHabitability() > b.getHabitability(); }

inline bool operator<=(const Planet &a, const Planet &b)
{ return !(a > b); }

inline bool operator<(const Planet &a, const Planet &b)
{ return a.getHabitability() < b.getHabitability(); }

inline bool operator>=(const Planet &a, const Planet &b)
{ return !(a < b); }

#endif //CODE_PLANET_H

