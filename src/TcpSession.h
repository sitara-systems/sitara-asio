#pragma once

#include "asio/asio.hpp"

namespace midnight {
	namespace sockets {
		class TcpSession {
		public:
			~TcpSession();
			static std::shared_ptr<TcpSession> make(asio::io_service& service);
			void start();
			asio::ip::tcp::socket& getSocket();
			char getTerminator();
			void setTerminator(char terminator);
		protected:
			TcpSession(asio::io_service& service);
			void setIncomingBufferSize(std::size_t buffer_size);
			void receive();
			void onWrite(const asio::error_code& error, std::size_t bytesReceived);
			void onReceive(const asio::error_code& error, std::size_t bytesReceived);
			std::string mIncomingMessage;
			asio::ip::tcp::socket mSocket;
			bool mIsConnected;
			char mTerminator;
		};
	}
}