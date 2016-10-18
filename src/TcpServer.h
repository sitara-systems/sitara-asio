#pragma once

#include <thread>
#include "asio/asio.hpp"
#include "Session.h"

namespace ofxAsio {
  class TcpServer {
  public:
    static std::shared_ptr<TcpServer> make(int port);
    static std::shared_ptr<TcpServer> make(std::string localAddress, int port);
    ~TcpServer();
    void start();
  protected:
	  TcpServer(int port);
	  TcpServer(std::string localAddress, int port);
	  void init(std::string localAddress, int port);
	  void createSession();
	  void onConnect(std::shared_ptr<Session> session, const asio::error_code& error);
	  asio::io_service mService;
	  std::thread mServiceThread;
	  asio::ip::tcp::socket mSocket;
	  asio::ip::tcp::endpoint mLocalEndpoint;
	  std::shared_ptr<asio::ip::tcp::acceptor> mAcceptor;
  };
  
}

