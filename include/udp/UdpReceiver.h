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

#pragma once

#include "UdpSocket.h"
#include "asio/asio.hpp"

/*
To be used as such:

receiver = UdpReceiver(8080); // or UdpReceiver("192.168.0.17", 8080) to specify interface
receiver.setOnReceive([](std::shared_ptr<Datagram> datagram) {
  std::cout << "Received message " << datagram->getMessage() << " from " << datagram.getIpAddress() << ":" <<
datagram.getPort() << std::endl;
});
receiver.start();

 */

namespace sitara {
namespace udp {

class UdpReceiver : public UdpSocket {
   public:
    static std::shared_ptr<UdpReceiver> make(int port);
    static std::shared_ptr<UdpReceiver> make(std::string localAddress, int port);
    ~UdpReceiver();
    void start();

   protected:
    UdpReceiver(int port);
    UdpReceiver(std::string localAddress, int port);
};

}  // namespace udp
}  // namespace sitara
