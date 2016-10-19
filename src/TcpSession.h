#pragma once

#include "asio/asio.hpp"
#include "Datagram.h"

namespace ofxAsio {
	class TcpSession {
	public:
		~TcpSession();
		static std::shared_ptr<TcpSession> make(asio::io_service& service);
		void start();
		void receive();
		asio::ip::tcp::socket& getSocket();
		void addOnReceiveFn(std::function<void(std::shared_ptr<Datagram> msg)> response);
		void addOnResponseFn(std::function<void(std::shared_ptr<Datagram> msg)> response);
	protected:
		TcpSession(asio::io_service& service);
		void onReceive(const asio::error_code& error, size_t bytes_received);
		void onResponse(const asio::error_code& error);
		std::shared_ptr<Datagram> mIncomingDatagram;
		std::string mIncomingMessage;
		asio::ip::tcp::socket mSocket;
		bool mIsConnected;
		std::vector<std::function<void(std::shared_ptr<Datagram> msg)> > mOnReceiveFns;
		std::vector<std::function<void(std::shared_ptr<Datagram> msg)> > mOnResponseFns;
	};
}