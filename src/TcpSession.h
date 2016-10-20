#pragma once

#include "asio/asio.hpp"
#include "Datagram.h"

namespace ofxAsio {
	class TcpSession {
	public:
		~TcpSession();
		static std::shared_ptr<TcpSession> make(asio::io_service& service);
		void start();
		asio::ip::tcp::socket& getSocket();
		std::shared_ptr<Datagram> getDatagram();
	protected:
		TcpSession(asio::io_service& service);
		void setIncomingBufferSize(std::size_t buffer_size);
		void receive();
		void onWrite(const asio::error_code& error, std::size_t bytesReceived);
		void onRead(const asio::error_code& error, std::size_t bytesReceived);
		std::shared_ptr<Datagram> mIncomingDatagram;
		std::string mIncomingMessage;
		asio::ip::tcp::socket mSocket;
		bool mIsConnected;
	};
}