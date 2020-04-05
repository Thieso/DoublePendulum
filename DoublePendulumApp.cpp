#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include <iostream>
#include "Pendulum.h"

using namespace ci;
using namespace ci::app;

class PendulumApp : public App {
	private: 
		Pendulum *p1; 
		Pendulum *p2; 
		int color1[3] = {0, 0, 1}; 
		int color2[3] = {0, 1, 0}; 
	public: 
		void draw(); 
		void setup(); 
};

void prepareSettings( PendulumApp::Settings* settings ){
	settings->setWindowSize(800, 600); 
	settings->setFrameRate(60.0f); 
	settings->setTitle("Cinder"); // to make it float on default 
}

void PendulumApp::setup(){
    // create pendulums
	p1 = new Pendulum(0, 0, color1); 
	p2 = new Pendulum(0, 1, color2); 
}

void PendulumApp::draw(){
	gl::clear(); 
    // simulate the pendulum with visualization
	p1->updatePendulum(); 
	p2->updatePendulum(); 

    // draw a graph of the height values of the pendulum
	p1->drawHeightGraph(); 
	p2->drawHeightGraph(); 
}

// This line tells Cinder to actually create and run the application.
CINDER_APP(PendulumApp, RendererGl, prepareSettings)
