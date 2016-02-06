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
    std::string message = datagram->getMessage();
    Endpoint endpoint = datagram->getEndpoint();
   
    asio::buffer buffer(message, message.length());

	mSocket.send_to(buffer, endpoint.getAsioEndpoint(), 0, errorCode);
    
    if (errorCode) {
      std::printf("ofxAsio::UdpSocket::send -- Cannot send data. %s", errorCode.message());
      return false;
    }
    else {
      return true;
    }
  }
  
  std::shared_ptr<Datagram> UdpSocket::receive(size_t bufferSize) {
    asio::error_code errorCode;
    std::shared_ptr<Datagram> datagram = std::make_shared<Datagram>();
    std::string message = datagram->getMessage();
    message.resize(bufferSize);

    asio::buffer buffer = asio::buffer(dataGram->getMessage());
    int receivedSize = mSocket.receive_from(buffer, datagram->getEndpoint().getAsioEndpoint(), 0, errorCode);

    if (errorCode) {
      std::printf("ofxAsio::UdpSocket::receive -- Cannot recieve data. %s", errorCode.message());
      return std::shared_ptr<Datagram>();
    }
    else {
      message.resize(receivedSize);
      datagram->setMessage(message);
      return datagram;
    }
  }

  void setOnReceive(std::function<void(std::shared_ptr<Datagram> msg)> response) {
	  mOnReceiveFunction = response;
  };

  void setOnSend(std::function<void(std::shared_ptr<Datagram> msg)> response) {
	  mOnSendFunction = response;
  }