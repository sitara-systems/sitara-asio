#pragma once

#include <thread>
#include <chrono>
#include "asio/asio.hpp"
#include "asio/system_timer.hpp"
#include "Datagram.h"

namespace ofxAsio {
	class TcpClient {
	public:
		~TcpClient();
		static std::shared_ptr<TcpClient> make();
		void connect(std::string ip_address, int port);
		void disconnect();
		char getTerminator();
		void setTerminator(char terminator);
		void send(std::string message);
		void addOnSendFn(std::function<void(std::string msg)> response);
		void addOnReceiveFn(std::function<void(std::string msg)> response);
	protected:
		TcpClient();
		void init();
		void tryConnect(asio::ip::tcp::resolver::iterator resolver);
		void onConnect(const asio::error_code& ec, asio::ip::tcp::resolver::iterator endpoint_iter);
		void receive();
		void onReceive(const asio::error_code& ec, size_t bytes_received);
		void sendHeartbeat();
		void onWrite(const asio::error_code& e, size_t bytes_received, std::string message);
		//void checkDeadline(const asio::error_code& error);
		bool mIsConnected;
		char mTerminator;
		asio::streambuf input_buffer_;
		asio::io_service mService;
        asio::io_service::work mWork;
		std::thread mServiceThread;
		asio::ip::tcp::socket mSocket;
		std::shared_ptr<asio::ip::tcp::resolver> mResolver;
		//asio::system_timer mTimer;
		//asio::system_timer mHeartbeatTimer;
		std::shared_ptr<Datagram> mIncomingDatagram;
		std::string mIncomingMessage;
		std::vector<std::function<void(std::string msg)> > mOnSendFns;
		std::vector<std::function<void(std::string msg)> > mOnReceiveFns;
	};
}