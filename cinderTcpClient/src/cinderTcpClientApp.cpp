#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "ofxAsio.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class cinderTcpClientApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void cinderTcpClientApp::setup()
{
}

void cinderTcpClientApp::mouseDown( MouseEvent event )
{
}

void cinderTcpClientApp::update()
{
}

void cinderTcpClientApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( cinderTcpClientApp, RendererGl, [=](cinder::app::App::Settings* settings) {settings->setConsoleWindowEnabled(); })
