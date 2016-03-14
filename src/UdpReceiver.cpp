#include "UdpReceiver.h"

using namespace ofxAsio;

UdpReceiver::UdpReceiver(int port) : UdpSocket(port) {
}

UdpReceiver::UdpReceiver(std::string localAddress, int port) : UdpSocket(localAddress, port) {

}

UdpReceiver::~UdpReceiver() {

}

void UdpReceiver::start() {
	std::printf("ofxAsio::UdpReceiver -- listening for messages at %s:%d\n", mLocalEndpoint.getIpAddress().c_str(), mLocalEndpoint.getPort());
	receive();
}