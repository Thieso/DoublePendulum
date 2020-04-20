#include <iostream>
#include <cmath>
#include <list>
#include <vector>
#include <algorithm>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "States.h"

#ifndef DOUBLEPENDULUM_H
#define DOUBLEPENDULUM_H

using namespace ci;
using namespace ci::app;
using namespace std;

class DoublePendulum{
    private: 
        glm::vec2 upperPointP1;       // upper point of pendulum 1
        glm::vec2 lowerPointP1;       // lower point of pendulum 1 and upper point of 2
        glm::vec2 lowerPointP2;       // lower point of pendulum 2
        int* color1;                  // color of pendulum 1
        int* color2;                  // color of pendulum 2
        float radius = 7;             // radius of circle
        float g = 9.81;               // [m/s^2] gravitation
        float pi = 3.14;              // pi for this project
        double draw_length = 150;     // base draw length for pendulums
        double m1, m2;                // masses of pendulums
        double l1, l2;                // length of pendulums
        double t;                     // time
        States states;                // state vector holding angles and angular velocities for both pendulums
        States a;                     // helper state vector for runge kutta method
        States b;                     // helper state vector for runge kutta method
        States c;                     // helper state vector for runge kutta method
        States d;                     // helper state vector for runge kutta method
        double h = 0.025;             // step size
        double ssScaling = 100;       // scaling for state space values to make it easily visible
        std::list<glm::vec2> phi1Array; // array holding the phi1 values
        std::list<glm::vec2> phi2Array; // array holding the phi2 values
        int angleSize = 400;             // size of array holding angle values
    public: 
        DoublePendulum(int*, int*); 
        ~DoublePendulum(); 
        void f(States*, States);
        void calculateLowerPoints(); 
        void calculateNextTimestep(); 
        void updatePendulum(); 
        void drawStateSpace(); 
        void drawAngleTime();
};

#endif
