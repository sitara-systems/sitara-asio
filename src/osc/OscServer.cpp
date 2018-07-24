#include "OscServer.h"

using namespace ofxAsio::osc;

std::shared_ptr<OscServer> OscServer::make(int port) {
	std::shared_ptr<OscServer> server(new OscServer(port));
	return server;
}

std::shared_ptr<OscServer> OscServer::make(std::string localAddress, int port) {
	std::shared_ptr<OscServer> server(new OscServer(localAddress, port));
	return server;
}

void OscServer::start() {
	listen(
		[](asio::error_code error, protocol::endpoint endpoint) -> bool {
		if (error) {
			return false;
		}
		else
			return true;
	});

	mServiceThread = std::thread([&] {
		mService.run();
	});
}

OscServer::OscServer(int port) : ReceiverUdp(port, asio::ip::udp::v4(), mService), mWork(mService) {
	init();
}

OscServer::OscServer(std::string localAddress, int port) : ReceiverUdp(port, asio::ip::udp::v4(), mService), mWork(mService) {
	init();
}

OscServer::~OscServer() {
	mService.stop();
	if (mServiceThread.joinable()) {
		mServiceThread.join();
	}
}

void OscServer::init() {
	try {
		bind();
	}
	catch (const cinder::osc::Exception &ex) {
		CI_LOG_E("Error binding: " << ex.what() << " val: " << ex.value());
	}
}