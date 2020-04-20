#include "DoublePendulum.h"

// create DoublePendulum object
DoublePendulum::DoublePendulum(int* _color1, int* _color2){
    //initialize variables
    upperPointP1 = glm::vec2(getWindowWidth()/2, 0); 
    lowerPointP1 = glm::vec2(getWindowWidth()/2, getWindowHeight()/2);
    lowerPointP2 = glm::vec2(getWindowWidth()/2, getWindowHeight()/2);
    color1 = _color1; 
    color2 = _color2; 
    t = 0;
    // set mass and length of pendulums
    m1 = 2;
    m2 = 2;
    l1 = 1;
    l2 = 1;
    // set initial states
    states.set_phi1(pi/2);
    states.set_phi2(pi);
}

// destructor
DoublePendulum::~DoublePendulum(){
}

// calculate where the lower point is at by using the upper point, the angle and
// the length
void DoublePendulum::calculateLowerPoints(){
    double lengthScaling = min(getWindowWidth()/4, getWindowHeight()/2);
    lowerPointP1 = glm::vec2(lengthScaling * sin(states[0]), lengthScaling * cos(states[0])) + upperPointP1;
    lowerPointP2 = glm::vec2(lengthScaling * l2/l1 * sin(states[1]), lengthScaling * l2/l1 * cos(states[1])) + lowerPointP1;
}

// calculate the next time step depending on the previous one. Calculation
// depends on whether damping is enabled or not
void DoublePendulum::calculateNextTimestep(){
    // calculate new angular velocity using runge kutta 4th order method
    f(&a, states);
    f(&b, states + a * (h/2));
    f(&c, states + b * (h/2));
    f(&d, states + c * h);

    // calculate new states values
    states = states + (a + b * 2.0 + c * 2.0 + d) * (h/6);

    // dont let angles get bigger than 2 pi
    if (states[0] > pi)
        states[0] = states[0] - 2*pi;
    else if (states[0] < -pi)
        states[0] = states[0] + 2*pi;
    if (states[1] > pi)
        states[1] = states[1] - 2*pi;
    else if (states[1] < -pi)
        states[1] = states[1] + 2*pi;

    // increase time 
    t += h;
}

// function to evaluate the equation of motion of the double pendulum at states
// s, save the results in return_states
void DoublePendulum::f(States* returnStates, States s) {
    (*returnStates)[0] = s[2];
    (*returnStates)[1] = s[3];
    (*returnStates)[2] = (-g * (2*m1 + m2) * sin(s[0]) - m2 * g * sin(s[0] - 2*s[1]) - 2 * sin(s[0] - s[1]) * m2 * (s[3]*s[3] * l2 + s[2]*s[2] * l1 * cos(s[0] - s[1]))) / (l2 * (2 * m1 + m2 - m2 * cos(2 * s[0] - 2 * s[1])));
    (*returnStates)[3] = (2 * sin(s[0] - s[1]) * (s[2]*s[2] * l1 * (m1 + m2) + g * (m1 + m2) * cos(s[0]) + s[3]*s[3] * l2 * m2 * cos(s[0] - s[1]))) / (l2 * (2 * m1 + m2 - m2 * cos(2 * s[0] - 2 * s[1])));
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

    // set the color of pendulum 2
    gl::color(color2[0], color2[1], color2[2]); 

    // draw the lower pendulum
    gl::drawLine(lowerPointP1, lowerPointP2);
    gl::drawSolidCircle(lowerPointP2, radius); 
}

// display the state space consisting of phi1 and phi2 
void DoublePendulum::drawStateSpace() {
    // set scaling
    this->ssScaling = min(getWindowWidth()/(2 * pi), getWindowHeight()/(2 * pi));
    glm::vec2 origin = glm::vec2(getWindowWidth()/2, getWindowHeight()/2);
    gl::drawSolidCircle(glm::vec2(states[0] * ssScaling, states[1] * ssScaling) + origin, 2); 
}


// display the graph of angles over time
void DoublePendulum::drawAngleTime() {
    // if list is has reached a certain size remove the last element
    if (phi1Array.size() >= angleSize){
        phi1Array.pop_back(); 
        phi2Array.pop_back(); 
    }

    // push new element to the list holding the state space values
    phi1Array.push_front(glm::vec2(0, states[0] * ssScaling)); 
    phi2Array.push_front(glm::vec2(0, states[1] * ssScaling)); 

    // set color of state space graph to color of DoublePendulum
    gl::color(color1[0], color1[1], color1[2]); 

    // Display the array below the DoublePendulum
    glm::vec2 origin = glm::vec2(getWindowWidth()/2, getWindowHeight()/2);
    int offsetValue = 0;
    for(auto i = phi1Array.begin(); i != phi1Array.end(); i++){
        glm::vec2 offset = glm::vec2(offsetValue, 0);
        gl::drawSolidCircle(*i + origin - offset, 2); 
        offsetValue++;
    }
    offsetValue = 0;
    for(auto i = phi2Array.begin(); i != phi2Array.end(); i++){
        glm::vec2 offset = glm::vec2(offsetValue, 0);
        gl::drawSolidCircle(*i + origin - offset, 2); 
        offsetValue++;
    }
}
