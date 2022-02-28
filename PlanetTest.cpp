//
// Created by Francesca on 18/01/2022.
//

#include "Planet.h"

bool testPlanet(){
    bool pass = true;
    try{
        auto* p = new Planet ("Bongo", "Jungle", "capture", 2036,
                                "Bristol", 30.7, 35.56, 76);
    }
    catch(Planet::ConstructorFailure& e){
        std::cerr << "Error: Array index out of bounds: " << std::endl;
        pass = false;
    }
    return pass;
}