#include "TcpSession.h"

using namespace ofxAsio;

std::shared_ptr<TcpSession> TcpSession::make(asio::io_service& service) {
	std::shared_ptr<TcpSession> session = std::shared_ptr<TcpSession>(new TcpSession(service));
	return session;
}

TcpSession::TcpSession(asio::io_service& service) : mSocket(service) {
}


TcpSession::~TcpSession() {
	std::printf("ofxAsio::TcpSession::onReceive -- TcpSession ended.\n");
}

asio::ip::tcp::socket& TcpSession::getSocket() {
	return mSocket;
}