#include "TcpServer.h"

using namespace ofxAsio;

std::shared_ptr<TcpServer> TcpServer::make(int port) {
	std::shared_ptr<TcpServer> Server(new TcpServer(port));
	return Server;
}

TcpServer::TcpServer(int port) : mService(), mSocket(mService), mWork(mService), mAcceptor(mService) {
	init(port);
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

void TcpServer::onConnect(std::vector<std::shared_ptr<TcpSession>>::iterator session_iter, const asio::error_code& error) {
	if (!error) {
		std::printf("ofxAsio::TcpServer -- Connection from %s received!\n", (*session_iter)->getSocket().remote_endpoint().address().to_string().c_str());

		(*session_iter)->start();
		createSession();

		/*
		// Write a response
		std::string msg = "Hello World!\r\n\r\n";
		asio::mutable_buffers_1 buffer = asio::mutable_buffers_1((char*)msg.c_str(), msg.size());

		asio::async_write((*session_iter)->getSocket(), buffer, 
			[this, session_iter](const asio::error_code &error, std::size_t bytesReceived) {
			onWrite(session_iter, error, bytesReceived);
		});

		// begin listening
		receive(session_iter);
		*/
	}
	else {
		std::printf("ofxAsio::TcpServer::onConnect -- Error receiving data. %s\n", error.message().c_str());
		mSessions.erase(session_iter);
	}
}

void TcpServer::createSession() {
	std::printf("ofxAsio::TcpServer -- Creating new session...\n");

	std::shared_ptr<TcpSession> newSession = TcpSession::make(mService);
	std::vector<std::shared_ptr<TcpSession>>::iterator iterator = mSessions.insert(mSessions.end(), newSession);

	mAcceptor.async_accept(newSession->getSocket(),
		[this, iterator](const asio::error_code &error) {
		onConnect(iterator, error);
	});
}

/*
void TcpServer::onWrite(std::vector<std::shared_ptr<TcpSession>>::iterator session_iter, const asio::error_code& error, std::size_t bytesReceived) {
	if (!error) {
		std::printf("Sent message\n");
	}
	else {
		std::printf("We had an error: %s\n", error.message().c_str());
		mSessions.erase(session_iter);
	}
}

void TcpServer::onRead(std::vector<std::shared_ptr<TcpSession>>::iterator session_iter, const asio::error_code& error, std::size_t bytesReceived) {
	if (bytesReceived > 0) {
			std::istream is(&(*session_iter)->getBuffer());
			std::string line;
			std::getline(is, line);
			std::printf("Message Received: %s\n", line);
	}

	if (!error) {
		std::printf("ofxAsio::TcpSession::onReceive -- received message\n");
		receive(session_iter);
	}
	else {
		std::printf("ofxAsio::TcpSession::onReceive -- Error receiving data. %s\n", error.message().c_str());;
	}
}

void TcpServer::receive(std::vector<std::shared_ptr<TcpSession>>::iterator session_iter) { 
	asio::async_read_until((*session_iter)->getSocket(), (*session_iter)->getBuffer(), "\0",
		[this, session_iter](const asio::error_code &error, std::size_t bytes_received) {
		if (bytes_received) {
			setIncomingBufferSize(bytes_received);
			(*session_iter)->getDatagram()->setData(mIncomingMessage);
		}
		onRead(session_iter, error, bytes_received);
	});

}

void TcpServer::setIncomingBufferSize(std::size_t buffer_size) {
	mIncomingMessage.resize(buffer_size);
}
*/