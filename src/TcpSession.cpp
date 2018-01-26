#include "TcpSession.h"

<<<<<<< HEAD
using namespace midnight::sockets;
=======
using namespace ofxAsio;
>>>>>>> 00371c6502e9a17e37b9c6febbe8352dabfb7372

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
<<<<<<< HEAD
	std::printf("midnight::sockets::TcpSession -- TcpSession ended.\n");
}

void TcpSession::start() {
	std::printf("midnight::sockets::TcpSession -- TcpSession starting.\n");
=======
	std::printf("ofxAsio::TcpSession -- TcpSession ended.\n");
}

void TcpSession::start() {
	std::printf("ofxAsio::TcpSession -- TcpSession starting.\n");
>>>>>>> 00371c6502e9a17e37b9c6febbe8352dabfb7372
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

<<<<<<< HEAD
void TcpSession::onWrite(const asio::error_code& error, std::size_t bytesReceived) {
	if (!error && mIsConnected) {
		receive();
	}
	else {
		std::printf("midnight::sockets::TcpSession::onWrite -- Error writing data. %s\n", error.message().c_str());;
=======
void TcpSession::addOnReceiveFn(std::function<void(std::string msg)> response) {
	mOnReceiveFns.push_back(response);
}

void TcpSession::addOnSendFn(std::function<void(std::string msg)> response) {
	mOnSendFns.push_back(response);
}

void TcpSession::onWrite(const asio::error_code& error, std::size_t bytesReceived, std::string message) {
	if (!error && mIsConnected) {
		for (auto& callback : mOnSendFns) {
			callback(message);
		}
		receive();
	}
	else {
		std::printf("ofxAsio::TcpSession::onWrite -- Error writing data. %s\n", error.message().c_str());;
>>>>>>> 00371c6502e9a17e37b9c6febbe8352dabfb7372
	}
}

void TcpSession::onReceive(const asio::error_code& error, std::size_t bytesReceived) {
	if (bytesReceived) {
<<<<<<< HEAD
		std::printf("midnight::sockets::TcpSession::onReceive -- received message %s in %d bytes\n", mIncomingMessage.c_str(), bytesReceived);
		if (mIncomingMessage[bytesReceived - 1] == mTerminator) {
			std::printf("midnight::sockets::TcpSession::onReceive -- received terminator charactder %s\n", mTerminator);
			--bytesReceived;
			setIncomingBufferSize(bytesReceived);
			mIsConnected = false;
=======
		//std::printf("ofxAsio::TcpSession::onReceive -- received message %s in %d bytes\n", mIncomingMessage.c_str(), bytesReceived);
		if (mIncomingMessage[bytesReceived - 1] == mTerminator) {
			std::printf("ofxAsio::TcpSession::onReceive -- received terminator character %s\n", mTerminator);
			--bytesReceived;
			setIncomingBufferSize(bytesReceived);
>>>>>>> 00371c6502e9a17e37b9c6febbe8352dabfb7372
		}
	}

	if (!error && mIsConnected) {
<<<<<<< HEAD
		asio::async_write(mSocket, asio::buffer(mIncomingMessage.c_str(), mIncomingMessage.size()),
			[this](const asio::error_code &error, std::size_t bytes_received) {
				onWrite(error, bytes_received);
		});
	}
	else {
		std::printf("midnight::sockets::TcpSession::onReceive -- Error receiving data. %s\n", error.message().c_str());;
=======
		for (auto& callback : mOnReceiveFns) {
			callback(mIncomingMessage);
		}

		mIncomingMessage += mTerminator;
		asio::async_write(mSocket, asio::buffer(mIncomingMessage.c_str(), mIncomingMessage.size()),
			[this](const asio::error_code &error, std::size_t bytes_received) {
				onWrite(error, bytes_received, mIncomingMessage);
		});

	}
	else {
		std::printf("ofxAsio::TcpSession::onReceive -- Error receiving data. %s\n", error.message().c_str());;
>>>>>>> 00371c6502e9a17e37b9c6febbe8352dabfb7372
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


