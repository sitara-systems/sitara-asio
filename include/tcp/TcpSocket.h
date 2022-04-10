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

#include <array>
#include <memory>
#include <string>
#include <thread>

#include "../Datagram.h"
#include "../Endpoint.h"
#include "asio/asio.hpp"

namespace sitara {
namespace tcp {
class TcpSocket {
   public:
    TcpSocket();
    TcpSocket(int port);
    TcpSocket(std::string localAddress, int port);
    ~TcpSocket();

   protected:
    void init();
    asio::io_service mService;
    std::thread mServiceThread;
    asio::io_service::work mWork;
    asio::ip::tcp::socket mSocket;
    asio::ip::tcp::endpoint mLocalEndpoint;
    std::shared_ptr<Datagram> mIncomingDatagram;
    asio::ip::tcp::endpoint mIncomingEndpoint;
    std::string mIncomingMessage;
};

}  // namespace tcp
}  // namespace sitara
