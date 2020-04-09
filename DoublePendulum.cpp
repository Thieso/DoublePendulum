// in order to include this class in the project you have to adjust CMakeLists.txt in the parent directory
#include <cmath>
#include <iostream>
#include <algorithm>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "DoublePendulum.h"

// create DoublePendulum object
DoublePendulum::DoublePendulum(int* _color1, int* _color2){
    //initialize variables
    upperPointP1 = glm::vec2(getWindowWidth()/2, 0); 
    lowerPointP1 = glm::vec2(getWindowWidth()/2, getWindowHeight()/2);
    lowerPointP2 = glm::vec2(getWindowWidth()/2, getWindowHeight()/2);
    color1 = _color1; 
    color2 = _color2; 
    m1 = 1;
    m2 = 2;
    l1 = 1;
    l2 = 1;
    // set initial states
    states.set_phi1(pi/4);
    states.set_phi2(pi/2);
}

// destructor
DoublePendulum::~DoublePendulum(){
}

// calculate where the lower point is at by using the upper point, the angle and
// the length
void DoublePendulum::calculateLowerPoints(){
    lowerPointP1 = glm::vec2(100 * sin(states.get_phi1()), 100 * cos(states.get_phi1())) + upperPointP1;
    lowerPointP2 = glm::vec2(100 * l2/l1 * sin(states.get_phi2()), 100 * l2/l1 * cos(states.get_phi2())) + lowerPointP1;
}

// calculate the next time step depending on the previous one. Calculation
// depends on whether damping is enabled or not
void DoublePendulum::calculateNextTimestep(){
    // calculate new angular velocity using runge kutta 4th order method
    f(states);
    a.set_states(x);

    f(states + a * (h/2));
    b.set_states(x);

    f(states + b * (h/2));
    c.set_states(x);

    f(states + c * h);
    d.set_states(x);

    // calculate new states values
    states = states + (a + b * 2.0 + c * 2.0 + d) * (h/6);
}

void DoublePendulum::f(States states) {
    // convert to array for easier 
    phi1 = states.get_phi1();
    phi2 = states.get_phi2();
    phi1d = states.get_phi1d();
    phi2d = states.get_phi2d();

    // set new phi1d and phi2d
    x[0] = phi1d;
    x[1] = phi2d;

    // calculate new s[3]d
    x[2] = (-g * (2*m1 + m2) * sin(phi1) - m2 * g * sin(phi1 - 2*phi2) - 2 * sin(phi1 - phi2) * m2 * (phi2d*phi2d * l2 + phi1d*phi1d * l1 * cos(phi1 - phi2))) / (l2 * (2 * m1 + m2 - m2 * cos(2 * phi1 - 2 * phi2)));
    
    // calculate new phi2dd
    x[3] = (2 * sin(phi1 - phi2) * (phi1d*phi1d * l1 * (m1 + m2) + g * (m1 + m2) * cos(phi1) + phi2d*phi2d * l2 * m2 * cos(phi1 - phi2))) / (l2 * (2 * m1 + m2 - m2 * cos(2 * phi1 - 2 * phi2)));
}


// update the DoublePendulum for the next time step
void DoublePendulum::updatePendulum(){
    // calculate the angle for the next timestep 
    calculateNextTimestep(); 

    // update the upper point in case window got resized
    upperPointP1 = glm::vec2(getWindowWidth()/2, 0); 

    // calculate the position of the lower point of the DoublePendulum
    calculateLowerPoints(); 

    // set the color of pendulum 1
    gl::color(color1[0], color1[1], color1[2]); 

    // draw the upper pendulum
    gl::drawLine(upperPointP1, lowerPointP1);
    gl::drawSolidCircle(lowerPointP1, radius); 

    // set the color of pendulum 1
    gl::color(color2[0], color2[1], color2[2]); 

    // draw the upper pendulum
    gl::drawLine(lowerPointP1, lowerPointP2);
    gl::drawSolidCircle(lowerPointP2, radius); 
}

// display a height graph showing the height of the end of the DoublePendulum
//void DoublePendulum::drawHeightGraph(){
    //// get height of DoublePendulum
    //float h = phi*l;  

    //// push new element to the list holding the height values
    //hArray.push_front(h); 

    //// if list is has reached a certain size remove the last element
    //if (hArray.size() > heigh_array_size){
        //hArray.pop_back(); 
    //}

    //// set color of height graph to color of DoublePendulum
    //gl::color(color[0], color[1], color[2]); 

    //// Display the array below the DoublePendulum
    //int positionShift = 0; 
    //for(auto i = hArray.begin(); i != hArray.end(); i++){
        //heightPoint = glm::vec2(getWindowWidth()/2-positionShift, 2*l - 0.5*_phi*l - 0.4*(*i) - radius);
        //gl::drawSolidCircle(heightPoint, 2); 
        //positionShift += 1; 
    //}
//}
