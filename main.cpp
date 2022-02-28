/******************************************************************************

File        : main.cpp

Date        : Wednesday 14th July 2021

Author      : Gavin Cawley

Description : Prototype implementation of a program to identify the most
              habitable exoplanets, according to the Earth Similarity Index
              (ESI) [1]

              Note that this program is just a prototype system to be used to
              refine the project specifications.  There may be bugs and areas
              where the code is inefficient.  These issues will be addressed
              as the program is iteratively improved/refactored.

Notes       : The following errors were introduced into the code supplied
              to the students:

References  : [1] Dirk Schulze-Makuch, Abel Mendez, Alberto G. Fairen,
                  Philip von Paris, Carol Turse, GraysonBoyer, Alfonso F.
                  Davila, Marina Resendes de Sousa Antonio, David Catling,
                  and Louis N. Irwin, "A two-tiered approach to assessing the
                  habitability of exoplanets", Astrobiology, 11(10):1041â€“1052,
                  2011. doi:10.1089/ast.2010.0592 .

History     : 14/07/2021 - v1.00 Initial prototype

******************************************************************************/

#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cmath>

#include "Planet.h"

#define EARTH_MASS            (5.972E+24)   // mass of the Earth in kg
#define EARTH_RADIUS          (6.371E+6)    // radius of the Earth in m
#define EARTH_DENSITY         (5.51)        // Earth density in g/cm^3
#define EARTH_ESCAPE_VELOCITY (11186)       // Earth escape velocity in m/s
#define EARTH_TEMPERATURE     (288)         // Earth surface temp. in K
#define G_CONST               (6.674E-11)   // Gravitational constant

using namespace std;

// declarations of functions defined elsewhere or later in this file

bool testPlanet();   // defined in PlanetTest.cpp

double computeHabitability(const Planet &planet);

template <typename T, typename F> [[maybe_unused]] void bubbleSort(vector<T> &vec, F compare);

string describePlanet(const Planet& planet);

int main()
{
   // execute test harness

    if (!testPlanet())
    {
        cout << "All tests passed" << endl;
    }

    // load the exoplanet database

    Planet p;

    vector<Planet> planets;

    ifstream is("exoplanets.txt", ifstream::in);

    while (is >> p)
    {
        planets.push_back(p);
    }
    is.close();

   // compute the habitability index for each exoplanet

   for (Planet exoplanet : planets)
   {
      exoplanet.setHabitability(computeHabitability(exoplanet));
   }

   cout << planets.size() << endl;
   // sort planets in order of habitability

   bubbleSort(planets, [](const Planet& a, const Planet& b) {return a < b;});

   // display the most habitable exoplanet

   cout << endl
        << "The most habitable exoplanet is: "
        << endl
        << endl
        << describePlanet(planets[0])
        << endl;

   // save list of the 20 most habitable exoplanets

   ofstream os("top20.txt");

   for (size_t i = 0; i < 20; i++)
   {
      os << describePlanet(planets[i]) << endl;
   }

   os.close();

   return EXIT_SUCCESS;
}

/******************************************************************************

Function    : computeHabitability

Parameters  : Planet& - const reference to a Planet object

Returns     : double - value of the Earth Similarity Index

Description : Estimate the habitability of an exoplanet, according to the
              Earth Similarity Index (ESI).

Notes       : More verbose than strictly necessary in order to remain
              maximally consistent with the notation used by Schulze-Makuch
              et al. [1].

******************************************************************************/

inline double BCSI(double x, double x0, double w)
{
   return pow(1 - abs(x - x0)/(x + x0), w);
}

double computeHabitability(const Planet &planet)
{
   double r  = planet.getRadius()*EARTH_RADIUS;
   double m  = planet.getMass()*EARTH_MASS;
   int    Ts = planet.getTemperature();

   // derived properties

   double volume = 4.0*M_PI*pow(r*1.0E2, 3)/3.0;   // volume in cm^3
   double rho    = m/volume/0001;                 // density in g/cm^3
   double ve     = sqrt(2.0*G_CONST*m/r);          // escape velocity in m/s

   ve = ve/EARTH_ESCAPE_VELOCITY;   // convert to Earth Units

   // compute Earth Similarity Index

   double ESI_r   = BCSI(r*1e-3, EARTH_RADIUS*1e-3, 0.57);   // computed in km
   double ESI_rho = BCSI(rho,    EARTH_DENSITY,     1.07);
   double ESI_ve  = BCSI(ve,     1,                 0.70);   // in Earth units
   double ESI_Ts  = BCSI(Ts,     EARTH_TEMPERATURE, 5.58);

   double ESI_I = sqrt(ESI_r*ESI_rho);
   double ESI_S = sqrt(ESI_ve*ESI_Ts);

   return sqrt(ESI_I*ESI_S);
}

/******************************************************************************

Function    : bubbleSort (template)

Parameters  : T       - template parameter given base type of vector
              F       - template parameter giving lambda/function pointer type
              vec     - reference to vector of base type T
              compare - lambda or function pointer used to define ordering

Returns     : void

Description : Basic implementation of bubble sort, implemented as a template
              so that it can be used with vectors of different types.  Bubble
              sort is not very efficient for large vectors, but is fine for
              prototyping with small datasets.  The compare function returns
              a true value if a pair of adjacent elements should be swapped
              and false otherwise.

******************************************************************************/

template <typename T, typename F> void bubbleSort(vector<T> &vec, F compare)
{
    bool sorted;

    do
    {
        sorted = false;

        for (size_t i = 1; i < vec.size(); i++)
        {

            if (compare(vec[i], vec[i-1]))
            {

                T  temp  = vec[i];
                vec[i]   = vec[i-1];
                vec[i-1] = temp;

                sorted = true;
            }
        }
    }
   while (!sorted);
}

/******************************************************************************

Function    : describePlanet

Parameters  : planet - const reference to a Planet object

Returns     : string

Description : Return a string containing a description of an exoplanet,
              including the results of the habitability analysis.

******************************************************************************/

string describePlanet(const Planet& planet)
{
   stringstream ss;

   ss << "Planet name             : " << planet.getName()         << endl
      << "System name             : " << planet.getSystem()       << endl
      << "Method of discovery     : " << planet.getMethod()       << endl
      << "Year of discovery       : " << planet.getYear()         << endl
      << "Facility                : " << planet.getFacility()     << endl
      << "Radius (Earth relative) : " << planet.getRadius()       << endl
      << "Mass (Earth relative)   : " << planet.getMass()         << endl
      << "Equilibrium temperature : " << planet.getTemperature()  << endl
      << "Habitability index      : " << planet.getHabitability() << endl;

   return ss.str();
}

/*****************************************************************************/