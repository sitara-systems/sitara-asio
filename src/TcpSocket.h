#pragma once

#include "asio/asio.hpp"
#include "Endpoint.h"
#include "Datagram.h"
#include <memory>
#include <thread>
#include <array>
#include <string>

namespace ofxAsio {

	class TcpSocket {
	public:
		TcpSocket();
		TcpSocket(int port);
		TcpSocket(std::string localAddress, int port);
		~TcpSocket();
	protected:
		void init();
		asio::io_service mService;
		std::thread mServiceThread;
		asio::io_service::work mWork;
		asio::ip::tcp::socket mSocket;
		asio::ip::tcp::endpoint mLocalEndpoint;
		std::shared_ptr<Datagram> mIncomingDatagram;
		asio::ip::tcp::endpoint mIncomingEndpoint;
		std::string mIncomingMessage;
	};
  
}


