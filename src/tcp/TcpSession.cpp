#include "TcpSession.h"

using namespace ofxAsio;
using namespace ofxAsio::tcp;

std::shared_ptr<TcpSession> TcpSession::make(asio::io_service& service) {
	std::shared_ptr<TcpSession> session = std::shared_ptr<TcpSession>(new TcpSession(service));
	return session;
}

TcpSession::TcpSession(asio::io_service& service) : mSocket(service) {
	mTerminator = '\0';
	mIsConnected = false;
	setIncomingBufferSize(1024);
}


TcpSession::~TcpSession() {
	std::printf("ofxAsio::sockets::TcpSession -- TcpSession ended.\n");
}

void TcpSession::start() {
	std::printf("ofxAsio::sockets::TcpSession -- TcpSession starting.\n");
	mIsConnected = true;
	receive();
}

asio::ip::tcp::socket& TcpSession::getSocket() {
	return mSocket;
}

char TcpSession::getTerminator() {
	return mTerminator;
}

void TcpSession::setTerminator(char terminator) {
	mTerminator = terminator;
}

void TcpSession::onWrite(const asio::error_code& error, std::size_t bytesReceived) {
	if (!error && mIsConnected) {
		receive();
	}
	else {
		std::printf("ofxAsio::sockets::TcpSession::onWrite -- Error writing data. %s\n", error.message().c_str());;
	}
}

void TcpSession::onReceive(const asio::error_code& error, std::size_t bytesReceived) {
	if (bytesReceived) {
		std::printf("ofxAsio::sockets::TcpSession::onReceive -- received message %s in %d bytes\n", mIncomingMessage.c_str(), bytesReceived);
		if (mIncomingMessage[bytesReceived - 1] == mTerminator) {
			std::printf("ofxAsio::sockets::TcpSession::onReceive -- received terminator charactder %s\n", mTerminator);
			--bytesReceived;
			setIncomingBufferSize(bytesReceived);
			mIsConnected = false;
		}
	}

	if (!error && mIsConnected) {
		asio::async_write(mSocket, asio::buffer(mIncomingMessage.c_str(), mIncomingMessage.size()),
			[this](const asio::error_code &error, std::size_t bytes_received) {
				onWrite(error, bytes_received);
		});
	}
	else {
		std::printf("ofxAsio::sockets::TcpSession::onReceive -- Error receiving data. %s\n", error.message().c_str());;
	}
}

void TcpSession::receive() {
	asio::mutable_buffers_1 buffer = asio::mutable_buffers_1((char*)mIncomingMessage.c_str(), mIncomingMessage.size());

	mSocket.async_read_some(buffer,
		[this](const asio::error_code &error, std::size_t bytesReceived) {
		if (bytesReceived) {
			setIncomingBufferSize(bytesReceived);
		}
		onReceive(error, bytesReceived);
	});

}

void TcpSession::setIncomingBufferSize(std::size_t buffer_size) {
	mIncomingMessage.resize(buffer_size);
}
