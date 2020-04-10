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
    lowerPointP1 = glm::vec2(100 * sin(states[0]), 100 * cos(states[0])) + upperPointP1;
    lowerPointP2 = glm::vec2(100 * l2/l1 * sin(states[1]), 100 * l2/l1 * cos(states[1])) + lowerPointP1;
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

    // set the color of pendulum 1
    gl::color(color2[0], color2[1], color2[2]); 

    // draw the upper pendulum
    gl::drawLine(lowerPointP1, lowerPointP2);
    gl::drawSolidCircle(lowerPointP2, radius); 
}

// display the state space consisting of phi1 and phi2 
void DoublePendulum::drawStateSpace(){
    // push new element to the list holding the state space values
    ssArray.push_front(glm::vec2(states[0] * ssScaling, states[1] * ssScaling)); 

    // if list is has reached a certain size remove the last element
    if (ssArray.size() > ssSize){
        ssArray.pop_back(); 
    }

    // set color of state space graph to color of DoublePendulum
    gl::color(color1[0], color1[1], color1[2]); 

    // Display the array below the DoublePendulum
    glm::vec2 origin = glm::vec2(getWindowWidth()/2, getWindowHeight() - 2.2 * ssScaling);
    for(auto i = ssArray.begin(); i != ssArray.end(); i++){
        gl::drawSolidCircle(*i + origin, 2); 
    }
}
