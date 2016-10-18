#include "Session.h"

using namespace ofxAsio;

std::shared_ptr<Session> Session::make(asio::io_service& service) {
	std::shared_ptr<Session> session = std::shared_ptr<Session>(new Session(service));
	return session;
}

Session::Session(asio::io_service& service) : mSocket(service), mIsConnected(false) {
}


Session::~Session() {
	std::printf("ofxAsio::Session::onReceive -- Session ended.\n");
}

void Session::start() {
	std::printf("ofxAsio::Session::onReceive -- Starting Session.\n");

	mIsConnected = true;
	receive();
}

void Session::receive() {
	asio::mutable_buffers_1 buffer = asio::mutable_buffers_1((char*)mIncomingMessage.c_str(), mIncomingMessage.size());

	mSocket.async_read_some(buffer, 
		[this](const asio::error_code &error, std::size_t bytes_received) {
		mIncomingDatagram->setData(mIncomingMessage);
		onReceive(error, bytes_received);
	});

}

void Session::onReceive(const asio::error_code& error, size_t bytes_received) {
	if (mIncomingMessage[bytes_received-1] == '\0') {
		std::printf("ofxAsio::Session::onReceive -- Client sent a terminator.\n");
		--bytes_received;
		mIsConnected = false;
	}

	if (!error && bytes_received > 0) {
		for (auto callback : mOnReceiveFns) {
			callback(mIncomingDatagram);
		}
		std::printf("ofxAsio::Session::onReceive -- Writing back to client.\n");
		asio::async_write(mSocket, asio::buffer(mIncomingMessage, mIncomingMessage.size()),
			[this](const asio::error_code& error, std::size_t bytes_transferred) {
			onResponse(error);
		});
	}
	else {
		std::printf("ofxAsio::Session::onReceive -- Error receiving data. %s\n", error.message().c_str());;
	}
}

void Session::onResponse(const asio::error_code& error) {
	if (!error && mIsConnected) {
		std::printf("ofxAsio::Session::onReceive -- Ready for a new read.\n");
		receive();
	}

	for (auto callback : mOnReceiveFns) {
		callback(mIncomingDatagram);
	}
}

asio::ip::tcp::socket& Session::getSocket() {
	return mSocket;
}

void Session::addOnReceiveFn(std::function<void(std::shared_ptr<Datagram> msg)> response) {
	mOnReceiveFns.push_back(response);
}

void Session::addOnResponseFn(std::function<void(std::shared_ptr<Datagram> msg)> response) {
	mOnResponseFns.push_back(response);
}
