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

#include <chrono>
#include <thread>

#include "../Datagram.h"
#include "asio/asio.hpp"
#include "asio/system_timer.hpp"

namespace sitara {
namespace tcp {
class TcpClient {
   public:
    ~TcpClient();
    static std::shared_ptr<TcpClient> make();
    void connect(std::string ip_address, int port);
    void disconnect();
    void send(const std::string& message);
    //		void addOnSendFn(std::function<void(std::shared_ptr<Datagram> msg)> response);
    //		void addOnResponseFn(std::function<void(std::shared_ptr<Datagram> msg)> response);
   protected:
    TcpClient();
    void init();
    void start_connect(asio::ip::tcp::resolver::iterator resolver);
    void handle_connect(const asio::error_code& ec, asio::ip::tcp::resolver::iterator endpoint_iter);
    void start_read();
    void handle_read(const asio::error_code& ec, size_t bytes_received);
    void start_write();
    void handle_write(const asio::error_code& e, size_t bytes_receivedc);
    void check_deadline(const asio::error_code& error);
    //		void onReceive(const asio::error_code& error, size_t bytes_received);
    //		void onResponse(const asio::error_code& error);
    bool mIsConnected;
    asio::streambuf input_buffer_;
    asio::io_service mService;
    asio::io_service::work mWork;
    std::thread mServiceThread;
    asio::ip::tcp::socket mSocket;
    std::shared_ptr<asio::ip::tcp::resolver> mResolver;
    asio::system_timer mTimer;
    asio::system_timer mHeartbeatTimer;
    std::shared_ptr<Datagram> mIncomingDatagram;
    std::string mIncomingMessage;
    std::vector<std::function<void(std::shared_ptr<Datagram> msg)> > mOnSendFns;
    std::vector<std::function<void(std::shared_ptr<Datagram> msg)> > mOnResponseFns;
};

}  // namespace tcp
}  // namespace sitara
