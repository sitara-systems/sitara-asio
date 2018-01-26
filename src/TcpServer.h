#pragma once

#include <thread>
#include "asio/asio.hpp"
#include "TcpSession.h"
#include "Datagram.h"

<<<<<<< HEAD
namespace midnight {
	namespace sockets {
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
			std::vector < std::shared_ptr<TcpSession>> mSessions;
		};
	}
=======
namespace ofxAsio {
  class TcpServer {
  public:
    static std::shared_ptr<TcpServer> make(int port);
    ~TcpServer();
    void start();
	void addOnSendFn(std::function<void(std::string msg)> response);
	void addOnReceiveFn(std::function<void(std::string msg)> response);
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
	  std::vector < std::shared_ptr<TcpSession>> mSessions;
	  std::vector<std::function<void(std::string msg)> > mOnSendFns;
	  std::vector<std::function<void(std::string msg)> > mOnReceiveFns;
  };
  
>>>>>>> 00371c6502e9a17e37b9c6febbe8352dabfb7372
}

