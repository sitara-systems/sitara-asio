#pragma once

#include "asio/asio.hpp"
#include "UdpSocket.h"

/*
To be used as such:

sender = UdpSender(8080); //local port
std::shared_ptr<Datagram> datagram(new Datagram("Hello world", "192.168.0.27", 8080));
sender.send(datagram)

 */
namespace midnight {
	namespace sockets {
		class UdpSender : public UdpSocket {
		public:
			static std::shared_ptr<UdpSender> make();
			static std::shared_ptr<UdpSender> make(int port);
			static std::shared_ptr<UdpSender> make(std::string localAddress, int port);
			~UdpSender();
			void send(std::shared_ptr<Datagram> datagram);
			void send_to(std::string ip_address, int port, std::string message);
			void send_to(std::string ip_address, int port, std::vector<unsigned char> data);
		protected:
			UdpSender();
			UdpSender(int port);
			UdpSender(std::string localAddress, int port);
			void on_send(asio::error_code errorCode, std::size_t bytes_transferred) {};
		};

	}
}
