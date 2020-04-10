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
    settings->setWindowSize(800, 600); 
    settings->setFrameRate(50.0f); 
    settings->setTitle("Double Pendulum Simulation"); 
}

void PendulumApp::setup(){
    // create pendulums
    p = new DoublePendulum(color1, color2); 
}

void PendulumApp::draw(){
    gl::clear(); 
    // simulate the DoublePendulum with visualization
    p->updatePendulum(); 
    // draw the state space of the angles
    p->drawStateSpace(); 
}

// This line tells Cinder to actually create and run the application.
CINDER_APP(PendulumApp, RendererGl, prepareSettings)
