#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include <iostream>
#include "DoublePendulum.h"

using namespace ci;
using namespace ci::app;

class PendulumApp : public App {
    private: 
        DoublePendulum *p; 
        int color1[3] = {0, 0, 1}; 
        int color2[3] = {0, 1, 0}; 
        float frameRate = 60.0;
    public: 
        void draw(); 
        void setup(); 
};

void prepareSettings(PendulumApp::Settings* settings){
    settings->setWindowSize(800, 400); 
    settings->setFrameRate(50.0f); 
    settings->setTitle("Double Pendulum Simulation"); 
}

void PendulumApp::setup(){
    // create pendulums
    p = new DoublePendulum(color1, color2); 
}

void PendulumApp::draw(){
    gl::enable(GL_SCISSOR_TEST);
    // simulate the DoublePendulum with visualization
    gl::viewport(glm::vec2(0, getWindowHeight()/2), glm::vec2(getWindowWidth()/2, getWindowHeight()/2));
    gl::scissor(glm::vec2(0, getWindowHeight()/2), glm::vec2(getWindowWidth()/2, getWindowHeight()/2));
    gl::clear(); 
    p->updatePendulum(); 
    // draw the state space of the angles
    gl::viewport(glm::vec2(getWindowWidth()/2, 0), glm::vec2(getWindowWidth()/2, getWindowHeight()));
    gl::scissor(glm::vec2(getWindowWidth()/2, 0), glm::vec2(getWindowWidth()/2, getWindowHeight()));
    p->drawStateSpace(); 
    // draw angle graph
    gl::viewport(glm::vec2(0, 0), glm::vec2(getWindowWidth()/2, getWindowHeight()/2));
    gl::scissor(glm::vec2(0, 0), glm::vec2(getWindowWidth()/2, getWindowHeight()/2));
    gl::clear(); 
    p->drawAngleTime(); 
}

// This line tells Cinder to actually create and run the application.
CINDER_APP(PendulumApp, RendererGl, prepareSettings)
