#include "UdpSocket.h"

using namespace ofxAsio;

  UdpSocket::UdpSocket() {
    mSocket = mService;
    mSocket.open(asio::ip::udp::v4());
    mLocalEndpoint = Endpoint(asio::ip::udp::v4(), 0);
  }

  UdpSocket::UdpSocket(int port) {
    mLocalEndpoint = Endpoint(asio::ip::udp::v4(), port);
    mSocket(mService, mLocalEndpoint);
  }

  UdpSocket::UdpSocket(std::string localAddress, int port) {
    mLocalEndpoint = Endpoint(localAddress, port);
    mSocket(mService, mLocalEndpoint);
  }

  bool UdpSocket::send(std::shared_ptr<Datagram> datagram) {
    asio::error_code errorCode;
    std::string message = datagram->getMessage();
    Endpoint endpoint = datagram->getEndPoint();
   
    asio::buffer buffer = asio::buffer(message);
    
    mSocket.send_to(buffer, endPoint, 0, errorCode);
    
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
    int receivedSize = mSocket.receive_from(buffer, datagram->getEndPoint(), 0, errorCode);

    if (errorCode) {
      std::printf("ofxAsio::UdpSocket::receive -- Cannot recieve data. %s", errorCode.message());
      return shared_ptr<Datagram>();
    }
    else {
      message.resize(receivedSize);
      datagram->setMessage(message);
      return datagram;
    }
  }

  void setOnReceive(std::function<void(std::shared_ptr<Datagram> msg)> response) {
    mOnReceiveFunction = response;
  }

  void setOnSend(std::function<void(std::shared_ptr<Datagram> msg)> response) {
    mOnSendFunction = response;
  }

}
