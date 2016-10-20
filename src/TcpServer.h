#pragma once

#include <thread>
#include "asio/asio.hpp"
#include "TcpSession.h"
#include "Datagram.h"

namespace ofxAsio {
  class TcpServer {
  public:
    static std::shared_ptr<TcpServer> make(int port);
    ~TcpServer();
    void start();
  protected:
	  TcpServer(int port);
	  void init(int port);
	  void createSession();
	  void onConnect(std::vector<std::shared_ptr<TcpSession>>::iterator session_iter, const asio::error_code& error);
	  asio::io_service mService;
      asio::io_service::work mWork;
	  std::thread mServiceThread;
	  asio::ip::tcp::acceptor mAcceptor;
	  asio::ip::tcp::socket mSocket;
	  asio::ip::tcp::endpoint mLocalEndpoint;
	  std::string mIncomingMessage;
	  std::vector < std::shared_ptr<TcpSession>> mSessions;
  };
  
}

