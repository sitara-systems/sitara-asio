// Copyright (c) 2022 Nathan S Lachenmyer
//
// MIT License
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "udp/UdpSender.h"

using namespace sitara;
using namespace sitara::udp;

std::shared_ptr<UdpSender> UdpSender::make() {
	std::shared_ptr<UdpSender> sender(new UdpSender());
	return sender;
}

std::shared_ptr<UdpSender> UdpSender::make(int port) {
	std::shared_ptr<UdpSender> sender(new UdpSender(port));
	return sender;
}

std::shared_ptr<UdpSender> UdpSender::make(std::string localAddress, int port) {
	std::shared_ptr<UdpSender> sender(new UdpSender(localAddress, port));
	return sender;
}

UdpSender::UdpSender() : UdpSocket() {

}

UdpSender::UdpSender(int port) : UdpSocket(port) {

}

UdpSender::UdpSender(std::string localAddress, int port) : UdpSocket(localAddress, port) {

}

UdpSender::~UdpSender() {

}

void UdpSender::send(std::shared_ptr<Datagram> datagram) {
	sendDatagram(datagram);
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
