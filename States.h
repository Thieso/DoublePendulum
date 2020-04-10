// in order to include this class in the project you have to adjust CMakeLists.txt in the parent directory
#include <iostream>
#include <cmath>
#include <list>
#include <vector>

#ifndef STATES_H
#define STATES_H

using namespace std;

class States{
    private: 
        double phi1, phi2; // angles of pendulums
        double phi1d, phi2d; // angular velocities of pendulums
    public: 
        States(); 
        void set_states(double*);
        double get_phi1();
        void set_phi1(double);
        double get_phi2();
        void set_phi2(double);
        double get_phi1d();
        void set_phi1d(double);
        double get_phi2d();
        void set_phi2d(double);
        States operator+(const States&);
        States operator*(const double);
        double& operator[](const int);
};

#endif
