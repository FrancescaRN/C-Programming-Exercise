//
// Created by Francesca on 18/01/2022.
//

#include "Planet.h"
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class isteamFailure : public exception{
public :
    isteamFailure() : exception() {}
};

istream& operator >> (istream &is, Planet& p)
{
    string name, system, method, facility;
    int year, temperature;
    double radius, mass;
    char c1, c2, c3, c;


    if (is >> quoted(name) >> c >>
        quoted(system) >> c >> quoted(method) >> c >>
        year >> c1 >> quoted(facility) >> c >> radius>> c2 >>
        mass >> c3 >> temperature ){
        if (c == ',' && c1 == ',' && c2 == ',' && c3 == ',')
        {
            p = Planet (name, system,method, year,
                        facility, radius, mass, temperature);
        }
        else
        {
            cout << "Input stream failure" << endl;
            is.clear(ios_base::failbit);
            throw isteamFailure();
        }
    }
    else {
        throw isteamFailure();
    }

    return is;
}