#include "TcpSession.h"

using namespace ofxAsio;

std::shared_ptr<TcpSession> TcpSession::make(asio::io_service& service) {
	std::shared_ptr<TcpSession> session = std::shared_ptr<TcpSession>(new TcpSession(service));
	return session;
}

TcpSession::TcpSession(asio::io_service& service) : mSocket(service) {
	mIncomingDatagram = std::shared_ptr<Datagram>(new Datagram());
	mIsConnected = false;
}


TcpSession::~TcpSession() {
	std::printf("ofxAsio::TcpSession -- TcpSession ended.\n");
}

void TcpSession::start() {
	std::printf("ofxAsio::TcpSession -- TcpSession starting.\n");
	mIsConnected = true;
	receive();
}

asio::ip::tcp::socket& TcpSession::getSocket() {
	return mSocket;
}

std::shared_ptr<Datagram> TcpSession::getDatagram() {
	return mIncomingDatagram;
}

void TcpSession::onWrite(const asio::error_code& error, std::size_t bytesReceived) {
	if (!error && mIsConnected) {
		std::printf("Sent message\n");
	}
	else {
		std::printf("We had an error: %s\n", error.message().c_str());
	}
}

void TcpSession::onRead(const asio::error_code& error, std::size_t bytesReceived) {
	if (bytesReceived) {
		std::printf("ofxAsio::TcpSession::onReceive -- received %d bytes", bytesReceived);
	}

	if (bytesReceived && mIncomingMessage[bytesReceived - 1] == '\0') {
		std::printf("ofxAsio::TcpSession::onReceive -- received message %s", mIncomingDatagram->getDataAsString().c_str());
		--bytesReceived;
		mIsConnected = false;
	}

	if (!error && mIsConnected) {
		receive();
	}
	else {
		std::printf("ofxAsio::TcpSession::onReceive -- Error receiving data. %s\n", error.message().c_str());;
		delete this;
	}
}

void TcpSession::receive() {
	std::printf("ofxAsio::TcpSession::onReceive -- receive()");
	mSocket.async_read_some(asio::mutable_buffers_1((char*)mIncomingMessage.c_str(), mIncomingMessage.size()),
		[this](const asio::error_code &error, std::size_t bytes_received) {
		if (bytes_received) {
			setIncomingBufferSize(bytes_received);
			mIncomingDatagram->setData(mIncomingMessage);
		}
		onRead(error, bytes_received);
	});

}

void TcpSession::setIncomingBufferSize(std::size_t buffer_size) {
	mIncomingMessage.resize(buffer_size);
}


