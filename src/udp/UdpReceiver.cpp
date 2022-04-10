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

UdpReceiver::UdpReceiver(int port) : UdpSocket(port) {}

UdpReceiver::UdpReceiver(std::string localAddress, int port) : UdpSocket(localAddress, port) {}

UdpReceiver::~UdpReceiver() {}

void UdpReceiver::start() {
    std::cout << "sitara::sockets::UdpReceiver -- listening for messages at " << mLocalEndpoint.getIpAddress() << ":"
              << mLocalEndpoint.getPort() << std::endl;
    receive();
}