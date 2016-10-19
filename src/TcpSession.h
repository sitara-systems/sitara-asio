#pragma once

#include "asio/asio.hpp"
#include "Datagram.h"

namespace ofxAsio {
	class TcpSession {
	public:
		~TcpSession();
		static std::shared_ptr<TcpSession> make(asio::io_service& service);
		asio::ip::tcp::socket& getSocket();
	protected:
		TcpSession(asio::io_service& service);
		std::shared_ptr<Datagram> mIncomingDatagram;
		std::string mIncomingMessage;
		asio::ip::tcp::socket mSocket;
	};
}