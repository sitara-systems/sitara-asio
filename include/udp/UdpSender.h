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

sender = UdpSender(8080); //local port
std::shared_ptr<Datagram> datagram(new Datagram("Hello world", "192.168.0.27", 8080));
sender.send(datagram)

 */
namespace sitara {
namespace udp {

class UdpSender : public UdpSocket {
   public:
    static std::shared_ptr<UdpSender> make();
    static std::shared_ptr<UdpSender> make(int port);
    static std::shared_ptr<UdpSender> make(std::string localAddress, int port);
    ~UdpSender();
    void send(std::shared_ptr<Datagram> datagram);
    void send_to(std::string ip_address, int port, std::string message);
    void send_to(std::string ip_address, int port, std::vector<unsigned char> data);

   protected:
    UdpSender();
    UdpSender(int port);
    UdpSender(std::string localAddress, int port);
    void on_send(asio::error_code errorCode, std::size_t bytes_transferred){};
};

}  // namespace udp
}  // namespace sitara
