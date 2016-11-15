#pragma once

#include "asio/asio.hpp"
#include "UdpSocket.h"

/*
To be used as such:

receiver = UdpReceiver(8080); // or UdpReceiver("192.168.0.17", 8080) to specify interface
receiver.setOnReceive([](std::shared_ptr<Datagram> datagram) {
  std::cout << "Received message " << datagram->getMessage() << " from " << datagram.getIpAddress() << ":" << datagram.getPort() << std::endl;
});
receiver.start();

 */

namespace midnight {
	namespace ofxAsio {

		class UdpReceiver : public UdpSocket {
		public:
			static std::shared_ptr<UdpReceiver> make(int port);
			static std::shared_ptr<UdpReceiver> make(std::string localAddress, int port);
			~UdpReceiver();
			void start();
		protected:
			UdpReceiver(int port);
			UdpReceiver(std::string localAddress, int port);
		};

	}
}
