#include "TcpSession.h"

using namespace ofxAsio;

std::shared_ptr<TcpSession> TcpSession::make(asio::io_service& service) {
	std::shared_ptr<TcpSession> session = std::shared_ptr<TcpSession>(new TcpSession(service));
	return session;
}

TcpSession::TcpSession(asio::io_service& service) : mSocket(service), mIsConnected(false) {
}


TcpSession::~TcpSession() {
	std::printf("ofxAsio::TcpSession::onReceive -- TcpSession ended.\n");
}

void TcpSession::start() {
	std::printf("ofxAsio::TcpSession::onReceive -- Starting TcpSession.\n");

	mIsConnected = true;
	receive();
}

void TcpSession::receive() {
	asio::mutable_buffers_1 buffer = asio::mutable_buffers_1((char*)mIncomingMessage.c_str(), mIncomingMessage.size());

	mSocket.async_read_some(buffer, 
		[this](const asio::error_code &error, std::size_t bytes_received) {
		mIncomingDatagram->setData(mIncomingMessage);
		onReceive(error, bytes_received);
	});

}

void TcpSession::onReceive(const asio::error_code& error, size_t bytes_received) {
	if (mIncomingMessage[bytes_received-1] == '\0') {
		std::printf("ofxAsio::TcpSession::onReceive -- Client sent a terminator.\n");
		--bytes_received;
		mIsConnected = false;
	}

	if (!error && bytes_received > 0) {
		for (auto callback : mOnReceiveFns) {
			callback(mIncomingDatagram);
		}
		std::printf("ofxAsio::TcpSession::onReceive -- Writing back to client.\n");
		asio::async_write(mSocket, asio::buffer(mIncomingMessage, mIncomingMessage.size()),
			[this](const asio::error_code& error, std::size_t bytes_transferred) {
			onResponse(error);
		});
	}
	else {
		std::printf("ofxAsio::TcpSession::onReceive -- Error receiving data. %s\n", error.message().c_str());;
	}
}

void TcpSession::onResponse(const asio::error_code& error) {
	if (!error && mIsConnected) {
		std::printf("ofxAsio::TcpSession::onReceive -- Ready for a new read.\n");
		receive();
	}

	for (auto callback : mOnReceiveFns) {
		callback(mIncomingDatagram);
	}
}

asio::ip::tcp::socket& TcpSession::getSocket() {
	return mSocket;
}

void TcpSession::addOnReceiveFn(std::function<void(std::shared_ptr<Datagram> msg)> response) {
	mOnReceiveFns.push_back(response);
}

void TcpSession::addOnResponseFn(std::function<void(std::shared_ptr<Datagram> msg)> response) {
	mOnResponseFns.push_back(response);
}
