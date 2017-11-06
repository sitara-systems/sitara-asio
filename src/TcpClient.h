#pragma once

#include <thread>
#include <chrono>
#include "asio/asio.hpp"
#include "asio/system_timer.hpp"
#include "Datagram.h"

namespace midnight {
	namespace sockets {
		class TcpClient {
		public:
			~TcpClient();
			static std::shared_ptr<TcpClient> make();
			void connect(std::string ip_address, int port);
			void disconnect();
			void send(std::string& message);
			//		void addOnSendFn(std::function<void(std::shared_ptr<Datagram> msg)> response);
			//		void addOnResponseFn(std::function<void(std::shared_ptr<Datagram> msg)> response);
		protected:
			TcpClient();
			void init();
			void start_connect(asio::ip::tcp::resolver::iterator resolver);
			void handle_connect(const asio::error_code& ec, asio::ip::tcp::resolver::iterator endpoint_iter);
			void start_read();
			void handle_read(const asio::error_code& ec, size_t bytes_received);
			void start_write();
			void handle_write(const asio::error_code& e, size_t bytes_receivedc);
			void check_deadline(const asio::error_code& error);
			//		void onReceive(const asio::error_code& error, size_t bytes_received);
			//		void onResponse(const asio::error_code& error);
			bool mIsConnected;
			asio::streambuf input_buffer_;
			asio::io_service mService;
			asio::io_service::work mWork;
			std::thread mServiceThread;
			asio::ip::tcp::socket mSocket;
			std::shared_ptr<asio::ip::tcp::resolver> mResolver;
			asio::system_timer mTimer;
			asio::system_timer mHeartbeatTimer;
			std::shared_ptr<Datagram> mIncomingDatagram;
			std::string mIncomingMessage;
			std::vector<std::function<void(std::shared_ptr<Datagram> msg)> > mOnSendFns;
			std::vector<std::function<void(std::shared_ptr<Datagram> msg)> > mOnResponseFns;
		};
	}
}