#pragma once

#include "asio/asio.hpp"
#include "../Endpoint.h"
#include "../Datagram.h"
#include <memory>
#include <thread>
#include <array>
#include <string>

namespace sitara {
	namespace udp {
		class UdpSocket {
		public:
			UdpSocket();
			UdpSocket(int port);
			UdpSocket(std::string localAddress, int port);
			~UdpSocket();
			void setIncomingBufferSize(std::size_t buffer_size);
			void addOnReceiveFn(std::function<void(std::shared_ptr<Datagram> msg)> response);
			void addOnSendFn(std::function<void(std::shared_ptr<Datagram> msg)> response);
			const Endpoint& getEndpoint();
			const std::string& getIpAddress();
			const int& getPortNumber();
		protected:
			void init();
			void sendDatagram(std::shared_ptr<Datagram> msg);
			void receive();
			void onReceive(const asio::error_code &error, std::size_t bytes_received);
			asio::io_service mService;
			std::thread mServiceThread;
			asio::io_service::work mWork;
			asio::ip::udp::socket mSocket;
			Endpoint mLocalEndpoint;
			std::size_t mMaxBufferSize;
			std::shared_ptr<Datagram> mIncomingDatagram;
			asio::ip::udp::endpoint mIncomingEndpoint;
			std::vector<unsigned char> mIncomingMessage;
			std::vector<std::function<void(std::shared_ptr<Datagram> msg)> > mOnReceiveFns;
			std::vector<std::function<void(std::shared_ptr<Datagram> msg)> > mOnSendFns;
		};

	}
}
