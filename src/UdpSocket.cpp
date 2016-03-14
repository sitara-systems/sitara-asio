#include "UdpSocket.h"

using namespace ofxAsio;

  UdpSocket::UdpSocket() : mSocket(mService), mWork(mService), mLocalEndpoint(asio::ip::udp::endpoint(asio::ip::address_v4::any(), 0)) {
	  init();
  }

  UdpSocket::UdpSocket(int port) : mSocket(mService, asio::ip::udp::endpoint(asio::ip::udp::v4(), port)), mWork(mService),
	  mLocalEndpoint(asio::ip::udp::endpoint(asio::ip::address_v4::any(), port)) {
	  init();
  }

  UdpSocket::UdpSocket(std::string localAddress, int port) : mSocket(mService, asio::ip::udp::endpoint(asio::ip::address::from_string(localAddress), port)), mWork(mService),
	  mLocalEndpoint(asio::ip::udp::endpoint(asio::ip::address::from_string(localAddress), port)) {
	  init();
  }

  UdpSocket::~UdpSocket() {
	  mSocket.cancel();
	  mService.stop();
	  if (mServiceThread.joinable()) {
		  mServiceThread.join();
	  }
  }

  void UdpSocket::init() {
	  mIncomingDatagram = std::make_shared<Datagram>();
	  setIncomingBufferSize(1024);
	  mServiceThread = std::thread([&] {
		  mService.run();
	  });
  }

  void UdpSocket::setIncomingBufferSize(std::size_t buffer_size) {
	  mIncomingDatagram->getMessage().resize(buffer_size);
  }

 void UdpSocket::send_datagram(std::shared_ptr<Datagram> datagram) {
	asio::mutable_buffers_1 buffer = asio::mutable_buffers_1((char*)datagram->getMessage().c_str(), datagram->getMessage().length());

	mSocket.async_send_to(buffer, datagram->getEndpoint().getAsioEndpoint(),
		[this, datagram](const asio::error_code& error, std::size_t bytes_transferred) {
		if (!error) {
			for (auto callback : mOnSendFns) {
				callback(datagram);
			}
		}
		else{ 
			std::printf("ofxAsio::UdpSocket::send -- Cannot send data. %s\n", error.message().c_str());;
		}
	});
  }
  
void UdpSocket::receive() {
	asio::mutable_buffers_1 buffer = asio::mutable_buffers_1((char*)mIncomingDatagram->getMessage().c_str(), mIncomingDatagram->getMessage().length());
	mSocket.async_receive_from(buffer, mIncomingDatagram->getEndpoint().getAsioEndpoint(),
		[this](const asio::error_code &error, size_t bytes_received) {
			onReceive(error, bytes_received);
	});
  }

void UdpSocket::onReceive(const asio::error_code &error, size_t bytes_received) {
	if (!error && bytes_received > 0) {
		onReceive(error, bytes_received);
		for (auto callback : mOnReceiveFns) {
			callback(mIncomingDatagram);
		}
	}
	else {
		std::printf("ofxAsio::UdpSocket::receive -- Error receiving data. %s\n", error.message().c_str());;
	}
	
	// queues up the next async receive after this receive has completed.
	receive();
}

void UdpSocket::addOnReceiveFn(std::function<void(std::shared_ptr<Datagram> msg)> response) {
	mOnReceiveFns.push_back(response);
}

void UdpSocket::addOnSendFn(std::function<void(std::shared_ptr<Datagram> msg)> response) {
	mOnSendFns.push_back(response);
}
