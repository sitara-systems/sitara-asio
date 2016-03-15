#include "UdpSender.h"

using namespace ofxAsio;

UdpSender::UdpSender() : UdpSocket() {

}

UdpSender::UdpSender(int port) : UdpSocket(port) {

}

UdpSender::UdpSender(std::string localAddress, int port) : UdpSocket(localAddress, port) {

}

UdpSender::~UdpSender() {

}

void UdpSender::send(std::shared_ptr<Datagram> datagram) {
	send_datagram(datagram);
}

void UdpSender::send_to(std::string ip_address, int port, std::string message) {
	std::shared_ptr<Datagram> outgoingDatagram = std::make_shared<Datagram>();
	outgoingDatagram->setEndpoint(ip_address, port);
	outgoingDatagram->setData(message);
	send(outgoingDatagram);
}

void UdpSender::send_to(std::string ip_address, int port, std::vector<unsigned char> data) {
	std::shared_ptr<Datagram> outgoingDatagram = std::make_shared<Datagram>();
	outgoingDatagram->setEndpoint(ip_address, port);
	outgoingDatagram->setData(data);
	send(outgoingDatagram);
}