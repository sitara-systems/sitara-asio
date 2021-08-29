#include "udp/UdpSocket.h"
#include <iostream>

using namespace sitara;
using namespace sitara::udp;

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
	mMaxBufferSize = 4096;
	mIncomingDatagram = std::make_shared<Datagram>();
	mIncomingEndpoint = asio::ip::udp::endpoint(asio::ip::udp::v4(), 0);
	mServiceThread = std::thread([&] {
		mService.run();
		});
}

void UdpSocket::setIncomingBufferSize(std::size_t buffer_size) {
	mMaxBufferSize = buffer_size;
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
			else {
				std::cout << "sitara::sockets::UdpSocket::send -- Cannot send data : " << error.message() << std::endl;
			}
		});
}

void UdpSocket::receive() {
	mIncomingMessage.resize(mMaxBufferSize);

	mSocket.async_receive_from(asio::buffer(mIncomingMessage.data(), mIncomingMessage.size()), mIncomingEndpoint,
		[this](const asio::error_code& error, size_t bytes_received) {
			mIncomingDatagram->setEndpoint(mIncomingEndpoint);
			mIncomingMessage.resize(bytes_received);
			mIncomingDatagram->setData(mIncomingMessage);
			onReceive(error, bytes_received);
		});
}

void UdpSocket::onReceive(const asio::error_code& error, size_t bytes_received) {
	if (!error && bytes_received > 0) {
		for (auto callback : mOnReceiveFns) {
			callback(mIncomingDatagram);
		}
	}
	else {
		std::cout << "sitara::sockets::UdpSocket::receive -- Error receiving data : " << error.message() << std::endl;
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

Endpoint UdpSocket::getEndpoint() {
	return mLocalEndpoint;
}

std::string UdpSocket::getIpAddress() {
	return mLocalEndpoint.getIpAddress();
}

int UdpSocket::getPortNumber() {
	return mLocalEndpoint.getPort();
}
