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

#include "tcp/TcpSession.h"

using namespace sitara;
using namespace sitara::tcp;

std::shared_ptr<TcpSession> TcpSession::make(asio::io_service& service) {
    std::shared_ptr<TcpSession> session = std::shared_ptr<TcpSession>(new TcpSession(service));
    return session;
}

TcpSession::TcpSession(asio::io_service& service) : mSocket(service) {
    mTerminator = '\0';
    mIsConnected = false;
    setIncomingBufferSize(1024);
}

TcpSession::~TcpSession() {
    std::printf("sitara::sockets::TcpSession -- TcpSession ended.\n");
}

void TcpSession::start() {
    std::printf("sitara::sockets::TcpSession -- TcpSession starting.\n");
    mIsConnected = true;
    receive();
}

asio::ip::tcp::socket& TcpSession::getSocket() {
    return mSocket;
}

char TcpSession::getTerminator() {
    return mTerminator;
}

void TcpSession::setTerminator(char terminator) {
    mTerminator = terminator;
}

void TcpSession::onWrite(const asio::error_code& error, std::size_t bytesReceived) {
    if (!error && mIsConnected) {
        receive();
    } else {
        std::printf("sitara::sockets::TcpSession::onWrite -- Error writing data. %s\n", error.message().c_str());
        ;
    }
}

void TcpSession::onReceive(const asio::error_code& error, std::size_t bytesReceived) {
    if (bytesReceived) {
        std::printf("sitara::sockets::TcpSession::onReceive -- received message %s in %d bytes\n",
                    mIncomingMessage.c_str(), bytesReceived);
        if (mIncomingMessage[bytesReceived - 1] == mTerminator) {
            std::printf("sitara::sockets::TcpSession::onReceive -- received terminator charactder %s\n", mTerminator);
            --bytesReceived;
            setIncomingBufferSize(bytesReceived);
            mIsConnected = false;
        }
    }

    if (!error && mIsConnected) {
        asio::async_write(
            mSocket, asio::buffer(mIncomingMessage.c_str(), mIncomingMessage.size()),
            [this](const asio::error_code& error, std::size_t bytes_received) { onWrite(error, bytes_received); });
    } else {
        std::printf("sitara::sockets::TcpSession::onReceive -- Error receiving data. %s\n", error.message().c_str());
        ;
    }
}

void TcpSession::receive() {
    asio::mutable_buffers_1 buffer = asio::mutable_buffers_1((char*)mIncomingMessage.c_str(), mIncomingMessage.size());

    mSocket.async_read_some(buffer, [this](const asio::error_code& error, std::size_t bytesReceived) {
        if (bytesReceived) {
            setIncomingBufferSize(bytesReceived);
        }
        onReceive(error, bytesReceived);
    });
}

void TcpSession::setIncomingBufferSize(std::size_t buffer_size) {
    mIncomingMessage.resize(buffer_size);
}
