// in order to include this class in the project you have to adjust CMakeLists.txt in the parent directory
#include <iostream>
#include <cmath>
#include <list>
#include <vector>
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
        glm::vec2 upperPointP1; 
        glm::vec2 lowerPointP1; 
        glm::vec2 lowerPointP2; 
        int* color1;  // color of pendulum 1
        int* color2;  // color of pendulum 2
        float radius         = 7; // radius of circle
        float g              = 9.81; // [m/s^2] gravitation
        float pi             = 3.14; // pi
        float _phi           = pi/4; // initial angel of pendulums
        double draw_length = 150; // base draw length for pendulums
        double h = 0.02; // step size
        States a;
        States b;
        States c;
        States d;
        double* x;
        States states; // state vector holding angles and angular velocities for both pendulums
        double m1, m2; // masses of pendulums
        double l1, l2; // length of pendulums
        double phi1, phi2, phi1d, phi2d; // helper variables for easier calculations
        // parameters for height graph
        glm::vec2 heightPoint; // single height point 
        std::list<float> hArray; // array holding the heigh values
        int heigh_array_size = 200; // size of array holding height values for graph
    public: 
        DoublePendulum(int*, int*); 
        ~DoublePendulum(); 
        void f(States);
        void calculateLowerPoints(); 
        void calculateNextTimestep(); 
        void updatePendulum(); 
        //void drawHeightGraph(); 
};

#endif
