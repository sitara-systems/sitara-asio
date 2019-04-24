#include "UdpSocket.h"

using namespace ofxAsio;
using namespace ofxAsio::udp;

  UdpSocket::UdpSocket() : mSocket(mService, asio::ip::udp::endpoint(asio::ip::address_v4::any(), 0)),
	  mWork(mService), mLocalEndpoint(asio::ip::udp::endpoint(asio::ip::address_v4::any(), 0)) {
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
	  mIncomingEndpoint = asio::ip::udp::endpoint(asio::ip::udp::v4(), 0);
	  setIncomingBufferSize(4096);
	  mServiceThread = std::thread([&] {
		  mService.run();
	  });
  }

  void UdpSocket::setIncomingBufferSize(std::size_t buffer_size) {
	  mIncomingMessage.resize(buffer_size);
  }

 void UdpSocket::sendDatagram(std::shared_ptr<Datagram> datagram) {
	 std::shared_ptr<Datagram> outgoingDatagram = std::make_shared<Datagram>(datagram->getEndpoint());
	 outgoingDatagram->setData(datagram->getDataAsString());

	 mSocket.async_send_to(asio::buffer(outgoingDatagram->getData(), outgoingDatagram->getDataLength()), outgoingDatagram->getEndpoint().getAsioEndpoint(),
		[this, datagram](const asio::error_code& error, std::size_t bytes_transferred) {
		if (!error) {
			for (auto callback : mOnSendFns) {
				callback(datagram);
			}
		}
		else{
			std::printf("asio::UdpSocket::send -- Cannot send data. %s\n", error.message().c_str());;
		}
	});
  }

void UdpSocket::receive() {
	asio::mutable_buffers_1 buffer = asio::mutable_buffers_1((char*)mIncomingMessage.c_str(), mIncomingMessage.size());

	mSocket.async_receive_from(buffer, mIncomingEndpoint,
		[this](const asio::error_code &error, size_t bytes_received) {
			mIncomingDatagram->setEndpoint(mIncomingEndpoint);
			setIncomingBufferSize(bytes_received);
			mIncomingDatagram->setData(mIncomingMessage);
			onReceive(error, bytes_received);
	});
  }

void UdpSocket::onReceive(const asio::error_code &error, size_t bytes_received) {
	if (!error && bytes_received > 0) {
		for (auto callback : mOnReceiveFns) {
			callback(mIncomingDatagram);
		}
	}
	else {
		std::printf("ofxAsio::sockets::UdpSocket::receive -- Error receiving data. %s\n", error.message().c_str());;
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
