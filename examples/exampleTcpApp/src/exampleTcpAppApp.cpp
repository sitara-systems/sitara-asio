#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "Tcp.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class exampleTcpAppApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;

	std::shared_ptr<sitara::tcp::TcpServer> mServer;
	std::shared_ptr<sitara::tcp::TcpClient> mClient;
};

void exampleTcpAppApp::setup() {
	mServer = sitara::tcp::TcpServer::make(7331);
	mServer->start();

	mClient = sitara::tcp::TcpClient::make();
	mClient->connect("127.0.0.1", 7331);
}

void exampleTcpAppApp::mouseDown( MouseEvent event ) {
}

void exampleTcpAppApp::update() {
	if (ci::app::getElapsedFrames() % 60 == 0) {
		mClient->send("Hello world");
	}
}

void exampleTcpAppApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( exampleTcpAppApp, RendererGl, [=](cinder::app::App::Settings* settings) {settings->setConsoleWindowEnabled(); })
