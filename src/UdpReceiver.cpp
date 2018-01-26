<<<<<<< HEAD
#include "UdpReceiver.h"

using namespace midnight::sockets;

=======
#include "UdpReceiver.h"

using namespace ofxAsio;

>>>>>>> 00371c6502e9a17e37b9c6febbe8352dabfb7372
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
	std::printf("midnight::sockets::UdpReceiver -- listening for messages at %s:%d\n", mLocalEndpoint.getIpAddress().c_str(), mLocalEndpoint.getPort());
	receive();
}