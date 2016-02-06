#include "asio.hpp"
#include "UdpSocket.h"

/*
To be used as such:

receiver = UdpReceiver(8080); // or UdpReceiver("192.168.0.17", 8080) to specify interface
receiver.setOnReceive([](std::shared_ptr<Datagram> datagram) {
  std::cout << "Received message " << datagram->getMessage() << " from " << datagram.getIpAddress() << ":" << datagram.getPort() << std::endl;
});
receiver.start();

 */

namespace ofxAsio {

  class UdpReceiver : public UdpSocket {
  public:
    UdpReceiver(int port);
    UdpReceiver(std::string localAddress, int port);
    ~UdpReceiver();
    void start();
  protected:
    UdpReceiver();
    virtual void on_receive(asio::error_code errorCode, std::size_t bytes_received);
  }
  
}

