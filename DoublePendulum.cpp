// in order to include this class in the project you have to adjust CMakeLists.txt in the parent directory
#include <iostream>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "Pendulum.h"

// create pendulum object
Pendulum::Pendulum(int _smallAngles, int _damping, int* _color){
    //initialize variables
    upperPoint = glm::vec2(getWindowWidth()/2, 0); 
    lowerPoint = glm::vec2(getWindowWidth()/2, getWindowHeight()/2);
    color = _color; 
    smallAngles = _smallAngles; 
    damping = _damping; 
}

// calculate where the lower point is at by using the upper point, the angle and
// the length
void Pendulum::calculateLowerPoint(){
    lowerPoint = glm::vec2(l * sin(phi), l * cos(phi)) + upperPoint;
}

// calculate the next time step depending on the previous one. Calculation
// depends on whether damping is enabled or not
void Pendulum::calculateNextTimestep(){
    // get current angle
    float temp = phi; 
    // calculate new angle
    if (damping)
        phi = -dt*dt*((g/(l/400))*sin(phi)+dr*(phi-phiPrev))+2*phi-phiPrev; 
    else
        phi = -dt*dt*((g/(l/400))*sin(phi))+2*phi-phiPrev; 
    // set previous angle
    phiPrev = temp; 
}

// calculate next time step assuming a small angle approximation
void Pendulum::calculateNextTimestepSmallAngles(){
    // calculate phi
    t += dt; 
    phi = _phi * cos(sqrt(g/(l/400))*t); 
}

// update the pendulum for the next time step
void Pendulum::updatePendulum(){
    // calculate the angle for the next timestep 
    if (smallAngles)
        calculateNextTimestepSmallAngles(); 
    else
        calculateNextTimestep(); 

    // calculate the position of the lower point of the pendulum
    calculateLowerPoint(); 

    // set the color of the pendulum
    gl::color(color[0], color[1], color[2]); 

    // update the upper point in case window got resized
    upperPoint = glm::vec2(getWindowWidth()/2, 0); 

    // draw the line of the pendulum
    gl::drawLine(upperPoint, lowerPoint);

    // draw a circle at the end of the line
    gl::drawSolidCircle(lowerPoint, radius); 
}

// display a height graph showing the height of the end of the pendulum
void Pendulum::drawHeightGraph(){
    // get height of pendulum
    float h = phi*l;  

    // push new element to the list holding the height values
    hArray.push_front(h); 

    // if list is has reached a certain size remove the last element
    if (hArray.size() > heigh_array_size){
        hArray.pop_back(); 
    }

    // set color of height graph to color of pendulum
    gl::color(color[0], color[1], color[2]); 

    // Display the array below the pendulum
    int positionShift = 0; 
    for(auto i = hArray.begin(); i != hArray.end(); i++){
        heightPoint = glm::vec2(getWindowWidth()/2-positionShift, 2*l - 0.5*_phi*l - 0.4*(*i) - radius);
        gl::drawSolidCircle(heightPoint, 2); 
        positionShift += 1; 
    }
}
