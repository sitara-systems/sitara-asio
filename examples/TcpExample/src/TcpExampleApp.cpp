#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "Tcp.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace sitara;
using namespace sitara::tcp;

class TcpExampleApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;

	std::shared_ptr<sitara::tcp::TcpServer> mServer;
	std::shared_ptr<sitara::tcp::TcpClient> mClient;
};

void TcpExampleApp::setup() {
	mServer = TcpServer::make(7331);
	mServer->start();

	mClient = TcpClient::make();
	mClient->connect("127.0.0.1", 7331);
}

void TcpExampleApp::mouseDown( MouseEvent event )
{
}	

void TcpExampleApp::update() {
	if (ci::app::getElapsedFrames() % 60 == 0) {
		mClient->send("Hello world");
	}
}

void TcpExampleApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( TcpExampleApp, RendererGl )
