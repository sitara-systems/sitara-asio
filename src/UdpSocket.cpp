#include "UdpSocket.h"

using namespace ofxAsio;

  UdpSocket::UdpSocket() : mSocket(mService), mLocalEndpoint(asio::ip::udp::endpoint(asio::ip::address_v4::any(), 0)) {
  }

  UdpSocket::UdpSocket(int port) : mSocket(mService, asio::ip::udp::endpoint(asio::ip::udp::v4(), port)), 
									mLocalEndpoint(asio::ip::udp::endpoint(asio::ip::address_v4::any(), port)) {
  }

  UdpSocket::UdpSocket(std::string localAddress, int port) : mSocket(mService, asio::ip::udp::endpoint(asio::ip::address::from_string(localAddress), port)), 
																mLocalEndpoint(asio::ip::udp::endpoint(asio::ip::address::from_string(localAddress), port)) {
  }

  UdpSocket::~UdpSocket() {
  }

  bool UdpSocket::send(std::shared_ptr<Datagram> datagram) {
    asio::error_code errorCode;
	asio::mutable_buffers_1 buffer = asio::mutable_buffers_1((char*)datagram->getMessage().c_str(), datagram->getMessage().size());

	mSocket.send_to(buffer, datagram->getEndpoint().getAsioEndpoint(), 0, errorCode);
    
    if (errorCode) {
      std::printf("ofxAsio::UdpSocket::send -- Cannot send data. %s", errorCode.message().c_str());
      return false;
    }
    else {
      return true;
    }
  }
  
  std::shared_ptr<Datagram> UdpSocket::receive(size_t bufferSize) {
    asio::error_code errorCode;
    std::shared_ptr<Datagram> datagram = std::make_shared<Datagram>();
	datagram->getMessage().resize(bufferSize);

	asio::mutable_buffers_1 buffer = asio::mutable_buffers_1((char*)datagram->getMessage().c_str(), datagram->getMessage().size());
    int receivedSize = mSocket.receive_from(buffer, datagram->getEndpoint().getAsioEndpoint(), 0, errorCode);

    if (errorCode) {
      std::printf("ofxAsio::UdpSocket::receive -- Cannot recieve data. %s", errorCode.message().c_str());
      return std::shared_ptr<Datagram>();
    }
    else {
      datagram->getMessage().resize(receivedSize);
      return datagram;
    }
  }