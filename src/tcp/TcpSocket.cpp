#include "TcpSocket.h"

using namespace ofxAsio;
using namespace ofxAsio::tcp;

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
