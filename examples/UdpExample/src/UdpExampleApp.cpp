#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "Udp.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class UdpExampleApp : public App {
public:
	void setup() override;
	void mouseDown(MouseEvent event) override;
	void update() override;
	void draw() override;

	std::shared_ptr<sitara::udp::UdpSender> mSender;
	std::shared_ptr<sitara::udp::UdpReceiver> mReceiver;
};

void UdpExampleApp::setup() {
	mSender = sitara::udp::UdpSender::make();
	mSender->addOnSendFn([](std::shared_ptr<sitara::Datagram> datagram) {
		std::printf("Sent message '%s' to %s:%d!\n", datagram->getDataAsString().c_str(), datagram->getIpAddress().c_str(), datagram->getPort());
	});

	mReceiver = sitara::udp::UdpReceiver::make("127.0.0.1", 7331); // or UdpReceiver("192.168.0.17", 8080) to specify interface
	mReceiver->addOnReceiveFn([](std::shared_ptr<sitara::Datagram> datagram) {
		std::printf("Asio callback -- received %d bytes from %s:%d\n", datagram->getDataLength(), datagram->getIpAddress().c_str(), datagram->getPort());
	});
	mReceiver->start();
}

void UdpExampleApp::mouseDown(MouseEvent event)
{
}

void UdpExampleApp::update() {
	if (ci::app::getElapsedFrames() % 300 == 0) {
		std::shared_ptr<sitara::Datagram> datagram = std::make_shared<sitara::Datagram>("Hello world", "127.0.0.1", 7331);
		mSender->send(datagram);
	}


	if (ci::app::getElapsedFrames() % 120 == 0) {
		std::printf("Application updating!  Work is still happening while we wait for a received message.\n");
	}
}

void UdpExampleApp::draw()
{
	gl::clear(Color(0, 0, 0));
}

CINDER_APP(UdpExampleApp, RendererGl, [=](cinder::app::App::Settings* settings) {settings->setConsoleWindowEnabled(); })
