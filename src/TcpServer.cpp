#include "TcpServer.h"

using namespace ofxAsio;

std::shared_ptr<TcpServer> TcpServer::make(int port) {
	std::shared_ptr<TcpServer> Server(new TcpServer(port));
	return Server;
}

TcpServer::TcpServer(int port) : mService(), mSocket(mService), mAcceptor(mService) {
	init(port);
}

TcpServer::~TcpServer() {
	mSocket.cancel();
	mService.stop();
//	if (mServiceThread.joinable()) {
//		mServiceThread.join();
//	}
}

void TcpServer::start() {
	//std::printf("ofxAsio::TcpServer -- listening for messages at %s:%d\n", mLocalEndpoint.getIpAddress().c_str(), mLocalEndpoint.getPort());
	createSession();
}

void TcpServer::onConnect(std::vector<std::shared_ptr<TcpSession>>::iterator session_iter, const asio::error_code& error) {
	if (!error) {
		std::printf("ofxAsio::TcpServer -- Connection from %s received!\n", (*session_iter)->getSocket().remote_endpoint().address().to_string().c_str());

		// Write a response
		//auto buff = std::make_shared<std::string>("Hello World!\r\n\r\n");

		//asio::async_write((*session_iter)->getSocket(), asio::buffer(*buff), 
		//	[this, session_iter](const asio::error_code &error, std::size_t bytesReceived) {
		//	onWrite(session_iter, error, bytesReceived);
		//});

		// begin listening
		//receive(session_iter);

	}
	else {
		std::printf("ofxAsio::TcpServer::onConnect -- Error receiving data. %s\n", error.message().c_str());
		mSessions.erase(session_iter);
	}
}

void TcpServer::onWrite(std::vector<std::shared_ptr<TcpSession>>::iterator session_iter, const asio::error_code& error, std::size_t bytesReceived) {
	if (!error) {
		std::printf("Sent message\n");
		if ((*session_iter)->getSocket().is_open()) {

		}
	}
	else {
		std::printf("We had an error: %s\n", error.message());
		mSessions.erase(session_iter);
	}
}

void TcpServer::onRead(std::vector<std::shared_ptr<TcpSession>>::iterator session_iter, const asio::error_code& error, std::size_t bytesReceived) {
	if (mIncomingMessage[bytesReceived - 1] == '\0') {
		std::printf("ofxAsio::TcpSession::onReceive -- Client sent a terminator.\n");
		--bytesReceived;
	}

	if (!error && bytesReceived > 0) {
		std::printf("ofxAsio::TcpSession::onReceive -- received message\n");
		receive(session_iter);
	}
	else {
		std::printf("ofxAsio::TcpSession::onReceive -- Error receiving data. %s\n", error.message().c_str());;
	}
}



void TcpServer::init(int port) {
	mLocalEndpoint = asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port);

	std::printf("ofxAsio::TcpServer -- Creating endpoint %s:%d ...\n", mLocalEndpoint.address().to_string().c_str(), mLocalEndpoint.port());

	mAcceptor.open(mLocalEndpoint.protocol());
	mAcceptor.set_option(asio::ip::tcp::acceptor::reuse_address(true));
	mAcceptor.bind(mLocalEndpoint);
	mAcceptor.listen();

	mServiceThread = std::thread([&] {
		mService.run();
	});

}

void TcpServer::createSession() {
	std::printf("ofxAsio::TcpServer -- Creating new session...\n");

	std::shared_ptr<TcpSession> newSession = TcpSession::make(mService);
	std::vector<std::shared_ptr<TcpSession>>::iterator iterator = mSessions.insert(mSessions.end(), newSession);

	mAcceptor.async_accept(newSession->getSocket(), 
		[this, iterator](const asio::error_code &error) {
		std::printf("Async Accept\n");
		onConnect(iterator, error);
	});
}

void TcpServer::receive(std::vector<std::shared_ptr<TcpSession>>::iterator session_iter) {
	asio::mutable_buffers_1 buffer = asio::mutable_buffers_1((char*)mIncomingMessage.c_str(), mIncomingMessage.size());
	mIncomingDatagram = std::shared_ptr<Datagram>(new Datagram());

	mSocket.async_read_some(buffer,
		[this, session_iter](const asio::error_code &error, std::size_t bytes_received) {
		mIncomingDatagram->setData(mIncomingMessage);
		onRead(session_iter, error, bytes_received);
	});

}