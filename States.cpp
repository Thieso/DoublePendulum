#include "States.h"

// create States object
States::States() {
    phi1 = 0;
    phi2 = 0;
    phi1d = 0;
    phi2d = 0;
}

// set states 
void States::set_states(double* s) {
    phi1 = s[0];
    phi2 = s[1];
    phi1d = s[2];
    phi2d = s[3];
}

// getter functions
double States::get_phi1(){
    return phi1;
}
double States::get_phi2(){
    return phi2;
}
double States::get_phi1d(){
    return phi1d;
}
double States::get_phi2d(){
    return phi2d;
}

// setter functions
void States::set_phi1(double p){
    phi1 = p;
}
void States::set_phi2(double p){
    phi2 = p;
}
void States::set_phi1d(double p){
    phi1d = p;
}
void States::set_phi2d(double p){
    phi2d = p;
}


// operator overloading for the addition method
States States::operator+(const States& s) {
    States states;
    states.phi1  = this->phi1 + s.phi1;
    states.phi2  = this->phi2 + s.phi2;
    states.phi1d = this->phi1d + s.phi1d;
    states.phi2d = this->phi2d + s.phi2d;
    return states;
}

// operator overloading for the multiplication with a double
States States::operator*(const double d) {
    States states;
    states.phi1  = this->phi1 * d;
    states.phi2  = this->phi2 * d;
    states.phi1d = this->phi1d * d;
    states.phi2d = this->phi2d * d;
    return states;
}


// operator overloading for easier getter
double& States::operator[](const int i) {
    if (i == 0)
        return phi1;
    else if (i == 1)
        return phi2;
    else if (i == 2)
        return phi1d;
    else
        return phi2d;
}
