// in order to include this class in the project you have to adjust CMakeLists.txt in the parent directory
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include <iostream>
#include <list>

#ifndef PENDULUM_H
#define PENDULUM_H

using namespace ci;
using namespace ci::app;

class Pendulum{
    private: 
        glm::vec2 upperPoint; 
        glm::vec2 lowerPoint; 
        int* color;  // color of Pendulum
        float radius         = 10; // radius of circle
        float l              = 300; // [mm] length of pendulum
        float g              = 9.81; // [m/s^2] gravitation
        float pi             = 3.14; // pi
        float _phi           = pi/4; // initial angel of pendulum
        float phi            = _phi;  // angel of pendulum
        float phiPrev        = _phi; // prev angle
        float dt             = 0.017; // time step
        float t              = 0; // total time
        int smallAngles      = 0; // set the calculation method
        int damping          = 0; // damping (true or false)
        float dr             = 10; // damping ratio
        // parameters for height graph
        glm::vec2 heightPoint; // single height point 
        std::list<float> hArray; // array holding the heigh values
        int heigh_array_size = 200; // size of array holding height values for graph
    public: 
        Pendulum(int, int, int*); 
        void calculateLowerPoint(); 
        void calculateNextTimestep(); 
        void calculateNextTimestepSmallAngles(); 
        void updatePendulum(); 
        void drawHeightGraph(); 
};

#endif
