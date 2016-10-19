#include "TcpServer.h"

using namespace ofxAsio;

std::shared_ptr<TcpServer> TcpServer::make(int port) {
	std::shared_ptr<TcpServer> Server(new TcpServer(port));
	return Server;
}

std::shared_ptr<TcpServer> TcpServer::make(std::string localAddress, int port) {
	std::shared_ptr<TcpServer> Server(new TcpServer(localAddress, port));
	return Server;
}

TcpServer::TcpServer(int port) : mSocket(mService) {
	init("", port);
}

TcpServer::TcpServer(std::string localAddress, int port) : mSocket(mService) {
	init(localAddress, port);
}

TcpServer::~TcpServer() {
	mSocket.cancel();
	mService.stop();
	if (mServiceThread.joinable()) {
		mServiceThread.join();
	}
}

void TcpServer::start() {
	//std::printf("ofxAsio::TcpServer -- listening for messages at %s:%d\n", mLocalEndpoint.getIpAddress().c_str(), mLocalEndpoint.getPort());
	createSession();
}

void TcpServer::onConnect(std::shared_ptr<TcpSession> session, const asio::error_code& error) {
	if (!error) {
		session->start();
		createSession();
	}
}


void TcpServer::init(std::string localAddress, int port) {
		if (localAddress == "") {
		mLocalEndpoint = asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port);
	}
	else {
		mLocalEndpoint = asio::ip::tcp::endpoint(asio::ip::address::from_string(localAddress), port);
	}

	std::printf("ofxAsio::TcpServer -- Creating endpoint %s:%d ...\n", mLocalEndpoint.address().to_string().c_str(), mLocalEndpoint.port());

	mAcceptor = std::shared_ptr<asio::ip::tcp::acceptor>(new asio::ip::tcp::acceptor(mService, mLocalEndpoint));

	mServiceThread = std::thread([&] {
		mService.run();
	});

}

void TcpServer::createSession() {
	std::shared_ptr<TcpSession> session = TcpSession::make(mService);
	asio::error_code error;

	mAcceptor->async_accept(mSocket, 
		[this, session](const asio::error_code &error) {
		onConnect(session, error);
	});

}