#include "udp/UdpReceiver.h"
#include <iostream>

using namespace sitara;
using namespace sitara::udp;

std::shared_ptr<UdpReceiver> UdpReceiver::make(int port) {
	std::shared_ptr<UdpReceiver> receiver(new UdpReceiver(port));
	return receiver;
}

std::shared_ptr<UdpReceiver> UdpReceiver::make(std::string localAddress, int port) {
	std::shared_ptr<UdpReceiver> receiver(new UdpReceiver(localAddress, port));
	return receiver;
}

UdpReceiver::UdpReceiver(int port) : UdpSocket(port) {
}

UdpReceiver::UdpReceiver(std::string localAddress, int port) : UdpSocket(localAddress, port) {

}

UdpReceiver::~UdpReceiver() {

}

void UdpReceiver::start() {
	std::cout << "sitara::sockets::UdpReceiver -- listening for messages at " << mLocalEndpoint.getIpAddress() << ":" << mLocalEndpoint.getPort() << std::endl;
	receive();
}
