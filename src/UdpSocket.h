#pragma once

#include "asio.hpp"
#include "Endpoint.h"
#include "Datagram.h"
#include <memory>
#include <array>
#include <string>


namespace ofxAsio {

    class UdpSocket {
  public:
    UdpSocket();
    UdpSocket(int port);
    UdpSocket(std::string localAddress, int port);
    ~UdpSocket();
    bool send(std::shared_ptr<Datagram> msg);
    std::shared_ptr<Datagram> receive(size_t bufferSize = 9216);
    void setOnReceive(std::function<void(std::shared_ptr<Datagram> msg)> response);
    void setOnSend(std::function<void(std::shared_ptr<Datagram> msg)> response);
  protected:
    //TO DO
    virtual void on_receive(asio::error_code &ec, size_t bytes_received) {};
    virtual void on_send(asio::error_code &ec, size_t bytes_transferred) {};
    asio::io_service mService;
    asio::ip::udp::socket mSocket;
    Endpoint mLocalEndpoint;
    std::function<void(Datagram msg)> mOnReceiveFunction;
    std::function<void(Datagram msg)> mOnSendFunction;
  };
  
}


