#include "TcpSocket.h"

<<<<<<< HEAD
using namespace midnight::sockets;
=======
using namespace ofxAsio;
>>>>>>> 00371c6502e9a17e37b9c6febbe8352dabfb7372

  TcpSocket::TcpSocket() : mSocket(mService, asio::ip::tcp::endpoint(asio::ip::address_v4::any(), 0)),
	  mWork(mService), mLocalEndpoint(asio::ip::tcp::endpoint(asio::ip::address_v4::any(), 0)) {
	  init();
  }

  TcpSocket::TcpSocket(int port) : mSocket(mService, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)), mWork(mService),
	  mLocalEndpoint(asio::ip::tcp::endpoint(asio::ip::address_v4::any(), port)) {
	  init();
  }

  TcpSocket::TcpSocket(std::string localAddress, int port) : mSocket(mService, asio::ip::tcp::endpoint(asio::ip::address::from_string(localAddress), port)), mWork(mService),
	  mLocalEndpoint(asio::ip::tcp::endpoint(asio::ip::address::from_string(localAddress), port)) {
	  init();
  }

  TcpSocket::~TcpSocket() {
	  mSocket.cancel();
	  mService.stop();
	  if (mServiceThread.joinable()) {
		  mServiceThread.join();
	  }
  }

  void TcpSocket::init() {
	  mIncomingDatagram = std::make_shared<Datagram>();
	  mIncomingEndpoint = asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 0);
	  mServiceThread = std::thread([&] {
		  mService.run();
	  });
  }